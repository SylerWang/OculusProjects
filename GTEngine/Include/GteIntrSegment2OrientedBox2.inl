// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Segment2<Real>, OrientedBox2<Real>>::Result
TIQuery<Real, Segment2<Real>, OrientedBox2<Real>>::operator()(
    Segment2<Real> const& segment, OrientedBox2<Real> const& box)
{
    // Transform the segment to the oriented-box coordinate system.
    Vector2<Real> tmpOrigin, tmpDirection;
    Real segExtent;
    segment.GetCenteredForm(tmpOrigin, tmpDirection, segExtent);
    Vector2<Real> diff = tmpOrigin - box.center;
    Vector2<Real> segOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1])
    );
    Vector2<Real> segDirection
    (
        Dot(tmpDirection, box.axis[0]),
        Dot(tmpDirection, box.axis[1])
    );

    Result result;
    this->DoQuery(segOrigin, segDirection, segExtent, box.extent, result);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Segment2<Real>, OrientedBox2<Real>>::Result
FIQuery<Real, Segment2<Real>, OrientedBox2<Real>>::operator()(
    Segment2<Real> const& segment, OrientedBox2<Real> const& box)
{
    // Transform the segment to the oriented-box coordinate system.
    Vector2<Real> tmpOrigin, tmpDirection;
    Real segExtent;
    segment.GetCenteredForm(tmpOrigin, tmpDirection, segExtent);
    Vector2<Real> diff = tmpOrigin - box.center;
    Vector2<Real> segOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1])
    );
    Vector2<Real> segDirection
    (
        Dot(tmpDirection, box.axis[0]),
        Dot(tmpDirection, box.axis[1])
    );

    Result result;
    this->DoQuery(segOrigin, segDirection, segExtent, box.extent, result);
    for (int i = 0; i < result.numIntersections; ++i)
    {
        result.point[i] = segOrigin + result.parameter[i] * segDirection;
    }
    return result;
}
//----------------------------------------------------------------------------
