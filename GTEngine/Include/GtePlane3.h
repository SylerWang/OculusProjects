// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteVector3.h"

namespace gte
{

// The plane is represented as Dot(N,X) = c where N is a unit-length normal
// vector, c is the plane constant, and X is any point on the plane.  The user
 // must ensure that the normal vector is unit length.

template <typename Real>
class Plane3 : public GeometricPrimitive<Plane3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the normal
    // to (0,0,1) and the constant to zero (plane z = 0).
    Plane3();

    // Specify N and c directly.
    Plane3(Vector3<Real> const& inNormal, Real inConstant);

    // N is specified, c = Dot(N,P) where P is a point on the plane.
    Plane3(Vector3<Real> const& inNormal, Vector3<Real> const& p);

    // N = Cross(P1-P0,P2-P0)/Length(Cross(P1-P0,P2-P0)), c = Dot(N,P0) where
    // P0, P1, P2 are points on the plane.
    Plane3(Vector3<Real> const p[3]);
    Plane3(Vector3<Real> const& p0, Vector3<Real> const& p1,
        Vector3<Real> const& p2);

    // Public member access.
    Vector3<Real> normal;
    Real constant;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Plane3 const& plane) const;
    bool IsLessThan(Plane3 const& plane) const;
};

#include "GtePlane3.inl"

}
