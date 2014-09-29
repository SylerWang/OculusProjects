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
#include "GteSphere3.h"
#include "GteCircle3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Plane3<Real>, Sphere3<Real>>
{
    struct Result
    {
        bool intersect;
    };

    Result operator()(Plane3<Real> const& plane, Sphere3<Real> const& sphere);
};

template <typename Real>
class FIQuery<Real, Plane3<Real>, Sphere3<Real>>
{
    struct Result
    {
        bool intersect;

        // If 'intersect' is true, the intersection is either a point or a
        // circle.  When 'isCircle' is true, 'circle' is valid.  When
        // 'isCircle' is false, 'point' is valid.
        bool isCircle;
        Circle3<Real> circle;
        Vector3<Real> point;
    };

    Result operator()(Plane3<Real> const& plane, Sphere3<Real> const& sphere);
};

#include "GteIntrPlane3Sphere3.inl"

}
