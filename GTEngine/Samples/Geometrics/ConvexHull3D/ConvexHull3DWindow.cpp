// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#include "ConvexHull3DWindow.h"

//----------------------------------------------------------------------------
ConvexHull3DWindow::~ConvexHull3DWindow()
{
    UnsubscribeCW(mMesh);
}
//----------------------------------------------------------------------------
ConvexHull3DWindow::ConvexHull3DWindow(Parameters& parameters)
    :
    Window(parameters),
    mFileQuantity(46),
    mCurrentFile(1),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 1.0f, 5000.0f);
    Vector4<float> camPosition(0.0f, 0.0f, -4.0f, 1.0f);
    Vector4<float> camDVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);
    EnableCameraMotion(0.1f, 0.01f, 2.0f, 2.0f);

    mEffect.reset(new VertexColorEffect());
    if (!LoadData())
    {
        parameters.created = false;
        return;
    }

    mWireState.reset(new RasterizerState());
    mWireState->cullMode = RasterizerState::CULL_NONE;
    mWireState->fillMode = RasterizerState::FILL_WIREFRAME;

    EnableObjectMotion();
}
//----------------------------------------------------------------------------
void ConvexHull3DWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    mEngine->ClearBuffers();

    if (mMesh)
    {
        mEngine->Draw(mMesh);
    }

    if (mMessage != "")
    {
        mEngine->Draw(8, 16, mTextColor, mMessage);
    }

    DrawFrameRate(8, mYSize-8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool ConvexHull3DWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':  // Load a new data set.
    case 'D':
        if (++mCurrentFile == mFileQuantity)
        {
            mCurrentFile = 1;
        }

        LoadData();
        return true;

    case 'w':  // Toggle solid-wire mode.
    case 'W':
        if (mWireState == mEngine->GetRasterizerState())
        {
            mEngine->SetDefaultRasterizerState();
        }
        else
        {
            mEngine->SetRasterizerState(mWireState);
        }
        return true;
    }

    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool ConvexHull3DWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }

    mEnvironment.Insert(path + "/Samples/Geometrics/ConvexHull3D/Data/");
    return true;
}
//----------------------------------------------------------------------------
bool ConvexHull3DWindow::LoadData()
{
    std::string filename = "data";
    if (mCurrentFile < 10)
    {
        filename += "0";
    }
    else
    {
    }
    filename += std::to_string(mCurrentFile) + ".txt";
    std::string path = mEnvironment.GetPath(filename);
    if (path == "")
    {
        return false;
    }

    std::ifstream input(path);
    if (!input)
    {
        return false;
    }

    Vector3<float> center(0.0f, 0.0f, 0.0f);
    unsigned int numVertices;
    input >> numVertices;
    std::vector<Vector3<float>> vertices(numVertices);
    for (auto& v : vertices)
    {
        for (int j = 0; j < 3; ++j)
        {
            input >> v[j];
        }
        center += v;
    }
    input.close();
    center /= static_cast<float>(numVertices);

    float radius = 0.0f;
    for (auto const& v : vertices)
    {
        Vector3<float> diff = v - center;
        float length = Length(diff);
        if (length > radius)
        {
            radius = length;
        }
    }

    // Empirical knowledge.  The data sets loaded lead to no more than a
    // BSUInteger requiring 5 32-bit array elements.
    ConvexHull3<float, BSNumber<BSUInteger<5>>> ch;
    if (numVertices < 4 || !ch(numVertices, &vertices[0], 0.0f))
    {
        if (mMesh)
        {
            UnsubscribeCW(mMesh);
            mMesh = nullptr;
        }

        mMessage = "File = " + std::to_string(mCurrentFile) +
            " has intrinsic dimension " + std::to_string(ch.GetDimension());
        return false;
    }
#if defined(GTE_COLLECT_BSNUMBER_STATISTICS)
    std::cout << "max size = " << gte::gBSNumberMaxSize << std::endl;
#endif

    std::vector<TriangleKey<true>> const& triangles = ch.GetHullUnordered();

    std::mt19937 mte;
    std::uniform_real_distribution<float> rnd(0.0f, 1.0f);

    struct Vertex
    {
        Vector3<float> position;
        Vector4<float> color;
    };
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_COLOR, DF_R32G32B32A32_FLOAT, 0);
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat,
        numVertices));
    Vertex* vertex = vbuffer->Get<Vertex>();
    for (unsigned int i = 0; i < numVertices; ++i)
    {
        vertex[i].position = vertices[i];
        vertex[i].color[0] = rnd(mte);
        vertex[i].color[1] = rnd(mte);
        vertex[i].color[2] = rnd(mte);
        vertex[i].color[3] = 1.0f;
    }

    unsigned int numPrimitives = static_cast<unsigned int>(triangles.size());
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_TRIMESH,
        numPrimitives, sizeof(unsigned int)));
    memcpy(ibuffer->GetData(), &triangles[0], ibuffer->GetNumBytes());

    // Update all information associated with the mesh transforms.
    if (mMesh)
    {
        UnsubscribeCW(mMesh);
    }
    mMesh.reset(new Visual(vbuffer, ibuffer, mEffect));
    mMesh->localTransform.SetTranslation(-center);
    mMesh->worldTransform = mMesh->localTransform;
    SubscribeCW(mMesh, mEffect->GetPVWMatrixConstant());

    // Move the camera for a centered view of the mesh.
    Vector4<float> camPosition = Vector4<float>::Origin()
        - 2.5f*radius*mCamera.GetDVector();
    mCamera.SetPosition(camPosition);

    UpdateCW();

    // Update the message for display.
    mMessage =
        "File = " + std::to_string(mCurrentFile) + " , " +
        "Vertices = " + std::to_string(numVertices) + " , " +
        "Triangles =" + std::to_string(numPrimitives);
    return true;
}
//----------------------------------------------------------------------------
