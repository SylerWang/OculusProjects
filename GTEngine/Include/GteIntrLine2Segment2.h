// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrLine2Line2.h"
#include "GteSegment2.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Line2<Real>, Segment2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (line and segment intersect in
        // a single point) or std::numeric_limits<int>::max() (line and
        // segment are collinear).
        int numIntersections;
    };

    Result operator()(Line2<Real> const& line, Segment2<Real> const& segment);
};

template <typename Real>
class FIQuery<Real, Line2<Real>, Segment2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (line and segment intersect in
        // a single point) or std::numeric_limits<int>::max() (line and
        // segment are collinear).
        int numIntersections;

        // If numIntersections is 1, the intersection is
        //   point = line.origin + lineParameter[0] * line.direction
        //         = segment.origin + segmentParameter[0] * segment.direction
        // If numIntersections is maxInt, point is not valid but the
        // intervals are
        //   lineParameter[] = { -maxReal, +maxReal }
        //   segmentParameter[] = { -segmentExtent, segmentExtent }
        Real lineParameter[2], segmentParameter[2];
        Vector2<Real> point;
    };

    Result operator()(Line2<Real> const& line, Segment2<Real> const& segment);
};

#include "GteIntrLine2Segment2.inl"

}
