// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrLine2Line2.h"
#include "GteSegment2.h"
#include "GteIntrIntervals.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Segment2<Real>, Segment2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (ssegment intersect in a
        // single point), or 2 (segments are collinear and intersect in a
        // segment).
        int numIntersections;
    };

    Result operator()(Segment2<Real> const& segment0,
        Segment2<Real> const& segment1);
};

template <typename Real>
class FIQuery<Real, Segment2<Real>, Segment2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (ssegment intersect in a
        // a single point), or 2 (segments are collinear and intersect
        // in a segment).
        int numIntersections;

        // If numIntersections is 1, the intersection is
        //   point[0]
        //     = segment0.origin + segment0Parameter[0] * segment0.direction
        //     = segment1.origin + segment1Parameter[0] * segment1.direction
        // If numIntersections is 2, the endpoints of the segment of
        // intersection are
        //   point[i]
        //     = segment0.origin + segment0Parameter[i] * segment0.direction
        //     = segment1.origin + segment1Parameter[i] * segment1.direction
        // with segment0Parameter[0] <= segment0Parameter[1] and
        // segment1Parameter[0] <= segment1Parameter[1].
        Real segment0Parameter[2], segment1Parameter[2];
        Vector2<Real> point[2];
    };

    Result operator()(Segment2<Real> const& segment0,
        Segment2<Real> const& segment1);
};

#include "GteIntrSegment2Segment2.inl"

}
