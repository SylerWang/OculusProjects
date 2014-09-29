// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GTEnginePCH.h"
#include "GteFluid2ComputeDivergence.h"
#include "GteShaderFactory.h"
using namespace gte;

//----------------------------------------------------------------------------
Fluid2ComputeDivergence::~Fluid2ComputeDivergence()
{
}
//----------------------------------------------------------------------------
Fluid2ComputeDivergence::Fluid2ComputeDivergence(int xSize, int ySize,
    int numXThreads, int numYThreads,
    std::shared_ptr<ConstantBuffer> const& parameters)
    :
    mNumXGroups(xSize/numXThreads),
    mNumYGroups(ySize/numYThreads)
{
    HLSLDefiner definer;
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Y_THREADS", numYThreads);

    // Create the shader for computing the divergence of the velocity.
    mComputeDivergence.reset(ShaderFactory::CreateCompute("ComputeDivergence",
        msHLSLComputeDivergenceString, definer));
    LogAssert(mComputeDivergence != nullptr, "Cannot create compute shader.");

    mDivergence.reset(new Texture2(DF_R32_FLOAT, xSize, ySize));
    mDivergence->SetUsage(Resource::SHADER_OUTPUT);

    mComputeDivergence->Set("Parameters", parameters);
    mComputeDivergence->Set("divergence", mDivergence);
}
//----------------------------------------------------------------------------
std::shared_ptr<Texture2> const& Fluid2ComputeDivergence::GetDivergence()
    const
{
    return mDivergence;
}
//----------------------------------------------------------------------------
void Fluid2ComputeDivergence::Execute(DX11Engine* engine,
    std::shared_ptr<Texture2> const& state)
{
    mComputeDivergence->Set("state", state);
    engine->Execute(mComputeDivergence, mNumXGroups, mNumYGroups, 1);
}
//----------------------------------------------------------------------------

std::string const Fluid2ComputeDivergence::msHLSLComputeDivergenceString =
GTE_MAKE_HLSL_STRING(
cbuffer Parameters
{
    float4 spaceDelta;    // (dx, dy, 0, 0)
    float4 halfDivDelta;  // (0.5/dx, 0.5/dy, 0, 0)
    float4 timeDelta;     // (dt, dt/dx, dt/dy, 0)
    float4 viscosityX;    // (velVX, velVX, 0, denVX)
    float4 viscosityY;    // (velVX, velVY, 0, denVY)
    float4 epsilon;       // (epsilonX, epsilonY, 0, epsilon0)
};

Texture2D<float4> state;
RWTexture2D<float> divergence;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, 1)]
void CSMain(uint2 c : SV_DispatchThreadID)
{
    uint2 dim;
    state.GetDimensions(dim.x, dim.y);

    int x = int(c.x);
    int y = int(c.y);
    int xm = max(x - 1, 0);
    int xp = min(x + 1, dim.x - 1);
    int ym = max(y - 1, 0);
    int yp = min(y + 1, dim.y - 1);

    float2 velocityGradient = float2(
        state[int2(xp, y)].x - state[int2(xm, y)].x,
        state[int2(x, yp)].y - state[int2(x, ym)].y
    );

    divergence[c] = dot(halfDivDelta.xy, velocityGradient);
}
);
