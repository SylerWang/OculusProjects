// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteDistSegment3Triangle3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Triangle3<Real>, Triangle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real triangle0Parameter[3], triangle1Parameter[3];
        Vector3<Real> closestPoint[2];
    };

    Result operator()(Triangle3<Real> const& triangle0,
        Triangle3<Real> const& triangle1);
};

#include "GteDistTriangle3Triangle3.inl"

}
