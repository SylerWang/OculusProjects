// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GTEnginePCH.h"
#include "GteFluid3AdjustVelocity.h"
#include "GteShaderFactory.h"
using namespace gte;

//----------------------------------------------------------------------------
Fluid3AdjustVelocity::~Fluid3AdjustVelocity()
{
}
//----------------------------------------------------------------------------
Fluid3AdjustVelocity::Fluid3AdjustVelocity(int xSize, int ySize, int zSize,
    int numXThreads, int numYThreads, int numZThreads,
    std::shared_ptr<ConstantBuffer> const& parameters)
    :
    mNumXGroups(xSize/numXThreads),
    mNumYGroups(ySize/numYThreads),
    mNumZGroups(zSize/numZThreads)
{
    HLSLDefiner definer;
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Y_THREADS", numYThreads);
    definer.SetInt("NUM_Z_THREADS", numZThreads);

    mAdjustVelocity.reset(ShaderFactory::CreateCompute("AdjustVelocity",
        msHLSLAdjustVelocityString, definer));
    LogAssert(mAdjustVelocity != nullptr, "Cannot create compute shader.");

    mAdjustVelocity->Set("Parameters", parameters);
}
//----------------------------------------------------------------------------
void Fluid3AdjustVelocity::Execute(DX11Engine* engine,
    std::shared_ptr<Texture3> const& inState,
    std::shared_ptr<Texture3> const& poisson,
    std::shared_ptr<Texture3> const& outState)
{
    mAdjustVelocity->Set("inState", inState);
    mAdjustVelocity->Set("poisson", poisson);
    mAdjustVelocity->Set("outState", outState);
    engine->Execute(mAdjustVelocity, mNumXGroups, mNumYGroups, mNumZGroups);
}
//----------------------------------------------------------------------------

std::string const Fluid3AdjustVelocity::msHLSLAdjustVelocityString =
GTE_MAKE_HLSL_STRING(
cbuffer Parameters
{
    float4 spaceDelta;    // (dx, dy, dz, 0)
    float4 halfDivDelta;  // (0.5/dx, 0.5/dy, 0.5/dz, 0)
    float4 timeDelta;     // (dt/dx, dt/dy, dt/dz, dt)
    float4 viscosityX;    // (velVX, velVX, velVX, denVX)
    float4 viscosityY;    // (velVX, velVY, velVY, denVY)
    float4 viscosityZ;    // (velVZ, velVZ, velVZ, denVZ)
    float4 epsilon;       // (epsilonX, epsilonY, epsilonZ, epsilon0)
};

Texture3D<float4> inState;
Texture3D<float> poisson;
RWTexture3D<float4> outState;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, NUM_Z_THREADS)]
void CSMain(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    inState.GetDimensions(dim.x, dim.y, dim.z);

    int x = int(c.x);
    int y = int(c.y);
    int z = int(c.z);
    int xm = max(x - 1, 0);
    int xp = min(x + 1, dim.x - 1);
    int ym = max(y - 1, 0);
    int yp = min(y + 1, dim.y - 1);
    int zm = max(z - 1, 0);
    int zp = min(z + 1, dim.z - 1);

    // Sample the state at (x,y,z).
    float4 state = inState[c.xyz];

    // Sample Poisson values at immediate neighbors of (x,y,z).
    float poisPZZ = poisson[int3(xp, y, z)];
    float poisMZZ = poisson[int3(xm, y, z)];
    float poisZPZ = poisson[int3(x, yp, z)];
    float poisZMZ = poisson[int3(x, ym, z)];
    float poisZZP = poisson[int3(x, y, zp)];
    float poisZZM = poisson[int3(x, y, zm)];

    float4 diff = float4(poisPZZ - poisMZZ, poisZPZ - poisZMZ,
        poisZZP - poisZZM, 0.0f);
    outState[c.xyz] = state + halfDivDelta*diff;
}
);
