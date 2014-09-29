// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteOrientedBox3.h"
#include "GteSphere3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, OrientedBox3<Real>, Sphere3<Real>>
{
public:
    // The intersection query considers the box and sphere to be solids.
    // For example, if the sphere is strictly inside the box (does not touch
    // the box faces), the objects intersect.
    struct Result
    {
        bool intersect;
    };

    Result operator()(OrientedBox3<Real> const& box,
        Sphere3<Real> const& sphere);
};

template <typename Real>
class FIQuery<Real, OrientedBox3<Real>, Sphere3<Real>>
{
public:
    // Currently, only a dynamic query is supported.  The static query must
    // compute the intersection set of (solid) box and sphere.
    struct Result
    {
        bool intersect;
        Real contactTime;
        Vector3<Real> contactPoint;
    };

    Result operator()(Real maxTime, OrientedBox3<Real> const& box,
        Vector3<Real> const& boxVelocity, Sphere3<Real> const& sphere,
        Vector3<Real> const& sphereVelocity);

private:
    // Support for dynamic query.
    Real GetVertexIntersection(Real dx, Real dy, Real dz, Real vx,
        Real vy, Real vz, Real rsqr);

    Real GetEdgeIntersection(Real dx, Real dz, Real vx, Real vz,
        Real vsqr, Real rsqr);

    int FindFaceRegionIntersection(Real ex, Real ey, Real ez, Real cx,
        Real cy, Real cz, Real vx, Real vy, Real vz, Real& ix, Real& iy,
        Real& iz, bool aboveFace, Real radius, Real& contactTime);

    int FindJustEdgeIntersection(Real cy, Real ex, Real ey, Real ez, Real dx,
        Real dz, Real vx, Real vy, Real vz, Real& ix, Real& iy, Real& iz,
        Real radius, Real& contactTime);

    int FindEdgeRegionIntersection(Real ex, Real ey, Real ez, Real cx,
        Real cy, Real cz, Real vx, Real vy, Real vz, Real& ix, Real& iy,
        Real& iz, bool aboveEdge, Real radius, Real& contactTime);

    int FindVertexRegionIntersection(Real ex, Real ey, Real ez, Real cx,
        Real cy, Real cz, Real vx, Real vy, Real vz, Real& ix, Real& iy,
        Real& iz, Real radius, Real& contactTime);
};

#include "GteIntrOrientedBox3Sphere3.inl"

}
