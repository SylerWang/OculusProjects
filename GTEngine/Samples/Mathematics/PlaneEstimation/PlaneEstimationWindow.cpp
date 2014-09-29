// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "PlaneEstimationWindow.h"

//----------------------------------------------------------------------------
PlaneEstimationWindow::~PlaneEstimationWindow()
{
}
//----------------------------------------------------------------------------
PlaneEstimationWindow::PlaneEstimationWindow (Parameters& parameters)
    :
    Window(parameters),
    mTextColor(1.0f, 1.0f, 0.0f, 1.0f)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    // Create the shaders.
    HLSLDefiner definer;
    int const numThreads = 8;
    definer.SetInt("NUM_X_THREADS", numThreads);
    definer.SetInt("NUM_Y_THREADS", numThreads);
    definer.SetInt("RADIUS", 3);

    mPositionShader.reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("EvaluateBezier.hlsl"), definer));
    if (!mPositionShader)
    {
        LogError("Failed to compile EvaluateBezier.hlsl.");
        parameters.created = false;
        return;
    }

    mPlaneShader.reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("PlaneEstimation.hlsl"), definer));
    if (!mPlaneShader)
    {
        LogError("Failed to compile PlaneEstimation.hlsl.");
        parameters.created = false;
        return;
    }

    std::shared_ptr<PixelShader> posPShader(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("PositionVisualize.hlsl")));
    if (!posPShader)
    {
        LogError("Failed to compile PositionVisualize.hlsl.");
        parameters.created = false;
        return;
    }

    std::shared_ptr<PixelShader> plnPShader(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("PlaneVisualize.hlsl")));
    if (!plnPShader)
    {
        LogError("Failed to compile PlaneVisualize.hlsl.");
        parameters.created = false;
        return;
    }

    // Create and attach resources to the shaders.
    mPositionShader->Set("ControlPoints", CreateBezierControls());

    int const txWidth = 1024, txHeight = 1024;
    mPositions.reset(new Texture2(DF_R32G32B32A32_FLOAT, txWidth, txHeight));
    mPositions->SetUsage(Resource::SHADER_OUTPUT);
    mPositionShader->Set("positions", mPositions);

    mNumXGroups = txWidth / numThreads;
    mNumYGroups = txHeight / numThreads;

    mPlaneShader->Set("positions", mPositions);

    mPlanes.reset(new Texture2(DF_R32G32B32A32_FLOAT, txWidth, txHeight));
    mPlanes->SetUsage(Resource::SHADER_OUTPUT);
    mPlaneShader->Set("planes", mPlanes);

    std::shared_ptr<SamplerState> sstate(new SamplerState());
    sstate->filter = SamplerState::MIN_L_MAG_L_MIP_P;
    sstate->mode[0] = SamplerState::CLAMP;
    sstate->mode[1] = SamplerState::CLAMP;

    posPShader->Set("myTexture", mPositions);
    posPShader->Set("mySampler", sstate);
    mOverlay[0].reset(new OverlayEffect(mXSize, mYSize, txWidth, txHeight,
        posPShader));
    std::array<int, 4> rect0 = { 0, 0, mXSize / 2, mYSize };
    mOverlay[0]->SetOverlayRectangle(rect0);

    plnPShader->Set("myTexture", mPlanes);
    plnPShader->Set("mySampler", sstate);
    mOverlay[1].reset(new OverlayEffect(mXSize, mYSize, txWidth, txHeight,
        plnPShader));
    std::array<int, 4> rect1 = { mXSize/2, 0, mXSize / 2, mYSize };
    mOverlay[1]->SetOverlayRectangle(rect1);
}
//----------------------------------------------------------------------------
void PlaneEstimationWindow::OnIdle ()
{
    MeasureTime();

    mEngine->Execute(mPositionShader, mNumXGroups, mNumYGroups, 1);
    mEngine->Execute(mPlaneShader, mNumXGroups, mNumYGroups, 1);
    mEngine->Draw(mOverlay[0]);
    mEngine->Draw(mOverlay[1]);
    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool PlaneEstimationWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }
    mEnvironment.Insert(path + "/Samples/Numerics/PlaneEstimation/Shaders/");

    if (mEnvironment.GetPath("EvaluateBezier.hlsl") == "")
    {
        LogError("Cannot find EvaluateBezier.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("PlaneEstimation.hlsl") == "")
    {
        LogError("Cannot find PlaneEstimation.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("PlaneVisualize.hlsl") == "")
    {
        LogError("Cannot find PlaneVisualize.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("PositionVisualize.hlsl") == "")
    {
        LogError("Cannot find PositionVisualize.hlsl.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
std::shared_ptr<ConstantBuffer> PlaneEstimationWindow::CreateBezierControls()
{
    // Generate random samples for the bicubic Bezier surface.  The w-channel
    // is irrelevant, so is set to zero.
    std::mt19937 mte;
    std::uniform_real_distribution<float> rnd(-0.25f, 1.0f);
    float P[4][4];
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            P[r][c]= rnd(mte);
        }
    }

    // Construct the control points from the samples.
    float control[4][4];
    control[0][0] = P[0][0];
    control[0][1] = (
        -5.0f*P[0][0] + 18.0f*P[0][1] - 9.0f*P[0][2] + 2.0f*P[0][3]
        ) / 6.0f;
    control[0][2] = (
        +2.0f*P[0][0] - 9.0f*P[0][1] + 18.0f*P[0][2] - 5.0f*P[0][3]
        ) / 6.0f;
    control[0][3] = P[0][3];
    control[1][0] = (
        -5.0f*P[0][0] + 18.0f*P[1][0] - 9.0f*P[2][0] - 5.0f*P[3][0]
        ) / 6.0f;
    control[1][1] = (
        + 25.0f*P[0][0] -  90.0f*P[0][1] +  45.0f*P[0][2] - 10.0f*P[0][3]
        - 90.0f*P[1][0] + 324.0f*P[1][1] - 162.0f*P[1][2] + 36.0f*P[1][3]
        + 45.0f*P[2][0] - 162.0f*P[2][1] +  81.0f*P[2][2] - 18.0f*P[2][3]
        - 10.0f*P[3][0] +  36.0f*P[3][1] -  18.0f*P[3][2] +  4.0f*P[3][3]
        ) / 36.0f;
    control[1][2] = (
        - 10.0f*P[0][0] +  45.0f*P[0][1] -  90.0f*P[0][2] + 25.0f*P[0][3]
        + 36.0f*P[1][0] - 162.0f*P[1][1] + 324.0f*P[1][2] - 90.0f*P[1][3]
        - 18.0f*P[2][0] +  81.0f*P[2][1] - 162.0f*P[2][2] + 45.0f*P[2][3]
        +  4.0f*P[3][0] -  18.0f*P[3][1] +  36.0f*P[3][2] - 10.0f*P[3][3]
        ) / 36.0f;
    control[1][3] = (
        -5.0f*P[0][3] + 18.0f*P[1][3] - 9.0f*P[2][3] + 2.0f*P[3][3]
        ) / 6.0f;
    control[2][0] = (
        +2.0f*P[0][0] - 9.0f*P[1][0] + 18.0f*P[2][0] - 5.0f*P[3][0]
        ) / 6.0f;
    control[2][1] = (
        - 10.0f*P[0][0] +  36.0f*P[0][1] -  18.0f*P[0][2] +  4.0f*P[0][3]
        + 45.0f*P[1][0] - 162.0f*P[1][1] +  81.0f*P[1][2] - 18.0f*P[1][3]
        - 90.0f*P[2][0] + 324.0f*P[2][1] - 162.0f*P[2][2] + 36.0f*P[2][3]
        + 25.0f*P[3][0] -  90.0f*P[3][1] +  45.0f*P[3][2] - 10.0f*P[3][3]
        ) / 36.0f;
    control[2][2] = (
        +  4.0f*P[0][0] -  18.0f*P[0][1] +  36.0f*P[0][2] - 10.0f*P[0][3]
        - 18.0f*P[1][0] +  81.0f*P[1][1] - 162.0f*P[1][2] + 45.0f*P[1][3]
        + 36.0f*P[2][0] - 162.0f*P[2][1] + 324.0f*P[2][2] - 90.0f*P[2][3]
        - 10.0f*P[3][0] +  45.0f*P[3][1] -  90.0f*P[3][2] + 25.0f*P[3][3]
        ) / 36.0f;
    control[2][3] = (
        +2.0f*P[0][3] - 9.0f*P[1][3] + 18.0f*P[2][3] - 5.0f*P[3][3]
        ) / 6.0f;
    control[3][0] = P[3][0];
    control[3][1] = (
        -5.0f*P[3][0] + 18.0f*P[3][1] - 9.0f*P[3][2] + 2.0f*P[3][3]
        ) / 6.0f;
    control[3][2] = (
        +2.0f*P[3][0] - 9.0f*P[3][1] + 18.0f*P[3][2] - 5.0f*P[3][3]
        ) / 6.0f;
    control[3][3] = P[3][3];

    size_t const numBytes = 16 * sizeof(Vector4<float>);
    std::shared_ptr<ConstantBuffer> controlBuffer(new ConstantBuffer(numBytes,
        false));
    Vector4<float>* data = controlBuffer->Get<Vector4<float>>();
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            // The HLSL constant buffer stores one float per 4-tuple register.
            Vector4<float>& trg = data[c + 4 * r];
            trg[0] = control[r][c];
            trg[1] = 0.0f;
            trg[2] = 0.0f;
            trg[3] = 0.0f;
        }
    }

    return controlBuffer;
}
//----------------------------------------------------------------------------
