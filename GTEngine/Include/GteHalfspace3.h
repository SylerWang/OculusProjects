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

// The halfspace is represented as Dot(N,X) >= c where N is a unit-length
// normal vector, c is the plane constant, and X is any point in space.
// The user must ensure that the normal vector is unit length.

template <typename Real>
class Halfspace3 : public GeometricPrimitive<Halfspace3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the normal
    // to (0,0,1) and the constant to zero (halfspace z >= 0).
    Halfspace3();

    // Specify N and c directly.
    Halfspace3(Vector3<Real> const& inNormal, Real inConstant);

    // Public member access.
    Vector3<Real> normal;
    Real constant;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Halfspace3 const& halfspace) const;
    bool IsLessThan(Halfspace3 const& halfspace) const;
};

#include "GteHalfspace3.inl"

}
