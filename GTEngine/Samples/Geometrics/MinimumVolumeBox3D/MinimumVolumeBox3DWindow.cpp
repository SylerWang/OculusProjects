// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "MinimumVolumeBox3DWindow.h"

//----------------------------------------------------------------------------
MinimumVolumeBox3DWindow::~MinimumVolumeBox3DWindow()
{
    UnsubscribeCW(mPoints);
    Unsubscribe(mScene);
}
//----------------------------------------------------------------------------
MinimumVolumeBox3DWindow::MinimumVolumeBox3DWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f),
    mVertices(NUM_POINTS)
{
    mWireState.reset(new RasterizerState());
    mWireState->cullMode = RasterizerState::CULL_NONE;
    mWireState->fillMode = RasterizerState::FILL_WIREFRAME;
    mEngine->SetRasterizerState(mWireState);

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(0.0f, 0.0f, -2.0f, 1.0f);
    Vector4<float> camDVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    CreateScene();

    EnableCameraMotion(0.001f, 0.01f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void MinimumVolumeBox3DWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    mEngine->ClearBuffers();
    mEngine->Draw(mPoints);
    mEngine->Draw(mPolytope);
    mEngine->Draw(mBoxMesh);
    DrawFrameRate(8, mYSize - 8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
void MinimumVolumeBox3DWindow::CreateScene()
{
    mScene.reset(new Node());

    std::mt19937 mte;
    std::uniform_real_distribution<float> rnd(-1.0f, 1.0f);
    Vector3<double> center(0.0f, 0.0f, 0.0f);
    Vector3<double> extent(1.0f, 0.25f, 0.125f);
    Vector3<double> axis[3] = {
        Vector3<double>(1.0f, 1.0f, 0.0f),
        Vector3<double>(-1.0f, 1.0f, 0.0f),
        Vector3<double>(0.0f, 0.0f, 1.0f)
    };
    Normalize(axis[0]);
    Normalize(axis[1]);
    Normalize(axis[2]);
    for (auto& v : mVertices)
    {
        double theta = rnd(mte) * (double)GTE_C_TWO_PI;
        double phi = rnd(mte) * (double)GTE_C_PI;
        double radius = 0.5f * (rnd(mte) + 1.0f);
        double x = extent[0] * cos(theta) * sin(phi);
        double y = extent[1] * sin(theta) * sin(phi);
        double z = extent[2] * cos(phi);
        v = center + radius * (x * axis[0] + y * axis[1] + z * axis[2]);
    }

    struct Vertex
    {
        Vector3<float> position;
        Vector4<float> color;
    };
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_COLOR, DF_R32G32B32A32_FLOAT, 0);
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat,
        NUM_POINTS));
    Vertex* vertex = vbuffer->Get<Vertex>();
    for (int i = 0; i < NUM_POINTS; ++i)
    {
        vertex[i].position[0] = (float)mVertices[i][0];
        vertex[i].position[1] = (float)mVertices[i][1];
        vertex[i].position[2] = (float)mVertices[i][2];
        vertex[i].color[0] = 0.5f * (rnd(mte) + 1.0f);
        vertex[i].color[1] = 0.5f * (rnd(mte) + 1.0f);
        vertex[i].color[2] = 0.5f * (rnd(mte) + 1.0f);
        vertex[i].color[3] = 1.0f;
    }

    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_POLYPOINT,
        NUM_POINTS));

    std::shared_ptr<VertexColorEffect> effect(new VertexColorEffect());

    mPoints.reset(new Visual(vbuffer, ibuffer, effect));
    Subscribe(mPoints->worldTransform, effect->GetPVWMatrixConstant());
    mScene->AttachChild(mPoints);

    OrientedBox3<double> minBox;
    mMVB3(NUM_POINTS, &mVertices[0], 0.0, minBox);

    std::vector<int> const& hull = mMVB3.GetHull();
    ibuffer.reset(new IndexBuffer(IP_TRIMESH,
        static_cast<int>(hull.size() / 3), sizeof(int)));
    memcpy(ibuffer->GetData(), &hull[0], ibuffer->GetNumBytes());
    mPolytope.reset(new Visual(vbuffer, ibuffer, effect));
    mScene->AttachChild(mPolytope);

    double dot;
    dot = Dot(minBox.axis[0], minBox.axis[0]);
    dot = Dot(minBox.axis[0], minBox.axis[1]);
    dot = Dot(minBox.axis[0], minBox.axis[2]);
    dot = Dot(minBox.axis[1], minBox.axis[1]);
    dot = Dot(minBox.axis[1], minBox.axis[2]);
    dot = Dot(minBox.axis[2], minBox.axis[2]);

    vbuffer.reset(new VertexBuffer(vformat, 8));
    vertex = vbuffer->Get<Vertex>();
    Vector3<double> corner[8];
    minBox.GetVertices(corner);
    for (int i = 0; i < 8; ++i)
    {
        vertex[i].position[0] = (float)corner[i][0];
        vertex[i].position[1] = (float)corner[i][1];
        vertex[i].position[2] = (float)corner[i][2];
        vertex[i].color[0] = 0.5f * (rnd(mte) + 1.0f);
        vertex[i].color[1] = 0.5f * (rnd(mte) + 1.0f);
        vertex[i].color[2] = 0.5f * (rnd(mte) + 1.0f);
        vertex[i].color[3] = 1.0f;
    }

    ibuffer.reset(new IndexBuffer(IP_TRIMESH, 12, sizeof(int)));
    int* indices = ibuffer->Get<int>();
    indices[ 0] = 0;  indices[ 1] = 2;  indices[ 2] = 1;
    indices[ 3] = 0;  indices[ 4] = 3;  indices[ 5] = 2;
    indices[ 6] = 4;  indices[ 7] = 5;  indices[ 8] = 6;
    indices[ 9] = 4;  indices[10] = 6;  indices[11] = 7;
    indices[12] = 0;  indices[13] = 5;  indices[14] = 4;
    indices[15] = 0;  indices[16] = 1;  indices[17] = 5;
    indices[18] = 3;  indices[19] = 7;  indices[20] = 6;
    indices[21] = 3;  indices[22] = 6;  indices[23] = 2;
    indices[24] = 0;  indices[25] = 4;  indices[26] = 7;
    indices[27] = 0;  indices[28] = 7;  indices[29] = 3;
    indices[30] = 1;  indices[31] = 6;  indices[32] = 5;
    indices[33] = 1;  indices[34] = 2;  indices[35] = 6;

    mBoxMesh.reset(new Visual(vbuffer, ibuffer, effect));
    mScene->AttachChild(mBoxMesh);

    mScene->Update();
    Subscribe(mScene);
}
//----------------------------------------------------------------------------
