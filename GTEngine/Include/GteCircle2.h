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

// The circle is represented as |X-C| = R where C is the center and R is the
// radius.

template <typename Real>
class Circle2 : public GeometricPrimitive<Circle2<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the center
    // to (0,0) and the radius to 1.
    Circle2();
    Circle2(Vector2<Real> const& inCenter, Real inRadius);

    // Public member access.
    Vector2<Real> center;
    Real radius;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Circle2 const& circle) const;
    bool IsLessThan(Circle2 const& circle) const;
};

#include "GteCircle2.inl"

}
