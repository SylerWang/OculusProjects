// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/16)

#include "RopeWindow.h"

//----------------------------------------------------------------------------
RopeWindow::~RopeWindow()
{
    UnsubscribeCW(mRope);
}
//----------------------------------------------------------------------------
RopeWindow::RopeWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f),
    mLastIdle(0.0)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    mWireState.reset(new RasterizerState());
    mWireState->fillMode = RasterizerState::FILL_WIREFRAME;
    mEngine->SetClearColor(Vector4<float>(0.75f, 0.85f, 0.95f, 1.0f));

    CreateSprings();
    CreateRope();

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 1000.0f);
    Vector4<float> camPosition(0.0f, 1.25f, -0.5f, 1.0f);
    Vector4<float> camDVector(0.0f, -1.0f, 0.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 0.0f, 1.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    EnableCameraMotion(0.01f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void RopeWindow::OnIdle()
{
    MeasureTime();
    MoveCamera();

    double currIdle = mTimer.GetSeconds();
    double diff = currIdle - mLastIdle;
    if (diff >= 0.001)
    {
        mLastIdle = currIdle;
        PhysicsTick();
        GraphicsTick();
    }

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool RopeWindow::OnCharPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':  // toggle wireframe
    case 'W':
        if (mWireState != mEngine->GetRasterizerState())
        {
            mEngine->SetRasterizerState(mWireState);
        }
        else
        {
            mEngine->SetDefaultRasterizerState();
        }
        return true;
    case 'm':  // decrease mass
        if (mModule->GetMass(1) > 0.05f)
        {
            for (int i = 1; i < mModule->GetNumParticles() - 1; ++i)
            {
                mModule->SetMass(i, mModule->GetMass(i) - 0.01f);
            }
        }
        return true;
    case 'M':  // increase mass
        for (int i = 1; i < mModule->GetNumParticles() - 1; ++i)
        {
            mModule->SetMass(i, mModule->GetMass(i) + 0.01f);
        }
        return true;
    case 'c':  // decrease spring constant
        if (mModule->GetConstant(0) > 0.05f)
        {
            for (int i = 0; i < mModule->GetNumSprings(); ++i)
            {
                mModule->SetConstant(i, mModule->GetConstant(i) - 0.01f);
            }
        }
        return true;
    case 'C':  // increase spring constant
        for (int i = 0; i < mModule->GetNumSprings(); ++i)
        {
            mModule->SetConstant(i, mModule->GetConstant(i) + 0.01f);
        }
        return true;
    case 'l':  // decrease spring resting length
        if (mModule->GetLength(0) > 0.05f)
        {
            for (int i = 0; i < mModule->GetNumSprings(); ++i)
            {
                mModule->SetLength(i, mModule->GetLength(i) - 0.01f);
            }
        }
        return true;
    case 'L':  // increase spring resting length
        for (int i = 0; i < mModule->GetNumSprings(); ++i)
        {
            mModule->SetLength(i, mModule->GetLength(i) + 0.01f);
        }
        return true;
    case 'f':  // toggle wind force on/off
    case 'F':
        mModule->enableWind = !mModule->enableWind;
        return true;
    case 'r':  // toggle random wind direction change on/off
    case 'R':
        mModule->enableWindChange = !mModule->enableWindChange;
        return true;
    }

    return Window::OnCharPress(key, x, y);
}
//----------------------------------------------------------------------------
bool RopeWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }
    mEnvironment.Insert(path + "/Samples/Data/");

    if (mEnvironment.GetPath("Rope.bmp") == "")
    {
        LogError("Cannot find file Rope.bmp.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void RopeWindow::CreateSprings()
{
    int numParticles = 8;
    float step = 0.1f;
    Vector3<float> gravity(0.0f, 0.0f, -1.0f);
    Vector3<float> wind(0.0f, -0.25f, 0.0f);
    float windChangeAmplitude = 0.01f;
    float viscosity = 10.0f;
    mModule.reset(new PhysicsModule(numParticles, step, gravity, wind,
        windChangeAmplitude, viscosity));

    // Constant mass at interior points (endpoints are immovable).
    mModule->SetMass(0, std::numeric_limits<float>::max());
    mModule->SetMass(numParticles - 1, std::numeric_limits<float>::max());
    for (int i = 1; i < numParticles - 1; ++i)
    {
        mModule->SetMass(i, 1.0f);
    }

    // Initial position on a horizontal line segment.
    float factor = 1.0f / (float)(numParticles - 1);
    for (int i = 0; i < numParticles; ++i)
    {
        mModule->SetPosition(i, Vector3<float>(i * factor, 0.0f, 1.0f));
    }

    // Initial velocities are all zero.
    for (int i = 0; i < numParticles; ++i)
    {
        mModule->SetVelocity(i, Vector3<float>::Zero());
    }

    // Springs are at rest in the initial horizontal configuration.
    int numSprings = numParticles - 1;
    float restLength = 1.0f / (float)numSprings;
    for (int i = 0; i < numSprings; ++i)
    {
        mModule->SetConstant(i, 10.0f);
        mModule->SetLength(i, restLength);
    }
}
//----------------------------------------------------------------------------
void RopeWindow::CreateRope()
{
    BasisFunctionInput<float> input;
    input.numControls = mModule->GetNumParticles();
    input.degree = 2;
    input.uniform = true;
    input.periodic = false;
    input.numUniqueKnots = input.numControls - input.degree + 1;
    std::vector<UniqueKnot<float>> uniqueKnots(input.numUniqueKnots);
    input.uniqueKnots = &uniqueKnots[0];
    uniqueKnots.front().t = 0.0f;
    uniqueKnots.front().multiplicity = input.degree + 1;
    for (int i = 1; i <= input.numUniqueKnots - 2; ++i)
    {
        uniqueKnots[i].t = i / (input.numUniqueKnots - 1.0f);
        uniqueKnots[i].multiplicity = 1;
    }
    uniqueKnots.back().t = 1.0f;
    uniqueKnots.back().multiplicity = input.degree + 1;

    mSpline.reset(
        new BSplineCurve<3, float>(input, &mModule->GetPosition(0)));

    mSurface.reset(
        new TubeSurface<float>(mSpline, [](float){ return 0.025f; }));
    mSurface->Set(64, 8, false, false, true);
    int numVertices = mSurface->GetNumVertices();
    int numTriangles = mSurface->GetNumTriangles();

    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_TEXCOORD, DF_R32G32_FLOAT, 0);
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat,
        numVertices));
    vbuffer->SetUsage(Resource::DYNAMIC_UPDATE);
    Vertex* vertices = vbuffer->Get<Vertex>();
    mSurface->GetPositions(&vertices[0].position, sizeof(Vertex));
    mSurface->GetTCoords(&vertices[0].tcoord, sizeof(Vertex));

    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_TRIMESH,
        numTriangles, sizeof(int)));
    mSurface->GetIndices(ibuffer->Get<int>());

    std::string path = mEnvironment.GetPath("Rope.bmp");
    std::shared_ptr<Texture2> texture(WICFileIO::Load(path, true));
    texture->AutogenerateMipmaps();
    std::shared_ptr<Texture2Effect> effect(new Texture2Effect(texture,
        SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::WRAP,
        SamplerState::WRAP));

    mRope.reset(new Visual(vbuffer, ibuffer, effect));
    mRope->UpdateModelBound();
    mRope->localTransform.SetTranslation(-mRope->modelBound.GetCenter());
    mRope->Update();
    SubscribeCW(mRope, effect->GetPVWMatrixConstant());
}
//----------------------------------------------------------------------------
void RopeWindow::PhysicsTick()
{
    // Forces are independent of time, just pass in t = 0.
    mModule->Update(0.0f);

    // Update spline curve.  Remember that the spline maintains its own copy
    // of the control points, so this update is necessary.
    int numControls = mModule->GetNumParticles();
    for (int i = 0; i < numControls; ++i)
    {
        mSpline->SetControl(i, mModule->GetPosition(i));
    }

    // Update the GPU copy of the vertices.
    std::shared_ptr<VertexBuffer> vbuffer = mRope->GetVertexBuffer();
    Vertex* vertices = vbuffer->Get<Vertex>();
    mSurface->GetPositions(&vertices[0].position, sizeof(Vertex));
    mEngine->Update(vbuffer);
    UpdateCW();
}
//----------------------------------------------------------------------------
void RopeWindow::GraphicsTick()
{
    mEngine->ClearBuffers();
    mEngine->Draw(mRope);
    mEngine->DisplayColorBuffer(0);
}
//----------------------------------------------------------------------------
