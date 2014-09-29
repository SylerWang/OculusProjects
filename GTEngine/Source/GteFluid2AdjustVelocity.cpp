// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GTEnginePCH.h"
#include "GteFluid2AdjustVelocity.h"
#include "GteShaderFactory.h"
using namespace gte;

//----------------------------------------------------------------------------
Fluid2AdjustVelocity::~Fluid2AdjustVelocity()
{
}
//----------------------------------------------------------------------------
Fluid2AdjustVelocity::Fluid2AdjustVelocity(int xSize, int ySize, 
    int numXThreads, int numYThreads,
    std::shared_ptr<ConstantBuffer> const& parameters)
    :
    mNumXGroups(xSize/numXThreads),
    mNumYGroups(ySize/numYThreads)
{
    HLSLDefiner definer;
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Y_THREADS", numYThreads);

    mAdjustVelocity.reset(ShaderFactory::CreateCompute("AdjustVelocity",
        msHLSLAdjustVelocityString, definer));
    LogAssert(mAdjustVelocity != nullptr, "Cannot create compute shader.");

    mAdjustVelocity->Set("Parameters", parameters);
}
//----------------------------------------------------------------------------
void Fluid2AdjustVelocity::Execute(DX11Engine* engine,
    std::shared_ptr<Texture2> const& inState,
    std::shared_ptr<Texture2> const& poisson,
    std::shared_ptr<Texture2> const& outState)

{
    mAdjustVelocity->Set("inState", inState);
    mAdjustVelocity->Set("poisson", poisson);
    mAdjustVelocity->Set("outState", outState);
    engine->Execute(mAdjustVelocity, mNumXGroups, mNumYGroups, 1);
}
//----------------------------------------------------------------------------

std::string const Fluid2AdjustVelocity::msHLSLAdjustVelocityString =
GTE_MAKE_HLSL_STRING(
cbuffer Parameters
{
    float4 spaceDelta;    // (dx, dy, 0, 0)
    float4 halfDivDelta;  // (0.5/dx, 0.5/dy, 0, 0)
    float4 timeDelta;     // (dt/dx, dt/dy, 0, dt)
    float4 viscosityX;    // (velVX, velVX, 0, denVX)
    float4 viscosityY;    // (velVX, velVY, 0, denVY)
    float4 epsilon;       // (epsilonX, epsilonY, 0, epsilon0)
};

Texture2D<float4> inState;
Texture2D<float> poisson;
RWTexture2D<float4> outState;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, 1)]
void CSMain(uint2 c : SV_DispatchThreadID)
{
    uint2 dim;
    inState.GetDimensions(dim.x, dim.y);

    int x = int(c.x);
    int y = int(c.y);
    int xm = max(x - 1, 0);
    int xp = min(x + 1, dim.x - 1);
    int ym = max(y - 1, 0);
    int yp = min(y + 1, dim.y - 1);

    // Sample the state at (x,y).
    float4 state = inState[c];

    // Sample Poisson values at immediate neighbors of (x,y).
    float poisPZ = poisson[int2(xp, y)];
    float poisMZ = poisson[int2(xm, y)];
    float poisZP = poisson[int2(x, yp)];
    float poisZM = poisson[int2(x, ym)];

    float4 diff = float4(poisPZ - poisMZ, poisZP - poisZM, 0.0f, 0.0f);
    outState[c] = state + halfDivDelta*diff;
}
);
