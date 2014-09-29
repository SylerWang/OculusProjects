// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Segment3<Real>, Triangle3<Real>>::Result
DCPQuery<Real, Segment3<Real>, Triangle3<Real>>::operator()(
    Segment3<Real> const& segment, Triangle3<Real> const& triangle)
{
    Result result;

    Vector3<Real> segCenter, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segCenter, segDirection, segExtent);

    Line3<Real> line(segCenter, segDirection);
    DCPQuery<Real, Line3<Real>, Triangle3<Real>> ltQuery;
    auto ltResult = ltQuery(line, triangle);

    if (ltResult.lineParameter >= -segExtent)
    {
        if (ltResult.lineParameter <= segExtent)
        {
            result.distance = ltResult.distance;
            result.sqrDistance = ltResult.sqrDistance;
            result.segmentParameter = ltResult.lineParameter;
            result.triangleParameter[0] = ltResult.triangleParameter[0];
            result.triangleParameter[1] = ltResult.triangleParameter[1];
            result.triangleParameter[2] = ltResult.triangleParameter[2];
            result.closestPoint[0] = ltResult.closestPoint[0];
            result.closestPoint[1] = ltResult.closestPoint[1];
        }
        else
        {
            DCPQuery<Real, Vector3<Real>, Triangle3<Real>> ptQuery;
            Vector3<Real> point = segCenter + segExtent*segDirection;
            auto ptResult = ptQuery(point, triangle);
            result.sqrDistance = ptResult.sqrDistance;
            result.distance = ptResult.distance;
            result.segmentParameter = segExtent;
            result.closestPoint[0] = point;
            result.closestPoint[1] = ptResult.triangleClosestPoint;
        }
    }
    else
    {
        DCPQuery<Real, Vector3<Real>, Triangle3<Real>> ptQuery;
        Vector3<Real> point = segCenter - segExtent*segDirection;
        auto ptResult = ptQuery(point, triangle);
        result.sqrDistance = ptResult.sqrDistance;
        result.distance = ptResult.distance;
        result.segmentParameter = segExtent;
        result.closestPoint[0] = point;
        result.closestPoint[1] = ptResult.triangleClosestPoint;
    }
    return result;
}
//----------------------------------------------------------------------------
