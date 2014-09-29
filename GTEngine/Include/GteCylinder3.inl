// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Cylinder3<Real>::Cylinder3()
    :
    axis(Line3<Real>()),
    radius((Real)1),
    height((Real)1)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Cylinder3<Real>::Cylinder3(Line3<Real> const& inAxis, Real inRadius,
    Real inHeight)
    :
    axis(inAxis),
    radius(inRadius),
    height(inHeight)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Cylinder3<Real>::IsEqualTo(Cylinder3 const& cylinder) const
{
    return axis == cylinder.axis
        && radius == cylinder.radius
        && height == cylinder.height;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Cylinder3<Real>::IsLessThan(Cylinder3 const& cylinder) const
{
    if (axis < cylinder.axis)
    {
        return true;
    }

    if (axis > cylinder.axis)
    {
        return false;
    }

    if (radius < cylinder.radius)
    {
        return true;
    }

    if (radius > cylinder.radius)
    {
        return false;
    }

    return height < cylinder.height;
}
//----------------------------------------------------------------------------
