// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Ray3<Real>::Ray3()
    :
    origin(Vector3<Real>::Origin()),
    direction(Vector3<Real>::Basis0())
{
}
//----------------------------------------------------------------------------
template <typename Real>
Ray3<Real>::Ray3(Vector3<Real> const& inOrigin,
    Vector3<Real> const& inDirection)
    :
    origin(inOrigin),
    direction(inDirection)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ray3<Real>::IsEqualTo(Ray3 const& ray) const
{
    return origin == ray.origin && direction == ray.direction;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ray3<Real>::IsLessThan(Ray3 const& ray) const
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
