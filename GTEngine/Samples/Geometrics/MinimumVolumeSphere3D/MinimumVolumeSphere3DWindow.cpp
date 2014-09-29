// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "MinimumVolumeSphere3DWindow.h"

//----------------------------------------------------------------------------
MinimumVolumeSphere3DWindow::~MinimumVolumeSphere3DWindow()
{
    Unsubscribe(mIdentity);
    UnsubscribeCW(mSegments);
    UnsubscribeCW(mSphere);
}
//----------------------------------------------------------------------------
MinimumVolumeSphere3DWindow::MinimumVolumeSphere3DWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f),
    mIdentity(Matrix4x4<float>::Identity()),
    mNumActive(2),
    mVertices(NUM_POINTS)
{
    std::mt19937 mte;
    std::uniform_real_distribution<float> rnd(-1.0f, 1.0f);
    for (auto& v : mVertices)
    {
        v = Vector3<float>(rnd(mte), rnd(mte), rnd(mte));
    }

    mNoCullWireState.reset(new RasterizerState());
    mNoCullWireState->cullMode = RasterizerState::CULL_NONE;
    mNoCullWireState->fillMode = RasterizerState::FILL_WIREFRAME;
    mEngine->SetRasterizerState(mNoCullWireState);

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(0.0f, 0.0f, -4.0f, 1.0f);
    Vector4<float> camDVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    CreateScene();

    mMVS3(mNumActive, &mVertices[0], mMinimalSphere);
    UpdateScene();

    EnableCameraMotion(0.1f, 0.01f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void MinimumVolumeSphere3DWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    mEngine->ClearBuffers();
    for (int i = 0; i < mNumActive; ++i)
    {
        mEngine->Draw(mPoints[i]);
    }
    mEngine->Draw(mSegments);
    mEngine->Draw(mSphere);
    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool MinimumVolumeSphere3DWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'n':
    case 'N':
        if (mNumActive < NUM_POINTS)
        {
            mMVS3(++mNumActive, &mVertices[0], mMinimalSphere);
            UpdateScene();
        }
        return true;
    }

    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
void MinimumVolumeSphere3DWindow::CreateScene()
{
    // Create the points.
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);

    MeshFactory mf;
    mf.SetVertexFormat(vformat);

    std::shared_ptr<ConstantColorEffect> effect(new ConstantColorEffect(
        Vector4<float>(0.5f, 0.5f, 0.5f, 1.0f)));
    Subscribe(mIdentity, effect->GetPVWMatrixConstant());

    for (int i = 0; i < NUM_POINTS; ++i)
    {
        mPoints[i] = mf.CreateSphere(6, 6, 0.01f);
        mPoints[i]->SetEffect(effect);

        std::shared_ptr<VertexBuffer> vbuffer = mPoints[i]->GetVertexBuffer();
        Vector3<float>* vertex = vbuffer->Get<Vector3<float>>();
        Vector3<float> offset = mVertices[i];
        for (unsigned int j = 0; j < vbuffer->GetNumElements(); ++j)
        {
            vertex[j] += offset;
        }
    }

    // Create the segments.
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat, 12));
    vbuffer->SetUsage(Resource::DYNAMIC_UPDATE);
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(
        IP_POLYSEGMENT_DISJOINT, 6));
    effect.reset(new ConstantColorEffect(
        Vector4<float>(0.5f, 0.0f, 0.0f, 1.0f)));
    mSegments.reset(new Visual(vbuffer, ibuffer, effect));
    SubscribeCW(mSegments, effect->GetPVWMatrixConstant());
    mSegments->Update();

    // Create the sphere.
    mSphere = mf.CreateSphere(16, 16, 1.0f);

    effect.reset(new ConstantColorEffect(
        Vector4<float>(0.0f, 0.0f, 0.5f, 1.0f)));

    mSphere->SetEffect(effect);
    SubscribeCW(mSphere, effect->GetPVWMatrixConstant());
}
//----------------------------------------------------------------------------
void MinimumVolumeSphere3DWindow::UpdateScene()
{
    // Update the segments.
    std::shared_ptr<VertexBuffer> vbuffer = mSegments->GetVertexBuffer();
    Vector3<float>* vertex = vbuffer->Get<Vector3<float>>();
    std::shared_ptr<IndexBuffer> ibuffer = mSegments->GetIndexBuffer();

    int numSupport = mMVS3.GetNumSupport();
    std::array<int, 4> support = mMVS3.GetSupport();

    if (numSupport >= 2)
    {
        vertex[0] = mVertices[support[0]];
        vertex[1] = mVertices[support[1]];
        vbuffer->SetNumActiveElements(2);
    }

    if (numSupport >= 3)
    {
        vertex[2] = mVertices[support[1]];
        vertex[3] = mVertices[support[2]];
        vertex[4] = mVertices[support[2]];
        vertex[5] = mVertices[support[0]];
        vbuffer->SetNumActiveElements(6);
    }

    if (numSupport == 4)
    {
        vertex[ 6] = mVertices[support[3]];
        vertex[ 7] = mVertices[support[0]];
        vertex[ 8] = mVertices[support[3]];
        vertex[ 9] = mVertices[support[1]];
        vertex[10] = mVertices[support[3]];
        vertex[11] = mVertices[support[2]];
        vbuffer->SetNumActiveElements(12);
    }

    mEngine->Update(vbuffer);

    // Update the sphere.
    mSphere->localTransform.SetTranslation(mMinimalSphere.center);
    mSphere->localTransform.SetScale(mMinimalSphere.radius);
    mSphere->Update();

    UpdateCW();
}
//----------------------------------------------------------------------------
