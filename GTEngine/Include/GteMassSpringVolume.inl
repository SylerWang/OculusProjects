// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringVolume<N, Real>::~MassSpringVolume()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringVolume<N, Real>::MassSpringVolume(int numSlices, int numRows,
    int numCols, Real step)
    :
    ParticleSystem<N, Real>(numSlices * numRows * numCols, step),
    mNumSlices(numSlices),
    mNumRows(numRows),
    mNumCols(numCols),
    mConstantS(numSlices * numRows * numCols),
    mLengthS(numSlices * numRows * numCols),
    mConstantR(numSlices * numRows * numCols),
    mLengthR(numSlices * numRows * numCols),
    mConstantC(numSlices * numRows * numCols),
    mLengthC(numSlices * numRows * numCols)
{
    std::fill(mConstantS.begin(), mConstantS.end(), (Real)0);
    std::fill(mLengthS.begin(), mLengthS.end(), (Real)0);
    std::fill(mConstantR.begin(), mConstantR.end(), (Real)0);
    std::fill(mLengthR.begin(), mLengthR.end(), (Real)0);
    std::fill(mConstantC.begin(), mConstantC.end(), (Real)0);
    std::fill(mLengthC.begin(), mLengthC.end(), (Real)0);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringVolume<N, Real>::GetNumSlices() const
{
    return mNumSlices;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringVolume<N, Real>::GetNumRows() const
{
    return mNumRows;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringVolume<N, Real>::GetNumCols() const
{
    return mNumCols;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetMass(int s, int r, int c, Real mass)
{
    ParticleSystem<N, Real>::SetMass(GetIndex(s, r, c), mass);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetPosition(int s, int r, int c,
    Vector<N, Real> const& position)
{
    ParticleSystem<N, Real>::SetPosition(GetIndex(s, r, c), position);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetVelocity(int s, int r, int c,
    Vector<N, Real> const& velocity)
{
    ParticleSystem<N, Real>::SetVelocity(GetIndex(s, r, c), velocity);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringVolume<N, Real>::GetMass(int s, int r, int c) const
{
    return ParticleSystem<N, Real>::GetMass(GetIndex(s, r, c));
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> const& MassSpringVolume<N, Real>::GetPosition(int s, int r,
    int c) const
{
    return ParticleSystem<N, Real>::GetPosition(GetIndex(s, r, c));
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> const& MassSpringVolume<N, Real>::GetVelocity(int s, int r,
    int c) const
{
    return ParticleSystem<N, Real>::GetVelocity(GetIndex(s, r, c));
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetConstantS(int s, int r, int c,
    Real constant)
{
    mConstantS[GetIndex(s, r, c)] = constant;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetLengthS(int s, int r, int c, Real length)
{
    mLengthS[GetIndex(s, r, c)] = length;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetConstantR(int s, int r, int c,
    Real constant)
{
    mConstantR[GetIndex(s, r, c)] = constant;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetLengthR(int s, int r, int c, Real length)
{
    mLengthR[GetIndex(s, r, c)] = length;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetConstantC(int s, int r, int c,
    Real constant)
{
    mConstantC[GetIndex(s, r, c)] = constant;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringVolume<N, Real>::SetLengthC(int s, int r, int c, Real length)
{
    mLengthC[GetIndex(s, r, c)] = length;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringVolume<N, Real>::GetConstantS(int s, int r, int c) const
{
    return mConstantS[GetIndex(s, r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringVolume<N, Real>::GetLengthS(int s, int r, int c) const
{
    return mLengthS[GetIndex(s, r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringVolume<N, Real>::GetConstantR(int s, int r, int c) const
{
    return mConstantR[GetIndex(s, r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringVolume<N, Real>::GetLengthR(int s, int r, int c) const
{
    return mLengthR[GetIndex(s, r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringVolume<N, Real>::GetConstantC(int s, int r, int c) const
{
    return mConstantC[GetIndex(s, r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringVolume<N, Real>::GetLengthC(int s, int r, int c) const
{
    return mLengthC[GetIndex(s, r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringVolume<N, Real>::ExternalAcceleration(int, Real,
    std::vector<Vector<N, Real>> const&, std::vector<Vector<N, Real>> const&)
{
    return Vector<N, Real>::Zero();
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringVolume<N, Real>::Acceleration(int i, Real time,
    std::vector<Vector<N, Real>> const& position,
    std::vector<Vector<N, Real>> const& velocity)
{
    // Compute spring forces on position X[i].  The positions are not
    // necessarily mPosition, because the RK4 solver in ParticleSystem
    // evaluates the acceleration function at intermediate positions.  The
    // face, edge, and corner points of the volume of masses must be handled
    // separately, because each has fewer than eight springs attached to it.

    Vector<N, Real> acceleration = ExternalAcceleration(i, time, position,
        velocity);

    Vector<N, Real> diff, force;
    Real ratio;

    int s, r, c, prev, next;
    GetCoordinates(i, s, r, c);

    if (s > 0)
    {
        prev = i - mNumRows * mNumCols;  // index to previous s-neighbor
        diff = position[prev] - position[i];
        ratio = GetLengthS(s - 1, r, c) / Length(diff);
        force = GetConstantS(s - 1, r, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (s < mNumSlices - 1)
    {
        next = i + mNumRows * mNumCols;  // index to next s-neighbor
        diff = position[next] - position[i];
        ratio = GetLengthS(s, r, c)/Length(diff);
        force = GetConstantS(s, r, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (r > 0)
    {
        prev = i - mNumCols;  // index to previous r-neighbor
        diff = position[prev] - position[i];
        ratio = GetLengthR(s, r - 1, c) / Length(diff);
        force = GetConstantR(s, r - 1, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (r < mNumRows - 1)
    {
        next = i + mNumCols;  // index to next r-neighbor
        diff = position[next] - position[i];
        ratio = GetLengthR(s, r, c) / Length(diff);
        force = GetConstantR(s, r, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (c > 0)
    {
        prev = i - 1;  // index to previous c-neighbor
        diff = position[prev] - position[i];
        ratio = GetLengthC(s, r, c - 1) / Length(diff);
        force = GetConstantC(s, r, c - 1) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (c < mNumCols - 1)
    {
        next = i + 1;  // index to next c-neighbor
        diff = position[next] - position[i];
        ratio = GetLengthC(s, r, c) / Length(diff);
        force = GetConstantC(s, r, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    return acceleration;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringVolume<N, Real>::GetIndex(int s, int r, int c) const
{
    return c + mNumCols * (r + mNumRows * s);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void MassSpringVolume<N, Real>::GetCoordinates(int i, int& s, int& r, int& c)
    const
{
    c = i % mNumCols;
    i = (i - c) / mNumCols;
    r = i % mNumRows;
    s = i / mNumRows;
}
//----------------------------------------------------------------------------
