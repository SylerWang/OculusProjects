// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteDistPoint3Plane3.h"
#include "GteLine3.h"
#include <limits>

namespace gte
{

template <typename Real>
class TIQuery<Real, Line3<Real>, Plane3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Line3<Real> const& line, Plane3<Real> const& plane);
};

template <typename Real>
class FIQuery<Real, Line3<Real>, Plane3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number of intersections is 0 (no intersection), 1 (linear
        // component and plane intersect in a point), or
        // std::numeric_limits<int>::max() (linear component is on the plane).
        // If the linear component is on the plane, 'point' component's
        // origin and 'parameter' is zero.
        int numIntersections;
        Real parameter;
        Vector3<Real> point;
    };

    Result operator()(Line3<Real> const& line, Plane3<Real> const& plane);

protected:
    void DoQuery(Vector3<Real> const& lineOrigin,
        Vector3<Real> const& lineDirection, Plane3<Real> const& plane,
        Result& result);
};

#include "GteIntrLine3Plane3.inl"

}
