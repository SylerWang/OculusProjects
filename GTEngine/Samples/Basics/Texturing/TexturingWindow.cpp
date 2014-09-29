// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/14)

#include "TexturingWindow.h"

//----------------------------------------------------------------------------
TexturingWindow::~TexturingWindow()
{
    UnsubscribeCW(mSquare);
}
//----------------------------------------------------------------------------
TexturingWindow::TexturingWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(0.0f, 0.0f, 0.0f, 1.0f)
{
    if (!SetEnvironment())
    {
        parameters.created = false;
        return;
    }

    CreateScene();

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 100.0f);
    Vector4<float> camPosition(0.0f, 0.0f, 1.25f, 1.0f);
    Vector4<float> camDVector(0.0f, 0.0f, -1.0f, 0.0f);
    Vector4<float> camUVector(0.0f, 1.0f, 0.0f, 0.0f);
    Vector4<float> camRVector = Cross(camDVector, camUVector);
    mCamera.SetFrame(camPosition, camDVector, camUVector, camRVector);

    EnableCameraMotion(0.001f, 0.001f, 2.0f, 2.0f);
    EnableObjectMotion();
    UpdateCW();
}
//----------------------------------------------------------------------------
void TexturingWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    mEngine->ClearBuffers();
    mEngine->Draw(mSquare);
    DrawFrameRate(8, mYSize - 8, mTextColor);
    mEngine->DisplayColorBuffer(0);

#ifdef SAVE_RENDERING_TO_DISK
    mEngine->Enable(mTarget);
    mEngine->ClearBuffers();
    mEngine->Draw(mSquare);
    mEngine->Disable(mTarget);
    mEngine->CopyGpuToCpu(mTarget->GetRTTexture(0));
    WICFileIO::SaveToPNG("Texturing.png", mTarget->GetRTTexture(0).get());
#endif

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool TexturingWindow::SetEnvironment()
{
    // Set the search path to find images to load.
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }

    mEnvironment.Insert(path + "/Samples/Data/");

    if (mEnvironment.GetPath("StoneWall.png") == "")
    {
        LogError("Cannot find file Stonewall.png");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
void TexturingWindow::CreateScene()
{
    // Create a vertex buffer for a two-triangles square.  The PNG is stored
    // in left-handed coordinates.  The texture coordinates are chosen to
    // reflect the texture in the y-direction.
    struct Vertex
    {
        Vector3<float> position;
        Vector2<float> tcoord;
    };
    VertexFormat vformat;
    vformat.Bind(VA_POSITION, DF_R32G32B32_FLOAT, 0);
    vformat.Bind(VA_TEXCOORD, DF_R32G32_FLOAT, 0);
    std::shared_ptr<VertexBuffer> vbuffer(new VertexBuffer(vformat, 4));
    Vertex* vertex = vbuffer->Get<Vertex>();
    vertex[0].position = Vector3<float>(0.0f, 0.0f, 0.0f);
    vertex[0].tcoord = Vector2<float>(0.0f, 1.0f);
    vertex[1].position = Vector3<float>(1.0f, 0.0f, 0.0f);
    vertex[1].tcoord = Vector2<float>(1.0f, 1.0f);
    vertex[2].position = Vector3<float>(0.0f, 1.0f, 0.0f);
    vertex[2].tcoord = Vector2<float>(0.0f, 0.0f);
    vertex[3].position = Vector3<float>(1.0f, 1.0f, 0.0f);
    vertex[3].tcoord = Vector2<float>(1.0f, 0.0f);

    // Create an indexless buffer for a triangle mesh with two triangles.
    std::shared_ptr<IndexBuffer> ibuffer(new IndexBuffer(IP_TRISTRIP, 2));

    // Create an effect for the vertex and pixel shaders.  The texture is
    // bilinearly filtered and the texture coordinates are clamped to [0,1]^2.
    std::shared_ptr<Texture2> myTexture(WICFileIO::Load(
        mEnvironment.GetPath("StoneWall.png"), false));
    std::shared_ptr<Texture2Effect> effect(new Texture2Effect(myTexture,
        SamplerState::MIN_L_MAG_L_MIP_P, SamplerState::CLAMP,
        SamplerState::CLAMP));

    // Create the geometric object for drawing.  Translate it so that its
    // center of mass is at the origin.  This supports virtual trackball
    // motion about the object "center".
    mSquare.reset(new Visual(vbuffer, ibuffer, effect));
    mSquare->localTransform.SetTranslation(-0.5f, -0.5f, 0.0f);
    mSquare->Update();

    // Enable automatic updates of pvw-matrices and w-matrices.
    SubscribeCW(mSquare, effect->GetPVWMatrixConstant());

#ifdef SAVE_RENDERING_TO_DISK
    mTarget.reset(new DrawTarget(1, DF_R8G8B8A8_UNORM, mXSize, mYSize));
    mTarget->GetRTTexture(0)->SetCopyType(Resource::COPY_STAGING_TO_CPU);
#endif
}
//----------------------------------------------------------------------------
