// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.3.3 (2014/09/25)

#include "GenerateMeshUVsWindow.h"
#include <iostream>

//----------------------------------------------------------------------------
GenerateMeshUVsWindow::~GenerateMeshUVsWindow()
{
    UnsubscribeCW(mMeshOriginal);
    UnsubscribeCW(mMeshResampled);
}
//----------------------------------------------------------------------------
GenerateMeshUVsWindow::GenerateMeshUVsWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f),
    mDrawMeshOriginal(true)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    mNoCullState.reset(new RasterizerState());
    mNoCullState->cullMode = RasterizerState::CULL_NONE;
    mNoCullWireState.reset(new RasterizerState());
    mNoCullWireState->fillMode = RasterizerState::FILL_WIREFRAME;
    mNoCullWireState->cullMode = RasterizerState::CULL_NONE;
    mEngine->SetRasterizerState(mNoCullState);

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 1000.0f);
    Vector4<float> camPosition(-3.0f, 0.0f, 0.0f, 1.0f);
    Vector4<float> camDVector(1.0f, 0.0f, 0.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    CreateMeshOriginal();
    CreateMeshResampled();

    EnableCameraMotion(0.001f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void GenerateMeshUVsWindow::OnDisplay()
{
    mEngine->ClearBuffers();
    if (mDrawMeshOriginal)
    {
        mEngine->Draw(mMeshOriginal);
    }
    else
    {
        mEngine->Draw(mMeshResampled);
    }
    mEngine->DisplayColorBuffer(0);
}
//----------------------------------------------------------------------------
void GenerateMeshUVsWindow::OnIdle()
{
    if (MoveCamera())
    {
        OnDisplay();
    }
}
//----------------------------------------------------------------------------
bool GenerateMeshUVsWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        if (mNoCullState == mEngine->GetRasterizerState())
        {
            mEngine->SetRasterizerState(mNoCullWireState);
        }
        else
        {
            mEngine->SetRasterizerState(mNoCullState);
        }
        OnDisplay();
        return true;
    case 'm':
    case 'M':
        mDrawMeshOriginal = !mDrawMeshOriginal;
        OnDisplay();
        return true;
    }
    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool GenerateMeshUVsWindow::OnMouseClick(MouseButton button, MouseState state,
    int x, int y, unsigned int modifiers)
{
    OnDisplay();
    return Window::OnMouseClick(button, state, x, y, modifiers);
}
//----------------------------------------------------------------------------
bool GenerateMeshUVsWindow::OnMouseMotion(MouseButton button, int x, int y,
    unsigned int modifiers)
{
    OnDisplay();
    return Window::OnMouseMotion(button, x, y, modifiers);
}
//----------------------------------------------------------------------------
bool GenerateMeshUVsWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }
    mEnvironment.Insert(path + "/Samples/Data/");

    if (mEnvironment.GetPath("MedicineBag.jpg") == "")
    {
        LogError("Cannot find file MedicineBag.jpg.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void GenerateMeshUVsWindow::CreateMeshOriginal()
{
    std::mt19937 mte;
    std::uniform_real_distribution<float> rnd(-1.0f, 1.0f);

    // Generate a perturbed hemisphere.
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_TEXCOORD, DF_R32G32_FLOAT, 0);
    MeshFactory mf;
    mf.SetVertexFormat(vformat);
    mMeshOriginal = mf.CreateDisk(16, 16, 1.0f);
    float height = 0.25f;
    float radius = sqrt(1.0f - height*height);
    std::shared_ptr<VertexBuffer> vbuffer = mMeshOriginal->GetVertexBuffer();
    unsigned int numVertices = vbuffer->GetNumElements();
    Vertex* vertices = vbuffer->Get<Vertex>();
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        // Start with a hemisphere.
        float x = radius * vertices[i].position[0];
        float y = radius * vertices[i].position[1];
        float z = sqrt(std::max(1.0f - x*x - y*y, 0.0f));

        // Perturb points along rays, which preserves non-self-intersection.
        float r = 1.0f + 0.125f*rnd(mte);
        vertices[i].position = r * Vector3<float>(x, y, z);
    }

    std::string path = mEnvironment.GetPath("MedicineBag.jpg");
    std::shared_ptr<Texture2> texture(WICFileIO::Load(path, false));
    std::shared_ptr<Texture2Effect> effect(new Texture2Effect(texture,
        SamplerState::MIN_L_MAG_L_MIP_P, SamplerState::CLAMP,
        SamplerState::CLAMP));
    mMeshOriginal->SetEffect(effect);

    mMeshOriginal->Update();
    SubscribeCW(mMeshOriginal, effect->GetPVWMatrixConstant());
}
//----------------------------------------------------------------------------
void GenerateMeshUVsWindow::CreateMeshResampled()
{
    std::shared_ptr<VertexBuffer> vbuffer = mMeshOriginal->GetVertexBuffer();
    unsigned int numVertices = vbuffer->GetNumElements();
    Vertex* vertices = vbuffer->Get<Vertex>();

    std::shared_ptr<IndexBuffer> ibuffer = mMeshOriginal->GetIndexBuffer();
    int numIndices = (int)ibuffer->GetNumElements();
    int const* indices = ibuffer->Get<int>();
    std::vector<Vector3<double>> dvertices(numVertices);
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            dvertices[i][j] = vertices[i].position[j];
        }
    }

    // Generate texture coordinates.
    std::shared_ptr<GenerateMeshUV<double>::UVComputeModel> cmodel(
        new GenerateMeshUV<double>::UVComputeModel(mEngine, 1, nullptr));

    GenerateMeshUV<double> pm(cmodel);
    std::vector<Vector2<double>> tcoords(numVertices);
    unsigned int numGaussSeidelIterations = 128;
    pm(numGaussSeidelIterations, true, numVertices, &dvertices[0], numIndices,
        indices, &tcoords[0]);

    // Resample the mesh.
    typedef BSNumber<std::vector<uint32_t>> Numeric;
    typedef BSRational<std::vector<uint32_t>> Rational;
    int numTriangles = numIndices / 3;
    PlanarMesh<double, Numeric, Rational> pmesh(numVertices, &tcoords[0],
        numTriangles, &indices[0]);

    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_TEXCOORD, DF_R32G32_FLOAT, 0);
    MeshFactory mf;
    mf.SetVertexFormat(vformat);
    int size = 64;
    double dsize = (double)size;
    mMeshResampled = mf.CreateRectangle(size, size, 1.0f, 1.0f);
    vertices = mMeshResampled->GetVertexBuffer()->Get<Vertex>();

    Vector2<double> P;
    Vector3<double> resampled;
    int triangle = 0;
    std::array<double, 3> bary;
    std::array<int, 3> lookup;
    for (int y = 0; y < size; ++y)
    {
        P[1] = y / dsize;
        for (int x = 0; x < size; ++x)
        {
            P[0] = x / dsize;
            triangle = pmesh.GetContainingTriangle(P, triangle);
            if (triangle >= 0)
            {
                pmesh.GetBarycentrics(triangle, P, bary);
                pmesh.GetIndices(triangle, lookup);
                resampled =
                    bary[0] * dvertices[lookup[0]] +
                    bary[1] * dvertices[lookup[1]] +
                    bary[2] * dvertices[lookup[2]];
                for (int i = 0; i < 3; ++i)
                {
                    vertices[x + size*y].position[i] = (float)resampled[i];
                }
            }
            else
            {
                std::cout << "failed at (" << x << "," << y << ")"
                    << std::endl;
                triangle = 0;
                for (int i = 0; i < 3; ++i)
                {
                    vertices[x + size*y].position[i] = 0.0f;
                }
            }
        }
    }

    std::string path = mEnvironment.GetPath("MedicineBag.jpg");
    std::shared_ptr<Texture2> texture(WICFileIO::Load(path, false));
    std::shared_ptr<Texture2Effect> effect(new Texture2Effect(texture,
        SamplerState::MIN_L_MAG_L_MIP_P, SamplerState::CLAMP,
        SamplerState::CLAMP));
    mMeshResampled->SetEffect(effect);

    mMeshResampled->Update();
    SubscribeCW(mMeshResampled, effect->GetPVWMatrixConstant());
}
//----------------------------------------------------------------------------
