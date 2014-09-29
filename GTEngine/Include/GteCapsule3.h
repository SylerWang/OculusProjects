// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteSegment3.h"

namespace gte
{

// A capsule is the set of points that are equidistant from a segment, the
// common distance called the radius.

template <typename Real>
class Capsule3 : public GeometricPrimitive<Capsule3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the segment
    // to have endpoints p0 = (-1,0,0) and p1 = (1,0,0), and the radius is 1.
    Capsule3();
    Capsule3(Segment3<Real> const& inSegment, Real inRadius);

    // Public member access.
    Segment3<Real> segment;
    Real radius;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Capsule3 const& capsule) const;
    bool IsLessThan(Capsule3 const& capsule) const;
};

#include "GteCapsule3.inl"

}
