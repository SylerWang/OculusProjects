// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Segment3<Real>, OrientedBox3<Real>>::Result
TIQuery<Real, Segment3<Real>, OrientedBox3<Real>>::operator()(
    Segment3<Real> const& segment, OrientedBox3<Real> const& box)
{
    // Transform the segment to the oriented-box coordinate system.
    Vector3<Real> tmpOrigin, tmpDirection;
    Real segExtent;
    segment.GetCenteredForm(tmpOrigin, tmpDirection, segExtent);
    Vector3<Real> diff = tmpOrigin - box.center;
    Vector3<Real> segOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1]),
        Dot(diff, box.axis[2])
    );
    Vector3<Real> segDirection
    (
        Dot(tmpDirection, box.axis[0]),
        Dot(tmpDirection, box.axis[1]),
        Dot(tmpDirection, box.axis[2])
    );

    Result result;
    this->DoQuery(segOrigin, segDirection, segExtent, box.extent, result);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Segment3<Real>, OrientedBox3<Real>>::Result
FIQuery<Real, Segment3<Real>, OrientedBox3<Real>>::operator()(
    Segment3<Real> const& segment, OrientedBox3<Real> const& box)
{
    // Transform the segment to the oriented-box coordinate system.
    Vector3<Real> tmpOrigin, tmpDirection;
    Real segExtent;
    segment.GetCenteredForm(tmpOrigin, tmpDirection, segExtent);
    Vector3<Real> diff = tmpOrigin - box.center;
    Vector3<Real> segOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1]),
        Dot(diff, box.axis[2])
    );
    Vector3<Real> segDirection
    (
        Dot(tmpDirection, box.axis[0]),
        Dot(tmpDirection, box.axis[1]),
        Dot(tmpDirection, box.axis[2])
    );

    Result result;
    this->DoQuery(segOrigin, segDirection, segExtent, box.extent, result);
    for (int i = 0; i < result.numPoints; ++i)
    {
        result.point[i] = segOrigin + result.lineParameter[i] * segDirection;
    }
    return result;
}
//----------------------------------------------------------------------------
