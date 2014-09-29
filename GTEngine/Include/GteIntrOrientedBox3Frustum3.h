// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFrustum3.h"
#include "GteOrientedBox3.h"

namespace gte
{

// The method of separating axes is used.  The potential separating axes
// include the 3 box face normals, the 5 distinct frustum normals (near and
// far plane have the same normal), and cross products of normals, one from
// the box and one from the frustum.

template <typename Real>
class TIQuery<Real, OrientedBox3<Real>, Frustum3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(OrientedBox3<Real> const& box,
        Frustum3<Real> const& frustum);
};

#include "GteIntrOrientedBox3Frustum3.inl"

}
