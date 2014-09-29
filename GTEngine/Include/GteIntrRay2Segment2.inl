// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Ray2<Real>, Segment2<Real>>::Result
TIQuery<Real, Ray2<Real>, Segment2<Real>>::operator()(
    Ray2<Real> const& ray, Segment2<Real> const& segment)
{
    Result result;
    Vector2<Real> segOrigin, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segOrigin, segDirection, segExtent);

    FIQuery<Real, Line2<Real>, Line2<Real>> llQuery;
    Line2<Real> line0(ray.origin, ray.direction);
    Line2<Real> line1(segOrigin, segDirection);
    auto llResult = llQuery(line0, line1);
    if (llResult.numIntersections == 1)
    {
        // Test whether the line-line intersection is on the ray and segment.
        if (llResult.line0Parameter[0] >= (Real)0
            && std::abs(llResult.line1Parameter[0]) <= segExtent)
        {
            result.intersect = true;
            result.numIntersections = 1;
        }
        else
        {
            result.intersect = false;
            result.numIntersections = 0;
        }
    }
    else if (llResult.numIntersections == std::numeric_limits<int>::max())
    {
        // Compute the location of the right-most point of the segment
        // relative to the ray direction.
        Vector2<Real> diff = segOrigin - ray.origin;
        Real t = Dot(ray.direction, diff) + segExtent;
        if (t > (Real)0)
        {
            result.intersect = true;
            result.numIntersections = 2;
        }
        else if (t < (Real)0)
        {
            result.intersect = false;
            result.numIntersections = 0;
        }
        else  // t == 0
        {
            result.intersect = true;
            result.numIntersections = 1;
        }
    }
    else
    {
        result.intersect = false;
        result.numIntersections = 0;
    }

    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Ray2<Real>, Segment2<Real>>::Result
FIQuery<Real, Ray2<Real>, Segment2<Real>>::operator()(
    Ray2<Real> const& ray, Segment2<Real> const& segment)
{
    Result result;
    Vector2<Real> segOrigin, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segOrigin, segDirection, segExtent);

    FIQuery<Real, Line2<Real>, Line2<Real>> llQuery;
    Line2<Real> line0(ray.origin, ray.direction);
    Line2<Real> line1(segOrigin, segDirection);
    auto llResult = llQuery(line0, line1);
    if (llResult.numIntersections == 1)
    {
        // Test whether the line-line intersection is on the ray and segment.
        if (llResult.line0Parameter[0] >= (Real)0
            && std::abs(llResult.line1Parameter[0]) <= segExtent)
        {
            result.intersect = true;
            result.numIntersections = 1;
            result.rayParameter[0] = llResult.line0Parameter[0];
            result.segmentParameter[0] = llResult.line1Parameter[0];
            result.point[0] = llResult.point;
        }
        else
        {
            result.intersect = false;
            result.numIntersections = 0;
        }
    }
    else if (llResult.numIntersections == std::numeric_limits<int>::max())
    {
        // Compute t for which segment.origin = ray.origin + t*ray.direction.
        Vector2<Real> diff = segOrigin - ray.origin;
        Real t = Dot(ray.direction, diff);

        // Get the ray interval.
        std::array<Real, 2> interval0 =
        {
            (Real)0, std::numeric_limits<Real>::max()
        };

        // Compute the location of the segment endpoints relative to the ray.
        std::array<Real, 2> interval1 = { t - segExtent, t + segExtent };

        // Compute the intersection of [0,+infinity) and [tmin,tmax].
        FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>> iiQuery;
        auto iiResult = iiQuery(interval0, interval1);
        if (iiResult.intersect)
        {
            result.intersect = true;
            result.numIntersections = iiResult.numIntersections;
            for (int i = 0; i < iiResult.numIntersections; ++i)
            {
                result.rayParameter[i] = iiResult.overlap[i];
                result.segmentParameter[i] = iiResult.overlap[i] - t;
                result.point[i] = ray.origin +
                    result.rayParameter[i] * ray.direction;
            }
        }
        else
        {
            result.intersect = false;
            result.numIntersections = 0;
        }
    }
    else
    {
        result.intersect = false;
        result.numIntersections = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
