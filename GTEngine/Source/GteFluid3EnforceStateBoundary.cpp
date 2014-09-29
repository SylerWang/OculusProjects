// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GTEnginePCH.h"
#include "GteFluid3EnforceStateBoundary.h"
#include "GteShaderFactory.h"
using namespace gte;

//----------------------------------------------------------------------------
Fluid3EnforceStateBoundary::~Fluid3EnforceStateBoundary()
{
}
//----------------------------------------------------------------------------
Fluid3EnforceStateBoundary::Fluid3EnforceStateBoundary(int xSize, int ySize,
    int zSize, int numXThreads, int numYThreads, int numZThreads)
    :
    mNumXGroups(xSize/numXThreads),
    mNumYGroups(ySize/numYThreads),
    mNumZGroups(zSize/numZThreads)
{
    mXMin.reset(new Texture2(DF_R32G32_FLOAT, ySize, zSize));
    mXMin->SetUsage(Resource::SHADER_OUTPUT);
    mXMax.reset(new Texture2(DF_R32G32_FLOAT, ySize, zSize));
    mXMax->SetUsage(Resource::SHADER_OUTPUT);
    mYMin.reset(new Texture2(DF_R32G32_FLOAT, xSize, zSize));
    mYMin->SetUsage(Resource::SHADER_OUTPUT);
    mYMax.reset(new Texture2(DF_R32G32_FLOAT, xSize, zSize));
    mYMax->SetUsage(Resource::SHADER_OUTPUT);
    mZMin.reset(new Texture2(DF_R32G32_FLOAT, xSize, ySize));
    mZMin->SetUsage(Resource::SHADER_OUTPUT);
    mZMax.reset(new Texture2(DF_R32G32_FLOAT, xSize, ySize));
    mZMax->SetUsage(Resource::SHADER_OUTPUT);

    HLSLDefiner definer;
    definer.SetInt("USE_COPY_X_FACE", 1);
    definer.SetInt("NUM_Y_THREADS", numYThreads);
    definer.SetInt("NUM_Z_THREADS", numZThreads);
    mCopyXFace.reset(
        ShaderFactory::CreateCompute("CopyXFace",
        msHLSLEnforceStateBoundaryString, definer, "CopyXFace"));
    mCopyXFace->Set("xMin", mXMin);
    mCopyXFace->Set("xMax", mXMax);

    definer.Clear();
    definer.SetInt("USE_WRITE_X_FACE", 1);
    definer.SetInt("NUM_Y_THREADS", numYThreads);
    definer.SetInt("NUM_Z_THREADS", numZThreads);
    mWriteXFace.reset(
        ShaderFactory::CreateCompute("WriteXFace",
        msHLSLEnforceStateBoundaryString, definer, "WriteXFace"));
    mWriteXFace->Set("xMin", mXMin);
    mWriteXFace->Set("xMax", mXMax);

    definer.Clear();
    definer.SetInt("USE_COPY_Y_FACE", 1);
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Z_THREADS", numZThreads);
    mCopyYFace.reset(
        ShaderFactory::CreateCompute("CopyYFace",
        msHLSLEnforceStateBoundaryString, definer, "CopyYFace"));
    mCopyYFace->Set("yMin", mYMin);
    mCopyYFace->Set("yMax", mYMax);

    definer.Clear();
    definer.SetInt("USE_WRITE_Y_FACE", 1);
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Z_THREADS", numZThreads);
    mWriteYFace.reset(
        ShaderFactory::CreateCompute("WriteYFace",
        msHLSLEnforceStateBoundaryString, definer, "WriteYFace"));
    mWriteYFace->Set("yMin", mYMin);
    mWriteYFace->Set("yMax", mYMax);

    definer.Clear();
    definer.SetInt("USE_COPY_Z_FACE", 1);
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Y_THREADS", numYThreads);
    mCopyZFace.reset(
        ShaderFactory::CreateCompute("CopyZFace",
        msHLSLEnforceStateBoundaryString, definer, "CopyZFace"));
    mCopyZFace->Set("zMin", mZMin);
    mCopyZFace->Set("zMax", mZMax);

    definer.Clear();
    definer.SetInt("USE_WRITE_Z_FACE", 1);
    definer.SetInt("NUM_X_THREADS", numXThreads);
    definer.SetInt("NUM_Y_THREADS", numYThreads);
    mWriteZFace.reset(
        ShaderFactory::CreateCompute("WriteZFace",
        msHLSLEnforceStateBoundaryString, definer, "WriteZFace"));
    mWriteZFace->Set("zMin", mZMin);
    mWriteZFace->Set("zMax", mZMax);
}
//----------------------------------------------------------------------------
void Fluid3EnforceStateBoundary::Execute(DX11Engine* engine,
    std::shared_ptr<Texture3> const& state)
{
    // in: state
    // out: mXMin, mXMax
    mCopyXFace->Set("state", state);
    engine->Execute(mCopyXFace, 1, mNumYGroups, mNumZGroups);

    // in: mXMin, mXMax
    // out: state
    mWriteXFace->Set("state", state);
    engine->Execute(mWriteXFace, 1, mNumYGroups, mNumZGroups);

    // in: state
    // out: mYMin, mYMax
    mCopyYFace->Set("state", state);
    engine->Execute(mCopyYFace, mNumXGroups, 1, mNumZGroups);

    // in: mYMin, mYMax
    // out: state
    mWriteYFace->Set("state", state);
    engine->Execute(mWriteYFace, mNumXGroups, 1, mNumZGroups);

    // in: state
    // out: mZMin, mZMax
    mCopyZFace->Set("state", state);
    engine->Execute(mCopyZFace, mNumXGroups, mNumYGroups, 1);

    // in: mZMin, mZMax
    // out: state
    mWriteZFace->Set("state", state);
    engine->Execute(mWriteZFace, mNumXGroups, mNumYGroups, 1);
}
//----------------------------------------------------------------------------

std::string const
Fluid3EnforceStateBoundary::msHLSLEnforceStateBoundaryString =
GTE_MAKE_HLSL_STRING(
#if USE_COPY_X_FACE
Texture3D<float4> state;
RWTexture2D<float2> xMin;
RWTexture2D<float2> xMax;

[numthreads(1, NUM_Y_THREADS, NUM_Z_THREADS)]
void CopyXFace(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    state.GetDimensions(dim.x, dim.y, dim.z);
    xMin[c.yz] = state[uint3(1, c.y, c.z)].yz;
    xMax[c.yz] = state[uint3(dim.x - 2, c.y, c.z)].yz;
}
#endif

#if USE_WRITE_X_FACE
Texture2D<float2> xMin;
Texture2D<float2> xMax;
RWTexture3D<float4> state;

[numthreads(1, NUM_Y_THREADS, NUM_Z_THREADS)]
void WriteXFace(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    state.GetDimensions(dim.x, dim.y, dim.z);
    state[uint3(0, c.y, c.z)] = float4(0.0f, xMin[c.yz].x, xMin[c.yz].y, 0.0f);
    state[uint3(dim.x - 1, c.y, c.z)] = float4(0.0f, xMax[c.yz].x, xMax[c.yz].y, 0.0f);
}
#endif

#if USE_COPY_Y_FACE
Texture3D<float4> state;
RWTexture2D<float2> yMin;
RWTexture2D<float2> yMax;

[numthreads(NUM_X_THREADS, 1, NUM_Z_THREADS)]
void CopyYFace(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    state.GetDimensions(dim.x, dim.y, dim.z);
    yMin[c.xz] = state[uint3(c.x, 1, c.z)].xz;
    yMax[c.xz] = state[uint3(c.x, dim.y - 2, c.z)].xz;
}
#endif

#if USE_WRITE_Y_FACE
Texture2D<float2> yMin;
Texture2D<float2> yMax;
RWTexture3D<float4> state;

[numthreads(NUM_X_THREADS, 1, NUM_Z_THREADS)]
void WriteYFace(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    state.GetDimensions(dim.x, dim.y, dim.z);
    state[uint3(c.x, 0, c.z)] = float4(yMin[c.xz].x, 0.0f, yMin[c.xz].y, 0.0f);
    state[uint3(c.x, dim.y - 1, c.z)] = float4(yMax[c.xz].x, 0.0f, yMax[c.xz].y, 0.0f);
}
#endif

#if USE_COPY_Z_FACE
Texture3D<float4> state;
RWTexture2D<float2> zMin;
RWTexture2D<float2> zMax;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, 1)]
void CopyZFace(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    state.GetDimensions(dim.x, dim.y, dim.z);
    zMin[c.xy] = state[uint3(c.x, c.y, 1)].xy;
    zMax[c.xy] = state[uint3(c.x, c.y, dim.z - 2)].xy;
}
#endif

#if USE_WRITE_Z_FACE
Texture2D<float2> zMin;
Texture2D<float2> zMax;
RWTexture3D<float4> state;

[numthreads(NUM_X_THREADS, NUM_Y_THREADS, 1)]
void WriteZFace(uint3 c : SV_DispatchThreadID)
{
    uint3 dim;
    state.GetDimensions(dim.x, dim.y, dim.z);
    state[uint3(c.x, c.y, 0)] = float4(zMin[c.xy].x, zMin[c.xy].y, 0.0f, 0.0f);
    state[uint3(c.x, c.y, dim.z - 1)] = float4(zMax[c.xy].x, zMax[c.xy].y, 0.0f, 0.0f);
}
#endif
);
