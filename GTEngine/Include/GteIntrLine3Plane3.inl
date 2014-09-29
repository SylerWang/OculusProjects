// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Line3<Real>, Plane3<Real>>::Result
TIQuery<Real, Line3<Real>, Plane3<Real>>::operator()(
    Line3<Real> const& line, Plane3<Real> const& plane)
{
    Result result;

    Real DdN = Dot(line.direction, plane.normal);
    if (DdN != (Real)0)
    {
        // The line is not parallel to the plane, so they must intersect.
        result.intersect = true;
    }
    else
    {
        // The line and plane are parallel.
        DCPQuery<Real, Vector3<Real>, Plane3<Real>> vpQuery;
        result.intersect = (vpQuery(line.origin, plane).distance == (Real)0);
    }

    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line3<Real>, Plane3<Real>>::Result
FIQuery<Real, Line3<Real>, Plane3<Real>>::operator()(
    Line3<Real> const& line, Plane3<Real> const& plane)
{
    Result result;
    DoQuery(line.origin, line.direction, plane, result);
    if (result.intersect)
    {
        result.point = line.origin + result.parameter * line.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void FIQuery<Real, Line3<Real>, Plane3<Real>>::DoQuery(
    Vector3<Real> const& lineOrigin, Vector3<Real> const& lineDirection,
    Plane3<Real> const& plane, Result& result)
{
    Real DdN = Dot(lineDirection, plane.normal);
    DCPQuery<Real, Vector3<Real>, Plane3<Real>> vpQuery;
    auto vpResult = vpQuery(lineOrigin, plane);

    if (DdN != (Real)0)
    {
        // The line is not parallel to the plane, so they must intersect.
        result.intersect = true;
        result.numIntersections = 1;
        result.parameter = -vpResult.signedDistance / DdN;
    }
    else
    {
        // The line and plane are parallel.  Determine whether the line is on
        // the plane.
        if (vpResult.distance == (Real)0)
        {
            // The line is coincident with the plane, so choose t = 0 for the
            // parameter.
            result.intersect = true;
            result.numIntersections = std::numeric_limits<int>::max();
            result.parameter = (Real)0;
        }
        else
        {
            // The line is not on the plane.
            result.intersect = false;
            result.numIntersections = 0;
        }
    }
}
//----------------------------------------------------------------------------
