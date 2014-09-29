// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Line2<Real>, Segment2<Real>>::Result
DCPQuery<Real, Line2<Real>, Segment2<Real>>::operator()(
    Line2<Real> const& line, Segment2<Real> const& segment)
{
    Result result;

    Vector2<Real> segCenter, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segCenter, segDirection, segExtent);

    Vector2<Real> diff = line.origin - segCenter;
    Real a01 = -Dot(line.direction, segDirection);
    Real b0 = Dot(diff, line.direction);
    Real c = Dot(diff, diff);
    Real det = std::abs((Real)1 - a01*a01);
    Real b1, s0, s1, extDet;

    if (det > (Real)0)
    {
        // The line and segment are not parallel.
        b1 = -Dot(diff, segDirection);
        s1 = a01*b0 - b1;
        extDet = segExtent * det;

        if (s1 >= -extDet)
        {
            if (s1 <= extDet)
            {
                // Two interior points are closest, one on the line and one
                // on the segment.
                Real invDet = ((Real)1) / det;
                s0 = (a01*b1 - b0)*invDet;
                s1 *= invDet;
                result.sqrDistance = (Real)0;
            }
            else
            {
                // The endpoint e1 of the segment and an interior point of
                // the line are closest.
                s1 = segExtent;
                s0 = -(a01*s1 + b0);
                result.sqrDistance = -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
            }
        }
        else
        {
            // The endpoint e0 of the segment and an interior point of the
            // line are closest.
            s1 = -segExtent;
            s0 = -(a01*s1 + b0);
            result.sqrDistance = -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
        }
    }
    else
    {
        // The line and segment are parallel.  Choose the closest pair so that
        // one point is at segment origin.
        s1 = (Real)0;
        s0 = -b0;
        result.sqrDistance = b0*s0 + c;
    }

    // Account for numerical round-off errors.
    if (result.sqrDistance < (Real)0)
    {
        result.sqrDistance = (Real)0;
    }

    result.distance = sqrt(result.sqrDistance);
    result.closestPoint[0] = line.origin + s0*line.direction;
    result.closestPoint[1] = segCenter + s1*segDirection;
    return result;
}
//----------------------------------------------------------------------------
