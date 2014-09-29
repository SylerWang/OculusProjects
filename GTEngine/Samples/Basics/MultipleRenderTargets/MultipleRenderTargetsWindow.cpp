// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/14)

#include "MultipleRenderTargetsWindow.h"

static std::string const gsOverlay1PShader = GTE_MAKE_HLSL_STRING(
Texture2D<uint> depthTexture;
Texture2D<float4> positionTexture;
RWTexture2D<float4> colorTexture;
SamplerState nearestSampler;

struct PS_INPUT
{
    float2 vertexTCoord : TEXCOORD0;
};

struct PS_OUTPUT
{
    float4 pixelColor0 : SV_TARGET0;
};

PS_OUTPUT PSMain(PS_INPUT input)
{
    PS_OUTPUT output;
    float4 pos = positionTexture.Sample(nearestSampler, input.vertexTCoord);
    uint depthR24S8 = depthTexture[(int2)pos.xy];
    float gray = (depthR24S8 & 0x00FFFFFF) / 16777215.0f;
    output.pixelColor0 = float4(gray, gray, gray, 1.0f);
    colorTexture[(int2)pos.xy] = float4(0.4f, 0.5f, 0.6f, 1.0f);
    return output;
};
);

//----------------------------------------------------------------------------
MultipleRenderTargetsWindow::~MultipleRenderTargetsWindow()
{
    UnsubscribeCW(mSquare);
}
//----------------------------------------------------------------------------
MultipleRenderTargetsWindow::MultipleRenderTargetsWindow(Parameters& parameters)
    :
    Window(parameters),
    mTextColor(1.0f, 0.0f, 0.0f, 1.0f)
{
    if (!SetEnvironment() || !CreateScene() || !CreateOverlays())
    {
        parameters.created = false;
        return;
    }

    mCamera.SetFrustum(60.0f, GetAspectRatio(), 0.1f, 10.0f);
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
void MultipleRenderTargetsWindow::OnIdle()
{
    MeasureTime();

    MoveCamera();

    // Render the square to offscreen memory.
    mEngine->Enable(mDrawTarget);
    mEngine->ClearBuffers();
    mEngine->Draw(mSquare);
    mEngine->Disable(mDrawTarget);

#ifdef VERIFY_AUTO_RT_MIPMAPS_AND_RT_UAV
    // Verify that the mipmaps have been automatically generated.  Read back
    // level 1 and write to a PNG file.
    std::shared_ptr<TextureRT> rt0 = mDrawTarget->GetRTTexture(0);
    mEngine->CopyGpuToCpu(rt0);
    Vector4<float>* level = rt0->GetFor<Vector4<float>>(1);
    unsigned int numLevelElements = rt0->GetNumElementsFor(1);
    unsigned int* output = mVerifyAutoRT->Get<unsigned int>();
    for (unsigned int i = 0; i < numLevelElements; ++i)
    {
        Vector4<float> texel = *level++;
        unsigned int r = static_cast<unsigned int>(255.0f * texel[0]);
        unsigned int g = static_cast<unsigned int>(255.0f * texel[1]);
        unsigned int b = static_cast<unsigned int>(255.0f * texel[2]);
        *output++ = (r | (g << 8) | (b << 16) | 0xFF000000);
    }
    WICFileIO::SaveToPNG("VerifyAutoRT.png", mVerifyAutoRT.get());
#endif

    // PSMain of MultipleRenderTarget.hlsl has written linearized depth to the
    // depth buffer.  It is not possible to attach a depth-stencil texture as
    // a shader input (you cannot create a shader resource view for it), so the
    // best you can do is read it back from the GPU and copy it to a texture that
    // is a shader input.  NOTE: If you really want to use depth as a shader input,
    // pass the 'perspectiveDepth' to the pixel shader as is done in
    // MultipleRenderTarget.hlsl and write it to a render target (not the
    // depth-stencil texture).  You can hook up that render target as a shader
    // input.  This avoids the expensive read-back-and-copy step here.
    std::shared_ptr<TextureDS> dsTexture = mDrawTarget->GetDSTexture();
#if 1
    // AMD 7970:  250 fps
    mEngine->CopyGpuToCpu(dsTexture);
    memcpy(mLinearDepth->GetData(), dsTexture->GetData(),
        dsTexture->GetNumBytes());
    mEngine->CopyCpuToGpu(mLinearDepth);
#else
    // TODO: The block of code above does
    //   gpu -> srcStaging -> cpu(lineardepth) -> dstStaging -> gpu
    // The block of code below skips the cpu memory,
    //   gpu -> srcStaging -> dstStaging -> gpu
    // We should add CopyGpuToStaging, CopyStagingToGpu, CopyStagingToStaging.
    // CopyGpuToGpu can use CopyResource/CopySubresourceRegion as long as the
    // resources are compatible.  But in the situation here, the depth format
    // DF_D24_UNORM_S8_UINT is not compatible with DF_R32_UINT according to
    // the error messages produced by the D3D11 debug layer when calling
    // CopyResource, even though the textures are the dimensions and have the
    // same number of bytes.  In fact, CopyResource does not have a return
    // value that indicates the failure to copy, so how does one trap the
    // error?

    // AMD 7970:  337 fps
    ID3D11DeviceContext* context = mEngine->GetImmediate();
    DX11TextureDS* srcTexture = (DX11TextureDS*)mEngine->Bind(dsTexture);
    ID3D11Resource* srcResource = srcTexture->GetDXResource();
    ID3D11Resource* srcStaging = srcTexture->GetStagingResource();
    DX11Texture2* dstTexture = (DX11Texture2*)mEngine->Bind(mLinearDepth);
    ID3D11Resource* dstResource = dstTexture->GetDXResource();
    ID3D11Resource* dstStaging = dstTexture->GetStagingResource();
    context->CopySubresourceRegion(srcStaging, 0, 0, 0, 0, srcResource, 0,
        nullptr);
    D3D11_MAPPED_SUBRESOURCE srcSub, dstSub;
    HRESULT hr = context->Map(srcStaging, 0, D3D11_MAP_READ, 0, &srcSub);
    hr = context->Map(dstStaging, 0, D3D11_MAP_WRITE, 0, &dstSub);
    memcpy(dstSub.pData, srcSub.pData, dsTexture->GetNumBytes());
    context->Unmap(srcStaging, 0);
    context->Unmap(dstStaging, 0);
    context->CopySubresourceRegion(dstResource, 0, 0, 0, 0, dstStaging, 0,
        nullptr);
#endif

    // Display the draw-target outputs.
    mEngine->Draw(mOverlay[0]);
    mEngine->Draw(mOverlay[1]);

#ifdef VERIFY_AUTO_RT_MIPMAPS_AND_RT_UAV
    // Verify that the pixel shader of mOverlay[1] has written the color
    // (0.4,0.5,0.6,1.0) to all texels of level 0 of render target 0.
    mEngine->CopyGpuToCpu(rt0);
    level = rt0->GetFor<Vector4<float>>(0);
    numLevelElements = rt0->GetNumElementsFor(0);
    output = mVerifyRTUAV->Get<unsigned int>();
    for (unsigned int i = 0; i < numLevelElements; ++i)
    {
        Vector4<float> texel = *level++;
        unsigned int r = static_cast<unsigned int>(255.0f * texel[0]);
        unsigned int g = static_cast<unsigned int>(255.0f * texel[1]);
        unsigned int b = static_cast<unsigned int>(255.0f * texel[2]);
        *output++ = (r | (g << 8) | (b << 16) | 0xFF000000);
    }
    WICFileIO::SaveToPNG("VerifyRTUAV.png", mVerifyRTUAV.get());
#endif

    DrawFrameRate(8, mYSize - 8, mTextColor);
    mEngine->DisplayColorBuffer(0);

    UpdateFrameCount();
}
//----------------------------------------------------------------------------
bool MultipleRenderTargetsWindow::SetEnvironment()
{
    std::string path = mEnvironment.GetVariable("GTE_PATH");
    if (path == "")
    {
        LogError("You must create the environment variable GTE_PATH.");
        return false;
    }

    mEnvironment.Insert(path + "/Samples/Data/");
    mEnvironment.Insert(
        path + "/Samples/Basics/MultipleRenderTargets/Shaders/");

    if (mEnvironment.GetPath("MultipleRenderTargets.hlsl") == "")
    {
        LogError("Cannot find file MultipleRenderTargets.hlsl.");
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
bool MultipleRenderTargetsWindow::CreateScene()
{
    // Create a visual effect that populates the draw target.
    std::shared_ptr<VertexShader> vshader(ShaderFactory::CreateVertex(
        mEnvironment.GetPath("MultipleRenderTargets.hlsl")));
    if (!vshader)
    {
        return false;
    }

    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(
        mEnvironment.GetPath("MultipleRenderTargets.hlsl")));
    if (!pshader)
    {
        return false;
    }

    std::shared_ptr<ConstantBuffer> cbuffer(new ConstantBuffer(
        sizeof(Matrix4x4<float>), true));
    vshader->Set("PVWMatrix", cbuffer);

    std::shared_ptr<ConstantBuffer> farNearRatio(new ConstantBuffer(
        sizeof(float), false));
    pshader->Set("FarNearRatio", farNearRatio);
    farNearRatio->SetMember("farNearRatio",
        mCamera.GetDMax() / mCamera.GetDMin());

    std::string path = mEnvironment.GetPath("StoneWall.png");
    std::shared_ptr<Texture2> baseTexture(WICFileIO::Load(path, true));
    baseTexture->AutogenerateMipmaps();
    pshader->Set("baseTexture", baseTexture);

    std::shared_ptr<SamplerState> baseSampler(new SamplerState());
    baseSampler->filter = SamplerState::MIN_L_MAG_L_MIP_L;
    baseSampler->mode[0] = SamplerState::CLAMP;
    baseSampler->mode[1] = SamplerState::CLAMP;
    pshader->Set("baseSampler", baseSampler);

    std::shared_ptr<VisualEffect> effect(new VisualEffect(vshader, pshader));

    // Create a vertex buffer for a two-triangle square.  The PNG is stored
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
bool MultipleRenderTargetsWindow::CreateOverlays()
{
    std::shared_ptr<PixelShader> pshader(ShaderFactory::CreatePixel(
        "Overlay1PShader", gsOverlay1PShader));
    if (!pshader)
    {
        return false;
    }

    // Create the draw target with 2 render targets and 1 depth-stencil
    // texture.  Each of these is used as a texture for an overlay.
    unsigned int const rtSize = 1024;
    mDrawTarget.reset(new DrawTarget(2, DF_R32G32B32A32_FLOAT, rtSize,
        rtSize, true, true, DF_D24_UNORM_S8_UINT, true));
    mDrawTarget->AutogenerateRTMipmaps();
    mDrawTarget->GetRTTexture(0)->SetUsage(Resource::SHADER_OUTPUT);
    mDrawTarget->GetRTTexture(0)->SetCopyType(Resource::COPY_STAGING_TO_CPU);
    mDrawTarget->GetDSTexture()->SetCopyType(Resource::COPY_STAGING_TO_CPU);

    // Create two overlays, one for each output of the draw target.
    std::array<int, 4> rectangle[2] =
    {
        { 0, 0, mXSize / 2, mYSize },
        { mXSize / 2, 0, mXSize / 2, mYSize }
    };

    std::array<int, 4> texrectangle = { rtSize / 4, 0, rtSize / 2, rtSize };

    mOverlay[0].reset(new OverlayEffect(mXSize, mYSize, rtSize, rtSize,
        SamplerState::MIN_L_MAG_L_MIP_L, SamplerState::CLAMP,
        SamplerState::CLAMP, true));
    mOverlay[0]->SetOverlayRectangle(rectangle[0]);
    mOverlay[0]->SetTextureRectangle(texrectangle);
    mOverlay[0]->SetTexture(mDrawTarget->GetRTTexture(0));

    mLinearDepth.reset(new Texture2(DF_R32_UINT, rtSize, rtSize));
    mLinearDepth->SetUsage(Resource::SHADER_OUTPUT);
    mLinearDepth->SetCopyType(Resource::COPY_CPU_TO_STAGING);
    memset(mLinearDepth->GetData(), 0, mLinearDepth->GetNumBytes());

    std::shared_ptr<SamplerState> nearestSampler(new SamplerState());
    nearestSampler->filter = SamplerState::MIN_P_MAG_P_MIP_P;
    nearestSampler->mode[0] = SamplerState::CLAMP;
    nearestSampler->mode[1] = SamplerState::CLAMP;

    pshader->Set("depthTexture", mLinearDepth);
    pshader->Set("positionTexture", mDrawTarget->GetRTTexture(1));
    pshader->Set("colorTexture", mDrawTarget->GetRTTexture(0));
    pshader->Set("nearestSampler", nearestSampler);

    mOverlay[1].reset(new OverlayEffect(mXSize, mYSize, rtSize, rtSize,
        pshader));
    mOverlay[1]->SetOverlayRectangle(rectangle[1]);
    mOverlay[1]->SetTextureRectangle(texrectangle);

#ifdef VERIFY_AUTO_RT_MIPMAPS_AND_RT_UAV
    mVerifyAutoRT.reset(new Texture2(DF_R8G8B8A8_UNORM, rtSize / 2,
        rtSize / 2));
    mVerifyRTUAV.reset(new Texture2(DF_R8G8B8A8_UNORM, rtSize, rtSize));
#endif
    return true;
}
//----------------------------------------------------------------------------
