// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDistSegment3Rectangle3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Rectangle3<Real>, Rectangle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real rectangle0Parameter[2], rectangle1Parameter[2];
        Vector3<Real> closestPoint[2];
    };

    Result operator()(Rectangle3<Real> const& rectangle0,
        Rectangle3<Real> const& rectangle1);
};

#include "GteDistRectangle3Rectangle3.inl"

}
