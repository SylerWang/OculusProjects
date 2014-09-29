// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteDCPQuery.h"
#include "GteCircle3.h"
#include <limits>

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, Circle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;

        // The possibilities are 1 or std::numeric_limits<int>::max().  In the
        // latter case, the query point is on the line containing the circle
        // center and having direction the circle normal, and one closest point
        // is returned. 
        int numClosestPoints;
        Vector3<Real> circleClosestPoint;
    };

    Result operator()(Vector3<Real> const& point,
        Circle3<Real> const& circle);
};

#include "GteDistPoint3Circle3.inl"

}
