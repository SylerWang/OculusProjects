// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Line3<Real>, Rectangle3<Real>>::Result
DCPQuery<Real, Line3<Real>, Rectangle3<Real>>::operator()(
    Line3<Real> const& line, Rectangle3<Real> const& rectangle)
{
    Result result;

    // Test if line intersects rectangle.  If so, the squared distance is
    // zero.
    Vector3<Real> N = Cross(rectangle.axis[0], rectangle.axis[1]);
    Real NdD = Dot(N, line.direction);
    if (std::abs(NdD) > (Real)0)
    {
        // The line and rectangle are not parallel, so the line intersects
        // the plane of the rectangle.
        Vector3<Real> diff = line.origin - rectangle.center;
        Vector3<Real> basis[3];  // {D, U, V}
        basis[0] = line.direction;
        ComputeOrthogonalComplement<Real>(1, basis);
        Real UdD0 = Dot(basis[1], rectangle.axis[0]);
        Real UdD1 = Dot(basis[1], rectangle.axis[1]);
        Real UdPmC = Dot(basis[1], diff);
        Real VdD0 = Dot(basis[2], rectangle.axis[0]);
        Real VdD1 = Dot(basis[2], rectangle.axis[1]);
        Real VdPmC = Dot(basis[2], diff);
        Real invDet = ((Real)1)/(UdD0*VdD1 - UdD1*VdD0);

        // Rectangle coordinates for the point of intersection.
        Real s0 = (VdD1*UdPmC - UdD1*VdPmC)*invDet;
        Real s1 = (UdD0*VdPmC - VdD0*UdPmC)*invDet;

        if (std::abs(s0) <= rectangle.extent[0]
            && std::abs(s1) <= rectangle.extent[1])
        {
            // Line parameter for the point of intersection.
            Real DdD0 = Dot(line.direction, rectangle.axis[0]);
            Real DdD1 = Dot(line.direction, rectangle.axis[1]);
            Real DdDiff = Dot(line.direction, diff);
            result.lineParameter = s0*DdD0 + s1*DdD1 - DdDiff;

            // Rectangle coordinates for the point of intersection.
            result.rectangleParameter[0] = s0;
            result.rectangleParameter[1] = s1;

            // The intersection point is inside or on the rectangle.
            result.closestPoint[0] = line.origin +
                result.lineParameter*line.direction;

            result.closestPoint[1] = rectangle.center +
                s0*rectangle.axis[0] + s1*rectangle.axis[1];

            result.distance = (Real)0;
            result.sqrDistance = (Real)0;
            return result;
        }
    }

    // Either (1) the line is not parallel to the rectangle and the point of
    // intersection of the line and the plane of the rectangle is outside the
    // rectangle or (2) the line and rectangle are parallel.  Regardless, the
    // closest point on the rectangle is on an edge of the rectangle.  Compare
    // the line to all four edges of the rectangle.
    result.distance = std::numeric_limits<Real>::max();
    result.sqrDistance = std::numeric_limits<Real>::max();
    Vector3<Real> scaledDir[2] =
    {
        rectangle.extent[0] * rectangle.axis[0],
        rectangle.extent[1] * rectangle.axis[1]
    };
    for (int i1 = 0; i1 < 2; ++i1)
    {
        for (int i0 = 0; i0 < 2; ++i0)
        {
            Vector3<Real> segCenter = rectangle.center +
                ((Real)(2 * i0 - 1))*scaledDir[i1];
            Vector3<Real> segDirection = rectangle.axis[1 - i1];
            Real segExtent = rectangle.extent[1 - i1];
            Segment3<Real> segment(segCenter, segDirection, segExtent);

            DCPQuery<Real, Line3<Real>, Segment3<Real>> query;
            auto lsResult = query(line, segment);
            if (lsResult.sqrDistance < result.sqrDistance)
            {
                result.sqrDistance = lsResult.sqrDistance;
                result.distance = lsResult.distance;
                result.lineParameter = lsResult.parameter[0];
                Real ratio = lsResult.parameter[0] / segExtent;
                result.rectangleParameter[0] = rectangle.extent[0] *
                    ((1 - i1)*(2 * i0 - 1) + i1*ratio);
                result.rectangleParameter[1] = rectangle.extent[1] *
                    ((1 - i0)*(2 * i1 - 1) + i0*ratio);
                result.closestPoint[0] = lsResult.closestPoint[0];
                result.closestPoint[1] = lsResult.closestPoint[1];
            }
        }
    }

    return result;
}
//----------------------------------------------------------------------------
