// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/14)

#include "TextureArraysWindow.h"

//----------------------------------------------------------------------------
TextureArraysWindow::~TextureArraysWindow()
{
    UnsubscribeCW(mSquare);
}
//----------------------------------------------------------------------------
TextureArraysWindow::TextureArraysWindow(Parameters& parameters)
    :
    Window(parameters)
{
    if (!SetEnvironment() || !CreateScene())
    {
        parameters.created = false;
        return;
    }

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
void TextureArraysWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    mEngine->ClearBuffers();
    mEngine->Draw(mSquare);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool TextureArraysWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }

    mEnvironment.Insert(path + "/Samples/Data/");
    mEnvironment.Insert(path + "/Samples/Basics/TextureArrays/Shaders/");

    if (mEnvironment.GetPath("TextureArrays.hlsl") == "")
    {
        LogError("Cannot find file TextureArrays.hlsl.");
        return false;
    }

    if (mEnvironment.GetPath("StoneWall.png") == "")
    {
        LogError("Cannot find file StoneWall.png.");
        return false;
    }

    return true;
}
//----------------------------------------------------------------------------
bool TextureArraysWindow::CreateScene()
{
    // Create the shaders and associated resources.
    std::shared_ptr<VertexShader> vshader(ShaderFactory::CreateVertex(
        mEnvironment.GetPath("TextureArrays.hlsl")));
    if (!vshader)
    {
        return false;
    }

    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("TextureArrays.hlsl")));
    if (!pshader)
    {
        return false;
    }

    // Create a vertex buffer for a single triangle.  The PNG is stored in
    // left-handed coordinates.  The texture coordinates are chosen to reflect
    // the texture in the y-direction.
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
    std::shared_ptr<ConstantBuffer> cbuffer(new ConstantBuffer(
        sizeof(Matrix4x4<float>), true));
    vshader->Set("PVWMatrix", cbuffer);

    std::shared_ptr<Texture1Array> t1array(new Texture1Array(2,
        DF_R8G8B8A8_UNORM, 2));
    unsigned int* t1data = t1array->Get<unsigned int>();
    t1data[0] = 0xFF000000;
    t1data[1] = 0xFFFFFFFF;
    pshader->Set("myTexture1", t1array);

    Texture2* stoneTexture = WICFileIO::Load(
        mEnvironment.GetPath("StoneWall.png"), false);
    std::shared_ptr<Texture2Array> t2array(new Texture2Array(2,
        DF_R8G8B8A8_UNORM, 256, 256));
    unsigned char* t2data = t2array->Get<unsigned char>();
    size_t const numBytes = stoneTexture->GetNumBytes();
    memcpy(t2data, stoneTexture->GetData(), numBytes);
    t2data += numBytes;
    delete stoneTexture;
    for (size_t i = 0; i < numBytes; ++i)
    {
        *t2data++ = static_cast<unsigned char>(rand() % 256);
    }
    pshader->Set("myTexture2", t2array);

    std::shared_ptr<SamplerState> samplerState(new SamplerState());
    samplerState->filter = SamplerState::MIN_L_MAG_L_MIP_P;
    samplerState->mode[0] = SamplerState::CLAMP;
    samplerState->mode[1] = SamplerState::CLAMP;
    pshader->Set("mySampler", samplerState);

    std::shared_ptr<VisualEffect> effect(new VisualEffect(vshader, pshader));

    // Create the geometric object for drawing.  Translate it so that its
    // center of mass is at the origin.  This supports virtual trackball
    // motion about the object "center".
    mSquare.reset(new Visual(vbuffer, ibuffer, effect));
    mSquare->localTransform.SetTranslation(-0.5f, -0.5f, 0.0f);
    mSquare->Update();

    // Enable automatic updates of pvw-matrices and w-matrices.
    SubscribeCW(mSquare, cbuffer);
    return true;
}
//----------------------------------------------------------------------------
