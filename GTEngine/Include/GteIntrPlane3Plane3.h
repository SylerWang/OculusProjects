// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GtePlane3.h"
#include "GteLine3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Plane3<Real>, Plane3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Plane3<Real> const& plane0, Plane3<Real> const& plane1);
};

template <typename Real>
class FIQuery<Real, Plane3<Real>, Plane3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // If 'intersect' is true, the intersection is either a line or the
        // planes are the same.  When a line, 'line' is valid.  When a plane,
        // 'plane' is set to one of the planes.
        bool isLine;
        Line3<Real> line;
        Plane3<Real> plane;
    };

    Result operator()(Plane3<Real> const& plane0, Plane3<Real> const& plane1);
};

#include "GteIntrPlane3Plane3.inl"

}
