// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Ray2<Real>, OrientedBox2<Real>>::Result
TIQuery<Real, Ray2<Real>, OrientedBox2<Real>>::operator()(
    Ray2<Real> const& ray, OrientedBox2<Real> const& box)
{
    // Transform the ray to the oriented-box coordinate system.
    Vector2<Real> diff = ray.origin - box.center;
    Vector2<Real> rayOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1])
    );
    Vector2<Real> rayDirection = Vector2<Real>
    (
        Dot(ray.direction, box.axis[0]),
        Dot(ray.direction, box.axis[1])
    );

    Result result;
    this->DoQuery(rayOrigin, rayDirection, box.extent, result);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Ray2<Real>, OrientedBox2<Real>>::Result
FIQuery<Real, Ray2<Real>, OrientedBox2<Real>>::operator()(
    Ray2<Real> const& ray, OrientedBox2<Real> const& box)
{
    // Transform the ray to the oriented-box coordinate system.
    Vector2<Real> diff = ray.origin - box.center;
    Vector2<Real> rayOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1])
    );
    Vector2<Real> rayDirection = Vector2<Real>
    (
        Dot(ray.direction, box.axis[0]),
        Dot(ray.direction, box.axis[1])
    );

    Result result;
    this->DoQuery(rayOrigin, rayDirection, box.extent, result);
    for (int i = 0; i < result.numIntersections; ++i)
    {
        result.point[i] = ray.origin + result.parameter[i] * ray.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
