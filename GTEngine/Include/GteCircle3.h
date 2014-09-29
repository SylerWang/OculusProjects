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

// The circle is the intersection of the sphere |X-C|^2 = r^2 and the
// plane Dot(N,X-C) = 0, where C is the circle center, r is the radius,
// and N is a unit-length plane normal.

template <typename Real>
class Circle3 : public GeometricPrimitive<Circle3<Real>>
{
public:

    // Construction and destruction.  The default constructor sets center to
    // (0,0,0), normal to (0,0,1), and radius to 1.
    Circle3();
    Circle3(Vector3<Real> const& inCenter, Vector3<Real> const& inNormal,
        Real inRadius);

    // Public member access.
    Vector3<Real> center, normal;
    Real radius;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Circle3 const& capsule) const;
    bool IsLessThan(Circle3 const& capsule) const;
};

#include "GteCircle3.inl"

}
