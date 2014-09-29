// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "VideoStream.h"
using namespace gte;

//----------------------------------------------------------------------------
VideoStream::~VideoStream()
{
}
//----------------------------------------------------------------------------
VideoStream::VideoStream(DX11Engine* engine)
    :
    mEngine(engine),
    mType(DF_UNKNOWN),
    mWidth(0),
    mHeight(0),
    mPerformanceFrames(0),
    mPerformanceTicks(0)
{
}
//----------------------------------------------------------------------------
DX11Engine* VideoStream::GetEngine() const
{
    return mEngine;
}
//----------------------------------------------------------------------------
DFType VideoStream::GetType() const
{
    return mType;
}
//----------------------------------------------------------------------------
unsigned int VideoStream::GetWidth() const
{
    return mWidth;
}
//----------------------------------------------------------------------------
unsigned int VideoStream::GetHeight() const
{
    return mHeight;
}
//----------------------------------------------------------------------------
VideoStream::Frame VideoStream::GetFrame() const
{
    return mFrame;
}
//----------------------------------------------------------------------------
void VideoStream::CaptureFrame()
{
    int64_t startTicks = mProductionTimer.GetTicks();

    char* data = GetImage();
    if (data)
    {
        // The texture is created without system memory.  The derived class
        // provides this data, so the texture is given temporary access to
        // it in order for the Bind(...) call to copy the data to the GPU.
        mFrame.image.reset(
            new Texture2(mType, mWidth, mHeight, false, false));
        mFrame.image->SetData(data);
        mEngine->Bind(mFrame.image);
        mFrame.image->SetData(nullptr);
    }
    // else: GetImage has signaled that there is no image available.

    int64_t finalTicks = mProductionTimer.GetTicks();
    mFrame.ticks = finalTicks - startTicks;

    mPerformanceTicks = mPerformanceTimer.GetTicks();
    ++mPerformanceFrames;
}
//----------------------------------------------------------------------------
void VideoStream::ResetPerformanceMeasurements()
{
    mPerformanceFrames = 0;
    mPerformanceTicks = 0;
    mPerformanceTimer.Reset();
}
//----------------------------------------------------------------------------
unsigned int VideoStream::GetPerformanceFrames() const
{
    return mPerformanceFrames;
}
//----------------------------------------------------------------------------
int64_t VideoStream::GetPerformanceTicks() const
{
    return mPerformanceTicks;
}
//----------------------------------------------------------------------------
double VideoStream::GetFramesPerSecond() const
{
    if (mPerformanceTicks > 0)
    {
        double seconds = mPerformanceTimer.GetSeconds(mPerformanceTicks);
        return static_cast<double>(mPerformanceFrames)/seconds;
    }
    return 0.0;
}
//----------------------------------------------------------------------------
double VideoStream::GetSecondsPerFrame() const
{
    if (mPerformanceFrames > 0)
    {
        double seconds = mPerformanceTimer.GetSeconds(mPerformanceTicks);
        return seconds/static_cast<double>(mPerformanceFrames);
    }
    return 0.0;
}
//----------------------------------------------------------------------------
