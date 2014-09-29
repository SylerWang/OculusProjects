// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/31)

#include "GTEnginePCH.h"
#include "GteTextEffect.h"
#include "GteShaderFactory.h"
#include "GteVector2.h"
using namespace gte;

//----------------------------------------------------------------------------
TextEffect::TextEffect(std::shared_ptr<Texture2> const& texture)
{
    mTranslate.reset(new ConstantBuffer(sizeof(Vector2<float>), true));
    mColor.reset(new ConstantBuffer(sizeof(Vector4<float>), true));
    mSamplerState.reset(new SamplerState());

    // Create the text shaders.
    mVShader.reset(ShaderFactory::CreateVertex("VSMain", msHLSLString));
    if (mVShader)
    {
        SetTranslate(0.0f, 0.0f);
        mVShader->Set("Translate", mTranslate);
    }
    else
    {
        LogError("Unable to create vertex shader.");
    }

    mPShader.reset(ShaderFactory::CreatePixel("PSMain", msHLSLString));
    if (mPShader)
    {
        SetColor(Vector4<float>::Zero());
        mPShader->Set("TextColor", mColor);
        mPShader->Set("baseTexture", texture);
        mPShader->Set("baseSampler", mSamplerState);
    }
    else
    {
        LogError("Unable to create pixel shader.");
    }
}
//----------------------------------------------------------------------------
std::shared_ptr<ConstantBuffer> const& TextEffect::GetTranslate() const
{
    return mTranslate;
}
//----------------------------------------------------------------------------
std::shared_ptr<ConstantBuffer> const& TextEffect::GetColor() const
{
    return mColor;
}
//----------------------------------------------------------------------------
void TextEffect::SetTranslate(float x, float  y)
{
    float* data = mTranslate->Get<float>();
    data[0] = x;
    data[1] = y;
}
//----------------------------------------------------------------------------
void TextEffect::SetColor(Vector4<float> const& color)
{
    Vector4<float>* data = mColor->Get<Vector4<float>>();
    *data = color;
}
//----------------------------------------------------------------------------
void TextEffect::SetName(std::string const& name)
{
    VisualEffect::SetName(name);
    mTranslate->SetName(mName + ":mTranslate");
    mColor->SetName(mName + ":mColor");
    mSamplerState->SetName(mName + ":mSamplerState");
}
//----------------------------------------------------------------------------

std::string const TextEffect::msHLSLString = GTE_MAKE_HLSL_STRING(
cbuffer Translate
{
    float2 translate;
};
struct VS_INPUT
{
    float2 modelPosition : POSITION;
    float2 modelTCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
    float2 vertexTCoord : TEXCOORD0;
    float4 clipPosition : SV_POSITION;
};

VS_OUTPUT VSMain (VS_INPUT input)
{
    VS_OUTPUT output;
    output.vertexTCoord = input.modelTCoord;
    output.clipPosition.x = 2.0f*input.modelPosition.x - 1.0f + 2.0f*translate.x;
    output.clipPosition.y = 2.0f*input.modelPosition.y - 1.0f + 2.0f*translate.y;
    output.clipPosition.z = 0.0f;
    output.clipPosition.w = 1.0f;
    return output;
}

cbuffer TextColor
{
    float4 textColor;
};

Texture2D baseTexture;
SamplerState baseSampler;

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
    float bitmapAlpha = baseTexture.Sample(baseSampler, input.vertexTCoord).r;
    if (bitmapAlpha > 0.5f)
    {
        discard;
    }
    output.pixelColor0 = textColor;
    return output;
};
);
