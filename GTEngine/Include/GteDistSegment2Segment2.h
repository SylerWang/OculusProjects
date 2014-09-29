// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteSegment2.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Segment2<Real>, Segment2<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Vector2<Real> closestPoint[2];
    };

    Result operator()(Segment2<Real> const& segment0,
        Segment2<Real> const& segment1);
};

#include "GteDistSegment2Segment2.inl"

}
