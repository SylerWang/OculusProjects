// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include <GteShaderFactory.h>
#include <GteWICFileIO.h>
#include "BlendedTerrainEffect.h"
using namespace gte;

//----------------------------------------------------------------------------
BlendedTerrainEffect::~BlendedTerrainEffect()
{
}
//----------------------------------------------------------------------------
BlendedTerrainEffect::BlendedTerrainEffect(Environment const& environment,
    bool& created)
{
    created = false;

    // Load and compile the shaders.
    std::string path = environment.GetPath("BlendedTerrain.hlsl");
    unsigned int flags =
        D3DCOMPILE_ENABLE_STRICTNESS |
        D3DCOMPILE_IEEE_STRICTNESS |
        D3DCOMPILE_DEBUG |
        D3DCOMPILE_SKIP_OPTIMIZATION;
    mVShader.reset(ShaderFactory::CreateVertex(path, HLSLDefiner(),
        "VSMain", "vs_5_0", flags));
    if (!mVShader)
    {
        LogError("Cannot compile vertex shader.");
        return;
    }

    mPShader.reset(ShaderFactory::CreatePixel(path, HLSLDefiner(),
        "PSMain", "ps_5_0", flags));
    if (!mPShader)
    {
        LogError("Cannot compile pixel shader.");
        return;
    }

    // Load the textures.
    path = environment.GetPath("BTGrass.bmp");
    mGrassTexture.reset(WICFileIO::Load(path, true));
    mGrassTexture->AutogenerateMipmaps();

    path = environment.GetPath("BTStone.bmp");
    mStoneTexture.reset(WICFileIO::Load(path, true));
    mStoneTexture->AutogenerateMipmaps();

    path = environment.GetPath("BTCloud.bmp");
    mCloudTexture.reset(WICFileIO::Load(path, true));
    mCloudTexture->AutogenerateMipmaps();

    // Create the shader constants.
    mPVWMatrixConstant.reset(new ConstantBuffer(sizeof(Matrix4x4<float>),
        true));
    mPVWMatrix = mPVWMatrixConstant->Get<Matrix4x4<float>>();
    *mPVWMatrix = Matrix4x4<float>::Identity();

    mFlowDirectionConstant.reset(new ConstantBuffer(sizeof(Vector2<float>),
        true));
    mFlowDirection = mFlowDirectionConstant->Get<Vector2<float>>();
    *mFlowDirection = Vector2<float>(0.0f, 0.0f);

    mPowerFactorConstant.reset(new ConstantBuffer(sizeof(float), true));
    mPowerFactor = mPowerFactorConstant->Get<float>();
    *mPowerFactor = 1.0f;

    // Create a 1-dimensional texture whose intensities are proportional to
    // height.
    unsigned int const numTexels = 256;
    mBlendTexture.reset(new Texture1(DF_R8_UNORM, numTexels));
    unsigned char* texels = mBlendTexture->Get<unsigned char>();
    for (unsigned int i = 0; i < numTexels; ++i, ++texels)
    {
        *texels = static_cast<unsigned char>(i);
    }

    // Create the texture samplers.  The common sampler uses trilinear
    // interpolation (mipmapping).  The blend sample uses bilinear
    // interpolation (no mipmapping).
    mCommonSampler.reset(new SamplerState());
    mCommonSampler->filter = SamplerState::MIN_L_MAG_L_MIP_L;
    mCommonSampler->mode[0] = SamplerState::WRAP;
    mCommonSampler->mode[1] = SamplerState::WRAP;
    mBlendSampler.reset(new SamplerState());
    mBlendSampler->filter = SamplerState::MIN_L_MAG_L_MIP_P;
    mBlendSampler->mode[0] = SamplerState::WRAP;

    // Set the resources for the shaders.
    mVShader->Set("PVWMatrix", mPVWMatrixConstant);
    mVShader->Set("FlowDirection", mFlowDirectionConstant);
    mPShader->Set("PowerFactor", mPowerFactorConstant);
    mPShader->Set("grassTexture", mGrassTexture);
    mPShader->Set("stoneTexture", mStoneTexture);
    mPShader->Set("blendTexture", mBlendTexture);
    mPShader->Set("cloudTexture", mCloudTexture);
    mPShader->Set("commonSampler", mCommonSampler);
    mPShader->Set("blendSampler", mBlendSampler);

    created = true;
}
//----------------------------------------------------------------------------
