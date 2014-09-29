// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrLine2Line2.h"
#include "GteRay2.h"
#include "GteSegment2.h"
#include "GteIntrIntervals.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Ray2<Real>, Segment2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (ray and segment intersect in
        // a single point), or 2 (ray and segment are collinear and intersect
        // in a segment).
        int numIntersections;
    };

    Result operator()(Ray2<Real> const& ray, Segment2<Real> const& segment);
};

template <typename Real>
class FIQuery<Real, Ray2<Real>, Segment2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (ray and segment intersect in
        // a single point), or 2 (ray and segment are collinear and intersect
        // in a segment).
        int numIntersections;

        // If numIntersections is 1, the intersection is
        //   point[0] = ray.origin + rayParameter[0] * ray.direction
        //     = segment.center + segmentParameter[0] * segment.direction
        // If numIntersections is 2, the endpoints of the segment of
        // intersection are
        //   point[i] = ray.origin + rayParameter[i] * ray.direction
        //     = segment.center + segmentParameter[i] * segment.direction
        // with rayParameter[0] <= rayParameter[1] and
        // segmentParameter[0] <= segmentParameter[1].
        Real rayParameter[2], segmentParameter[2];
        Vector2<Real> point[2];
    };

    Result operator()(Ray2<Real> const& ray, Segment2<Real> const& segment);
};

#include "GteIntrRay2Segment2.inl"

}
