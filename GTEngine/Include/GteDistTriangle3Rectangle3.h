// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDistSegment3Rectangle3.h"
#include "GteDistSegment3Triangle3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Triangle3<Real>, Rectangle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real triangleParameter[3], rectangleParameter[2];
        Vector3<Real> closestPoint[2];
    };

    Result operator()(Triangle3<Real> const& triangle,
        Rectangle3<Real> const& rectangle);
};

#include "GteDistTriangle3Rectangle3.inl"

}
