// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrIntervals.h"
#include "GteIntrLine2Triangle2.h"
#include "GteSegment2.h"

// The queries consider the triangle to be a solid.

namespace gte
{

template <typename Real>
class TIQuery<Real, Segment2<Real>, Triangle2<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Segment2<Real> const& segment,
        Triangle2<Real> const& triangle);
};

template <typename Real>
class FIQuery <Real, Segment2<Real>, Triangle2<Real>>
    :
    public FIQuery<Real, Line2<Real>, Triangle2<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line2<Real>, Triangle2<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Segment2<Real> const& segment,
        Triangle2<Real> const& triangle);

protected:
    void DoQuery(Vector2<Real> const& segOrigin,
        Vector2<Real> const& segDirection, Real segExtent,
        Triangle2<Real> const& triangle, Result& result);
};

#include "GteIntrSegment2Triangle2.inl"

}
