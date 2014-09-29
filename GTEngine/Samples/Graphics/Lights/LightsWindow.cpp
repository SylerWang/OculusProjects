// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "LightsWindow.h"
#include <iostream>

//----------------------------------------------------------------------------
LightsWindow::~LightsWindow()
{
    UnsubscribeCW(mPlane[SVTX]);
    UnsubscribeCW(mPlane[SPXL]);
    UnsubscribeCW(mSphere[SVTX]);
    UnsubscribeCW(mSphere[SPXL]);
}
//----------------------------------------------------------------------------
LightsWindow::LightsWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(1.0f, 1.0f, 1.0f, 1.0f)
{
    mEngine->SetClearColor(Vector4<float>(0.0f, 0.25f, 0.75f, 1.0f));
    mWireState = std::make_shared<RasterizerState>();
    mWireState->fillMode = RasterizerState::FILL_WIREFRAME;

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(16.0f, 0.0f, 8.0f, 1.0f);
    Vector4<float> camDVector = Vector4<float>::Basis3() - camPosition;
    Normalize(camDVector);
    Vector4<float> camUVector(camDVector[2], 0.0f, -camDVector[0], 0.0f);
    Vector4<float> camRVector(0.0f, 1.0f, 0.0f, 0.0f);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    CreateScene();

    EnableCameraMotion(0.01f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void LightsWindow::OnIdle()
{
    MeasureTime();
    MoveCamera();
    UpdateConstants();

    mEngine->ClearBuffers();
    mEngine->Draw(mPlane[0]);
    mEngine->Draw(mPlane[1]);
    mEngine->Draw(mSphere[0]);
    mEngine->Draw(mSphere[1]);
    mEngine->Draw(8, 16, mTextColor, mCaption[mType]);
    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool LightsWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':   // toggle wireframe
    case 'W':
        if (mEngine->GetRasterizerState() == mWireState)
        {
            mEngine->SetDefaultRasterizerState();
        }
        else
        {
            mEngine->SetRasterizerState(mWireState);
        }
        return true;

    case 'd':   // use directional lights
    case 'D':
        UseLightType(LDIR);
        return true;

    case 'p':   // use point lights
    case 'P':
        UseLightType(LPNT);
        return true;

    case 's':   // use spot lights
    case 'S':
        UseLightType(LSPT);
        return true;

    case 'i':   // decrease light intensity
        for (int lt = 0; lt < LNUM; ++lt)
        {
            for (int gt = 0; gt < GNUM; ++gt)
            {
                for (int st = 0; st < SNUM; ++st)
                {
                    auto effect = mEffect[lt][gt][st].get();
                    float& intensity = 
                        effect->GetLighting().lightAttenuation[3];
                    intensity -= 0.125f;
                    intensity = std::max(intensity, 0.0f);
                    mEngine->Update(effect->GetLightingConstant());
                }
            }
        }
        return true;

    case 'I':   // increase light intensity
        for (int lt = 0; lt < LNUM; ++lt)
        {
            for (int gt = 0; gt < GNUM; ++gt)
            {
                for (int st = 0; st < SNUM; ++st)
                {
                    auto effect = mEffect[lt][gt][st].get();
                    float& intensity =
                        effect->GetLighting().lightAttenuation[3];
                    intensity += 0.125f;
                    mEngine->Update(effect->GetLightingConstant());
                }
            }
        }
        return true;

    case 'a':   // decrease spot angle
        for (int gt = 0; gt < GNUM; ++gt)
        {
            for (int st = 0; st < SNUM; ++st)
            {
                auto effect = mEffect[LSPT][gt][st].get();
                auto& params = effect->GetLighting().lightSpotCutoff;
                params[0] -= 0.1f;
                params[0] = std::max(params[0], 0.0f);
                params[1] = cos(params[0]);
                params[2] = sin(params[0]);
                mEngine->Update(effect->GetLightingConstant());
            }
        }
        return true;

    case 'A':   // increase spot angle
        for (int gt = 0; gt < GNUM; ++gt)
        {
            for (int st = 0; st < SNUM; ++st)
            {
                auto effect = mEffect[LSPT][gt][st].get();
                auto& params = effect->GetLighting().lightSpotCutoff;
                params[0] += 0.1f;
                params[0] = std::min(params[0], (float)GTE_C_HALF_PI);
                params[1] = cos(params[0]);
                params[2] = sin(params[0]);
                mEngine->Update(effect->GetLightingConstant());
            }
        }
        return true;

    case 'e':   // decrease spot exponent
        for (int gt = 0; gt < GNUM; ++gt)
        {
            for (int st = 0; st < SNUM; ++st)
            {
                auto effect = mEffect[LSPT][gt][st].get();
                auto& params = effect->GetLighting().lightSpotCutoff;
                params[3] *= 0.5f;
                mEngine->Update(effect->GetLightingConstant());
            }
        }
        return true;

    case 'E':   // increase spot exponent
        for (int gt = 0; gt < GNUM; ++gt)
        {
            for (int st = 0; st < SNUM; ++st)
            {
                auto effect = mEffect[LSPT][gt][st].get();
                auto& params = effect->GetLighting().lightSpotCutoff;
                params[3] *= 2.0f;
                mEngine->Update(effect->GetLightingConstant());
            }
        }
        return true;
    }
    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
void LightsWindow::CreateScene()
{
    // Copper color for the planes.
    Vector4<float> planeAmbient(0.2295f, 0.08825f, 0.0275f, 1.0f);
    Vector4<float> planeDiffuse(0.5508f, 0.2118f, 0.066f, 1.0f);
    Vector4<float> planeSpecular(0.580594f, 0.223257f, 0.0695701f, 51.2f);

    // Gold color for the spheres.
    Vector4<float> sphereAmbient(0.24725f, 0.2245f, 0.0645f, 1.0f);
    Vector4<float> sphereDiffuse(0.34615f, 0.3143f, 0.0903f, 1.0f);
    Vector4<float> sphereSpecular(0.797357f, 0.723991f, 0.208006f, 83.2f);

    // Various parameters shared by the lighting constants.  The geometric
    // parameters are dynamic, modified by UpdateConstants() whenever the
    // camera or scene moves.  These include camera model position, light
    // model position, light model direction, and model-to-world matrix.
    Vector4<float> darkGray(0.1f, 0.1f, 0.1f, 1.0f);
    Vector4<float> lightGray(0.75f, 0.75f, 0.75f, 1.0f);
    float angle = 0.125f*(float)GTE_C_PI;
    Vector4<float> lightSpotCutoff(angle, cos(angle), sin(angle), 1.0f);

    mLightWorldPosition[SVTX] = Vector4<float>(4.0f, 4.0f - 8.0f, 8.0f, 1.0f);
    mLightWorldPosition[SPXL] = Vector4<float>(4.0f, 4.0f + 8.0f, 8.0f, 1.0f);
    mLightWorldDirection = Vector4<float>(-1.0f, -1.0f, -1.0f, 0.0f);
    Normalize(mLightWorldDirection);

    LightingConstants lighting[LNUM][GNUM];

    // Initialize the directional lighting constants.
    lighting[LDIR][GPLN].materialAmbient = planeAmbient;
    lighting[LDIR][GPLN].materialDiffuse = planeDiffuse;
    lighting[LDIR][GPLN].materialSpecular = planeSpecular;
    lighting[LDIR][GPLN].lightAmbient = lightGray;
    lighting[LDIR][GSPH].materialAmbient = sphereAmbient;
    lighting[LDIR][GSPH].materialDiffuse = sphereDiffuse;
    lighting[LDIR][GSPH].materialSpecular = sphereSpecular;
    lighting[LDIR][GSPH].lightAmbient = lightGray;

    // Initialize the point lighting constants.
    lighting[LPNT][GPLN].materialAmbient = planeAmbient;
    lighting[LPNT][GPLN].materialDiffuse = planeDiffuse;
    lighting[LPNT][GPLN].materialSpecular = planeSpecular;
    lighting[LPNT][GPLN].lightAmbient = darkGray;
    lighting[LPNT][GSPH].materialAmbient = sphereAmbient;
    lighting[LPNT][GSPH].materialDiffuse = sphereDiffuse;
    lighting[LPNT][GSPH].materialSpecular = sphereSpecular;
    lighting[LPNT][GSPH].lightAmbient = darkGray;

    // Initialize the spot lighting constants.
    lighting[LSPT][GPLN].materialAmbient = planeAmbient;
    lighting[LSPT][GPLN].materialDiffuse = planeDiffuse;
    lighting[LSPT][GPLN].materialSpecular = planeSpecular;
    lighting[LSPT][GPLN].lightAmbient = darkGray;
    lighting[LSPT][GPLN].lightSpotCutoff = lightSpotCutoff;
    lighting[LSPT][GSPH].materialAmbient = sphereAmbient;
    lighting[LSPT][GSPH].materialDiffuse = sphereDiffuse;
    lighting[LSPT][GSPH].materialSpecular = sphereSpecular;
    lighting[LSPT][GSPH].lightAmbient = darkGray;
    lighting[LSPT][GSPH].lightSpotCutoff = lightSpotCutoff;

    // Create the effects.
    mEffect[LDIR][GPLN][SVTX] =
        std::make_shared<LightDirectionPerVertexEffect>(lighting[LDIR][GPLN]);
    mEffect[LDIR][GPLN][SPXL] =
        std::make_shared<LightDirectionPerPixelEffect>(lighting[LDIR][GPLN]);
    mEffect[LDIR][GSPH][SVTX] =
        std::make_shared<LightDirectionPerVertexEffect>(lighting[LDIR][GSPH]);
    mEffect[LDIR][GSPH][SPXL] =
        std::make_shared<LightDirectionPerPixelEffect>(lighting[LDIR][GSPH]);
    mEffect[LPNT][GPLN][SVTX] =
        std::make_shared<LightPointPerVertexEffect>(lighting[LPNT][GPLN]);
    mEffect[LPNT][GPLN][SPXL] =
        std::make_shared<LightPointPerPixelEffect>(lighting[LPNT][GPLN]);
    mEffect[LPNT][GSPH][SVTX] =
        std::make_shared<LightPointPerVertexEffect>(lighting[LPNT][GSPH]);
    mEffect[LPNT][GSPH][SPXL] =
        std::make_shared<LightPointPerPixelEffect>(lighting[LPNT][GSPH]);
    mEffect[LSPT][GPLN][SVTX] =
        std::make_shared<LightSpotPerVertexEffect>(lighting[LSPT][GPLN]);
    mEffect[LSPT][GPLN][SPXL] =
        std::make_shared<LightSpotPerPixelEffect>(lighting[LSPT][GPLN]);
    mEffect[LSPT][GSPH][SVTX] =
        std::make_shared<LightSpotPerVertexEffect>(lighting[LSPT][GSPH]);
    mEffect[LSPT][GSPH][SPXL] =
        std::make_shared<LightSpotPerPixelEffect>(lighting[LSPT][GSPH]);

    // Create the planes and spheres.
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_NORMAL, DF_R32G32B32_FLOAT, 0);
    MeshFactory mf;
    mf.SetVertexFormat(vformat);

    mPlane[SVTX] = mf.CreateRectangle(128, 128, 8.0f, 8.0f);
    mPlane[SVTX]->localTransform.SetTranslation(0.0f, -8.0f, 0.0f);
    mPlane[SVTX]->Update();

    mPlane[SPXL] = mf.CreateRectangle(128, 128, 8.0f, 8.0f);
    mPlane[SPXL]->localTransform.SetTranslation(0.0f, +8.0f, 0.0f);
    mPlane[SPXL]->Update();

    mSphere[SVTX] = mf.CreateSphere(64, 64, 2.0f);
    mSphere[SVTX]->localTransform.SetTranslation(0.0f, -8.0f, 2.0f);
    mSphere[SVTX]->Update();

    mSphere[SPXL] = mf.CreateSphere(64, 64, 2.0f);
    mSphere[SPXL]->localTransform.SetTranslation(0.0f, +8.0f, 2.0f);
    mSphere[SPXL]->Update();

    mCaption[LDIR] = "Directional Light (left per vertex, right per pixel)";
    mCaption[LPNT] = "Point Light (left per vertex, right per pixel)";
    mCaption[LSPT] = "Spot Light (left per vertex, right per pixel)";

    UseLightType(LDIR);
}
//----------------------------------------------------------------------------
void LightsWindow::UseLightType(int type)
{
    UnsubscribeCW(mPlane[SVTX]);
    mPlane[SVTX]->SetEffect(mEffect[type][GPLN][SVTX]);
    SubscribeCW(mPlane[SVTX],
        mEffect[type][GPLN][SVTX]->GetPVWMatrixConstant());

    UnsubscribeCW(mPlane[SPXL]);
    mPlane[SPXL]->SetEffect(mEffect[type][GPLN][SPXL]);
    SubscribeCW(mPlane[SPXL],
        mEffect[type][GPLN][SPXL]->GetPVWMatrixConstant());

    UnsubscribeCW(mSphere[SVTX]);
    mSphere[SVTX]->SetEffect(mEffect[type][GSPH][SVTX]);
    SubscribeCW(mSphere[SVTX],
        mEffect[type][GSPH][SVTX]->GetPVWMatrixConstant());

    UnsubscribeCW(mSphere[SPXL]);
    mSphere[SPXL]->SetEffect(mEffect[type][GSPH][SPXL]);
    SubscribeCW(mSphere[SPXL],
        mEffect[type][GSPH][SPXL]->GetPVWMatrixConstant());

    mType = type;

    UpdateCW();
}
//----------------------------------------------------------------------------
void LightsWindow::UpdateConstants()
{
    // The pvw-matrices are updated automatically whenever the camera moves
    // or the trackball is rotated, which happens before this call.  Here we
    // need to update the camera model position, light model position, and
    // light model direction.

    // Compute the model-to-world transforms for the planes and spheres.
    Matrix4x4<float> wMatrix[GNUM][SNUM];
    Matrix4x4<float> rotate = GetTrackballRotation();
#if defined(GTE_USE_MAT_VEC)
    wMatrix[GPLN][SVTX] = rotate * mPlane[SVTX]->worldTransform;
    wMatrix[GPLN][SPXL] = rotate * mPlane[SPXL]->worldTransform;
    wMatrix[GSPH][SVTX] = rotate * mSphere[SVTX]->worldTransform;
    wMatrix[GSPH][SPXL] = rotate * mSphere[SPXL]->worldTransform;
#else
    wMatrix[GPLN][SVTX] = mPlane[SVTX]->worldTransform * rotate;
    wMatrix[GPLN][SPXL] = mPlane[SPXL]->worldTransform * rotate;
    wMatrix[GSPH][SVTX] = mSphere[SVTX]->worldTransform * rotate;
    wMatrix[GSPH][SPXL] = mSphere[SPXL]->worldTransform * rotate;
#endif

    // Compute the world-to-model transforms for the planes and spheres.
    Matrix4x4<float> invWMatrix[GNUM][SNUM];
    for (int gt = 0; gt < GNUM; ++gt)
    {
        for (int st = 0; st < SNUM; ++st)
        {
            invWMatrix[gt][st] = Inverse(wMatrix[gt][st]);
        }
    }

    Vector4<float> cameraWorldPosition = mCamera.GetPosition();
    for (int lt = 0; lt < LNUM; ++lt)
    {
        for (int gt = 0; gt < GNUM; ++gt)
        {
            for (int st = 0; st < SNUM; ++st)
            {
                auto effect = mEffect[lt][gt][st].get();
                LightingConstants& param = effect->GetLighting();

#if defined(GTE_USE_MAT_VEC)
                param.cameraModelPosition =
                    invWMatrix[gt][st] * cameraWorldPosition;
                param.lightModelPosition =
                    invWMatrix[gt][st] * mLightWorldPosition[st];
                param.lightModelDirection =
                    invWMatrix[gt][st] * mLightWorldDirection;
                param.wMatrix = wMatrix[gt][st];
#else
                param.cameraModelPosition =
                    camWPosition * invWMatrix[gt][st];
                param.lightModelPosition =
                    mLightWorldPosition[st] * invWMatrix[gt][st];
                param.lightModelDirection =
                    mLightWorldDirection * invWMatrix[gt][st];
                param.wMatrix = wMatrix[gt][st];
#endif
                mEngine->Update(effect->GetLightingConstant());
            }
        }
    }
}
//----------------------------------------------------------------------------
