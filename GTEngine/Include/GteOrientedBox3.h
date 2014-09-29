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

// A box has center C; axis directions U[0], U[1], and U[2]; and extents
// e[0], e[1], and e[2].  The set {U[0],U[1],U[2]} is orthonormal, which means
// the vectors are unit-length and mutually perpendicular.  The extents are
// nonnegative; zero is allowed, meaning the box is degenerate in the
// corresponding direction.  A point X is represented in box coordinates by
// X = C + y[0]*U[0] + y[1]*U[1] + y[2]*U[2].  This point is inside or on the
// box whenever |y[i]| <= e[i] for all i.

template <typename Real>
class OrientedBox3 : public GeometricPrimitive<OrientedBox3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the center
    // to (0,0,0), axis D to Vector3<Real>::BasisD(), and extent i to +1.
    OrientedBox3();
    OrientedBox3(Vector3<Real> const& inCenter, Vector3<Real> const inAxis[3],
        Vector3<Real> const& inExtent);
    OrientedBox3(Vector3<Real> const& inCenter, Vector3<Real> const& axis0,
        Vector3<Real> const& axis1, Vector3<Real> const& axis2, Real extent0,
        Real extent1, Real extent2);

    // Compute the vertices of the box.
    void GetVertices(Vector3<Real> vertex[8]) const;

    // Public member access.  It is required that extent[i] >= 0.
    Vector3<Real> center;
    Vector3<Real> axis[3];
    Vector3<Real> extent;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(OrientedBox3 const& box) const;
    bool IsLessThan(OrientedBox3 const& box) const;
};

#include "GteOrientedBox3.inl"

}
