// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteFIQuery.h"
#include "GteCylinder3.h"
#include "GteLine3.h"
#include "GteLogger.h"

// The queries consider the cylinder to be a solid.

namespace gte
{

template <typename Real>
class FIQuery<Real, Line3<Real>, Cylinder3<Real>>
{
public:
    struct Result
    {
        bool intersect;
        int numIntersections;
        std::array<Real, 2> parameter;
        std::array<Vector3<Real>, 2> point;
    };

    Result operator()(Line3<Real> const& line,
        Cylinder3<Real> const& cylinder);

protected:
    void DoQuery(Vector3<Real> const& lineOrigin,
        Vector3<Real> const& lineDirection, Cylinder3<Real> const& cylinder,
        Result& result);
};

#include "GteIntrLine3Cylinder3.inl"

}
