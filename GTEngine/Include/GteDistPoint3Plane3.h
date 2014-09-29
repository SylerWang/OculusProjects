// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GtePlane3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, Plane3<Real>>
{
public:
    struct Result
    {
        Real distance, signedDistance;
        Vector3<Real> planeClosestPoint;
    };

    Result operator()(Vector3<Real> const& point, Plane3<Real> const& plane);
};

#include "GteDistPoint3Plane3.inl"

}
