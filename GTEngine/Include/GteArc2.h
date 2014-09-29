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

// The circle containing the arc is represented as |X-C| = R where C is the
// center and R is the radius.  The arc is defined by two points end0 and end1
// on the circle so that end1 is obtained from end0 by traversing
// counterclockwise.  The application is responsible for ensuring that end0
// and end1 are on the circle and that they are properly ordered.

template <typename Real>
class Arc2 : public GeometricPrimitive<Arc2<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the center
    // to (0,0), radius to 1, end0 to (1,0), and end1 to (0,1).
    Arc2();
    Arc2(Vector2<Real> const& inCenter, Real inRadius,
        Vector2<Real>const& inEnd0, Vector2<Real>const & inEnd1);

    // Test whether P is on the arc.  The application must ensure that P is on
    // the circle; that is, |P-C| = R.  This test works for any angle between
    // B-C and A-C, not just those between 0 and pi radians.
    bool Contains(Vector2<Real> const& p) const;

    Vector2<Real> center;
    Real radius;
    Vector2<Real> end[2];

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Arc2 const& arc) const;
    bool IsLessThan(Arc2 const& arc) const;
};

#include "GteArc2.inl"

}
