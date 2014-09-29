// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteDistPoint3Frustum3.h"
#include "GteSphere3.h"
#include "GteFrustum3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Sphere3<Real>, Frustum3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Sphere3<Real> const& sphere,
        Frustum3<Real> const& frustum);
};

#include "GteIntrSphere3Frustum3.inl"

}
