// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteCircle2.h"
#include <limits>

namespace gte
{

template <typename Real>
class TIQuery<Real, Circle2<Real>, Circle2<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Circle2<Real> const& circle0,
        Circle2<Real> const& circle1);
};

template <typename Real>
class FIQuery<Real, Circle2<Real>, Circle2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number of intersections is 0, 1, 2, or maxInt =
        // std::numeric_limits<int>::max().  When 1, the circles are tangent
        // and intersect in a single point.  When 2, circles have two
        // transverse intersection points.  When maxInt, the circles are the
        // same.
        int numIntersections;

        // Valid only when numIntersections = 1 or 2.
        Vector2<Real> point[2];

        // Valid only when numIntersections = maxInt.
        Circle2<Real> circle;
    };

    Result operator()(Circle2<Real> const& circle0,
        Circle2<Real> const& circle1);
};

#include "GteIntrCircle2Circle2.inl"

}
