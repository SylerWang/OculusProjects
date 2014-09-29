// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteFrustum3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, Frustum3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Vector3<Real> frustumClosestPoint;
    };

    Result operator()(Vector3<Real> const& point,
        Frustum3<Real> const& frustum);
};

#include "GteDistPoint3Frustum3.inl"

}
