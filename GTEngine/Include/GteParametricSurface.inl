// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/18)

//----------------------------------------------------------------------------
template <int N, typename Real>
ParametricSurface<N, Real>::ParametricSurface(Real umin, Real umax,
    Real vmin, Real vmax, bool rectangular)
    :
    mUMin(umin),
    mUMax(umax),
    mVMin(vmin),
    mVMax(vmax),
    mRectangular(rectangular)
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
ParametricSurface<N, Real>::~ParametricSurface()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
ParametricSurface<N, Real>::operator bool() const
{
    return mConstructed;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real ParametricSurface<N, Real>::GetUMin() const
{
    return mUMin;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real ParametricSurface<N, Real>::GetUMax() const
{
    return mUMax;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real ParametricSurface<N, Real>::GetVMin() const
{
    return mVMin;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real ParametricSurface<N, Real>::GetVMax() const
{
    return mVMax;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
bool ParametricSurface<N, Real>::IsRectangular() const
{
    return mRectangular;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> ParametricSurface<N, Real>::GetPosition(Real u, Real v) const
{
    Vector<N, Real> values[6];
    Evaluate(u, v, 0, values);
    return values[0];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> ParametricSurface<N, Real>::GetUTangent(Real u, Real v) const
{
    Vector<N, Real> values[6];
    Evaluate(u, v, 1, values);
    Normalize(values[1]);
    return values[1];
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Vector<N, Real> ParametricSurface<N, Real>::GetVTangent(Real u, Real v) const
{
    Vector<N, Real> values[6];
    Evaluate(u, v, 1, values);
    Normalize(values[2]);
    return values[2];
}
//----------------------------------------------------------------------------
