// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteLine2.h"
#include "GteTriangle2.h"

// The queries consider the triangle to be a solid.

namespace gte
{

template <typename Real>
class TIQuery<Real, Line2<Real>, Triangle2<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Line2<Real> const& line,
        Triangle2<Real> const& triangle);
};

template <typename Real>
class FIQuery<Real, Line2<Real>, Triangle2<Real>>
{
public:
    struct Result
    {
        bool intersect;
        int numIntersections;
        std::array<Real, 2> parameter;
        std::array<Vector2<Real>, 2> point;
    };

    Result operator()(Line2<Real> const& line,
        Triangle2<Real> const& triangle);

protected:
    void DoQuery(Vector2<Real> const& lineOrigin,
        Vector2<Real> const& lineDirection, Triangle2<Real> const& triangle,
        Result& result);
};

#include "GteIntrLine2Triangle2.inl"

}
