// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

#pragma once

#include "GteVector.h"
#include <limits>
#include <vector>

namespace gte
{

template <int N, typename Real>
class ParticleSystem
{
public:
    // Construction and destruction.  If a particle is to be immovable, set
    // its mass to std::numeric_limits<Real>::max().
    virtual ~ParticleSystem();
    ParticleSystem(int numParticles, Real step);

    // Member access.
    inline int GetNumParticles() const;
    void SetMass(int i, Real mass);
    inline void SetPosition(int i, Vector<N, Real> const& position);
    inline void SetVelocity(int i, Vector<N, Real> const& velocity);
    void SetStep(Real step);
    inline Real const& GetMass(int i) const;
    inline Vector<N, Real> const& GetPosition(int i) const;
    inline Vector<N, Real> const& GetVelocity(int i) const;
    inline Real GetStep() const;

    // Update the particle positions based on current time and particle state.
    // The Acceleration(...) function is called in this update for each
    // particle.  This function is virtual so that derived classes can perform
    // pre-update and/or post-update semantics.
    virtual void Update(Real time);

protected:
    // Callback for acceleration (ODE solver uses x" = F/m) applied to
    // particle i.  The positions and velocities are not necessarily
    // mPosition and mVelocity, because the ODE solver evaluates the
    // impulse function at intermediate positions.
    virtual Vector<N, Real> Acceleration(int i, Real time,
        std::vector<Vector<N, Real>> const& position,
        std::vector<Vector<N, Real>> const& velocity) = 0;

    int mNumParticles;
    std::vector<Real> mMass, mInvMass;
    std::vector<Vector<N, Real>> mPosition, mVelocity;
    Real mStep, mHalfStep, mSixthStep;

    // Temporary storage for the Runge-Kutta differential equation solver.
    struct Temporary
    {
        Vector<N, Real> d1, d2, d3, d4;
    };
    std::vector<Vector<N, Real>> mPTmp, mVTmp;
    std::vector<Temporary> mPAllTmp, mVAllTmp;
};

#include "GteParticleSystem.inl"

}
