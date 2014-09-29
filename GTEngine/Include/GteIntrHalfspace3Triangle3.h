// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteHalfspace3.h"
#include "GteTriangle3.h"

// Queries for intersection of objects with halfspaces.  These are useful for
// containment testing, object culling, and clipping.

namespace gte
{

template <typename Real>
class TIQuery<Real, Halfspace3<Real>, Triangle3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Halfspace3<Real> const& halfspace,
        Triangle3<Real> const& triangle);
};

template <typename Real>
class FIQuery<Real, Halfspace3<Real>, Triangle3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The triangle is clipped against the plane defining the halfspace.
        // The 'numPoints' is either 0 (no intersection), 1 (point), 2
        // (segment), 3 (triangle), or 4 (quadrilateral).
        int numPoints;
        Vector3<Real> point[4];
    };

    Result operator()(Halfspace3<Real> const& halfspace,
        Triangle3<Real> const& triangle);
};

#include "GteIntrHalfspace3Triangle3.inl"

}
