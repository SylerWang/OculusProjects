// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringCurve<N, Real>::~MassSpringCurve()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringCurve<N, Real>::MassSpringCurve(int numParticles, Real step)
    :
    ParticleSystem<N, Real>(numParticles, step),
    mConstant(numParticles - 1),
    mLength(numParticles - 1)
{
    std::fill(mConstant.begin(), mConstant.end(), (Real)0);
    std::fill(mLength.begin(), mLength.end(), (Real)0);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringCurve<N, Real>::GetNumSprings() const
{
    return this->mNumParticles - 1;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringCurve<N, Real>::SetConstant(int i, Real constant)
{
    mConstant[i] = constant;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringCurve<N, Real>::SetLength(int i, Real length)
{
    mLength[i] = length;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringCurve<N, Real>::GetConstant(int i) const
{
    return mConstant[i];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringCurve<N, Real>::GetLength(int i) const
{
    return mLength[i];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringCurve<N, Real>::ExternalAcceleration(int, Real,
    std::vector<Vector<N, Real>> const&, std::vector<Vector<N, Real>> const&)
{
    return Vector<N, Real>::Zero();
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringCurve<N, Real>::Acceleration(int i, Real time,
    std::vector<Vector<N, Real>> const& position,
    std::vector<Vector<N, Real>> const& velocity)
{
    // Compute spring forces on position X[i].  The positions are not
    // necessarily mPosition, because the RK4 solver in ParticleSystem
    // evaluates the acceleration function at intermediate positions.  The end
    // points of the curve of masses must be handled separately, because each
    // has only one spring attached to it.

    Vector<N, Real> acceleration = ExternalAcceleration(i, time, position,
        velocity);

    Vector<N, Real> diff, force;
    Real ratio;

    if (i > 0)
    {
        int iM1 = i - 1;
        diff = position[iM1] - position[i];
        ratio = mLength[iM1] / Length(diff);
        force = mConstant[iM1] * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    int iP1 = i + 1;
    if (iP1 < this->mNumParticles)
    {
        diff = position[iP1] - position[i];
        ratio = mLength[i] / Length(diff);
        force = mConstant[i] * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i]*force;
    }

    return acceleration;
}
//----------------------------------------------------------------------------
