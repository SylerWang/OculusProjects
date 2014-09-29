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

// The sphere is represented as |X-C| = R where C is the center and R is the
// radius.

template <typename Real>
class Sphere3 : public GeometricPrimitive<Sphere3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the center
    // to (0,0,0) and the radius to 1.
    Sphere3();
    Sphere3(Vector3<Real> const& inCenter, Real inRadius);

    // Public member access.
    Vector3<Real> center;
    Real radius;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Sphere3 const& sphere) const;
    bool IsLessThan(Sphere3 const& sphere) const;
};

#include "GteSphere3.inl"

}
