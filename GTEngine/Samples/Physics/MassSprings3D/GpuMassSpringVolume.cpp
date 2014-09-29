// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "GpuMassSpringVolume.h"

//----------------------------------------------------------------------------
GpuMassSpringVolume::~GpuMassSpringVolume()
{
}
//----------------------------------------------------------------------------
GpuMassSpringVolume::GpuMassSpringVolume(int numColumns, int numRows,
    int numSlices, float step, float viscosity, Environment& environment,
    bool& created)
    :
    mNumColumns(numColumns),
    mNumRows(numRows),
    mNumSlices(numSlices)
{
    created = false;

    // Create the shaders.
    std::string path = environment.GetPath("RungeKutta.hlsl");
    int const numThreads = 4;
    HLSLDefiner definer;
    definer.SetInt("NUM_X_THREADS", numThreads);
    definer.SetInt("NUM_Y_THREADS", numThreads);
    definer.SetInt("NUM_Z_THREADS", numThreads);

    mRK4Shader[0].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step1a"));
    if (!mRK4Shader[0])
    {
        LogError("Failed to compile RK4Step1a of RungeKutta.hlsl");
        return;
    }

    mRK4Shader[1].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step1b"));
    if (!mRK4Shader[1])
    {
        LogError("Failed to compile RK4Step1b of RungeKutta.hlsl");
        return;
    }

    mRK4Shader[2].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step2a"));
    if (!mRK4Shader[2])
    {
        LogError("Failed to compile RK4Step2a of RungeKutta.hlsl");
        return;
    }

    mRK4Shader[3].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step2b"));
    if (!mRK4Shader[3])
    {
        LogError("Failed to compile RK4Step2b of RungeKutta.hlsl");
        return;
    }

    mRK4Shader[4].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step3a"));
    if (!mRK4Shader[4])
    {
        LogError("Failed to compile RK4Step3a of RungeKutta.hlsl");
        return;
    }

    mRK4Shader[5].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step3b"));
    if (!mRK4Shader[5])
    {
        LogError("Failed to compile RK4Step3b of RungeKutta.hlsl");
        return;
    }

    mRK4Shader[6].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step4a"));
    if (!mRK4Shader[6])
    {
        LogError("Failed to compile RK4Step4a of RungeKutta.hlsl");
        return;
    }

    mRK4Shader[7].reset(ShaderFactory::CreateCompute(path, definer,
        "RK4Step4b"));
    if (!mRK4Shader[7])
    {
        LogError("Failed to compile RK4Step4b of RungeKutta.hlsl");
        return;
    }

    // The cbuffer is tightly packed.  Only time, halfTime, and fullTime vary.
    mParameters.reset(new ConstantBuffer(sizeof(SimulationParameters), true));
    SimulationParameters& p = *mParameters->Get<SimulationParameters>();
    p.dimensions[0] = numColumns;
    p.dimensions[1] = numRows;
    p.dimensions[2] = numSlices;
    p.dimensions[3] = numColumns * numRows;
    p.viscosity = viscosity;
    p.time = 0.0f;
    p.delta = step;
    p.halfDelta = p.delta / 2.0f;
    p.sixthDelta = p.delta / 6.0f;
    p.halfTime = p.time + p.halfDelta;
    p.fullTime = p.time + p.delta;

    unsigned int const numParticles = p.dimensions[2] * p.dimensions[3];
    size_t const vecsize = sizeof(Vector3<float>);
    mMass.reset(new StructuredBuffer(numParticles, sizeof(float)));
    mInvMass.reset(new StructuredBuffer(numParticles, sizeof(float)));
    mPosition.reset(new StructuredBuffer(numParticles, vecsize));
    mPosition->SetUsage(Resource::SHADER_OUTPUT);
    mPosition->SetCopyType(Resource::COPY_STAGING_TO_CPU);
    mVelocity.reset(new StructuredBuffer(numParticles, vecsize));
    mVelocity->SetUsage(Resource::SHADER_OUTPUT);
    mConstantC.reset(new StructuredBuffer(numParticles, sizeof(float)));
    mLengthC.reset(new StructuredBuffer(numParticles, sizeof(float)));
    mConstantR.reset(new StructuredBuffer(numParticles, sizeof(float)));
    mLengthR.reset(new StructuredBuffer(numParticles, sizeof(float)));
    mConstantS.reset(new StructuredBuffer(numParticles, sizeof(float)));
    mLengthS.reset(new StructuredBuffer(numParticles, sizeof(float)));

    mPTmp.reset(new StructuredBuffer(numParticles, vecsize, true));
    mPTmp->SetUsage(Resource::SHADER_OUTPUT);
    mPTmp->SetCopyType(Resource::COPY_STAGING_TO_CPU);
    mPAllTmp.reset(new StructuredBuffer(numParticles, 4 * vecsize, true));
    mPAllTmp->SetUsage(Resource::SHADER_OUTPUT);
    mPAllTmp->SetCopyType(Resource::COPY_STAGING_TO_CPU);
    mVTmp.reset(new StructuredBuffer(numParticles, vecsize, true));
    mVTmp->SetUsage(Resource::SHADER_OUTPUT);
    mVTmp->SetCopyType(Resource::COPY_STAGING_TO_CPU);
    mVAllTmp.reset(new StructuredBuffer(numParticles, 4 * vecsize, true));
    mVAllTmp->SetUsage(Resource::SHADER_OUTPUT);
    mVAllTmp->SetCopyType(Resource::COPY_STAGING_TO_CPU);

    mNumXGroups = p.dimensions[0] / numThreads;
    mNumYGroups = p.dimensions[1] / numThreads;
    mNumZGroups = p.dimensions[2] / numThreads;

    mRK4Shader[0]->Set("SimulationParameters", mParameters);
    mRK4Shader[0]->Set("invMass", mInvMass);
    mRK4Shader[0]->Set("constantC", mConstantC);
    mRK4Shader[0]->Set("lengthC", mLengthC);
    mRK4Shader[0]->Set("constantR", mConstantR);
    mRK4Shader[0]->Set("lengthR", mLengthR);
    mRK4Shader[0]->Set("constantS", mConstantS);
    mRK4Shader[0]->Set("lengthS", mLengthS);
    mRK4Shader[0]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[0]->Set("vAllTmp", mVAllTmp);
    mRK4Shader[0]->Set("position", mPosition);
    mRK4Shader[0]->Set("velocity", mVelocity);

    mRK4Shader[1]->Set("SimulationParameters", mParameters);
    mRK4Shader[1]->Set("invMass", mInvMass);
    mRK4Shader[1]->Set("pTmp", mPTmp);
    mRK4Shader[1]->Set("vTmp", mVTmp);
    mRK4Shader[1]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[1]->Set("vAllTmp", mVAllTmp);
    mRK4Shader[1]->Set("position", mPosition);
    mRK4Shader[1]->Set("velocity", mVelocity);

    mRK4Shader[2]->Set("SimulationParameters", mParameters);
    mRK4Shader[2]->Set("invMass", mInvMass);
    mRK4Shader[2]->Set("constantC", mConstantC);
    mRK4Shader[2]->Set("lengthC", mLengthC);
    mRK4Shader[2]->Set("constantR", mConstantR);
    mRK4Shader[2]->Set("lengthR", mLengthR);
    mRK4Shader[2]->Set("constantS", mConstantS);
    mRK4Shader[2]->Set("lengthS", mLengthS);
    mRK4Shader[2]->Set("pTmp", mPTmp);
    mRK4Shader[2]->Set("vTmp", mVTmp);
    mRK4Shader[2]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[2]->Set("vAllTmp", mVAllTmp);
    mRK4Shader[2]->Set("velocity", mVelocity);

    mRK4Shader[3]->Set("SimulationParameters", mParameters);
    mRK4Shader[3]->Set("invMass", mInvMass);
    mRK4Shader[3]->Set("pTmp", mPTmp);
    mRK4Shader[3]->Set("vTmp", mVTmp);
    mRK4Shader[3]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[3]->Set("vAllTmp", mVAllTmp);
    mRK4Shader[3]->Set("position", mPosition);
    mRK4Shader[3]->Set("velocity", mVelocity);

    mRK4Shader[4]->Set("SimulationParameters", mParameters);
    mRK4Shader[4]->Set("invMass", mInvMass);
    mRK4Shader[4]->Set("constantC", mConstantC);
    mRK4Shader[4]->Set("lengthC", mLengthC);
    mRK4Shader[4]->Set("constantR", mConstantR);
    mRK4Shader[4]->Set("lengthR", mLengthR);
    mRK4Shader[4]->Set("constantS", mConstantS);
    mRK4Shader[4]->Set("lengthS", mLengthS);
    mRK4Shader[4]->Set("pTmp", mPTmp);
    mRK4Shader[4]->Set("vTmp", mVTmp);
    mRK4Shader[4]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[4]->Set("vAllTmp", mVAllTmp);
    mRK4Shader[4]->Set("velocity", mVelocity);

    mRK4Shader[5]->Set("SimulationParameters", mParameters);
    mRK4Shader[5]->Set("invMass", mInvMass);
    mRK4Shader[5]->Set("pTmp", mPTmp);
    mRK4Shader[5]->Set("vTmp", mVTmp);
    mRK4Shader[5]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[5]->Set("vAllTmp", mVAllTmp);
    mRK4Shader[5]->Set("position", mPosition);
    mRK4Shader[5]->Set("velocity", mVelocity);

    mRK4Shader[6]->Set("SimulationParameters", mParameters);
    mRK4Shader[6]->Set("invMass", mInvMass);
    mRK4Shader[6]->Set("constantC", mConstantC);
    mRK4Shader[6]->Set("lengthC", mLengthC);
    mRK4Shader[6]->Set("constantR", mConstantR);
    mRK4Shader[6]->Set("lengthR", mLengthR);
    mRK4Shader[6]->Set("constantS", mConstantS);
    mRK4Shader[6]->Set("lengthS", mLengthS);
    mRK4Shader[6]->Set("pTmp", mPTmp);
    mRK4Shader[6]->Set("vTmp", mVTmp);
    mRK4Shader[6]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[6]->Set("vAllTmp", mVAllTmp);
    mRK4Shader[6]->Set("velocity", mVelocity);

    mRK4Shader[7]->Set("SimulationParameters", mParameters);
    mRK4Shader[7]->Set("invMass", mInvMass);
    mRK4Shader[7]->Set("position", mPosition);
    mRK4Shader[7]->Set("velocity", mVelocity);
    mRK4Shader[7]->Set("pAllTmp", mPAllTmp);
    mRK4Shader[7]->Set("vAllTmp", mVAllTmp);

    created = true;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetMass(int c, int r, int s, float mass)
{
    if (0.0f < mass && mass < std::numeric_limits<float>::max())
    {
        mMass->Get<float>()[GetIndex(c, r, s)] = mass;
        mInvMass->Get<float>()[GetIndex(c, r, s)] = 1.0f / mass;
    }
    else
    {
        mMass->Get<float>()[GetIndex(c, r, s)] =
            std::numeric_limits<float>::max();
        mInvMass->Get<float>()[GetIndex(c, r, s)] = 0.0f;
    }
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetPosition(int c, int r, int s,
    Vector3<float> const& position)
{
    mPosition->Get<Vector3<float>>()[GetIndex(c, r, s)] = position;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetVelocity(int c, int r, int s,
    Vector3<float> const& velocity)
{
    mVelocity->Get<Vector3<float>>()[GetIndex(c, r, s)] = velocity;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetConstantC(int c, int r, int s, float v)
{
    mConstantC->Get<float>()[GetIndex(c, r, s)] = v;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetLengthC(int c, int r, int s, float v)
{
    mLengthC->Get<float>()[GetIndex(c, r, s)] = v;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetConstantR(int c, int r, int s, float v)
{
    mConstantR->Get<float>()[GetIndex(c, r, s)] = v;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetLengthR(int c, int r, int s, float v)
{
    mLengthR->Get<float>()[GetIndex(c, r, s)] = v;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetConstantS(int c, int r, int s, float v)
{
    mConstantS->Get<float>()[GetIndex(c, r, s)] = v;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::SetLengthS(int c, int r, int s, float v)
{
    mLengthS->Get<float>()[GetIndex(c, r, s)] = v;
}
//----------------------------------------------------------------------------
Vector3<float> GpuMassSpringVolume::GetPosition(int c, int r, int s) const
{
    return mPosition->Get<Vector3<float>>()[GetIndex(c, r, s)];
}
//----------------------------------------------------------------------------
std::shared_ptr<StructuredBuffer>& GpuMassSpringVolume::GetPosition()
{
    return mPosition;
}
//----------------------------------------------------------------------------
void GpuMassSpringVolume::Update(float time, DX11Engine* engine)
{
    SimulationParameters& p = *mParameters->Get<SimulationParameters>();
    p.time = time;
    p.halfTime = p.time + p.halfDelta;
    p.fullTime = p.time + p.delta;
    engine->Update(mParameters);

    for (int i = 0; i < 8; ++i)
    {
        engine->Execute(mRK4Shader[i], mNumXGroups, mNumYGroups, mNumZGroups);
    }
}
//----------------------------------------------------------------------------
