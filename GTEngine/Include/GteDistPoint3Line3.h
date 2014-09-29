// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteLine3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, Line3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real lineParameter;
        Vector3<Real> lineClosestPoint;
    };

    Result operator()(Vector3<Real> const& point, Line3<Real> const& line);
};

#include "GteDistPoint3Line3.inl"

}
