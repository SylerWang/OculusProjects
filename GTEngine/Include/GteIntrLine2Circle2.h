// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteDistPoint2Line2.h"
#include "GteCircle2.h"

// The queries consider the circle to be a solid (disk).

namespace gte
{

template <typename Real>
class TIQuery<Real, Line2<Real>, Circle2<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Line2<Real> const& line, Circle2<Real> const& circle);
};

template <typename Real>
class FIQuery<Real, Line2<Real>, Circle2<Real>>
{
public:
    struct Result
    {
        bool intersect;
        int numIntersections;
        std::array<Real,2> parameter;
        std::array<Vector2<Real>, 2> point;
    };

    Result operator()(Line2<Real> const& line, Circle2<Real> const& circle);

protected:
    void DoQuery(Vector2<Real> const& lineOrigin,
        Vector2<Real> const& lineDirection, Circle2<Real> const& circle,
        Result& result);
};

#include "GteIntrLine2Circle2.inl"

}
