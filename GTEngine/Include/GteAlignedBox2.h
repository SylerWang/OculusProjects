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

// The box is aligned with the standard coordinate axes, which allows us to
// represent it using minimum and maximum values along each axis.  Some
// algorithms prefer the centered representation that is used for oriented
// boxes.  The center is C and the extents are the half-lengths in each
// coordinate-axis direction.

template <typename Real>
class AlignedBox2 : public GeometricPrimitive<AlignedBox2<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the
    // minimum values to -1 and the maximum values to +1.
    AlignedBox2();

    // Please ensure that inMin[i] <= inMax[i] for all i.
    AlignedBox2(Real const inMin[2], Real const inMax[2]);

    // Please ensure that min0 <= max0 and min1 <= max1.
    AlignedBox2(Real min0, Real min1, Real max0, Real max1);

    // Compute the centered representation.  NOTE:  If you set the minimum
    // and maximum values, compute C and extents, and then recompute the
    // minimum and maximum values, the numerical round-off errors can lead to
    // results different from what you started with.
    void GetCenteredForm(Vector2<Real>& center, Vector2<Real>& extent) const;

    // Public member access.  It is required that min[i] <= max[i].
    Real min[2], max[2];

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(AlignedBox2 const& box) const;
    bool IsLessThan(AlignedBox2 const& box) const;
};

#include "GteAlignedBox2.inl"

}
