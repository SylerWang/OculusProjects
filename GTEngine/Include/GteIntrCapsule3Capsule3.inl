// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)


//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Capsule3<Real>, Capsule3<Real>>::Result
TIQuery<Real, Capsule3<Real>, Capsule3<Real>>::operator()(
    Capsule3<Real> const& capsule0, Capsule3<Real> const& capsule1)
{
    Result result;
    DCPQuery<Real, Segment3<Real>, Segment3<Real>> ssQuery;
    auto ssResult = ssQuery(capsule0.segment, capsule1.segment);
    Real rSum = capsule0.radius + capsule1.radius;
    result.intersect = (ssResult.distance <= rSum);
    return result;
}
//----------------------------------------------------------------------------
