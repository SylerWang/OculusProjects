// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrPlane3Plane3.h"
#include "GteCircle3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Plane3<Real>, Circle3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Plane3<Real> const& plane, Circle3<Real> const& circle);
};

template <typename Real>
class FIQuery<Real, Plane3<Real>, Circle3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // If 'intersect' is true, the intersection is either 1 or 2 points
        // or the entire circle.  When points, 'numIntersections' and
        // 'point' are valid.  When a circle, 'circle' is set to the incoming
        // circle.
        bool isPoints;
        int numIntersections;
        Vector3<Real> point[2];
        Circle3<Real> circle;
    };

    Result operator()(Plane3<Real> const& plane, Circle3<Real> const& circle);
};

#include "GteIntrPlane3Circle3.inl"

}
