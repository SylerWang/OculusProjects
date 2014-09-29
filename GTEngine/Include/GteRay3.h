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

// The ray is represented by P+t*D, where P is the origin point, D is a
// unit-length direction vector, and t >= 0.  The user must ensure that D is
// unit length.

template <typename Real>
class Ray3 : public GeometricPrimitive<Ray3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the origin
    // to (0,0,0) and the ray direction to (1,0,0).
    Ray3();
    Ray3(Vector3<Real> const& inOrigin, Vector3<Real> const& inDirection);

    // Public member access.  The direction must be unit length.
    Vector3<Real> origin, direction;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Ray3 const& ray) const;
    bool IsLessThan(Ray3 const& ray) const;
};

#include "GteRay3.inl"

}
