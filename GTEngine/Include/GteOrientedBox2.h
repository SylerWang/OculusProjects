// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteVector2.h"

namespace gte
{

// A box has center C; axis directions U[0] and U[1]; and extents e[0] and
// e[1].  The set {U[0],U[1]} is orthonormal, which means the vectors are
// unit-length and mutually perpendicular.  The extents are nonnegative;
// zero is allowed, meaning the box is degenerate in the corresponding
// direction.  A point X is represented in box coordinates by
// X = C + y[0]*U[0] + y[1]*U[1].  This point is inside or on the
// box whenever |y[i]| <= e[i] for all i.

template <typename Real>
class OrientedBox2 : public GeometricPrimitive<OrientedBox2<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the center
    // to (0,0), axis D to Vector2<Real>::BasisD(), and extent i to +1.
    OrientedBox2();
    OrientedBox2(Vector2<Real> const& inCenter, Vector2<Real> const inAxis[2],
        Vector2<Real> const& inExtent);
    OrientedBox2(Vector2<Real> const& inCenter, Vector2<Real> const& axis0,
        Vector2<Real> const& axis1, Real extent0, Real extent1);

    // Compute the vertices of the box.
    void GetVertices(Vector2<Real> vertex[4]) const;

    // Public member access.  It is required that extent[i] >= 0.
    Vector2<Real> center;
    Vector2<Real> axis[2];
    Vector2<Real> extent;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(OrientedBox2 const& box) const;
    bool IsLessThan(OrientedBox2 const& box) const;
};

#include "GteOrientedBox2.inl"

}
