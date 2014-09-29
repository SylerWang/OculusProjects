// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Segment3<Real>, Cylinder3<Real>>::Result
FIQuery<Real, Segment3<Real>, Cylinder3<Real>>::operator()(
    Segment3<Real> const& segment, Cylinder3<Real> const& cylinder)
{
    Vector3<Real> segOrigin, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segOrigin, segDirection, segExtent);

    Result result;
    DoQuery(segOrigin, segDirection, segExtent, cylinder, result);
    for (int i = 0; i < result.numIntersections; ++i)
    {
        result.point[i] = segOrigin + result.parameter[i] * segDirection;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void FIQuery<Real, Segment3<Real>, Cylinder3<Real>>::DoQuery(
    Vector3<Real> const& segOrigin, Vector3<Real> const& segDirection,
    Real segExtent, Cylinder3<Real> const& cylinder, Result& result)
{
    FIQuery<Real, Line3<Real>, Cylinder3<Real>>::DoQuery(segOrigin,
        segDirection, cylinder, result);

    if (result.intersect)
    {
        // The line containing the segment intersects the cylinder; the
        // t-interval is [t0,t1].  The segment intersects the cylinder as
        // long as [t0,t1] overlaps the segment t-interval
        // [-segExtent,+segExtent].
        std::array<Real, 2> segInterval = { -segExtent, segExtent };
        FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>> iiQuery;
        result.parameter = iiQuery(result.parameter, segInterval).overlap;
    }
}
//----------------------------------------------------------------------------
