// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GTEnginePCH.h"
#include "GteFluid3UpdateState.h"
#include "GteShaderFactory.h"
using namespace gte;

//----------------------------------------------------------------------------
Fluid3UpdateState::~Fluid3UpdateState()
{
}
//----------------------------------------------------------------------------
Fluid3UpdateState::Fluid3UpdateState(int xSize, int ySize, int zSize,
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

    // Create the shader for generating velocity from vortices.
    mComputeUpdateState.reset(ShaderFactory::CreateCompute("UpdateState",
        msHLSLUpdateStateString, definer));
    LogAssert(mComputeUpdateState != nullptr,
        "Cannot create compute shader.");

    mUpdateState.reset(new Texture3(DF_R32G32B32A32_FLOAT, xSize, ySize,
        zSize));
    mUpdateState->SetUsage(Resource::SHADER_OUTPUT);

    mAdvectionSampler.reset(new SamplerState());
    mAdvectionSampler->filter = SamplerState::MIN_L_MAG_L_MIP_P;
    mAdvectionSampler->mode[0] = SamplerState::CLAMP;
    mAdvectionSampler->mode[1] = SamplerState::CLAMP;
    mAdvectionSampler->mode[2] = SamplerState::CLAMP;

    mComputeUpdateState->Set("Parameters", parameters);
    mComputeUpdateState->Set("advectionSampler", mAdvectionSampler);
    mComputeUpdateState->Set("updateState", mUpdateState);
}
//----------------------------------------------------------------------------
std::shared_ptr<Texture3> const& Fluid3UpdateState::GetUpdateState() const
{
    return mUpdateState;
}
//----------------------------------------------------------------------------
void Fluid3UpdateState::Execute(DX11Engine* engine,
    std::shared_ptr<Texture3> const& source,
    std::shared_ptr<Texture3> const& stateTm1,
    std::shared_ptr<Texture3> const& stateT)
{
    mComputeUpdateState->Set("source", source);
    mComputeUpdateState->Set("stateTm1", stateTm1);
    mComputeUpdateState->Set("stateT", stateT);
    engine->Execute(mComputeUpdateState, mNumXGroups, mNumYGroups,
        mNumZGroups);
}
//----------------------------------------------------------------------------

std::string const Fluid3UpdateState::msHLSLUpdateStateString =
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

Texture3D<float4> source;
Texture3D<float4> stateTm1;
Texture3D<float4> stateT;
SamplerState advectionSampler;  // trilinear, clamp
RWTexture3D<float4> updateState;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, NUM_Z_THREADS)]
void CSMain(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    stateT.GetDimensions(dim.x, dim.y, dim.z);

    int x = int(c.x);
    int y = int(c.y);
    int z = int(c.z);
    int xm = max(x - 1, 0);
    int xp = min(x + 1, dim.x - 1);
    int ym = max(y - 1, 0);
    int yp = min(y + 1, dim.y - 1);
    int zm = max(z - 1, 0);
    int zp = min(z + 1, dim.z - 1);

    // Sample states at (x,y,z) and immediate neighbors.
    float4 stateZZZ = stateT[int3(x, y, z)];
    float4 statePZZ = stateT[int3(xp, y, z)];
    float4 stateMZZ = stateT[int3(xm, y, z)];
    float4 stateZPZ = stateT[int3(x, yp, z)];
    float4 stateZMZ = stateT[int3(x, ym, z)];
    float4 stateZZP = stateT[int3(x, y, zp)];
    float4 stateZZM = stateT[int3(x, y, zm)];

    // Sample the source state at (x,y,z).
    float4 src = source[int3(x, y, z)];

    // Estimate second-order derivatives of state at (x,y,z).
    float4 stateDXX = statePZZ - 2.0f*stateZZZ + stateMZZ;
    float4 stateDYY = stateZPZ - 2.0f*stateZZZ + stateZMZ;
    float4 stateDZZ = stateZZP - 2.0f*stateZZZ + stateZZM;

    // Compute advection.
    float3 tcd = spaceDelta.xyz*(c.xyz - timeDelta.xyz*stateZZZ.xyz + 0.5f);
    float4 advection = stateTm1.SampleLevel(advectionSampler, tcd, 0.0f);

    // Update the state.
    updateState[c.xyz] = advection +
        (viscosityX*stateDXX + viscosityY*stateDYY + +viscosityZ*stateDZZ +
        timeDelta.w*src);
}
);
