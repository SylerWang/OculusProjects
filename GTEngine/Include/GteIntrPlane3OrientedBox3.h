// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteDistPoint3Plane3.h"
#include "GteOrientedBox3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Plane3<Real>, OrientedBox3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Plane3<Real> const& plane,
        OrientedBox3<Real> const& box);
};

#include "GteIntrPlane3OrientedBox3.inl"

}
