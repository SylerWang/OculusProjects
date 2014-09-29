// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Circle3<Real>::Circle3()
    :
    center(Vector3<Real>::Zero()),
    normal(Vector3<Real>::Basis2()),
    radius((Real)1)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Circle3<Real>::Circle3(Vector3<Real> const& inCenter,
    Vector3<Real> const& inNormal, Real inRadius)
    :
    center(inCenter),
    normal(inNormal),
    radius(inRadius)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Circle3<Real>::IsEqualTo(Circle3 const& circle) const
{
    return center == circle.center
        && normal == circle.normal
        && radius == circle.radius;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Circle3<Real>::IsLessThan(Circle3 const& circle) const
{
    if (center < circle.center)
    {
        return true;
    }

    if (center > circle.center)
    {
        return false;
    }

    if (normal < circle.normal)
    {
        return true;
    }

    if (normal > circle.normal)
    {
        return false;
    }

    return radius < circle.radius;
}
//----------------------------------------------------------------------------
