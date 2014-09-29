// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConvexHull3.h"

// Separate two point sets, if possible, by computing a plane for which the
// point sets lie on opposite sides.  The algorithm computes the convex hull
// of the point sets, then uses the method of separating axes to determine if
// the two convex polyhedra are disjoint.  The ComputeType is for the
// ConvexHull3 class.

namespace gte
{

template <typename Real, typename ComputeType>
class SeparatePoints3
{
public:
    // The return value is 'true' if and only if there is a separation.  If
    // 'true', the returned plane is a separating plane.  The code assumes
    // that each point set has at least 4 noncoplanar points.
    bool operator()(int numPoints0, Vector3<Real> const* points0,
        int numPoints1, Vector3<Real> const* points1,
        Plane3<Real>& separatingPlane) const;

private:
    int OnSameSide(Plane3<Real> const& plane, int numTriangles,
        int const* indices, Vector3<Real> const* points) const;

    int WhichSide(Plane3<Real> const& plane, int numTriangles,
        int const* indices, Vector3<Real> const* points) const;
};

#include "GteSeparatePoints3.inl"

}
