// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Line2<Real>, Segment2<Real>>::Result
TIQuery<Real, Line2<Real>, Segment2<Real>>::operator()(
    Line2<Real> const& line, Segment2<Real> const& segment)
{
    Result result;
    Vector2<Real> segOrigin, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segOrigin, segDirection, segExtent);

    FIQuery<Real, Line2<Real>, Line2<Real>> llQuery;
    auto llResult = llQuery(line, Line2<Real>(segOrigin, segDirection));
    if (llResult.numIntersections == 1)
    {
        // Test whether the line-line intersection is on the segment.
        if (std::abs(llResult.line1Parameter[0]) <= segExtent)
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
    else
    {
        result.intersect = llResult.intersect;
        result.numIntersections = llResult.numIntersections;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line2<Real>, Segment2<Real>>::Result
FIQuery<Real, Line2<Real>, Segment2<Real>>::operator()(
    Line2<Real> const& line, Segment2<Real> const& segment)
{
    Result result;
    Vector2<Real> segOrigin, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segOrigin, segDirection, segExtent);

    FIQuery<Real, Line2<Real>, Line2<Real>> llQuery;
    auto llResult = llQuery(line, Line2<Real>(segOrigin, segDirection));
    if (llResult.numIntersections == 1)
    {
        // Test whether the line-line intersection is on the ray.
        if (std::abs(llResult.line1Parameter[0]) <= segExtent)
        {
            result.intersect = true;
            result.numIntersections = 1;
            result.lineParameter[0] = llResult.line0Parameter[0];
            result.segmentParameter[0] = llResult.line1Parameter[0];
            result.point = llResult.point;
        }
        else
        {
            result.intersect = false;
            result.numIntersections = 0;
        }
    }
    else if (llResult.numIntersections == std::numeric_limits<int>::max())
    {
        result.intersect = true;
        result.numIntersections = std::numeric_limits<int>::max();
        Real maxReal = std::numeric_limits<Real>::max();
        result.lineParameter[0] = -maxReal;
        result.lineParameter[1] = +maxReal;
        result.segmentParameter[0] = -segExtent;
        result.segmentParameter[1] = +segExtent;
    }
    else
    {
        result.intersect = false;
        result.numIntersections = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
