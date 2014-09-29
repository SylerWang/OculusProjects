// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteLine2.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector2<Real>, Line2<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real lineParameter;
        Vector2<Real> lineClosestPoint;
    };

    Result operator()(Vector2<Real> const& point, Line2<Real> const& line);
};

#include "GteDistPoint2Line2.inl"

}
