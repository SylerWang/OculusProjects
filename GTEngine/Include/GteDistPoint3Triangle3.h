// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteDCPQuery.h"
#include "GteTriangle3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, Triangle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real triangleParameter[3];
        Vector3<Real> triangleClosestPoint;
    };

    Result operator()(Vector3<Real> const& point,
        Triangle3<Real> const& triangle);
};

#include "GteDistPoint3Triangle3.inl"

}
