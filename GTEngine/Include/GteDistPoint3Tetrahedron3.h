// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteDCPQuery.h"
#include "GteDistPoint3Triangle3.h"
#include "GteTetrahedron3.h"
#include <limits>

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, Tetrahedron3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Vector3<Real> tetrahedronClosestPoint;
    };

    Result operator()(Vector3<Real> const& point,
        Tetrahedron3<Real> const& tetrahedron);
};

#include "GteDistPoint3Tetrahedron3.inl"

}
