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

// The triangle is represented as an array of three vertices: V0, V1, and V2.

template <typename Real>
class Triangle2 : public GeometricPrimitive<Triangle2<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the
    // vertices to (0,0), (1,0), and (0,1).
    Triangle2();
    Triangle2(Vector2<Real> const& v0, Vector2<Real> const& v1,
        Vector2<Real> const& v2);
    Triangle2(Vector2<Real> const inV[3]);

    // Public member access.
    Vector2<Real> v[3];

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Triangle2 const& triangle) const;
    bool IsLessThan(Triangle2 const& triangle) const;
};

#include "GteTriangle2.inl"

}
