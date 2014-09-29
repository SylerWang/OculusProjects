// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Circle2<Real>::Circle2()
    :
    center(Vector2<Real>::Zero()),
    radius((Real)1)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Circle2<Real>::Circle2(Vector2<Real> const& inCenter, Real inRadius)
    :
    center(inCenter),
    radius(inRadius)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Circle2<Real>::IsEqualTo(Circle2 const& circle) const
{
    return center == circle.center && radius == circle.radius;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Circle2<Real>::IsLessThan(Circle2 const& circle) const
{
    if (center < circle.center)
    {
        return true;
    }

    if (center > circle.center)
    {
        return false;
    }

    return radius < circle.radius;
}
//----------------------------------------------------------------------------
