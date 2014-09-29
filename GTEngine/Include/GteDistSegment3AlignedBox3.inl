// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Segment3<Real>, AlignedBox3<Real>>::Result
DCPQuery<Real, Segment3<Real>, AlignedBox3<Real>> ::operator()(
    Segment3<Real> const& segment, AlignedBox3<Real> const& box)
{
    Result result;

    Vector3<Real> segCenter, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segCenter, segDirection, segExtent);

    Line3<Real> line(segCenter, segDirection);
    DCPQuery<Real, Line3<Real>, AlignedBox3<Real>> lbQuery;
    auto lbResult = lbQuery(line, box);

    if (lbResult.lineParameter >= -segExtent)
    {
        if (lbResult.lineParameter <= segExtent)
        {
            result.sqrDistance = lbResult.sqrDistance;
            result.distance = lbResult.distance;
            result.segmentParameter = lbResult.lineParameter;
            result.closestPoint[0] = lbResult.closestPoint[0];
            result.closestPoint[1] = lbResult.closestPoint[1];
        }
        else
        {
            DCPQuery<Real, Vector3<Real>, AlignedBox3<Real>> pbQuery;
            Vector3<Real> point = segCenter + segExtent*segDirection;
            auto pbResult = pbQuery(point, box);
            result.sqrDistance = pbResult.sqrDistance;
            result.distance = pbResult.distance;
            result.segmentParameter = segExtent;
            result.closestPoint[0] = point;
            result.closestPoint[1] = pbResult.boxClosestPoint;
        }
    }
    else
    {
        DCPQuery<Real, Vector3<Real>, AlignedBox3<Real>> pbQuery;
        Vector3<Real> point = segCenter - segExtent*segDirection;
        auto pbResult = pbQuery(point, box);
        result.sqrDistance = pbResult.sqrDistance;
        result.distance = pbResult.distance;
        result.segmentParameter = segExtent;
        result.closestPoint[0] = point;
        result.closestPoint[1] = pbResult.boxClosestPoint;
    }
    return result;
}
//----------------------------------------------------------------------------
