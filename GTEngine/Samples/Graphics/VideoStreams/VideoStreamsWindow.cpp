// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "VideoStreamsWindow.h"

//----------------------------------------------------------------------------
VideoStreamsWindow::~VideoStreamsWindow ()
{
#if defined(DO_TRIGGERED_SERIAL) || defined(DO_TRIGGERED_PARALLEL)
    mVideoStreamManager->StopTriggeredCapture();
#endif
    delete mVideoStreamManager;

    for (int i = 0; i < NUM_VIDEO_STREAMS; ++i)
    {
        delete mVideoStreams[i];
    }
}
//----------------------------------------------------------------------------
VideoStreamsWindow::VideoStreamsWindow (Parameters& parameters)
    :
    Window(parameters),
    mTextColor(1.0f, 1.0f, 1.0f, 1.0f),
    mClearColor(1.0f, 1.0f, 1.0f, 1.0f),
    mVideoStreams(NUM_VIDEO_STREAMS),
    mOverlay(NUM_VIDEO_STREAMS),
    mVideoStreamManager(nullptr),
    mCurrent(NUM_VIDEO_STREAMS)
{
    // Locate the context for the application regardless of where the
    // executable is launched.
    Environment env;
    std::string path = env.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        parameters.created = false;
        return;
    }
    std::string prefix = env.GetVariable("GTE_PATH");
    prefix += "/Samples/Graphics/VideoStreams/Data/VideoStream";

    // Generate dummy video files.  This avoids having to post large data
    // files for the sample.
    int const numImages = 16, txWidth = 640, txHeight = 512;
    int const format = static_cast<int>(DF_R8G8B8A8_UNORM);
    unsigned int colorMask[NUM_VIDEO_STREAMS] =
    {
        0xFF0000FF,
        0xFF00FF00,
        0xFFFF0000,
        0xFFFFFFFF
    };
    std::vector<unsigned int> texels(txWidth*txHeight);
    std::mt19937 mte;
    std::uniform_int_distribution<unsigned int> rnd(0, 127);
    for (int i = 0; i < NUM_VIDEO_STREAMS; ++i)
    {
        std::string name = prefix + std::to_string(i) + ".raw";
        std::ofstream output(name, std::ios::out | std::ios::binary);
        if (!output)
        {
            parameters.created = false;
            return;
        }
        output.write((char const*)&numImages, sizeof(numImages));
        output.write((char const*)&format, sizeof(format));
        output.write((char const*)&txWidth, sizeof(txWidth));
        output.write((char const*)&txHeight, sizeof(txHeight));
        unsigned int mask = colorMask[i];
        for (int j = 0; j < numImages; ++j)
        {
            // Randomly generate an RGBA image.
            for (auto& texel : texels)
            {
                unsigned int r = 128 + rnd(mte);
                unsigned int g = 128 + rnd(mte);
                unsigned int b = 128 + rnd(mte);
                texel = mask & (r | (g << 8) | (b << 16) | 0xFF000000);
            }

            // Use index j as the frame number.
            output.write((char const*)&j, sizeof(j));
            output.write((char const*)&texels[0], 4 * texels.size());
        }
        output.close();
    }

    if (!CreateOverlays(txWidth, txHeight))
    {
        parameters.created = false;
        return;
    }

    mEngine->SetClearColor(mClearColor);

    for (int i = 0; i < NUM_VIDEO_STREAMS; ++i)
    {
        std::string name = prefix + std::to_string(i) + ".raw";
        mVideoStreams[i] = new FileVideoStream(name, mEngine);
    }
    mVideoStreamManager = new VideoStreamManager(mVideoStreams, 30);

#ifdef DO_TRIGGERED_SERIAL
    mVideoStreamManager->StartTriggeredCapture(30.0, false);
#endif

#ifdef DO_TRIGGERED_PARALLEL
    mVideoStreamManager->StartTriggeredCapture(30.0, true);
#endif
}
//----------------------------------------------------------------------------
void VideoStreamsWindow::OnIdle ()
{
#ifdef DO_MANUAL_SERIAL
    mVideoStreamManager->CaptureFrameSerial();
    if (mVideoStreamManager->GetFrame(mCurrent))
    {
        for (int i = 0; i < 4; ++i)
        {
            mOverlay[i]->SetTexture(mCurrent.frames[i].image);
            mEngine->Draw(mOverlay[i]);
        }
        DrawStatistics();
        mEngine->DisplayColorBuffer(0);
    }
#endif

#ifdef DO_MANUAL_PARALLEL
    mVideoStreamManager->CaptureFrameParallel();
    if (mVideoStreamManager->GetFrame(mCurrent))
    {
        for (int i = 0; i < 4; ++i)
        {
            mOverlay[i]->SetTexture(mCurrent.frames[i].image);
            mEngine->Draw(mOverlay[i]);
        }
        DrawStatistics();
        mEngine->DisplayColorBuffer(0);
    }
#endif

#if defined(DO_TRIGGERED_SERIAL) || defined(DO_TRIGGERED_PARALLEL)
    if (mVideoStreamManager->GetFrame(mCurrent))
    {
        for (int i = 0; i < 4; ++i)
        {
            mOverlay[i]->SetTexture(mCurrent.frames[i].image);
            mEngine->Draw(mOverlay[i]);
        }
        DrawStatistics();
        mEngine->DisplayColorBuffer(0);
    }
#endif
}
//----------------------------------------------------------------------------
bool VideoStreamsWindow::OnCharPress (unsigned char key, int x, int y)
{
    switch (key)
    {
    case ' ':
        ResetTime();
        mVideoStreamManager->ResetPerformanceMeasurements();
        return true;
    }

    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool VideoStreamsWindow::CreateOverlays (int textureWidth, int textureHeight)
{
    // Use nearest filtering and clamped texture coordinates.
    SamplerState::Filter filter = SamplerState::MIN_P_MAG_P_MIP_P;
    SamplerState::Mode mode = SamplerState::CLAMP;
    mOverlay[0].reset(new OverlayEffect(mXSize, mYSize, textureWidth,
        textureHeight, filter, mode, mode, true));
    std::array<int,4> rect0 = { 0, 0, mXSize/2, mYSize/2 };
    mOverlay[0]->SetOverlayRectangle(rect0);

    mOverlay[1].reset(new OverlayEffect(mXSize, mYSize, textureWidth,
        textureHeight, filter, mode, mode, true));
    std::array<int,4> rect1 = { mXSize/2, 0, mXSize/2, mYSize/2 };
    mOverlay[1]->SetOverlayRectangle(rect1);

    mOverlay[2].reset(new OverlayEffect(mXSize, mYSize, textureWidth,
        textureHeight, filter, mode, mode, true));
    std::array<int,4> rect2 = { 0, mYSize/2, mXSize/2, mYSize/2 };
    mOverlay[2]->SetOverlayRectangle(rect2);

    mOverlay[3].reset(new OverlayEffect(mXSize, mYSize, textureWidth,
        textureHeight, filter, mode, mode, true));
    std::array<int,4> rect3 = { mXSize/2, mYSize/2, mXSize/2, mYSize/2 };
    mOverlay[3]->SetOverlayRectangle(rect3);

    // Create a black texture for the initial drawing of the window.
    std::shared_ptr<Texture2> texture(new Texture2(DF_R16_UNORM, textureWidth,
        textureHeight));
    texture->SetName("black texture");
    memset(texture->GetData(), 0, texture->GetNumBytes());
    mEngine->Bind(texture);
    mOverlay[0]->SetTexture(texture);
    mOverlay[1]->SetTexture(texture);
    mOverlay[2]->SetTexture(texture);
    mOverlay[3]->SetTexture(texture);
    return true;
}
//----------------------------------------------------------------------------
void VideoStreamsWindow::DrawStatistics ()
{
    double averageTime, averageVSMTime;
    std::vector<double> averageVSTime(NUM_VIDEO_STREAMS);
    mVideoStreamManager->GetStatistics(averageTime, averageVSMTime,
        averageVSTime);

    std::string message = Environment::CreateString("frame: %u",
        mCurrent.number);
    mEngine->Draw(8, mYSize - 56, mTextColor, message);

    message = Environment::CreateString("vsm average frame msec: %.1lf",
        averageTime);
    mEngine->Draw(8, mYSize - 40, mTextColor, message);

    message = Environment::CreateString("vsm average capture msec: %.1lf",
        averageVSMTime);
    mEngine->Draw(8, mYSize - 24, mTextColor, message);

    message = Environment::CreateString("vs average capture msec: ");
    for (int i = 0; i < NUM_VIDEO_STREAMS; ++i)
    {
        message += Environment::CreateString(", vs%d = %.1lf ", i,
            averageVSTime[i]);
    }
    mEngine->Draw(8, mYSize - 8, mTextColor, message);
}
//----------------------------------------------------------------------------
