// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Sphere3<Real>, Sphere3<Real>>::Result
TIQuery<Real, Sphere3<Real>, Sphere3<Real>>::operator()(
    Sphere3<Real> const& sphere0, Sphere3<Real> const& sphere1)
{
    Result result;
    Vector3<Real> diff = sphere1.center - sphere0.center;
    Real rSum = sphere0.radius + sphere1.radius;
    result.intersect = (Dot(diff, diff) <= rSum*rSum);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Sphere3<Real>, Sphere3<Real>>::Result
FIQuery<Real, Sphere3<Real>, Sphere3<Real>>::operator()(
    Sphere3<Real> const& sphere0, Sphere3<Real> const& sphere1)
{
    Result result;

    // The plane of intersection must have C1-C0 as its normal direction.
    Vector3<Real> C1mC0 = sphere1.center - sphere0.center;
    Real sqrLen = Dot(C1mC0, C1mC0);
    Real r0 = sphere0.radius, r1 = sphere1.radius;
    Real rSum = r0 + r1;
    Real rSumSqr = rSum * rSum;

    if (sqrLen > rSumSqr)
    {
        // The spheres are disjoint/separated.
        result.intersect = false;
        result.type = 0;
        return result;
    }

    if (sqrLen == rSumSqr)
    {
        // The spheres are just touching with each sphere outside the other.
        Normalize(C1mC0);
        result.intersect = true;
        result.type = 1;
        result.point = sphere0.center + r0 * C1mC0;
        return result;
    }

    Real rDif = r0 - r1;
    Real rDifSqr = rDif*rDif;
    if (sqrLen < rDifSqr)
    {
        // One sphere is strictly contained in the other.  Compute a point in
        // the intersection set.
        result.intersect = true;
        result.type = (rDif <= (Real)0 ? 3 : 5);
        result.point = ((Real)0.5)*(sphere0.center + sphere1.center);
        return result;
    }
    if (sqrLen == rDifSqr)
    {
        // One sphere is contained in the other sphere but with a single point
        // of contact.
        Normalize(C1mC0);
        result.intersect = true;
        if (rDif <= (Real)0)
        {
            result.type = 4;
            result.point = sphere1.center + r1 * C1mC0;
        }
        else
        {
            result.type = 6;
            result.point = sphere0.center + r0 * C1mC0;
        }
        return result;
    }

    // Compute t for which the circle of intersection has center
    // K = C0 + t*(C1 - C0).
    Real t = ((Real)0.5) * ((Real)1 + rDif * rSum / sqrLen);

    // Compute the center and radius of the circle of intersection.
    result.circle.center = sphere0.center + t * C1mC0;
    result.circle.radius = sqrt(std::max(r0*r0 - t*t*sqrLen, (Real)0));

    // Compute the normal for the plane of the circle.
    Normalize(C1mC0);
    result.circle.normal = C1mC0;

    // The intersection is a circle.
    result.intersect = true;
    result.type = 2;
    return result;
}
//----------------------------------------------------------------------------
