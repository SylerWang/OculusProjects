// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GtePlane3.h"
#include "GteTriangle3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Plane3<Real>, Triangle3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (plane and triangle intersect
        // at a single point [vertex]), 2 (plane and triangle intersect in a
        // segment), or 3 (triangle is in the plane).  When the number is 2,
        // the segment is either interior to the triangle or is an edge of the
        // triangle, the distinction stored in 'isInterior'.
        int numIntersections;
        bool isInterior;
    };

    Result operator()(Plane3<Real> const& plane,
        Triangle3<Real> const& triangle);
};

template <typename Real>
class FIQuery<Real, Plane3<Real>, Triangle3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (plane and triangle intersect
        // at a single point [vertex]), 2 (plane and triangle intersect in a
        // segment), or 3 (triangle is in the plane).  When the number is 2,
        // the segment is either interior to the triangle or is an edge of the
        // triangle, the distinction stored in 'isInterior'.
        int numIntersections;
        bool isInterior;
        Vector3<Real> point[3];
    };

    Result operator()(Plane3<Real> const& plane,
        Triangle3<Real> const& triangle);
};

#include "GteIntrPlane3Triangle3.inl"

}
