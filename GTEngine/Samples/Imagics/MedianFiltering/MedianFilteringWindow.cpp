// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "MedianFilteringWindow.h"

//----------------------------------------------------------------------------
MedianFilteringWindow::~MedianFilteringWindow()
{
}
//----------------------------------------------------------------------------
MedianFilteringWindow::MedianFilteringWindow (Parameters& parameters)
    :
    Window(parameters),
    mTextColor(1.0f, 1.0f, 0.0f, 1.0f),
    mSelection(0)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    unsigned int const txWidth = 1024, txHeight = 1024;
    mOriginal.reset(new Texture2(DF_R32_FLOAT, txWidth, txHeight));
    for (int i = 0; i < 2; ++i)
    {
        mImage[i].reset(new Texture2(DF_R32_FLOAT, txWidth, txHeight));
        mImage[i]->SetUsage(Resource::SHADER_OUTPUT);
        mImage[i]->SetCopyType(Resource::COPY_BIDIRECTIONAL);
    }

    std::mt19937 mte;
    std::uniform_real_distribution<float> rnd(0.0625f, 1.0f);
    float* data = mOriginal->Get<float>();
    for (unsigned int i = 0; i < txWidth*txHeight; ++i)
    {
        data[i] = rnd(mte);
    }
    memcpy(mImage[0]->GetData(), data, mImage[0]->GetNumBytes());
    memcpy(mImage[1]->GetData(), data, mImage[1]->GetNumBytes());

    // Create two overlays, one for the original image and one for the
    // median-filtered image.
    std::array<int, 4> rect[2] =
    {
        { 0, 0, mXSize / 2, mYSize },
        { mXSize / 2, 0, mXSize / 2, mYSize }
    };
    for (int i = 0; i < 2; ++i)
    {
        mOverlay[i].reset(new OverlayEffect(mXSize, mYSize, txWidth, txHeight,
            SamplerState::MIN_L_MAG_L_MIP_P, SamplerState::CLAMP,
            SamplerState::CLAMP, false));
        mOverlay[i]->SetOverlayRectangle(rect[i]);
    }
    mOverlay[0]->SetTexture(mOriginal);
    mOverlay[1]->SetTexture(mImage[1]);

    // Create the shaders.
    int const numThreads = 8;
    mNumXGroups = txWidth / numThreads;
    mNumYGroups = txHeight / numThreads;

    HLSLDefiner definer;
    definer.SetUnsignedInt("NUM_X_THREADS", numThreads);
    definer.SetUnsignedInt("NUM_Y_THREADS", numThreads);

    definer.SetInt("RADIUS", 1);
    mMedianShader[0].reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("MedianBySort.hlsl"), definer));
    mMedianShader[1].reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("Median3x3.hlsl"), definer));

    definer.SetInt("RADIUS", 2);
    mMedianShader[2].reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("MedianBySort.hlsl"), definer));
    mMedianShader[3].reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("Median5x5.hlsl"), definer));

    for (int i = 0; i < 4; ++i)
    {
        mMedianShader[i]->Set("input", mImage[0]);
        mMedianShader[i]->Set("output", mImage[1]);
    }
}
//----------------------------------------------------------------------------
void MedianFilteringWindow::OnIdle ()
{
    MeasureTime();

    mEngine->Execute(mMedianShader[mSelection], mNumXGroups, mNumYGroups, 1);
    mEngine->Draw(mOverlay[0]);
    mEngine->Draw(mOverlay[1]);
    std::swap(mImage[0], mImage[1]);
    mMedianShader[mSelection]->Set("input", mImage[0]);
    mMedianShader[mSelection]->Set("output", mImage[1]);
    mOverlay[1]->SetTexture(mImage[1]);
    mEngine->Draw(8, mYSize - 24, mTextColor, msName[mSelection]);
    DrawFrameRate(8, mYSize - 8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool MedianFilteringWindow::OnCharPress(unsigned char key, int x, int y)
{

    switch (key)
    {
    case '0':
        mSelection = 0;
        memcpy(mImage[0]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[0]);
        memcpy(mImage[1]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[1]);
        return true;

    case '1':
        mSelection = 1;
        memcpy(mImage[0]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[0]);
        memcpy(mImage[1]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[1]);
        return true;

    case '2':
        mSelection = 2;
        memcpy(mImage[0]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[0]);
        memcpy(mImage[1]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[1]);
        return true;

    case '3':
        mSelection = 3;
        memcpy(mImage[0]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[0]);
        memcpy(mImage[1]->GetData(), mOriginal->GetData(),
            mOriginal->GetNumBytes());
        mEngine->CopyCpuToGpu(mImage[1]);
        return true;
    }

    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool MedianFilteringWindow::SetEnvironment()
{
    std::string gtpath = mEnvironment.GetVariable("GTE_PATH");
    if (gtpath == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }
    mEnvironment.Insert(gtpath + "/Samples/Imagics/MedianFiltering/Shaders/");

    if (mEnvironment.GetPath("Median3x3.hlsl") == "")
    {
        LogError("Cannot find file Median3x3.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("Median5x5.hlsl") == "")
    {
        LogError("Cannot find file Median5x5.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("MedianBySort.hlsl") == "")
    {
        LogError("Cannot find file MedianBySort.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("MedianShared.hlsli") == "")
    {
        LogError("Cannot find file MedianShared.hlsli.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------

std::string MedianFilteringWindow::msName[4] =
{
    "median 3x3 by insertion sort",
    "median 3x3 by min-max",
    "median 5x5 by insertion sort",
    "median 5x5 by min-max"
};
