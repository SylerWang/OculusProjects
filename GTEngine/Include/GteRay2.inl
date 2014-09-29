// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Ray2<Real>::Ray2()
    :
    origin(Vector2<Real>::Origin()),
    direction(Vector2<Real>::Basis0())
{
}
//----------------------------------------------------------------------------
template <typename Real>
Ray2<Real>::Ray2(Vector2<Real> const& inOrigin,
    Vector2<Real> const& inDirection)
    :
    origin(inOrigin),
    direction(inDirection)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ray2<Real>::IsEqualTo(Ray2 const& ray) const
{
    return origin == ray.origin && direction == ray.direction;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ray2<Real>::IsLessThan(Ray2 const& ray) const
{
    if (origin < ray.origin)
    {
        return true;
    }

    if (origin > ray.origin)
    {
        return false;
    }

    return direction < ray.direction;
}
//----------------------------------------------------------------------------
