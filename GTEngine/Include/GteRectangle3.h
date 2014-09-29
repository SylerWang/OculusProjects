// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteVector2.h"
#include "GteVector3.h"

namespace gte
{

// Points are R(s0,s1) = C + s0*A0 + s1*A1, where C is the center of the
// rectangle and A0 and A1 are unit-length and perpendicular axes.  The
// parameters s0 and s1 are constrained by |s0| <= e0 and |s1| <= e1,
// where e0 > 0 and e1 > 0 are the extents of the rectangle.

template <typename Real>
class Rectangle3 : public GeometricPrimitive<Rectangle3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the origin
    // to (0,0,0), axis A0 to (1,0,0), axis A1 to (0,1,0), and both extents
    // to 1.
    Rectangle3();
    Rectangle3(Vector3<Real> const& inCenter, Vector3<Real> const inAxis[2],
        Vector2<Real> const& inExtent);
    Rectangle3(Vector3<Real> const& inCenter, Vector3<Real> const& axis0,
        Vector3<Real> const& axis1, Real extent0, Real extent1);

    // Compute the vertices of the rectangle.
    void GetVertices(Vector3<Real> vertex[4]) const;

    Vector3<Real> center;
    Vector3<Real> axis[2];
    Vector2<Real> extent;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Rectangle3 const& rectangle) const;
    bool IsLessThan(Rectangle3 const& rectangle) const;
};

#include "GteRectangle3.inl"

}
