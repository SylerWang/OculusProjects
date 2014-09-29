// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector3<Real>, Ray3<Real>>::Result
DCPQuery<Real, Vector3<Real>, Ray3<Real>>::operator()(
    Vector3<Real> const& point, Ray3<Real> const& ray)
{
    Result result;

    Vector3<Real> diff = point - ray.origin;
    result.rayParameter = Dot(ray.direction, diff);
    if (result.rayParameter > (Real)0)
    {
        result.rayClosestPoint =
            ray.origin + result.rayParameter*ray.direction;
    }
    else
    {
        result.rayClosestPoint = ray.origin;
    }

    diff = point - result.rayClosestPoint;
    result.sqrDistance = Dot(diff, diff);
    result.distance = sqrt(result.sqrDistance);

    return result;
}
//----------------------------------------------------------------------------
