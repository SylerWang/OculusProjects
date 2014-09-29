// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "VideoStreamManager.h"
using namespace gte;

//----------------------------------------------------------------------------
VideoStreamManager::~VideoStreamManager()
{
    StopTriggeredCapture();
}
//----------------------------------------------------------------------------
VideoStreamManager::VideoStreamManager(
    std::vector<VideoStream*> const& videoStreams, size_t maxQueueElements)
    :
    mVideoStreams(videoStreams),
    mFrameQueue(maxQueueElements),
    mCurrentFrame(0),
    mTrigger(nullptr),
    mPerformanceFrames(0),
    mPerformanceTicks(0),
    mAccumulatedVSMTicks(0),
    mAccumulatedVSTicks(videoStreams.size())
{
    ResetPerformanceMeasurements();
}
//----------------------------------------------------------------------------
std::vector<VideoStream*> const& VideoStreamManager::GetVideoStreams() const
{
    return mVideoStreams;
}
//----------------------------------------------------------------------------
bool VideoStreamManager::GetFrame(Frame& frame) const
{
    return mFrameQueue.Pop(frame);
}
//----------------------------------------------------------------------------
void VideoStreamManager::CaptureFrameSerial()
{
    int64_t startTicks = mProductionTimer.GetTicks();

    // Capture a frame for each video stream.
    size_t const numVideoStreams = mVideoStreams.size();
    for (size_t i = 0; i < numVideoStreams; ++i)
    {
        mVideoStreams[i]->CaptureFrame();
    }

    AssembleFullFrame(startTicks);
}
//----------------------------------------------------------------------------
void VideoStreamManager::CaptureFrameParallel()
{
    int64_t startTicks = mProductionTimer.GetTicks();

    // Launch capture threads for all video streams.
    size_t const numVideoStreams = mVideoStreams.size();
    std::vector<std::thread> captureThread(numVideoStreams);
    for (size_t i = 0; i < numVideoStreams; ++i)
    {
        captureThread[i] = std::thread
        (
            [this, i]()
            {
                mVideoStreams[i]->CaptureFrame();
            }
        );
    }

    // Wait for all video streams to capture their images.
    for (size_t i = 0; i < numVideoStreams; ++i)
    {
        captureThread[i].join();
    }

    AssembleFullFrame(startTicks);
}
//----------------------------------------------------------------------------
void VideoStreamManager::StartTriggeredCapture(double fps, bool parallel)
{
    if (nullptr == mTrigger && fps > 0.0)
    {
        void (VideoStreamManager::*Capture)(void);
        if (parallel)
        {
            Capture = &VideoStreamManager::CaptureFrameParallel;
        }
        else
        {
            Capture = &VideoStreamManager::CaptureFrameSerial;
        }

        mTrigger = new Trigger();
        mTrigger->ticksPerFrame = mTrigger->timer.GetTicks(1.0/fps);
        mTrigger->running = true;

        mTrigger->triggerThread = new std::thread
        (
            [this, Capture]()
            {
                int64_t startTime = mTrigger->timer.GetTicks();

                // The variable 'running' is set to 'false' in the function
                // StopTriggeredCapture().  Access here to 'running' is not
                // protected by a lock in order to help with performance.  The
                // worst case is that the trigger fires several times after
                // 'running' is set to 'false' (on program termination) but
                // before the read here notices the change.
                while (mTrigger->running)
                {
                    // Spin in the thread for an accurate 'sleep' time.  I am
                    // using the GTEngine Timer class because
                    //   std::chrono::high_resolution_clock
                    // and
                    //   std::this_thread::sleep_for
                    // are not accurate enough.  The high_resolution_clock
                    // problem is a known issue and is not yet fixed.  For
                    // details, see this post:
                    // http://connect.microsoft.com/VisualStudio/feedback/details/719443/c-chrono-headers-high-resolution-clock-does-not-have-high-resolution

                    int64_t finalTime = startTime + mTrigger->ticksPerFrame;
                    do
                    {
                        startTime = mTrigger->timer.GetTicks();
                    }
                    while (startTime < finalTime);

                    (this->*Capture)();
                }
            }
        );
    }
}
//----------------------------------------------------------------------------
void VideoStreamManager::StopTriggeredCapture()
{
    if (mTrigger && mTrigger->triggerThread)
    {
        mTrigger->running = false;
        mTrigger->triggerThread->join();
        delete mTrigger->triggerThread;
        mTrigger->triggerThread = nullptr;
        delete mTrigger;
        mTrigger = nullptr;
    }
}
//----------------------------------------------------------------------------
void VideoStreamManager::ResetPerformanceMeasurements()
{
    for (auto vs : mVideoStreams)
    {
        vs->ResetPerformanceMeasurements();
    }

    mPerformanceFrames = 0;
    mPerformanceTicks = 0;
    mPerformanceTimer.Reset();

    mAccumulatedVSMTicks = 0;
    for (auto& ticks : mAccumulatedVSTicks)
    {
        ticks = 0;
    }
}
//----------------------------------------------------------------------------
unsigned int VideoStreamManager::GetPerformanceFrames() const
{
    return mPerformanceFrames;
}
//----------------------------------------------------------------------------
int64_t VideoStreamManager::GetPerformanceTicks() const
{
    return mPerformanceTicks;
}
//----------------------------------------------------------------------------
double VideoStreamManager::GetFramesPerSecond() const
{
    if (mPerformanceTicks > 0)
    {
        double seconds = mPerformanceTimer.GetSeconds(mPerformanceTicks);
        return static_cast<double>(mPerformanceFrames)/seconds;
    }
    return 0.0;
}
//----------------------------------------------------------------------------
double VideoStreamManager::GetSecondsPerFrame() const
{
    if (mPerformanceFrames > 0)
    {
        double seconds = mPerformanceTimer.GetSeconds(mPerformanceTicks);
        return seconds/static_cast<double>(mPerformanceFrames);
    }
    return 0.0;
}
//----------------------------------------------------------------------------
void VideoStreamManager::GetStatistics(double& averageTime,
    double& averageVSMTime, std::vector<double>& averageVSTime)
{
    averageVSTime.resize(mVideoStreams.size());

    if (mPerformanceTicks > 0)
    {
        double invNumFrames = 1.0/static_cast<double>(mPerformanceFrames);

        double msecs = 1000.0*mPerformanceTimer.GetSeconds(mPerformanceTicks);
        averageTime = msecs*invNumFrames;

        msecs = 1000.0*mPerformanceTimer.GetSeconds(mAccumulatedVSMTicks);
        averageVSMTime = msecs*invNumFrames;

        for (size_t i = 0; i < mVideoStreams.size(); ++i)
        {
             msecs = 1000.0*mPerformanceTimer.GetSeconds(
                 mAccumulatedVSTicks[i]);
             averageVSTime[i] = msecs*invNumFrames;
        }
    }
    else
    {
        averageTime = 0.0;
        averageVSMTime = 0.0;
        for (size_t i = 0; i < mVideoStreams.size(); ++i)
        {
             averageVSTime[i] = 0.0;
        }
    }
}
//----------------------------------------------------------------------------
void VideoStreamManager::AssembleFullFrame(int64_t startTicks)
{
    size_t const numVideoStreams = mVideoStreams.size();
    Frame full(numVideoStreams);
    for (size_t i = 0; i < numVideoStreams; ++i)
    {
        full.frames[i] = mVideoStreams[i]->GetFrame();
    }

    int64_t finalTicks = mProductionTimer.GetTicks();
    full.number = mCurrentFrame++;
    full.ticks = finalTicks - startTicks;
    mFrameQueue.Push(full);

    mPerformanceTicks = mPerformanceTimer.GetTicks();
    ++mPerformanceFrames;

    mAccumulatedVSMTicks += full.ticks;
    for (size_t i = 0; i < numVideoStreams; ++i)
    {
        mAccumulatedVSTicks[i] += full.frames[i].ticks;
    }
}
//----------------------------------------------------------------------------
