// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Cone3<Real>::Cone3()
    :
    vertex(Vector3<Real>::Zero()),
    axis(Vector3<Real>::Basis2()),
    cosAngle((Real)GTE_C_QUARTER_PI),
    sinAngle((Real)GTE_C_QUARTER_PI),
    height((Real)1)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Cone3<Real>::Cone3(Vector3<Real> const& inVertex, Vector3<Real> const& inAxis,
    Real angle, Real inHeight)
    :
    vertex(inVertex),
    axis(inAxis),
    cosAngle(cos(angle)),
    sinAngle(sin(angle)),
    height(inHeight)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Cone3<Real>::Cone3(Vector3<Real> const& inVertex, Vector3<Real> const& inAxis,
    Real inCosAngle, Real inSinAngle, Real inHeight)
    :
    vertex(inVertex),
    axis(inAxis),
    cosAngle(inCosAngle),
    sinAngle(inSinAngle),
    height(inHeight)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Cone3<Real>::IsEqualTo(Cone3 const& cone) const
{
    return vertex == cone.vertex
        && axis == cone.axis
        && cosAngle == cone.cosAngle
        && sinAngle == cone.sinAngle
        && height == cone.height;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Cone3<Real>::IsLessThan(Cone3 const& cone) const
{
    if (vertex < cone.vertex)
    {
        return true;
    }

    if (vertex > cone.vertex)
    {
        return false;
    }

    if (axis < cone.axis)
    {
        return true;
    }

    if (axis > cone.axis)
    {
        return false;
    }

    if (cosAngle < cone.cosAngle)
    {
        return true;
    }

    if (cosAngle > cone.cosAngle)
    {
        return false;
    }

    if (sinAngle < cone.sinAngle)
    {
        return true;
    }

    if (sinAngle > cone.sinAngle)
    {
        return false;
    }

    return height < cone.height;
}
//----------------------------------------------------------------------------
