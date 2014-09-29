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

// The line is represented as P+t*D, where P is the line origin, D is a
// unit-length direction vector, and t is any real number.  The user must
// ensure that D is unit length.

template <typename Real>
class Line2 : public GeometricPrimitive<Line2<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the origin
    // to (0,0) and the line direction to (1,0).
    Line2();
    Line2(Vector2<Real> const& inOrigin, Vector2<Real> const& inDirection);

    // Public member access.  The direction must be unit length.
    Vector2<Real> origin, direction;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Line2 const& line) const;
    bool IsLessThan(Line2 const& line) const;
};

#include "GteLine2.inl"

}
