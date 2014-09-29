// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteLogger.h"
#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteDistPoint3Plane3.h"
#include "GteCylinder3.h"
#include "GteLine3.h"
#include "GteCircle3.h"
#include "GteEllipse3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Plane3<Real>, Cylinder3<Real>>
{
    struct Result
    {
        bool intersect;
    };

    // The cylinder must have finite height.
    Result operator()(Plane3<Real> const& plane,
        Cylinder3<Real> const& cylinder);
};

template <typename Real>
class FIQuery<Real, Plane3<Real>, Cylinder3<Real>>
{
    struct Result
    {
        bool intersect;

        // The type of intersection.
        //   0: none
        //   1: single line (cylinder is tangent to plane), line[0] valid
        //   2: two parallel lines (plane cuts cylinder in two lines)
        //   3: circle (cylinder axis perpendicular to plane)
        //   4: ellipse (cylinder axis neither parallel nor perpendicular)
        int type;
        Line3<Real> line[2];
        Circle3<Real> circle;
        Ellipse3<Real> ellipse;
    };

    // The cylinder must have infinite height.
    Result operator()(Plane3<Real> const& plane,
        Cylinder3<Real> const& cylinder);
};

#include "GteIntrPlane3Cylinder3.inl"

}
