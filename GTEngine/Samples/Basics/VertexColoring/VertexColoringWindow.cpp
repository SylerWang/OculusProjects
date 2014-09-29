// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "VertexColoringWindow.h"

//----------------------------------------------------------------------------
VertexColoringWindow::~VertexColoringWindow()
{
    UnsubscribeCW(mTriangle);
}
//----------------------------------------------------------------------------
VertexColoringWindow::VertexColoringWindow(Parameters& parameters)
    :
    Window(parameters)
{
    CreateScene();

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(0.0f, 0.0f, 1.25f, 1.0f);
    Vector4<float> camDVector(0.0f, 0.0f, -1.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

#ifdef SAVE_RENDERING_TO_DISK
    mTarget.reset(new DrawTarget(1, DF_R8G8B8A8_UNORM, mXSize, mYSize));
    mTarget->GetRTTexture(0)->SetCopyType(Resource::COPY_STAGING_TO_CPU);
#endif

    EnableCameraMotion(0.001f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void VertexColoringWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    mEngine->ClearBuffers();
    mEngine->Draw(mTriangle);
    mEngine->DisplayColorBuffer(0);

#ifdef SAVE_RENDERING_TO_DISK
    mEngine->Enable(mTarget);
    mEngine->ClearBuffers();
    mEngine->Draw(mTriangle);
    mEngine->Disable(mTarget);
    mEngine->CopyGpuToCpu(mTarget->GetRTTexture(0));
    WICFileIO::SaveToPNG("VertexColoring.png",
        mTarget->GetRTTexture(0).get());
#endif

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
void VertexColoringWindow::CreateScene()
{
    // Create a vertex buffer for a single triangle.
    struct Vertex
    {
        Vector3<float> position;
        Vector4<float> color;
    };
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_COLOR, DF_R32G32B32A32_FLOAT, 0);
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat, 3));
    Vertex* vertex = vbuffer->Get<Vertex>();
    vertex[0].position = Vector3<float>(0.0f, 0.0f, 0.0f);
    vertex[0].color = Vector4<float>(1.0f, 0.0f, 0.0f, 1.0f);
    vertex[1].position = Vector3<float>(1.0f, 0.0f, 0.0f);
    vertex[1].color = Vector4<float>(0.0f, 1.0f, 0.0f, 1.0f);
    vertex[2].position = Vector3<float>(0.0f, 1.0f, 0.0f);
    vertex[2].color = Vector4<float>(0.0f, 0.0f, 1.0f, 1.0f);

    // Create an indexless buffer for a triangle mesh with one triangle.
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_TRIMESH, 1));

    // Create an effect for the vertex and pixel shaders.
    std::shared_ptr<VertexColorEffect> effect(new VertexColorEffect());

    // Create the geometric object for drawing.  Translate it so that its
    // center of mass is at the origin.  This supports virtual trackball
    // motion about the object "center".
    mTriangle.reset(new Visual(vbuffer, ibuffer, effect));
    float const negOneThird = -1.0f / 3.0f;
    mTriangle->localTransform.SetTranslation(negOneThird, negOneThird, 0.0f);
    mTriangle->Update();

    // Enable automatic updates of pvw-matrices and w-matrices.
    SubscribeCW(mTriangle, effect->GetPVWMatrixConstant());
}
//----------------------------------------------------------------------------
