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

// The plane containing ellipse is Dot(N,X-C) = 0 where X is any point in the
// plane, C is the ellipse center, and N is a unit-length normal to the plane.
// Vectors A0, A1, and N form an orthonormal right-handed set.  The ellipse in
// the plane is parameterized by X = C + e0*cos(t)*A0 + e1*sin(t)*A1, where A0
// is the major axis, A1 is the minor axis, and e0 and e1 are the extents
// along those axes.  The angle t is in [-pi,pi) and e0 >= e1 > 0.

template <typename Real>
class Ellipse3 : public GeometricPrimitive<Ellipse3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets center to
    // (0,0,0), A0 to (1,0,0), A1 to (0,1,0), normal to (0,0,1), e0 to 1, and
    // e1 to 1.
    Ellipse3(); 
    Ellipse3(Vector3<Real> const& inCenter, Vector3<Real> const& inNormal,
        Vector3<Real> const inAxis[2], Vector2<Real> const& inExtent);

    // Public member access.
    Vector3<Real> center, normal;
    Vector3<Real> axis[2];
    Vector2<Real> extent;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Ellipse3 const& ellipse) const;
    bool IsLessThan(Ellipse3 const& ellipse) const;
};

#include "GteEllipse3.inl"

}
