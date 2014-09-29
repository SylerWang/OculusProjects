// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteAlignedBox2.h"
#include "GteOrientedBox2.h"

// The queries consider the box to be a solid.
//
// The test-intersection query uses the method of separating axes.  The set of
// potential separating directions includes the 2 edge normals of box0 and the
// 2 edge normals of box1.  The integer 'separating' identifies the axis that
// reported separation; there may be more than one but only one is reported.
// The value is 0 when box0.axis[0] separates, 1 when box0.axis[1] separates,
// 2 when box1.axis[0] separates, or 3 when box1.axis[1] separates.

namespace gte
{

template <typename Real>
class TIQuery<Real, AlignedBox2<Real>, OrientedBox2<Real>>
{
public:
    struct Result
    {
        bool intersect;
        int separating;
    };

    Result operator()(AlignedBox2<Real> const& box0,
        OrientedBox2<Real> const& box1);
};

#include "GteIntrAlignedBox2OrientedBox2.inl"

}
