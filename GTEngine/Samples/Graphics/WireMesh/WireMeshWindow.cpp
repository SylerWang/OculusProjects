// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "WireMeshWindow.h"

//----------------------------------------------------------------------------
WireMeshWindow::~WireMeshWindow()
{
    UnsubscribeCW(mMesh);
}
//----------------------------------------------------------------------------
WireMeshWindow::WireMeshWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f)
{
    if (!SetEnvironment() || !CreateScene())
    {
        parameters.created = false;
        return;
    }

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(0.0f, 0.0f, -2.5f, 1.0f);
    Vector4<float> camDVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    EnableCameraMotion(0.01f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void WireMeshWindow::OnIdle()
{
    MeasureTime();
    MoveCamera();

    mEngine->ClearBuffers();
    mEngine->Draw(mMesh);
    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool WireMeshWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }

    mEnvironment.Insert(path + "/Samples/Graphics/WireMesh/Shaders/");

    if (mEnvironment.GetPath("WireMesh.hlsl") == "")
    {
        LogError("Cannot find file WireMesh.hlsl.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
bool WireMeshWindow::CreateScene()
{
    std::string path = mEnvironment.GetPath("WireMesh.hlsl");
    std::shared_ptr<VertexShader> vshader(ShaderFactory::CreateVertex(path));
    if (!vshader)
    {
        return false;
    }

    std::shared_ptr<GeometryShader> gshader(ShaderFactory::CreateGeometry(
        path));
    if (!gshader)
    {
        return false;
    }

    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(path));
    if (!pshader)
    {
        return false;
    }

    std::shared_ptr<ConstantBuffer> parameters(
        new ConstantBuffer(3 * sizeof(Vector4<float>), false));
    Vector4<float>* data = parameters->Get<Vector4<float>>();
    data[0] = Vector4<float>(0.0f, 0.0f, 1.0f, 1.0f);  // mesh color
    data[1] = Vector4<float>(0.0f, 0.0f, 0.0f, 1.0f);  // edge color
    data[2] = Vector4<float>((float)mXSize, (float)mYSize, 0.0f, 0.0f);
    vshader->Set("WireParameters", parameters);
    gshader->Set("WireParameters", parameters);
    pshader->Set("WireParameters", parameters);

    std::shared_ptr<ConstantBuffer> cbuffer(
        new ConstantBuffer(sizeof(Matrix4x4<float>), true));
    vshader->Set("PVWMatrix", cbuffer);

    std::shared_ptr<VisualEffect> effect(new VisualEffect(vshader, pshader,
        gshader));

    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    MeshFactory mf;
    mf.SetVertexFormat(vformat);
    mMesh = mf.CreateSphere(16, 16, 1.0f);
    mMesh->SetEffect(effect);
    mMesh->Update();

    SubscribeCW(mMesh, cbuffer);
    return true;
}
//----------------------------------------------------------------------------
