// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringSurface<N, Real>::~MassSpringSurface()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
MassSpringSurface<N, Real>::MassSpringSurface(int numRows, int numCols,
    Real step)
    :
    ParticleSystem<N, Real>(numRows * numCols, step),
    mNumRows(numRows),
    mNumCols(numCols),
    mConstantR(numRows * numCols),
    mLengthR(numRows * numCols),
    mConstantC(numRows * numCols),
    mLengthC(numRows * numCols)
{
    std::fill(mConstantR.begin(), mConstantR.end(), (Real)0);
    std::fill(mLengthR.begin(), mLengthR.end(), (Real)0);
    std::fill(mConstantC.begin(), mConstantC.end(), (Real)0);
    std::fill(mLengthC.begin(), mLengthC.end(), (Real)0);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringSurface<N, Real>::GetNumRows() const
{
    return mNumRows;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringSurface<N, Real>::GetNumCols() const
{
    return mNumCols;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::SetMass(int r, int c, Real mass)
{
    ParticleSystem<N, Real>::SetMass(GetIndex(r, c), mass);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::SetPosition(int r, int c,
    Vector<N, Real> const& position)
{
    ParticleSystem<N, Real>::SetPosition(GetIndex(r, c), position);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::SetVelocity(int r, int c,
    Vector<N, Real> const& position)
{
    ParticleSystem<N, Real>::SetVelocity(GetIndex(r, c), position);
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringSurface<N, Real>::GetMass(int r, int c) const
{
    return ParticleSystem<N, Real>::GetMass(GetIndex(r, c));
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> const& MassSpringSurface<N, Real>::GetPosition(int r, int c)
    const
{
    return ParticleSystem<N, Real>::GetPosition(GetIndex(r, c));
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> const& MassSpringSurface<N, Real>::GetVelocity(int r, int c)
    const
{
    return ParticleSystem<N, Real>::GetVelocity(GetIndex(r, c));
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::SetConstantR (int r, int c, Real constant)
{
    mConstantR[GetIndex(r, c)] = constant;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::SetLengthR(int r, int c, Real length)
{
    mLengthR[GetIndex(r, c)] = length;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::SetConstantC(int r, int c, Real constant)
{
    mConstantC[GetIndex(r, c)] = constant;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::SetLengthC(int r, int c, Real length)
{
    mLengthC[GetIndex(r, c)] = length;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringSurface<N, Real>::GetConstantR(int r, int c) const
{
    return mConstantR[GetIndex(r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringSurface<N, Real>::GetLengthR(int r, int c) const
{
    return mLengthR[GetIndex(r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringSurface<N, Real>::GetConstantC(int r, int c) const
{
    return mConstantC[GetIndex(r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const& MassSpringSurface<N, Real>::GetLengthC(int r, int c) const
{
    return mLengthC[GetIndex(r, c)];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringSurface<N, Real>::ExternalAcceleration(int, Real,
    std::vector<Vector<N, Real>> const&, std::vector<Vector<N, Real>> const&)
{
    return Vector<N, Real>::Zero();
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> MassSpringSurface<N, Real>::Acceleration(int i, Real time,
    std::vector<Vector<N, Real>> const& position,
    std::vector<Vector<N, Real>> const& velocity)
{
    // Compute spring forces on position X[i].  The positions are not
    // necessarily mPosition, because the RK4 solver in ParticleSystem
    // evaluates the acceleration function at intermediate positions.  The
    // edge and corner points of the surface of masses must be handled
    // separately, because each has fewer than four springs attached to it.

    Vector<N, Real> acceleration = ExternalAcceleration(i, time, position,
        velocity);

    Vector<N, Real> diff, force;
    Real ratio;

    int r, c, prev, next;
    GetCoordinates(i, r, c);

    if (r > 0)
    {
        prev = i - mNumCols;  // index to previous row-neighbor
        diff = position[prev] - position[i];
        ratio = GetLengthR(r - 1, c) / Length(diff);
        force = GetConstantR(r - 1, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (r < mNumRows - 1)
    {
        next = i + mNumCols;  // index to next row-neighbor
        diff = position[next] - position[i];
        ratio = GetLengthR(r, c) / Length(diff);
        force = GetConstantR(r, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (c > 0)
    {
        prev = i - 1;  // index to previous col-neighbor
        diff = position[prev] - position[i];
        ratio = GetLengthC(r, c - 1) / Length(diff);
        force = GetConstantC(r, c - 1) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    if (c < mNumCols - 1)
    {
        next = i + 1;  // index to next col-neighbor
        diff = position[next] - position[i];
        ratio = GetLengthC(r, c) / Length(diff);
        force = GetConstantC(r, c) * ((Real)1 - ratio) * diff;
        acceleration += this->mInvMass[i] * force;
    }

    return acceleration;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int MassSpringSurface<N, Real>::GetIndex(int r, int c) const
{
    return c + mNumCols * r;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
void MassSpringSurface<N, Real>::GetCoordinates(int i, int& r, int& c) const
{
    c = i % mNumCols;
    r = i / mNumCols;
}
//----------------------------------------------------------------------------
