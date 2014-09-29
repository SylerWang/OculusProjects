// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConvexHull2.h"

// Separate two point sets, if possible, by computing a line for which the
// point sets lie on opposite sides.  The algorithm computes the convex hull
// of the point sets, then uses the method of separating axes to determine if
// the two convex polygons are disjoint.  The ComputeType is for the
// ConvexHull2 class.

namespace gte
{

template <typename Real, typename ComputeType>
class SeparatePoints2
{
public:
    // The return value is 'true' if and only if there is a separation.  If
    // 'true', the returned line is a separating line.  The code assumes that
    // each point set has at least 3 noncollinear points.
    bool operator()(int numPoints0, Vector2<Real> const* points0,
        int numPoints1, Vector2<Real> const* points1,
        Line2<Real>& separatingLine) const;

private:
    int OnSameSide(Vector2<Real> const& lineNormal, Real lineConstant,
        int numEdges, int const* edges, Vector2<Real> const* points) const;

    int WhichSide(Vector2<Real> const& lineNormal, Real lineConstant,
        int numEdges, int const* edges, Vector2<Real> const* points) const;
};

#include "GteSeparatePoints2.inl"

}
