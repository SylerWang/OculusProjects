// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrCircle2Circle2.h"
#include "GteArc2.h"

namespace gte
{

template <typename Real>
class FIQuery<Real, Arc2<Real>, Arc2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number of intersections is 0, 1, 2, or maxInt =
        // std::numeric_limits<int>::max().  When 1, the arcs intersect in a
        // single point.  When 2, the arcs are not co-circular and intersect
        // in two points.  When maxInt, the arcs are co-circular and
        // intersect.
        int numIntersections;

        // Valid only when numIntersections = 1 or 2.
        Vector2<Real> point[2];

        // Valid only when numIntersections = maxInt.
        Arc2<Real> arc;
    };

    Result operator()(Arc2<Real> const& arc0, Arc2<Real> const& arc1);
};

#include "GteIntrArc2Arc2.inl"

}
