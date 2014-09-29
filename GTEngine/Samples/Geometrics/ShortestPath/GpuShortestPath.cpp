// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GpuShortestPath.h"
#include "GteBitHacks.h"

//----------------------------------------------------------------------------
GpuShortestPath::GpuShortestPath(std::shared_ptr<Texture2> const& weights,
    Environment const& env, bool& created)
    :
    mSize(static_cast<int>(weights->GetWidth()))
{
    created = false;
    mLogSize = Log2OfPowerOfTwo(mSize);

    mDistance.reset(new Texture2(DF_R32_FLOAT, mSize, mSize));
    mDistance->SetUsage(Resource::SHADER_OUTPUT);
    memset(mDistance->GetData(), 0, mDistance->GetNumBytes());

    mPrevious.reset(new Texture2(DF_R32G32_SINT, mSize, mSize));
    mPrevious->SetUsage(Resource::SHADER_OUTPUT);
    mPrevious->SetCopyType(Resource::COPY_STAGING_TO_CPU);

    mSegment.reset(new ConstantBuffer(3 * sizeof(int), true));

    HLSLDefiner definer;
    definer.SetInt("ISIZE", mSize);
    mInitializeDiagToRow.reset(ShaderFactory::CreateCompute(
        env.GetPath("InitializeDiagToRow.hlsl"), definer));
    if (!mInitializeDiagToRow)
    {
        LogError("Failed to compile InitializeDiagToRow.hlsl.");
        return;
    }
    mInitializeDiagToRow->Set("weights", weights);
    mInitializeDiagToRow->Set("previous", mPrevious);
    mInitializeDiagToRow->Set("sum", mDistance);

    mInitializeDiagToCol.reset(ShaderFactory::CreateCompute(
        env.GetPath("InitializeDiagToCol.hlsl"), definer));
    if (!mInitializeDiagToCol)
    {
        LogError("Failed to compile InitializeDiagToCol.hlsl.");
        return;
    }
    mInitializeDiagToCol->Set("weights", weights);
    mInitializeDiagToCol->Set("previous", mPrevious);
    mInitializeDiagToCol->Set("sum", mDistance);

    mPartialSumDiagToRow.resize(mLogSize);
    mPartialSumDiagToCol.resize(mLogSize);
    for (int i = 0; i < mLogSize; ++i)
    {
        definer.SetInt("LOGN", mLogSize);
        definer.SetInt("P", i + 1);
        mPartialSumDiagToRow[i].reset(ShaderFactory::CreateCompute(
            env.GetPath("PartialSumsDiagToRow.hlsl"), definer));
        if (!mPartialSumDiagToRow[i])
        {
            LogError("Failed to compile PartialSumsDiagToRow.hlsl.");
            return;
        }
        mPartialSumDiagToRow[i]->Set("sum", mDistance);

        mPartialSumDiagToCol[i].reset(ShaderFactory::CreateCompute(
            env.GetPath("PartialSumsDiagToCol.hlsl"), definer));
        if (!mPartialSumDiagToCol[i])
        {
            LogError("Failed to compile PartialSumsDiagToCol.hlsl.");
            return;
        }
        mPartialSumDiagToCol[i]->Set("sum", mDistance);
    }

    mUpdate.reset(ShaderFactory::CreateCompute(
        env.GetPath("UpdateShader.hlsl"), definer));
    if (!mUpdate)
    {
        LogError("Failed to compile UpdateShader.hlsl.");
        return;
    }
    mUpdate->Set("Segment", mSegment);
    mUpdate->Set("weights", weights);
    mUpdate->Set("distance", mDistance);
    mUpdate->Set("previous", mPrevious);
    created = true;
}
//----------------------------------------------------------------------------
void GpuShortestPath::Compute(DX11Engine* engine,
    std::stack<std::pair<int, int>>& path)
{
    // Execute the shaders.
    engine->Execute(mInitializeDiagToRow, 1, 1, 1);
    for (int i = 0; i < mLogSize; ++i)
    {
        engine->Execute(mPartialSumDiagToRow[i], 1, 1, 1);
    }

    engine->Execute(mInitializeDiagToCol, 1, 1, 1);
    for (int i = 0; i < mLogSize; ++i)
    {
        engine->Execute(mPartialSumDiagToCol[i], 1, 1, 1);
    }

    int* segment = mSegment->Get<int>();
    for (int z = 2, numPixels = z - 1; z < mSize; ++z, ++numPixels)
    {
        segment[0] = 1;
        segment[1] = z - 1;
        segment[2] = numPixels;
        engine->Update(mSegment);
        engine->Execute(mUpdate, 1, 1, 1);
    }

    int const zmax = 2 * (mSize - 1);
    for (int z = mSize, numPixels = zmax - z + 1; z <= zmax; ++z, --numPixels)
    {
        segment[0] = z - (mSize - 1);
        segment[1] = mSize - 1;
        segment[2] = numPixels;
        engine->Update(mSegment);
        engine->Execute(mUpdate, 1, 1, 1);
    }

    // Read back the path from GPU memory.
    engine->CopyGpuToCpu(mPrevious);
    std::array<int, 2>* location = mPrevious->Get<std::array<int, 2>>();

    // Create the path by starting at (mXSize-1,mYSize-1) and following the
    // previous links.
    int x = mSize - 1, y = mSize - 1;
    while (x != -1 && y != -1)
    {
        path.push(std::make_pair(x, y));
        std::array<int, 2> prev = location[x + mSize*y];
        x = prev[0];
        y = prev[1];
    }
}
//----------------------------------------------------------------------------
