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
#include "GteCone3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Sphere3<Real>, Cone3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Sphere3<Real> const& sphere, Cone3<Real> const& cone);
};

template <typename Real>
class FIQuery<Real, Sphere3<Real>, Cone3<Real>>
{
public:
    struct Result
    {
        // If an intersection occurs, it is potentially an infinite set.  If
        // the cone vertex is inside the sphere, 'point' is set to the cone
        // vertex; else if the sphere center is inside the cone, 'point' is
        // set to the sphere center; else 'point' is set to the cone point
        // closest to the cone vertex.
        bool intersect;
        Vector3<Real> point;
    };

    Result operator()(Sphere3<Real> const& sphere, Cone3<Real> const& cone);
};

#include "GteIntrSphere3Cone3.inl"

}
