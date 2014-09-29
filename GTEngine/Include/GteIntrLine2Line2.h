// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteLine2.h"
#include <limits>

namespace gte
{

template <typename Real>
class TIQuery<Real, Line2<Real>, Line2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (lines intersect in a single
        // point) or std::numeric_limits<int>::max() (lines are the same).
        int numIntersections;
    };

    Result operator()(Line2<Real> const& line0, Line2<Real> const& line1);
};

template <typename Real>
class FIQuery<Real, Line2<Real>, Line2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (lines intersect in a single
        // point) or std::numeric_limits<int>::max() (lines are the same).
        int numIntersections;

        // If numIntersections is 1, the intersection is
        //   point = line0.origin + line0parameter[0] * line0.direction
        //         = line1.origin + line1parameter[0] * line1.direction
        // If numIntersections is maxInt, point is not valid but the
        // intervals are
        //   line0Parameter[] = { -maxReal, +maxReal }
        //   line1Parameter[] = { -maxReal, +maxReal }
        Real line0Parameter[2], line1Parameter[2];
        Vector2<Real> point;
    };

    Result operator()(Line2<Real> const& line0, Line2<Real> const& line1);
};

#include "GteIntrLine2Line2.inl"

}
