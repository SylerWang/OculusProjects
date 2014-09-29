// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Line3<Real>, Ray3<Real>>::Result
DCPQuery<Real, Line3<Real>, Ray3<Real>>::operator()(
    Line3<Real> const& line, Ray3<Real> const& ray)
{
    Result result;

    Vector3<Real> diff = line.origin - ray.origin;
    Real a01 = -Dot(line.direction, ray.direction);
    Real b0 = Dot(diff, line.direction);
    Real c = Dot(diff, diff);
    Real det = std::abs((Real)1 - a01*a01);
    Real b1, s0, s1;

    if (det > (Real)0)
    {
        b1 = -Dot(diff, ray.direction);
        s1 = a01*b0 - b1;

        if (s1 >= (Real)0)
        {
            // Two interior points are closest, one on line and one on ray.
            Real invDet = ((Real)1) / det;
            s0 = (a01*b1 - b0)*invDet;
            s1 *= invDet;
            result.sqrDistance = s0*(s0 + a01*s1 + ((Real)2)*b0) +
                s1*(a01*s0 + s1 + ((Real)2)*b1) + c;
        }
        else
        {
            // Origin of ray and interior point of line are closest.
            s0 = -b0;
            s1 = (Real)0;
            result.sqrDistance = b0*s0 + c;
        }
    }
    else
    {
        // Lines are parallel, closest pair with one point at ray origin.
        s0 = -b0;
        s1 = (Real)0;
        result.sqrDistance = b0*s0 + c;
    }

    // Account for numerical round-off errors.
    if (result.sqrDistance < (Real)0)
    {
        result.sqrDistance = (Real)0;
    }

    result.distance = sqrt(result.sqrDistance);
    result.parameter[0] = s0;
    result.parameter[1] = s1;
    result.closestPoint[0] = line.origin + s0*line.direction;
    result.closestPoint[1] = ray.origin + s1*ray.direction;
    return result;
}
//----------------------------------------------------------------------------
