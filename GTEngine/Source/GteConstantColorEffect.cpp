// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GTEnginePCH.h"
#include "GteConstantColorEffect.h"
#include "GteShaderFactory.h"
using namespace gte;

//----------------------------------------------------------------------------
ConstantColorEffect::ConstantColorEffect(Vector4<float> const& color)
{
    // Create the shader constants.
    mPVWMatrixConstant.reset(new ConstantBuffer(sizeof(Matrix4x4<float>),
        true));
    mPVWMatrix = mPVWMatrixConstant->Get<Matrix4x4<float>>();
    *mPVWMatrix = Matrix4x4<float>::Identity();

    mColorConstant.reset(new ConstantBuffer(sizeof(Vector4<float>), true));
    mColor = mColorConstant->Get<Vector4<float>>();
    *mColor = color;

    // Create the vertex color effect shaders.
    mVShader.reset(ShaderFactory::CreateVertex("VSMain", msHLSLString));
    if (mVShader)
    {
        mVShader->Set("PVWMatrix", mPVWMatrixConstant);
        mVShader->Set("ConstantColor", mColorConstant);
    }
    else
    {
        LogError("Unable to create vertex shader.");
    }

    mPShader.reset(ShaderFactory::CreatePixel("PSMain", msHLSLString));
    LogAssert(mPShader, "Unable to create pixel shader.");
}
//----------------------------------------------------------------------------
void ConstantColorEffect::SetName(std::string const& name)
{
    VisualEffect::SetName(name);
    mPVWMatrixConstant->SetName(name);
}
//----------------------------------------------------------------------------

std::string const ConstantColorEffect::msHLSLString = GTE_MAKE_HLSL_STRING(
cbuffer PVWMatrix
{
    float4x4 pvwMatrix;
};

cbuffer ConstantColor
{
    float4 constantColor;
};

struct VS_INPUT
{
    float3 modelPosition : POSITION;
};

struct VS_OUTPUT
{
    float4 vertexColor : COLOR0;
    float4 clipPosition : SV_POSITION;
};

VS_OUTPUT VSMain (VS_INPUT input)
{
    VS_OUTPUT output;
#ifdef GTE_USE_MAT_VEC
    output.clipPosition = mul(pvwMatrix, float4(input.modelPosition, 1.0f));
#else
    output.clipPosition = mul(float4(input.modelPosition, 1.0f), pvwMatrix);
#endif
    output.vertexColor = constantColor;
    return output;
}

struct PS_INPUT
{
    float4 vertexColor : COLOR0;
};

struct PS_OUTPUT
{
    float4 pixelColor0 : SV_TARGET0;
};

PS_OUTPUT PSMain(PS_INPUT input)
{
    PS_OUTPUT output;
    output.pixelColor0 = input.vertexColor;
    return output;
};
);
