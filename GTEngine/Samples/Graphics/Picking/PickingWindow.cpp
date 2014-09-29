// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.2.2 (2014/09/14)

#include "PickingWindow.h"

//----------------------------------------------------------------------------
PickingWindow::~PickingWindow()
{
    Unsubscribe(mTorus->worldTransform);
    Unsubscribe(mDodecahedron->worldTransform);
    Unsubscribe(mPoints->worldTransform);
    Unsubscribe(mSegments->worldTransform);
    for (int i = 0; i < SPHERE_BUDGET; ++i)
    {
        Unsubscribe(mSphere[i]->worldTransform);
    }
    Unsubscribe(mScene);
}
//----------------------------------------------------------------------------
PickingWindow::PickingWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f),
    mNumActiveSpheres(0)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    CreateScene();

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(-16.0f, 0.0f, 2.0f, 1.0f);
    Vector4<float> camDVector(1.0f, 0.0f, 0.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    EnableCameraMotion(0.01f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void PickingWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    mEngine->ClearBuffers();
    mEngine->Draw(mTorus);
    mEngine->Draw(mDodecahedron);
    mEngine->Draw(mPoints);
    mEngine->Draw(mSegments);
    for (int i = 0; i < mNumActiveSpheres; ++i)
    {
        mEngine->Draw(mSphere[i]);
    }
    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool PickingWindow::OnMouseClick(MouseButton button, MouseState state,
    int x, int y, unsigned int modifiers)
{
    if (button == MOUSE_RIGHT && state == MOUSE_DOWN)
    {
        DoPick(x, mYSize - 1 - y);
        return true;
    }

    return Window::OnMouseClick(button, state, x, y, modifiers);
}
//----------------------------------------------------------------------------
bool PickingWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }

    mEnvironment.Insert(path + "/Samples/Data/");

    if (mEnvironment.GetPath("Checkerboard.png") == "")
    {
        LogError("Cannot open file Checkerboard.png.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void PickingWindow::CreateScene()
{
    std::string path = mEnvironment.GetPath("Checkerboard.png");
    std::shared_ptr<Texture2> texture(WICFileIO::Load(path, false));

    mScene.reset(new Node());

    VertexFormat vformat0;
    vformat0.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat0.Bind(VA_TEXCOORD, DF_R32G32_FLOAT, 0);

    // The torus and dodecahedron are created by the mesh factory in which
    // the 'visual' model bounds are computed.  The points and segments
    // primitives are created explicitly here, so we need to compute their
    // model bounds to be used by the picking system.
    MeshFactory mf;
    mf.SetVertexFormat(vformat0);

    mTorus = mf.CreateTorus(16, 16, 4.0f, 1.0f);
    std::shared_ptr<Texture2Effect> effect(new Texture2Effect(texture,
        SamplerState::MIN_L_MAG_L_MIP_P, SamplerState::CLAMP,
        SamplerState::CLAMP));
    mTorus->SetEffect(effect);
    Subscribe(mTorus->worldTransform, effect->GetPVWMatrixConstant());
    mScene->AttachChild(mTorus);

    mDodecahedron = mf.CreateDodecahedron();
    effect.reset(new Texture2Effect(texture, SamplerState::MIN_L_MAG_L_MIP_P,
        SamplerState::CLAMP, SamplerState::CLAMP));
    mDodecahedron->SetEffect(effect);
    Subscribe(mDodecahedron->worldTransform, effect->GetPVWMatrixConstant());
    mScene->AttachChild(mDodecahedron);

    VertexFormat vformat1;
    vformat1.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat1, 4));
    Vector3<float>* vertices = vbuffer->Get<Vector3<float>>();
    vertices[0] = Vector3<float>(1.0f, 1.0f, 4.0f);
    vertices[1] = Vector3<float>(1.0f, 2.0f, 5.0f);
    vertices[2] = Vector3<float>(2.0f, 2.0f, 6.0f);
    vertices[3] = Vector3<float>(2.0f, 1.0f, 7.0f);
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_POLYPOINT, 4));
    std::shared_ptr<ConstantColorEffect> cceffect(new ConstantColorEffect(
        Vector4<float>(0.5f, 0.0f, 0.0f, 1.0f)));
    mPoints.reset(new Visual(vbuffer, ibuffer, cceffect));
    mPoints->UpdateModelBound();
    Subscribe(mPoints->worldTransform, cceffect->GetPVWMatrixConstant());
    mScene->AttachChild(mPoints);

    vbuffer.reset(new VertexBuffer(vformat1, 4));
    vertices = vbuffer->Get<Vector3<float>>();
    vertices[0] = Vector3<float>(-1.0f, -1.0f, 4.0f);
    vertices[1] = Vector3<float>(-1.0f, -2.0f, 5.0f);
    vertices[2] = Vector3<float>(-2.0f, -1.0f, 6.0f);
    vertices[3] = Vector3<float>(-2.0f, -2.0f, 7.0f);
    ibuffer.reset(new IndexBuffer(IP_POLYSEGMENT_CONTIGUOUS, 3, sizeof(int)));
    ibuffer->SetSegment(0, 0, 1);
    ibuffer->SetSegment(1, 1, 2);
    ibuffer->SetSegment(2, 2, 3);
    cceffect.reset(new ConstantColorEffect(
        Vector4<float>(0.0f, 0.0f, 0.5f, 1.0f)));
    mSegments.reset(new Visual(vbuffer, ibuffer, cceffect));
    mSegments->UpdateModelBound();
    Subscribe(mSegments->worldTransform, cceffect->GetPVWMatrixConstant());
    mScene->AttachChild(mSegments);

    for (int i = 0; i < SPHERE_BUDGET; ++i)
    {
        mSphere[i] = mf.CreateSphere(8, 8, 0.125f);
        cceffect.reset(new ConstantColorEffect(
            Vector4<float>(0.0f, 0.0f, 0.0f, 1.0f)));
        mSphere[i]->SetEffect(cceffect);
        Subscribe(mSphere[i]->worldTransform,
            cceffect->GetPVWMatrixConstant());
        mScene->AttachChild(mSphere[i]);
    }

    mScene->Update();
    Subscribe(mScene);
}
//----------------------------------------------------------------------------
void PickingWindow::DoPick(int x, int y)
{
    Vector4<float> origin, direction;
    if (GetPickLine(x, y, origin, direction))
    {
        // Use a ray for picking.
        float tmin = 0.0f, tmax = std::numeric_limits<float>::max();

        // Set the distance tolerance for point and segment primitives.
        mPicker.SetMaxDistance(0.0625f);

        // Request the results in model-space coordinates.  All the objects
        // in the scene have the same model space, so we can set the sphere
        // centers in model-space coordinates.
        mPicker(mScene, origin, direction, tmin, tmax, false);
        mNumActiveSpheres = std::min((int)mPicker.records.size(),
            (int)SPHERE_BUDGET);
        if (mNumActiveSpheres > 0)
        {
            // Place spheres at the picked locations.
            for (int i = 0; i < mNumActiveSpheres; ++i)
            {
                mSphere[i]->localTransform.SetTranslation(
                    mPicker.records[i].primitivePoint);
            }

            mScene->Update();
            UpdateCW();
        }
    }
}
//----------------------------------------------------------------------------
