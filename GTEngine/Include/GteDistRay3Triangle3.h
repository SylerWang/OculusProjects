// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDistPoint3Triangle3.h"
#include "GteDistLine3Triangle3.h"
#include "GteRay3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Ray3<Real>, Triangle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real rayParameter, triangleParameter[3];
        Vector3<Real> closestPoint[2];
    };

    Result operator()(Ray3<Real> const& ray, Triangle3<Real> const& triangle);
};

#include "GteDistRay3Triangle3.inl"

}
