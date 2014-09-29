// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Sphere3<Real>::Sphere3()
    :
    center(Vector3<Real>::Zero()),
    radius((Real)1)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Sphere3<Real>::Sphere3(Vector3<Real> const& inCenter, Real inRadius)
    :
    center(inCenter),
    radius(inRadius)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Sphere3<Real>::IsEqualTo(Sphere3 const& sphere) const
{
    return center == sphere.center && radius == sphere.radius;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Sphere3<Real>::IsLessThan(Sphere3 const& sphere) const
{
    if (center < sphere.center)
    {
        return true;
    }

    if (center > sphere.center)
    {
        return false;
    }

    return radius < sphere.radius;
}
//----------------------------------------------------------------------------
