// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteSphere3.h"
#include "GteCircle3.h"

// The queries consider the spheres to be solids.

namespace gte
{

template <typename Real>
class TIQuery<Real, Sphere3<Real>, Sphere3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Sphere3<Real> const& sphere0,
        Sphere3<Real> const& sphere1);
};

template <typename Real>
class FIQuery<Real, Sphere3<Real>, Sphere3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The type of intersection.
        //   0: spheres are disjoint and separated
        //   1: spheres touch at point, each sphere outside the other
        //   2: spheres intersect in a circle
        //   3: sphere0 strictly contained in sphere1
        //   4: sphere0 contained in sphere1, share common point
        //   5: sphere1 strictly contained in sphere0
        //   6: sphere1 contained in sphere0, share common point
        int type;
        Vector3<Real> point;    // types 1, 4, 6
        Circle3<Real> circle;   // type 2
    };

    Result operator()(Sphere3<Real> const& sphere0,
        Sphere3<Real> const& sphere1);
};

#include "GteIntrSphere3Sphere3.inl"

}
