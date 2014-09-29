// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/14)

#include "ConvolutionWindow.h"

//----------------------------------------------------------------------------
ConvolutionWindow::~ConvolutionWindow()
{
}
//----------------------------------------------------------------------------
ConvolutionWindow::ConvolutionWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(1.0f, 1.0f, 0.0f, 1.0f),
    mNumXGroups(0),
    mNumYGroups(0),
    mRadius(1),
    mSelection(0)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    // Load the color image to be convolved.
    std::string path = mEnvironment.GetPath("MedicineBag.jpg");
    Texture2* original = WICFileIO::Load(path, false);
    unsigned int const txWidth = original->GetWidth();
    unsigned int const txHeight = original->GetHeight();

    // Create images for shader inputs and outputs.
    for (int i = 0; i < 3; ++i)
    {
        mImage[i].reset(new Texture2(DF_R32G32B32A32_FLOAT, txWidth,
            txHeight));
        mImage[i]->SetUsage(Resource::SHADER_OUTPUT);
    }

    // Map the 8-bit RGBA image to 32-bit RGBA for the numerical convolution.
    unsigned int const* src = original->Get<unsigned int>();
    float* trg = mImage[0]->Get<float>();
    for (unsigned int j = 0; j < txWidth*txHeight; ++j)
    {
        unsigned int rgba = *src++;
        *trg++ = (rgba & 0x000000FF) / 255.0f;
        *trg++ = ((rgba & 0x0000FF00) >> 8) / 255.0f;
        *trg++ = ((rgba & 0x00FF0000) >> 16) / 255.0f;
        *trg++ = 1.0f;
    }
    delete original;

    // Create two overlays, one for the original image and one for the
    // convolved image.
    std::array<int, 4> rect[2] =
    {
        { 0, 0, mXSize / 2, mYSize },
        { mXSize / 2, 0, mXSize / 2, mYSize }
    };
    for (int i = 0; i < 2; ++i)
    {
        mOverlay[i].reset(new OverlayEffect(mXSize, mYSize, txWidth, txHeight,
            SamplerState::MIN_L_MAG_L_MIP_P, SamplerState::CLAMP,
            SamplerState::CLAMP, true));
        mOverlay[i]->SetOverlayRectangle(rect[i]);
        mOverlay[i]->SetTexture(mImage[i]);
    }

    CreateShaders();
}
//----------------------------------------------------------------------------
void ConvolutionWindow::OnIdle()
{
    MeasureTime();

    ExecuteShaders();
    mEngine->Draw(mOverlay[0]);
    mEngine->Draw(mOverlay[1]);
    std::string message = "radius = " + std::to_string(mRadius);
    mEngine->Draw(8, mYSize - 40, mTextColor, msName[mSelection]);
    mEngine->Draw(8, mYSize - 24, mTextColor, message);
    DrawFrameRate(8, mYSize - 8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool ConvolutionWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '0':
        mSelection = 0;
        CreateShaders();
        return true;

    case '1':
        mSelection = 1;
        CreateShaders();
        return true;

    case '2':
        mSelection = 2;
        CreateShaders();
        return true;

    case '3':
        mSelection = 3;
        CreateShaders();
        return true;

    case '4':
        mSelection = 4;
        CreateShaders();
        return true;

    case '+':
    case '=':
        if (mRadius < MAX_RADIUS)
        {
            ++mRadius;
            CreateShaders();
        }
        return true;

    case '-':
    case '_':
        if (mRadius > 1)
        {
            --mRadius;
            CreateShaders();
        }
        return true;
    }

    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool ConvolutionWindow::SetEnvironment()
{
    std::string gtpath = mEnvironment.GetVariable("GTE_PATH");
    if (gtpath == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }
    mEnvironment.Insert(gtpath + "/Samples/Imagics/Convolution/Shaders/");
    mEnvironment.Insert(gtpath + "/Samples/Data/");

    if (mEnvironment.GetPath("MedicineBag.jpg") == "")
    {
        LogError("Cannot find file MedicineBag.jpg.");
        return false;
    }

    if (mEnvironment.GetPath("Convolve.hlsl") == "")
    {
        LogError("Cannot find file Convolve.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ConvolveGS.hlsl") == "")
    {
        LogError("Cannot find file ConvolveGS.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ConvolveSeparableH.hlsl") == "")
    {
        LogError("Cannot find file ConvolveSeparableH.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ConvolveSeparableHGS.hlsl") == "")
    {
        LogError("Cannot find file ConvolveSeparableHGS.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ConvolveSeparableHGS2.hlsl") == "")
    {
        LogError("Cannot find file ConvolveSeparableHGS2.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ConvolveSeparableV.hlsl") == "")
    {
        LogError("Cannot find file ConvolveSeparableV.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ConvolveSeparableVGS.hlsl") == "")
    {
        LogError("Cannot find file ConvolveSeparableVGS.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("ConvolveSeparableVGS2.hlsl") == "")
    {
        LogError("Cannot find file ConvolveSeparableVGS2.hlsl.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void ConvolutionWindow::CreateShaders()
{
    HLSLDefiner definer;
    std::string path;

    switch (mSelection)
    {
    case 0:
        mNumXGroups = mImage[0]->GetWidth() / 16;
        mNumYGroups = mImage[0]->GetHeight() / 16;
        definer.SetUnsignedInt("NUM_X_THREADS", 16);
        definer.SetUnsignedInt("NUM_Y_THREADS", 16);
        definer.SetInt("RADIUS", mRadius);
        path = mEnvironment.GetPath("Convolve.hlsl");
        mConvolve.reset(
            ShaderFactory::CreateCompute(path, definer));
        if (mConvolve)
        {
            mConvolve->Set("input", mImage[0]);
            mConvolve->Set("output", mImage[1]);
            mConvolve->Set("Weights", GetKernel2(mRadius));
        }
        else
        {
            LogError("Failed to compile Convolve.hlsl.");
        }
        break;

    case 1:
        mNumXGroups = mImage[0]->GetWidth() / 16;
        mNumYGroups = mImage[0]->GetHeight() / 16;
        definer.SetInt("RADIUS", mRadius);
        definer.SetUnsignedInt("NUM_X_THREADS", 16);
        definer.SetUnsignedInt("NUM_Y_THREADS", 16);
        path = mEnvironment.GetPath("ConvolveGS.hlsl");
        mConvolveGS.reset(
            ShaderFactory::CreateCompute(path, definer));
        if (mConvolveGS)
        {
            mConvolveGS->Set("input", mImage[0]);
            mConvolveGS->Set("output", mImage[1]);
            mConvolveGS->Set("Weights", GetKernel2(mRadius));
        }
        else
        {
            LogError("Failed to compile ConvolveGS.hlsl.");
        }
        break;

    case 2:
        mNumXGroups = mImage[0]->GetWidth() / 16;
        mNumYGroups = mImage[0]->GetHeight() / 16;
        definer.SetUnsignedInt("NUM_X_THREADS", 16);
        definer.SetUnsignedInt("NUM_Y_THREADS", 16);
        definer.SetInt("RADIUS", mRadius);
        path = mEnvironment.GetPath("ConvolveSeparableH.hlsl");
        mConvolveSeparableH.reset(
            ShaderFactory::CreateCompute(path, definer));
        path = mEnvironment.GetPath("ConvolveSeparableV.hlsl");
        mConvolveSeparableV.reset(
            ShaderFactory::CreateCompute(path, definer));
        if (mConvolveSeparableH && mConvolveSeparableV)
        {
            mConvolveSeparableH->Set("input", mImage[0]);
            mConvolveSeparableH->Set("output", mImage[2]);
            mConvolveSeparableH->Set("Weights", GetKernel1(mRadius));
            mConvolveSeparableV->Set("input", mImage[2]);
            mConvolveSeparableV->Set("output", mImage[1]);
            mConvolveSeparableV->Set("Weights", GetKernel1(mRadius));
        }
        else
        {
            LogError("Failed to compile ConvolveSeparable{H,V}.hlsl.");
        }
        break;

    case 3:
        definer.SetInt("RADIUS", mRadius);
        path = mEnvironment.GetPath("ConvolveSeparableHGS.hlsl");
        mConvolveSeparableHGS.reset(
            ShaderFactory::CreateCompute(path, definer));
        path = mEnvironment.GetPath("ConvolveSeparableVGS.hlsl");
        mConvolveSeparableVGS.reset(
            ShaderFactory::CreateCompute(path, definer));
        if (mConvolveSeparableHGS && mConvolveSeparableVGS)
        {
            mConvolveSeparableHGS->Set("input", mImage[0]);
            mConvolveSeparableHGS->Set("output", mImage[2]);
            mConvolveSeparableHGS->Set("Weights", GetKernel1(mRadius));
            mConvolveSeparableVGS->Set("input", mImage[2]);
            mConvolveSeparableVGS->Set("output", mImage[1]);
            mConvolveSeparableVGS->Set("Weights", GetKernel1(mRadius));
        }
        else
        {
            LogError("Failed to compile ConvolveSeparable{H,V}GS.hlsl.");
        }
        break;

    case 4:
        definer.SetInt("RADIUS", mRadius);
        path = mEnvironment.GetPath("ConvolveSeparableHGS2.hlsl");
        mConvolveSeparableHGS2.reset(
            ShaderFactory::CreateCompute(path, definer));
        path = mEnvironment.GetPath("ConvolveSeparableVGS2.hlsl");
        mConvolveSeparableVGS2.reset(
            ShaderFactory::CreateCompute(path, definer));
        if (mConvolveSeparableHGS2 && mConvolveSeparableVGS2)
        {
            mConvolveSeparableHGS2->Set("input", mImage[0]);
            mConvolveSeparableHGS2->Set("output", mImage[2]);
            mConvolveSeparableHGS2->Set("Weights", GetKernel1(mRadius));
            mConvolveSeparableVGS2->Set("input", mImage[2]);
            mConvolveSeparableVGS2->Set("output", mImage[1]);
            mConvolveSeparableVGS2->Set("Weights", GetKernel1(mRadius));
        }
        else
        {
            LogError("Failed to compile ConvolveSeparable{H,V}GS2.hlsl.");
        }
        break;
    }
}
//----------------------------------------------------------------------------
void ConvolutionWindow::ExecuteShaders()
{
    switch (mSelection)
    {
    case 0:
        if (mConvolve)
        {
            mEngine->Execute(mConvolve, mNumXGroups, mNumYGroups, 1);
        }
        break;

    case 1:
        if (mConvolveGS)
        {
            mEngine->Execute(mConvolveGS, mNumXGroups, mNumYGroups, 1);
        }
        break;

    case 2:
        if (mConvolveSeparableH && mConvolveSeparableV)
        {
            mEngine->Execute(mConvolveSeparableH, mNumXGroups,
                mNumYGroups, 1);
            mEngine->Execute(mConvolveSeparableV, mNumXGroups,
                mNumYGroups, 1);
        }
        break;

    case 3:
        if (mConvolveSeparableHGS && mConvolveSeparableVGS)
        {
            mEngine->Execute(mConvolveSeparableHGS, 1,
                mImage[0]->GetHeight(), 1);
            mEngine->Execute(mConvolveSeparableVGS, mImage[0]->GetWidth(),
                1, 1);
        }
        break;

    case 4:
        if (mConvolveSeparableHGS2 && mConvolveSeparableVGS2)
        {
            mEngine->Execute(mConvolveSeparableHGS2, 4,
                mImage[0]->GetHeight(), 1);
            mEngine->Execute(mConvolveSeparableVGS2, mImage[0]->GetWidth(),
                4, 1);
        }
        break;
    }
}
//----------------------------------------------------------------------------
std::shared_ptr<ConstantBuffer> ConvolutionWindow::GetKernel1(int radius)
{
    // If radius/sigma = ratio, then exp(-ratio^2/2) = 0.001.
    float const ratio = 3.7169221888498384469524067613045f;
    float sigma = radius / ratio;

    int const numWeights = 2 * radius + 1;
    std::vector<float> weight(numWeights);
    float totalWeight = 0.0f;
    for (int x = -radius, i = 0; x <= radius; ++x, ++i)
    {
        float fx = x / sigma;
        float value = exp(-0.5f*fx*fx);
        weight[i] = value;
        totalWeight += value;
    }

    for (auto& w : weight)
    {
        w /= totalWeight;
    }

    std::shared_ptr<ConstantBuffer> cbuffer(new ConstantBuffer(
        numWeights*sizeof(Vector4<float>), false));
    Vector4<float>* data = cbuffer->Get<Vector4<float>>();
    for (int i = 0; i < numWeights; ++i)
    {
        // The HLSL constant buffer stores one float per 4-tuple register.
        Vector4<float>& entry = data[i];
        entry[0] = weight[i];
        entry[1] = 0.0f;
        entry[2] = 0.0f;
        entry[3] = 0.0f;
    }

    return cbuffer;
}
//----------------------------------------------------------------------------
std::shared_ptr<ConstantBuffer> ConvolutionWindow::GetKernel2(int radius)
{
    // If radius/sigma = ratio, then exp(-ratio^2/2) = 0.001.
    float const ratio = 3.7169221888498384469524067613045f;
    float sigma = radius / ratio;

    int const length = 2 * radius + 1;
    int const numWeights = length * length;
    std::vector<float> weight(numWeights);
    float totalWeight = 0.0f;
    for (int y = -radius, i = 0; y <= radius; ++y)
    {
        float fy = y / sigma;
        for (int x = -radius; x <= radius; ++x, ++i)
        {
            float fx = x / sigma;
            float value = exp(-0.5f*(fx*fx + fy*fy));
            weight[i] = value;
            totalWeight += value;
        }
    }

    for (auto& w : weight)
    {
        w /= totalWeight;
    }

    std::shared_ptr<ConstantBuffer> cbuffer(new ConstantBuffer(
        numWeights*sizeof(Vector4<float>), false));
    Vector4<float>* data = cbuffer->Get<Vector4<float>>();
    for (int i = 0; i < numWeights; ++i)
    {
        // The HLSL constant buffer stores one float per 4-tuple register.
        Vector4<float>& entry = data[i];
        entry[0] = weight[i];
        entry[1] = 0.0f;
        entry[2] = 0.0f;
        entry[3] = 0.0f;
    }

    return cbuffer;
}
//----------------------------------------------------------------------------

std::string ConvolutionWindow::msName[5] =
{
    "convolve",
    "convolve groupshared",
    "convolve separable",
    "convolve separable groupshared (one slice at a time)",
    "convolve separable groupshared (slice processed as subslices)"
};
