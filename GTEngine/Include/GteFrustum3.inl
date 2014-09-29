// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Frustum3<Real>::Frustum3()
    :
    origin((Real)0, (Real)0, (Real)0),
    dVector((Real)0, (Real)0, (Real)1),
    uVector((Real)0, (Real)1, (Real)0),
    rVector((Real)1, (Real)0, (Real)0),
    dMin((Real)1),
    dMax((Real)2),
    uBound((Real)1),
    rBound((Real)1)
{
    Update();
}
//----------------------------------------------------------------------------
template <typename Real>
Frustum3<Real>::Frustum3(Vector3<Real> const& inOrigin,
    Vector3<Real> const& inDVector, Vector3<Real> const& inUVector,
    Vector3<Real> const& inRVector, Real inDMin, Real inDMax, Real inUBound,
    Real inRBound)
    :
    origin(inOrigin),
    dVector(inDVector),
    uVector(inUVector),
    rVector(inRVector),
    dMin(inDMin),
    dMax(inDMax),
    uBound(inUBound),
    rBound(inRBound)
{
    Update();
}
//----------------------------------------------------------------------------
template <typename Real>
void Frustum3<Real>::Update()
{
    mDRatio = dMax / dMin;
    mMTwoUF = ((Real)-2) * uBound * dMax;
    mMTwoRF = ((Real)-2) * rBound * dMax;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real Frustum3<Real>::GetDRatio() const
{
    return mDRatio;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real Frustum3<Real>::GetMTwoUF() const
{
    return mMTwoUF;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real Frustum3<Real>::GetMTwoRF() const
{
    return mMTwoRF;
}
//----------------------------------------------------------------------------
template <typename Real>
void Frustum3<Real>::ComputeVertices(Vector3<Real> vertex[8]) const
{
    Vector3<Real> dScaled = dMin * dVector;
    Vector3<Real> uScaled = uBound * uVector;
    Vector3<Real> rScaled = rBound * rVector;

    vertex[0] = dScaled - uScaled - rScaled;
    vertex[1] = dScaled - uScaled + rScaled;
    vertex[2] = dScaled + uScaled + rScaled;
    vertex[3] = dScaled + uScaled - rScaled;

    for (int i = 0, ip = 4; i < 4; ++i, ++ip)
    {
        vertex[ip] = origin + mDRatio * vertex[i];
        vertex[i] += origin;
    }
}
//----------------------------------------------------------------------------
