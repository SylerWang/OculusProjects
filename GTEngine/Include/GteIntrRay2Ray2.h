// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrLine2Line2.h"
#include "GteRay2.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Ray2<Real>, Ray2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (rays intersect in a
        // single point), 2 (rays are collinear and intersect in a segment;
        // ray directions are opposite of each other), or
        // std::numeric_limits<int>::max() (intersection is a ray; ray
        // directions are the same).
        int numIntersections;
    };

    Result operator()(Ray2<Real> const& ray0, Ray2<Real> const& ray1);
};

template <typename Real>
class FIQuery<Real, Ray2<Real>, Ray2<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // The number is 0 (no intersection), 1 (rays intersect in a
        // single point), 2 (rays are collinear and intersect in a segment;
        // ray directions are opposite of each other), or
        // std::numeric_limits<int>::max() (intersection is a ray; ray
        // directions are the same).
        int numIntersections;

        // If numIntersections is 1, the intersection is
        //   point[0] = ray0.origin + ray0Parameter[0] * ray0.direction
        //            = ray1.origin + ray1Parameter[0] * ray1.direction
        // If numIntersections is 2, the segment of intersection is formed by
        // the ray origins,
        //   ray0Parameter[0] = ray1Parameter[0] = 0
        //   point[0] = ray0.origin
        //            = ray1.origin + ray1Parameter[1] * ray1.direction
        //   point[1] = ray1.origin
        //            = ray0.origin + ray0Parameter[1] * ray0.direction
        // where ray0Parameter[1] >= 0 and ray1Parameter[1] >= 0.
        // If numIntersections is maxInt, let
        //   ray1.origin = ray0.origin + t * ray0.direction
        // then
        //   ray0Parameter[] = { max(t,0), +maxReal }
        //   ray1Parameter[] = { -min(t,0), +maxReal }
        //   point[0] = ray0.origin + ray0Parameter[0] * ray0.direction
        Real ray0Parameter[2], ray1Parameter[2];
        Vector2<Real> point[2];
    };

    Result operator()(Ray2<Real> const& ray0, Ray2<Real> const& ray1);
};

#include "GteIntrRay2Ray2.inl"

}
