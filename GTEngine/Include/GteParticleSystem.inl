// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

//----------------------------------------------------------------------------
template <int N, typename Real>
ParticleSystem<N, Real>::~ParticleSystem()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
ParticleSystem<N, Real>::ParticleSystem(int numParticles, Real step)
    :
    mNumParticles(numParticles),
    mMass(numParticles),
    mInvMass(numParticles),
    mPosition(numParticles),
    mVelocity(numParticles),
    mStep(step),
    mHalfStep(step / (Real)2),
    mSixthStep(step / (Real)6),
    mPTmp(numParticles),
    mVTmp(numParticles),
    mPAllTmp(numParticles),
    mVAllTmp(numParticles)
{
    std::fill(mMass.begin(), mMass.end(), (Real)0);
    std::fill(mInvMass.begin(), mInvMass.end(), (Real)0);
    std::fill(mPosition.begin(), mPosition.end(), Vector<N, Real>::Zero());
    std::fill(mVelocity.begin(), mVelocity.end(), Vector<N, Real>::Zero());
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int ParticleSystem<N, Real>::GetNumParticles() const
{
    return mNumParticles;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void ParticleSystem<N, Real>::SetMass(int i, Real mass)
{
    if ((Real)0 < mass && mass < std::numeric_limits<Real>::max())
    {
        mMass[i] = mass;
        mInvMass[i] = ((Real)1) / mass;
    }
    else
    {
        mMass[i] = std::numeric_limits<Real>::max();
        mInvMass[i] = (Real)0;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void ParticleSystem<N, Real>::SetPosition(int i,
    Vector<N, Real> const& position)
{
    mPosition[i] = position;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void ParticleSystem<N, Real>::SetVelocity(int i,
    Vector<N, Real> const& velocity)
{
    mVelocity[i] = velocity;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void ParticleSystem<N, Real>::SetStep(Real step)
{
    mStep = step;
    mHalfStep = mStep / (Real)2;
    mSixthStep = mStep / (Real)6;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& ParticleSystem<N, Real>::GetMass(int i) const
{
    return mMass[i];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> const& ParticleSystem<N, Real>::GetPosition(int i) const
{
    return mPosition[i];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> const& ParticleSystem<N, Real>::GetVelocity(int i) const
{
    return mVelocity[i];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real ParticleSystem<N, Real>::GetStep() const
{
    return mStep;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void ParticleSystem<N, Real>::Update(Real time)
{
    // Runge-Kutta fourth-order solver.
    Real halfTime = time + mHalfStep;
    Real fullTime = time + mStep;

    // Compute the first step.
    int i;
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] > (Real)0)
        {
            mPAllTmp[i].d1 = mVelocity[i];
            mVAllTmp[i].d1 = Acceleration(i, time, mPosition, mVelocity);
        }
    }
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] >(Real)0)
        {
            mPTmp[i] = mPosition[i] + mHalfStep * mPAllTmp[i].d1;
            mVTmp[i] = mVelocity[i] + mHalfStep * mVAllTmp[i].d1;
        }
        else
        {
            mPTmp[i] = mPosition[i];
            mVTmp[i].MakeZero();
        }
    }

    // Compute the second step.
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] >(Real)0)
        {
            mPAllTmp[i].d2 = mVTmp[i];
            mVAllTmp[i].d2 = Acceleration(i, halfTime, mPTmp, mVTmp);
        }
    }
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] >(Real)0)
        {
            mPTmp[i] = mPosition[i] + mHalfStep * mPAllTmp[i].d2;
            mVTmp[i] = mVelocity[i] + mHalfStep * mVAllTmp[i].d2;
        }
        else
        {
            mPTmp[i] = mPosition[i];
            mVTmp[i].MakeZero();
        }
    }

    // Compute the third step.
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] >(Real)0)
        {
            mPAllTmp[i].d3 = mVTmp[i];
            mVAllTmp[i].d3 = Acceleration(i, halfTime, mPTmp, mVTmp);
        }
    }
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] >(Real)0)
        {
            mPTmp[i] = mPosition[i] + mStep * mPAllTmp[i].d3;
            mVTmp[i] = mVelocity[i] + mStep * mVAllTmp[i].d3;
        }
        else
        {
            mPTmp[i] = mPosition[i];
            mVTmp[i].MakeZero();
        }
    }

    // Compute the fourth step.
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] >(Real)0)
        {
            mPAllTmp[i].d4 = mVTmp[i];
            mVAllTmp[i].d4 = Acceleration(i, fullTime, mPTmp, mVTmp);
        }
    }
    for (i = 0; i < mNumParticles; ++i)
    {
        if (mInvMass[i] >(Real)0)
        {
            mPosition[i] += mSixthStep * (mPAllTmp[i].d1 +
                ((Real)2) * (mPAllTmp[i].d2 + mPAllTmp[i].d3) +
                mPAllTmp[i].d4);

            mVelocity[i] += mSixthStep * (mVAllTmp[i].d1 +
                ((Real)2) * (mVAllTmp[i].d2 + mVAllTmp[i].d3) +
                mVAllTmp[i].d4);
        }
    }
}
//----------------------------------------------------------------------------
