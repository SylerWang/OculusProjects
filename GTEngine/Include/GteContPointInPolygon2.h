// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteVector2.h"

// Given a polygon as an order list of vertices (x[i],y[i]) for 0 <= i < N
// and a test point (xt,yt), return 'true' if (xt,yt) is in the polygon and
// 'false' if it is not.  All queries require that the number of vertices
// satisfies N >= 3.

namespace gte
{

template <typename Real>
class PointInPolygon2
{
public:
    // The class object stores a copy of 'points', so be careful about the
    // persistence of 'points' when you have created a PointInPolygon2 object.
    PointInPolygon2(int numPoints, Vector2<Real> const* points);

    // Simple polygons (ray-intersection counting).
    bool Contains(Vector2<Real> const& p) const;

    // Algorithms for convex polygons.  The input polygons must have vertices
    // in counterclockwise order.

    // O(N) algorithm (which-side-of-edge tests)
    bool ContainsConvexOrderN(Vector2<Real> const& p) const;

    // O(log N) algorithm (bisection and recursion, like BSP tree)
    bool ContainsConvexOrderLogN(Vector2<Real> const& p) const;

    // The polygon must have exactly four vertices.  This method is like the
    // O(log N) and uses three which-side-of-segment test instead of four
    // which-side-of-edge tests.  If the polygon does not have four vertices,
    // the function returns false.
    bool ContainsQuadrilateral(Vector2<Real> const& p) const;

private:
    // For recursion in ContainsConvexOrderLogN.
    bool SubContainsPoint(Vector2<Real> const& p, int i0, int i1) const;

    int mNumPoints;
    Vector2<Real> const* mPoints;
};

#include "GteContPointInPolygon2.inl"

}
