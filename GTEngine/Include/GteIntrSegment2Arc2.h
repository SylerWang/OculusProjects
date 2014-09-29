// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrSegment2Circle2.h"
#include "GteArc2.h"

// The queries consider the arc to be a 1-dimensional object.

namespace gte
{

template <typename Real>
class TIQuery<Real, Segment2<Real>, Arc2<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Segment2<Real> const& segment, Arc2<Real> const& arc);
};

template <typename Real>
class FIQuery<Real, Segment2<Real>, Arc2<Real>>
{
public:
    struct Result
    {
        bool intersect;
        int numIntersections;
        std::array<Real, 2> parameter;
        std::array<Vector2<Real>, 2> point;
    };

    Result operator()(Segment2<Real> const& segment, Arc2<Real> const& arc);
};

#include "GteIntrSegment2Arc2.inl"

}
