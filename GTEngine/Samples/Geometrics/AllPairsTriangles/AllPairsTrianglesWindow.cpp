// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "AllPairsTrianglesWindow.h"

//----------------------------------------------------------------------------
AllPairsTrianglesWindow::~AllPairsTrianglesWindow()
{
}
//----------------------------------------------------------------------------
AllPairsTrianglesWindow::AllPairsTrianglesWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 1.0f, 1000.0f);
    Vector4<float> camPosition(8.0f, 0.0f, 0.0f, 1.0f);
    Vector4<float> camDVector(-1.0f, 0.0f, 0.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    int const count = 48;
    CreateCylinder(count, count, 1.0f, 8.0f);   // 4416 triangles
    CreateTorus(count, count, 2.0f, 0.5f);      // 4608 triangles

#ifndef USE_CPU_FIND_INTERSECTIONS
    CreateShaders();
#endif

    mWireState.reset(new RasterizerState());
    mWireState->fillMode = RasterizerState::FILL_WIREFRAME;

    EnableCameraMotion(0.1f, 0.01f, 2.0f, 2.0f);
    EnableObjectMotion();
}
//----------------------------------------------------------------------------
void AllPairsTrianglesWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();
    UpdateTransforms();
    FindIntersections();

    mEngine->ClearBuffers();
#ifdef USE_CPU_FIND_INTERSECTIONS
    mEngine->Draw(mCylinder);
    mEngine->Draw(mTorus);
#else
    mEngine->Draw(mCylinderID);
    mEngine->Draw(mTorusID);
#endif
    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool AllPairsTrianglesWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        if (mEngine->GetRasterizerState() != mWireState)
        {
            mEngine->SetRasterizerState(mWireState);
        }
        else
        {
            mEngine->SetDefaultRasterizerState();
        }
        return true;
    }
    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool AllPairsTrianglesWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }
    mEnvironment.Insert(
        path + "/Samples/Geometrics/AllPairsTriangles/Shaders/");

    if (mEnvironment.GetPath("DrawUsingVertexID.hlsl") == "")
    {
        LogError("Cannot find file DrawUsingVertexID.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("InitializeColors.hlsl") == "")
    {
        LogError("Cannot find file InitializeColors.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("TriangleIntersection.hlsl") == "")
    {
        LogError("Cannot find file TriangleIntersection.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("VertexColorIndexed.hlsl") == "")
    {
        LogError("Cannot find file VertexColorIndexed.hlsl.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void AllPairsTrianglesWindow::CreateCylinder(unsigned int numAxisSamples,
    unsigned int numRadialSamples, float radius, float height)
{
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    MeshFactory mf;
    mf.SetVertexFormat(vformat);
    mf.SetIndexFormat(true);

    std::shared_ptr<Visual> cylinder = mf.CreateCylinderClosed(
        numAxisSamples, numRadialSamples, radius, height);
    std::shared_ptr<VertexBuffer> vbuffer = cylinder->GetVertexBuffer();
    Vector3<float>* vertices = vbuffer->Get<Vector3<float>>();
    std::shared_ptr<IndexBuffer> ibuffer = cylinder->GetIndexBuffer();
    unsigned int numIndices = ibuffer->GetNumElements();
    unsigned int* indices = ibuffer->Get<unsigned int>();

    VertexFormat meshVFormat;
    meshVFormat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    meshVFormat.Bind(VA_COLOR, DF_R32_UINT, 0);
    std::shared_ptr<VertexBuffer> meshVBuffer(new VertexBuffer(meshVFormat,
        numIndices));
    meshVBuffer->SetUsage(Resource::DYNAMIC_UPDATE);
    Vertex* meshVertices = meshVBuffer->Get<Vertex>();
    for (unsigned int i = 0; i < numIndices; ++i)
    {
        meshVertices[i].position = vertices[indices[i]];
        meshVertices[i].colorIndex = 0;
    }
    std::shared_ptr<IndexBuffer> meshIBuffer(new IndexBuffer(IP_TRIMESH,
        numIndices / 3));

    std::shared_ptr<VertexShader> vshader(ShaderFactory::CreateVertex(
        mEnvironment.GetPath("VertexColorIndexed.hlsl")));
    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("VertexColorIndexed.hlsl")));
    mCylinderPVWMatrix.reset(new ConstantBuffer(sizeof(Matrix4x4<float>),
        true));
    vshader->Set("PVWMatrix", mCylinderPVWMatrix);
    mCylinderEffect.reset(new VisualEffect(vshader, pshader));

    mCylinder.reset(new Visual(meshVBuffer, meshIBuffer, mCylinderEffect));
    mNumCylinderTriangles = numIndices / 3;
}
//----------------------------------------------------------------------------
void AllPairsTrianglesWindow::CreateTorus(unsigned int numCircleSamples,
    unsigned int numRadialSamples, float outerRadius, float innerRadius)
{
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    MeshFactory mf;
    mf.SetVertexFormat(vformat);
    mf.SetIndexFormat(true);

    std::shared_ptr<Visual> cylinder = mf.CreateTorus(
        numCircleSamples, numRadialSamples, outerRadius, innerRadius);
    std::shared_ptr<VertexBuffer> vbuffer = cylinder->GetVertexBuffer();
    Vector3<float>* vertices = vbuffer->Get<Vector3<float>>();
    std::shared_ptr<IndexBuffer> ibuffer = cylinder->GetIndexBuffer();
    unsigned int numIndices = ibuffer->GetNumElements();
    unsigned int* indices = ibuffer->Get<unsigned int>();

    VertexFormat meshVFormat;
    meshVFormat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    meshVFormat.Bind(VA_COLOR, DF_R32_UINT, 0);
    std::shared_ptr<VertexBuffer> meshVBuffer(new VertexBuffer(meshVFormat,
        numIndices));
    meshVBuffer->SetUsage(Resource::DYNAMIC_UPDATE);
    Vertex* meshVertices = meshVBuffer->Get<Vertex>();
    for (unsigned int i = 0; i < numIndices; ++i)
    {
        meshVertices[i].position = vertices[indices[i]];
        meshVertices[i].colorIndex = 1;
    }
    std::shared_ptr<IndexBuffer> meshIBuffer(new IndexBuffer(IP_TRIMESH,
        numIndices / 3));

    std::shared_ptr<VertexShader> vshader(ShaderFactory::CreateVertex(
        mEnvironment.GetPath("VertexColorIndexed.hlsl")));
    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("VertexColorIndexed.hlsl")));
    mTorusPVWMatrix.reset(new ConstantBuffer(sizeof(Matrix4x4<float>),
        true));
    vshader->Set("PVWMatrix", mTorusPVWMatrix);
    mTorusEffect.reset(new VisualEffect(vshader, pshader));

    mTorus.reset(new Visual(meshVBuffer, meshIBuffer, mTorusEffect));
    mNumTorusTriangles = numIndices / 3;
}
//----------------------------------------------------------------------------
void AllPairsTrianglesWindow::UpdateTransforms()
{
    Matrix4x4<float> pvMatrix = mCamera.GetProjectionViewMatrix();
    Matrix4x4<float> pvwMatrix;
#if defined(GTE_USE_MAT_VEC)
    pvwMatrix = pvMatrix*GetTrackballRotation();
#else
    pvwMatrix = GetTrackballRotation()*pvMatrix;
#endif
    mCylinderPVWMatrix->SetMember("pvwMatrix", pvMatrix);
    mTorusPVWMatrix->SetMember("pvwMatrix", pvwMatrix);
    mEngine->Update(mCylinderPVWMatrix);
    mEngine->Update(mTorusPVWMatrix);

#ifndef USE_CPU_FIND_INTERSECTIONS
    TIParameters& data = *mTIParameters->Get<TIParameters>();
    data.wMatrix0 = Matrix4x4<float>::Identity();
    data.wMatrix1 = GetTrackballRotation();
    mEngine->Update(mTIParameters);

    std::shared_ptr<ConstantBuffer> cbuffer;
    cbuffer = mCylinderIDEffect->GetVertexShader()->Get<ConstantBuffer>(
        "PVWMatrix");
    *cbuffer->Get<Matrix4x4<float>>() = pvMatrix;
    mEngine->Update(cbuffer);
    cbuffer = mTorusIDEffect->GetVertexShader()->Get<ConstantBuffer>(
        "PVWMatrix");
    *cbuffer->Get<Matrix4x4<float>>() = pvwMatrix;
    mEngine->Update(cbuffer);
#endif
}
//----------------------------------------------------------------------------
void AllPairsTrianglesWindow::FindIntersections()
{
#ifdef USE_CPU_FIND_INTERSECTIONS
    std::shared_ptr<VertexBuffer> buffer0 = mCylinder->GetVertexBuffer();
    unsigned int numVertices0 = buffer0->GetNumElements();
    unsigned int numTriangles0 = numVertices0 / 3;
    Vertex* vertices0 = buffer0->Get<Vertex>();
    for (unsigned int i = 0; i < numVertices0; ++i)
    {
        vertices0[i].colorIndex = 0;
    }

    std::shared_ptr<VertexBuffer> buffer1 = mTorus->GetVertexBuffer();
    unsigned int numVertices1 = buffer1->GetNumElements();
    unsigned int numTriangles1 = numVertices1 / 3;
    Vertex* vertices1 = buffer1->Get<Vertex>();
    for (unsigned int i = 0; i < numVertices1; ++i)
    {
        vertices1[i].colorIndex = 1;
    }

    TriangleIntersection intersects;
    Vector3<float> cylinder[3], torus[3];
    for (unsigned int t0 = 0; t0 < numTriangles0; ++t0)
    {
        for (int j = 0; j < 3; ++j)
        {
            cylinder[j] = vertices0[3 * t0 + j].position;
        }

        for (unsigned int t1 = 0; t1 < numTriangles1; ++t1)
        {
            for (int j = 0; j < 3; ++j)
            {
                Vector3<float> pos3 = vertices1[3 * t1 + j].position;
                Vector4<float> pos4(pos3[0], pos3[1], pos3[2], 1.0f);
#if defined(GTE_USE_MAT_VEC)
                pos4 = GetTrackballRotation()*pos4;
#else
                pos4 = pos4*GetTrackballRotation();
#endif
                pos3 = Vector3<float>(pos4[0], pos4[1], pos4[2]);
                torus[j] = pos3;
            }

            if (intersects(cylinder, torus))
            {
                for (int j = 0; j < 3; ++j)
                {
                    vertices0[3 * t0 + j].colorIndex = 2;
                    vertices1[3 * t1 + j].colorIndex = 3;
                }
            }
        }
    }

    mEngine->Update(buffer0);
    mEngine->Update(buffer1);
#else
    mEngine->Execute(mInitializeColor, mNumXGroups, mNumYGroups, 1);
    mEngine->Execute(mTriangleIntersection, mNumXGroups, mNumYGroups, 1);
#endif
}
//----------------------------------------------------------------------------
#ifndef USE_CPU_FIND_INTERSECTIONS
//----------------------------------------------------------------------------
void AllPairsTrianglesWindow::CreateShaders()
{
    unsigned int const numIndices0 = 3 * mNumCylinderTriangles;
    unsigned int const numIndices1 = 3 * mNumTorusTriangles;

    mColor0Buffer.reset(new StructuredBuffer(numIndices0,
        sizeof(unsigned int)));
    mColor0Buffer->SetUsage(Resource::SHADER_OUTPUT);
    mColor0Buffer->SetCopyType(Resource::COPY_STAGING_TO_CPU);

    mColor1Buffer.reset(new StructuredBuffer(numIndices1,
        sizeof(unsigned int)));
    mColor1Buffer->SetUsage(Resource::SHADER_OUTPUT);
    mColor1Buffer->SetCopyType(Resource::COPY_STAGING_TO_CPU);

    mTIParameters.reset(new ConstantBuffer(sizeof(TIParameters), true));
    TIParameters& data = *mTIParameters->Get<TIParameters>();
    data.wMatrix0 = Matrix4x4<float>::Identity();
    data.wMatrix1 = Matrix4x4<float>::Identity();
    data.numTriangles0 = mNumCylinderTriangles;
    data.numTriangles1 = mNumTorusTriangles;

    mVertices0.reset(new StructuredBuffer(numIndices0,
        sizeof(Vector3<float>)));
    Vector3<float>* data0 = mVertices0->Get<Vector3<float>>();
    Vertex* meshVertices0 = mCylinder->GetVertexBuffer()->Get<Vertex>();
    for (unsigned int i = 0; i < numIndices0; ++i)
    {
        data0[i] = meshVertices0[i].position;
    }

    mVertices1.reset(new StructuredBuffer(numIndices1,
        sizeof(Vector3<float>)));
    Vector3<float>* data1 = mVertices1->Get<Vector3<float>>();
    Vertex* meshVertices1 = mTorus->GetVertexBuffer()->Get<Vertex>();
    for (unsigned int i = 0; i < numIndices1; ++i)
    {
        data1[i] = meshVertices1[i].position;
    }

    unsigned int const numThreads = 8;
    mNumXGroups = mNumCylinderTriangles / numThreads;
    mNumYGroups = mNumTorusTriangles / numThreads;
    HLSLDefiner definer;
    definer.SetInt("NUM_X_THREADS", numThreads);
    definer.SetInt("NUM_Y_THREADS", numThreads);

    mInitializeColor.reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("InitializeColors.hlsl"), definer));
    mInitializeColor->Set("color0", mColor0Buffer);
    mInitializeColor->Set("color1", mColor1Buffer);

    mTriangleIntersection.reset(ShaderFactory::CreateCompute(
        mEnvironment.GetPath("TriangleIntersection.hlsl"), definer));
    mTriangleIntersection->Set("Parameters", mTIParameters);
    mTriangleIntersection->Set("vertices0", mVertices0);
    mTriangleIntersection->Set("vertices1", mVertices1);
    mTriangleIntersection->Set("color0", mColor0Buffer);
    mTriangleIntersection->Set("color1", mColor1Buffer);

    std::shared_ptr<ConstantBuffer> cbuffer(new ConstantBuffer(
        sizeof(Matrix4x4<float>), true));
    std::shared_ptr<VertexShader> vshader(ShaderFactory::CreateVertex(
        mEnvironment.GetPath("DrawUsingVertexID.hlsl")));
    vshader->Set("PVWMatrix", cbuffer);
    vshader->Set("positions", mVertices0);
    vshader->Set("colorIndices", mColor0Buffer);
    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("DrawUsingVertexID.hlsl")));
    mCylinderIDEffect.reset(new VisualEffect(vshader, pshader));
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(numIndices0));
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_TRIMESH,
        numIndices0 / 3));
    mCylinderID.reset(new Visual(vbuffer, ibuffer, mCylinderIDEffect));

    cbuffer.reset(new ConstantBuffer(sizeof(Matrix4x4<float>), true));
    vshader.reset(ShaderFactory::CreateVertex(
        mEnvironment.GetPath("DrawUsingVertexID.hlsl")));
    vshader->Set("PVWMatrix", cbuffer);
    vshader->Set("positions", mVertices1);
    vshader->Set("colorIndices", mColor1Buffer);
    pshader.reset(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("DrawUsingVertexID.hlsl")));
    mTorusIDEffect.reset(new VisualEffect(vshader, pshader));
    vbuffer.reset(new VertexBuffer(numIndices1));
    ibuffer.reset(new IndexBuffer(IP_TRIMESH, numIndices1 / 3));
    mTorusID.reset(new Visual(vbuffer, ibuffer, mTorusIDEffect));
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
