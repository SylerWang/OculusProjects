// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteDistPoint2OrientedBox2.h"
#include "GteCircle2.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, OrientedBox2<Real>, Circle2<Real>>
{
public:
    // The intersection query considers the box and circle to be solids.
    // For example, if the circle is strictly inside the box (does not touch
    // the box edges), the objects intersect.
    struct Result
    {
        bool intersect;
    };

    Result operator()(OrientedBox2<Real> const& box,
        Circle2<Real> const& circle);
};

template <typename Real>
class FIQuery<Real, OrientedBox2<Real>, Circle2<Real>>
{
public:
    // Currently, only a dynamic query is supported.  The static query must
    // compute the intersection set of (solid) box and circle.
    struct Result
    {
        bool intersect;
        Real contactTime;
        Vector2<Real> contactPoint;
    };

    Result operator()(Real maxTime, OrientedBox2<Real> const& box,
        Vector2<Real> const& boxVelocity, Circle2<Real> const& circle,
        Vector2<Real> const& circleVelocity);

private:
    // Support for dynamic query.  Both functions return -1 if the objects are
    // initially intersecting, 0 if no intersection, or +1 if they intersect
    // at some positive time.
    int TestVertexRegion(Real cx, Real cy, Real vx, Real vy, Real ex,
        Real ey, Real& ix, Real& iy, Real radius, Real& contactTime);

    int TestEdgeRegion(Real cx, Real cy, Real vx, Real vy, Real ex, Real ey,
        Real& ix, Real& iy, Real radius, Real& contactTime);
};

#include "GteIntrOrientedBox2Circle2.inl"

}
