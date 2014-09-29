// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Ray3<Real>, Sphere3<Real>>::Result
TIQuery<Real, Ray3<Real>, Sphere3<Real>>::operator()(
    Ray3<Real> const& ray, Sphere3<Real> const& sphere)
{
    // The sphere is (X-C)^T*(X-C)-1 = 0 and the line is X = P+t*D.
    // Substitute the line equation into the sphere equation to obtain a
    // quadratic equation Q(t) = t^2 + 2*a1*t + a0 = 0, where a1 = D^T*(P-C),
    // and a0 = (P-C)^T*(P-C)-1.
    Result result;

    Vector3<Real> diff = ray.origin - sphere.center;
    Real a0 = Dot(diff, diff) - sphere.radius * sphere.radius;
    if (a0 <= (Real)0)
    {
        // P is inside the sphere.
        result.intersect = true;
        return result;
    }
    // else: P is outside the sphere

    Real a1 = Dot(ray.direction, diff);
    if (a1 >= (Real)0)
    {
        result.intersect = false;
        return result;
    }

    // Intersection occurs when Q(t) has real roots.
    Real discr = a1*a1 - a0;
    result.intersect = (discr >= (Real)0);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Ray3<Real>, Sphere3<Real>>::Result
FIQuery<Real, Ray3<Real>, Sphere3<Real>>::operator()(
    Ray3<Real> const& ray, Sphere3<Real> const& sphere)
{
    Result result;
    DoQuery(ray.origin, ray.direction, sphere, result);
    for (int i = 0; i < result.numIntersections; ++i)
    {
        result.point[i] = ray.origin + result.parameter[i] * ray.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void FIQuery<Real, Ray3<Real>, Sphere3<Real>>::DoQuery(
    Vector3<Real> const& rayOrigin, Vector3<Real> const& rayDirection,
    Sphere3<Real> const& sphere, Result& result)
{
    FIQuery<Real, Line3<Real>, Sphere3<Real>>::DoQuery(rayOrigin,
        rayDirection, sphere, result);

    if (result.intersect)
    {
        // The line containing the ray intersects the sphere; the t-interval
        // is [t0,t1].  The ray intersects the sphere as long as [t0,t1]
        // overlaps the ray t-interval [0,+infinity).
        std::array<Real, 2> rayInterval =
            { (Real)0, std::numeric_limits<Real>::max() };
        FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>> iiQuery;
        result.parameter = iiQuery(result.parameter, rayInterval).overlap;
    }
}
//----------------------------------------------------------------------------
