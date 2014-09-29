// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector2<Real>, Segment2<Real>>::Result
DCPQuery<Real, Vector2<Real>, Segment2<Real>>::operator()(
    Vector2<Real> const& point, Segment2<Real> const& segment)
{
    Result result;

    Vector2<Real> center, direction;
    Real extent;
    segment.GetCenteredForm(center, direction, extent);

    Vector2<Real> diff = point - center;
    result.segmentParameter = Dot(direction, diff);
    if (-extent < result.segmentParameter)
    {
        if (result.segmentParameter < extent)
        {
            result.segmentClosestPoint =
                center + result.segmentParameter*direction;
        }
        else
        {
            result.segmentClosestPoint = center + extent*direction;
        }
    }
    else
    {
        result.segmentClosestPoint = center - extent*direction;
    }

    diff = point - result.segmentClosestPoint;
    result.sqrDistance = Dot(diff, diff);
    result.distance = sqrt(result.sqrDistance);

    return result;
}
//----------------------------------------------------------------------------
