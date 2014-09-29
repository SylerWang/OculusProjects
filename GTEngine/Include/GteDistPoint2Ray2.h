// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteRay2.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector2<Real>, Ray2<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real rayParameter;
        Vector2<Real> rayClosestPoint;
    };

    Result operator()(Vector2<Real> const& point, Ray2<Real> const& ray);
};

#include "GteDistPoint2Ray2.inl"

}
