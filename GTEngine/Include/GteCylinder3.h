// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteLine3.h"

namespace gte
{

// The cylinder axis is a line.  The origin of the cylinder is chosen to be
// the line origin.  The cylinder wall is at a distance R units from the axis.
// An infinite cylinder has infinite height.  A finite cylinder has center C
// at the line origin and has a finite height H.  The segment for the finite
// cylinder has endpoints C-(H/2)*D and C+(H/2)*D where D is a unit-length
// direction of the line.

template <typename Real>
class Cylinder3 : public GeometricPrimitive<Cylinder3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets axis to
    // (0,0,1), radius to 1, and height to 1.
    Cylinder3();
    Cylinder3(Line3<Real> const& inAxis, Real inRadius, Real inHeight);

    Line3<Real> axis;
    Real radius, height;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Cylinder3 const& cylinder) const;
    bool IsLessThan(Cylinder3 const& cylinder) const;
};

#include "GteCylinder3.inl"

}
