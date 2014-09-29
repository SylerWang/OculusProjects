// Geometric Tools, LLC
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringArbitrary<N, Real>::~MassSpringArbitrary()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringArbitrary<N, Real>::MassSpringArbitrary(int numParticles,
    int numSprings, Real step)
    :
    ParticleSystem<N, Real>(numParticles, step),
    mSpring(numSprings),
    mAdjacent(numParticles)
{
    memset(&mSpring[0], 0, numSprings * sizeof(Spring));
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringArbitrary<N, Real>::GetNumSprings () const
{
    return static_cast<int>(mSpring.size());
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void MassSpringArbitrary<N, Real>::SetSpring(int index, Spring const& spring)
{
    mSpring[index] = spring;
    mAdjacent[spring.particle0].insert(index);
    mAdjacent[spring.particle1].insert(index);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
typename MassSpringArbitrary<N, Real>::Spring const&
MassSpringArbitrary<N, Real>::GetSpring(int index) const
{
    return mSpring[index];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringArbitrary<N, Real>::ExternalAcceleration(int, Real,
    std::vector<Vector<N, Real>> const&, std::vector<Vector<N, Real>> const&)
{
    return Vector<N, Real>::Zero();
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringArbitrary<N, Real>::Acceleration(int i, Real time,
    std::vector<Vector<N, Real>> const& position,
    std::vector<Vector<N, Real>> const& velocity)
{
    // Compute spring forces on position X[i].  The positions are not
    // necessarily mkPosition, because the RK4 solver in ParticleSystem
    // evaluates the acceleration function at intermediate positions.

    Vector<N, Real> acceleration = ExternalAcceleration(i, time, position,
        velocity);

    for (auto adj : mAdjacent[i])
    {
        // Process a spring connected to particle i.
        Spring const& spring = mSpring[adj];
        Vector<N, Real> diff;
        if (i != spring.particle0)
        {
            diff = position[spring.particle0] - position[i];
        }
        else
        {
            diff = position[spring.particle1] - position[i];
        }

        Real ratio = spring.length / Length(diff);
        Vector<N, Real> force = spring.constant * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    return acceleration;
}
//----------------------------------------------------------------------------
