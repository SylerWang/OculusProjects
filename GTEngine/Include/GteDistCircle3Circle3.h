// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteCircle3.h"
#include "GteRootsPolynomial.h"
#include "GteLogger.h"
#include <functional>

namespace gte
{

template <typename Real>
class DCPQuery<Real, Circle3<Real>, Circle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Vector3<Real> closestPoint[2];
    };

    Result operator()(Circle3<Real> const& circle0,
        Circle3<Real> const& circle1);
};

#include "GteDistCircle3Circle3.inl"

}
