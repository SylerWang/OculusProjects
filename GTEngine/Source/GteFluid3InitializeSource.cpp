// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/31)

#include "GTEnginePCH.h"
#include "GteFluid3InitializeSource.h"
#include "GteShaderFactory.h"
#include <random>
using namespace gte;

//----------------------------------------------------------------------------
Fluid3InitializeSource::~Fluid3InitializeSource()
{
}
//----------------------------------------------------------------------------
Fluid3InitializeSource::Fluid3InitializeSource(int xSize, int ySize,
    int zSize, int numXThreads, int numYThreads, int numZThreads,
    std::shared_ptr<ConstantBuffer> const& parameters)
    :
    mNumXGroups(xSize/numXThreads),
    mNumYGroups(ySize/numYThreads),
    mNumZGroups(zSize/numZThreads)
{
    // Create the resources for generating velocity from vortices.
    mVortex.reset(new ConstantBuffer(sizeof(Vortex), true));
    mVelocity0.reset(new Texture3(DF_R32G32B32A32_FLOAT, xSize, ySize, zSize));
    mVelocity0->SetUsage(Resource::SHADER_OUTPUT);
    mVelocity1.reset(new Texture3(DF_R32G32B32A32_FLOAT, xSize, ySize, zSize));
    mVelocity1->SetUsage(Resource::SHADER_OUTPUT);

    // Create the resources for generating velocity from wind and gravity.
    mExternal.reset(new ConstantBuffer(sizeof(External), false));
    External& e = *mExternal->Get<External>();
    e.densityProducer = Vector4<float>(0.5f, 0.5f, 0.5f, 0.0f);
    e.densityPData = Vector4<float>(0.01f, 16.0f, 0.0f, 0.0f);
    e.densityConsumer = Vector4<float>(0.75f, 0.75f, 0.75f, 0.0f);
    e.densityCData = Vector4<float>(0.01f, 0.0f, 0.0f, 0.0f);
    e.gravity = Vector4<float>(0.0f, 0.0f, 0.0f, 0.0f);
    e.windData = Vector4<float>(0.001f, 0.0f, 0.0f, 0.0f);
    mSource.reset(new Texture3(DF_R32G32B32A32_FLOAT, xSize, ySize, zSize));
    mSource->SetUsage(Resource::SHADER_OUTPUT);

    // Create the shader for generating velocity from vortices.
    HLSLDefiner definer;
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Y_THREADS", numYThreads);
    definer.SetInt("NUM_Z_THREADS", numZThreads);
    mGenerateVortex.reset(ShaderFactory::CreateCompute("GenerateVortex",
        msHLSLGenerateVortexString, definer));
    LogAssert(mGenerateVortex != nullptr, "Cannot create compute shader.");
    mGenerateVortex->Set("Parameters", parameters);
    mGenerateVortex->Set("Vortex", mVortex);
    mGenerateVortex->Set("inVelocity", mVelocity0);
    mGenerateVortex->Set("outVelocity", mVelocity1);

    // Create the shader for generating the sources to the fluid simulation.
    mInitializeSource.reset(ShaderFactory::CreateCompute("InitializeSource",
        msHLSLInitializeSourceString, definer));
    LogAssert(mInitializeSource != nullptr, "Cannot create compute shader.");
    mInitializeSource->Set("Parameters", parameters);
    mInitializeSource->Set("External", mExternal);
    mInitializeSource->Set("source", mSource);
}
//----------------------------------------------------------------------------
std::shared_ptr<Texture3> const& Fluid3InitializeSource::GetSource() const
{
    return mSource;
}
//----------------------------------------------------------------------------
void Fluid3InitializeSource::Execute(DX11Engine* engine)
{
    // Use a Mersenne twister engine for random numbers.
    std::mt19937 mte;
    std::uniform_real_distribution<float> unirnd(0.0f, 1.0f);
    std::uniform_real_distribution<float> symrnd(-1.0f, 1.0f);
    std::uniform_real_distribution<float> posrnd0(0.001f, 0.01f);
    std::uniform_real_distribution<float> posrnd1(64.0f, 128.0f);

    // Compute the velocity one vortex at a time.  After the loop terminates,
    // the final velocity is stored in mVelocity0.
    memset(mVelocity0->GetData(), 0, mVelocity0->GetNumBytes());
    Vortex& v = *mVortex->Get<Vortex>();
    for (int i = 0; i < NUM_VORTICES; ++i)
    {
        v.position[0] = unirnd(mte);
        v.position[1] = unirnd(mte);
        v.position[2] = unirnd(mte);
        v.position[3] = 0.0f;
        v.normal[0] = symrnd(mte);
        v.normal[1] = symrnd(mte);
        v.normal[2] = symrnd(mte);
        v.normal[3] = 0.0f;
        Normalize(v.normal);
        v.data[0] = posrnd0(mte);
        v.data[1] = posrnd1(mte);
        v.data[2] = 0.0f;
        v.data[3] = 0.0f;
        engine->Update(mVortex);

        engine->Execute(mGenerateVortex, mNumXGroups, mNumYGroups,
            mNumZGroups);

        std::swap(mVelocity0, mVelocity1);
        mGenerateVortex->Set("inVelocity", mVelocity0);
        mGenerateVortex->Set("outVelocity", mVelocity1);
    }

    // Compute the sources for the fluid simulation.
    mInitializeSource->Set("vortexVelocity", mVelocity0);
    engine->Execute(mInitializeSource, mNumXGroups, mNumYGroups, mNumZGroups);
}
//----------------------------------------------------------------------------

std::string const Fluid3InitializeSource::msHLSLGenerateVortexString =
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

cbuffer Vortex
{
    float4 position;  // (px, py, pz, *)
    float4 normal;    // (nx, ny, nz, *)
    float4 data;      // (variance, amplitude, *, *)
};

Texture3D<float4> inVelocity;
RWTexture3D<float4> outVelocity;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, NUM_Z_THREADS)]
void CSMain(uint3 c : SV_DispatchThreadID)
{
    float3 location = spaceDelta.xyz*(c.xyz + 0.5f);
    float3 diff = location - position.xyz;
    float arg = -dot(diff, diff) / data.x;
    float magnitude = data.y*exp(arg);
    float4 vortexVelocity = float4(magnitude*cross(normal.xyz, diff), 0.0f);
    outVelocity[c.xyz] = inVelocity[c.xyz] + vortexVelocity;
}
);

std::string const Fluid3InitializeSource::msHLSLInitializeSourceString =
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

cbuffer External
{
    float4 densityProducer;  // (x, y, z, *)
    float4 densityPData;     // (variance, amplitude, *, *)
    float4 densityConsumer;  // (x, y, z, *)
    float4 densityCData;     // (variance, amplitude, *, *)
    float4 gravity;          // (x, y, z, *)
    float4 windData;         // (variance, amplitude, *, *)
};

Texture3D<float4> vortexVelocity;
RWTexture3D<float4> source;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, NUM_Z_THREADS)]
void CSMain(uint3 c : SV_DispatchThreadID)
{
    // Compute the location of the voxel (x,y,z) in normalized [0,1]^3.
    float3 location = spaceDelta.xyz*(c.xyz + 0.5f);

    // Compute an input to the fluid simulation consisting of a producer of
    // density and a consumer of density.
    float3 diff = location - densityProducer.xyz;
    float arg = -dot(diff, diff) / densityPData.x;
    float density = densityPData.y*exp(arg);
    diff = location - densityConsumer.xyz;
    arg = -dot(diff, diff) / densityCData.x;
    density -= densityCData.y*exp(arg);

    // Compute an input to the fluid simulation consisting of gravity,
    // a single wind source, and vortex impulses.
    float windArg = -dot(location.xz, location.xz) / windData.x;
    float3 windVelocity = float3(0.0f, windData.y*exp(windArg), 0.0f);
    float3 velocity = gravity.xyz + windVelocity + vortexVelocity[c.xyz].xyz;

    source[c.xyz] = float4(velocity.xyz, density);
}
);
