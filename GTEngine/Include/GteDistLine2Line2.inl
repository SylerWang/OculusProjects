// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Line2<Real>, Line2<Real>>::Result
DCPQuery<Real, Line2<Real>, Line2<Real>>::operator()(
    Line2<Real> const& line0, Line2<Real> const& line1)
{
    Result result;

    Vector2<Real> diff = line0.origin - line1.origin;
    Real a01 = -Dot(line0.direction, line1.direction);
    Real b0 = Dot(diff, line0.direction);
    Real c = Dot(diff, diff);
    Real det = std::abs((Real)1 - a01*a01);
    Real b1, s0, s1;

    if (det > (Real)0)
    {
        // Lines are not parallel.
        b1 = -Dot(diff, line1.direction);
        Real invDet = ((Real)1)/det;
        s0 = (a01*b1 - b0)*invDet;
        s1 = (a01*b0 - b1)*invDet;
        result.sqrDistance = (Real)0;
    }
    else
    {
        // Lines are parallel, select any closest pair of points.
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
    result.closestPoint[0] = line0.origin + s0*line0.direction;
    result.closestPoint[1] = line1.origin + s1*line1.direction;
    return result;
}
//----------------------------------------------------------------------------
