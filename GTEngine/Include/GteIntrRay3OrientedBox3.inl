// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Ray3<Real>, OrientedBox3<Real>>::Result
TIQuery<Real, Ray3<Real>, OrientedBox3<Real>>::operator()(
    Ray3<Real> const& ray, OrientedBox3<Real> const& box)
{
    // Transform the ray to the oriented-box coordinate system.
    Vector3<Real> diff = ray.origin - box.center;
    Vector3<Real> rayOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1]),
        Dot(diff, box.axis[2])
    );
    Vector3<Real> rayDirection = Vector3<Real>
    (
        Dot(ray.direction, box.axis[0]),
        Dot(ray.direction, box.axis[1]),
        Dot(ray.direction, box.axis[2])
    );

    Result result;
    this->DoQuery(rayOrigin, rayDirection, box.extent, result);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Ray3<Real>, OrientedBox3<Real>>::Result
FIQuery<Real, Ray3<Real>, OrientedBox3<Real>>::operator()(
    Ray3<Real> const& ray, OrientedBox3<Real> const& box)
{
    // Transform the ray to the oriented-box coordinate system.
    Vector3<Real> diff = ray.origin - box.center;
    Vector3<Real> rayOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1]),
        Dot(diff, box.axis[2])
    );
    Vector3<Real> rayDirection = Vector3<Real>
    (
        Dot(ray.direction, box.axis[0]),
        Dot(ray.direction, box.axis[1]),
        Dot(ray.direction, box.axis[2])
    );

    Result result;
    this->DoQuery(rayOrigin, rayDirection, box.extent, result);
    for (int i = 0; i < result.numPoints; ++i)
    {
        result.point[i] =
            ray.origin + result.lineParameter[i] * ray.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
