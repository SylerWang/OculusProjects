// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteDistLine3Segment3.h"
#include "GteRectangle3.h"
#include <limits>

namespace gte
{

template <typename Real>
class DCPQuery<Real, Line3<Real>, Rectangle3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real lineParameter, rectangleParameter[2];
        Vector3<Real> closestPoint[2];
    };

    Result operator()(Line3<Real> const& line,
        Rectangle3<Real> const& rectangle);
};

#include "GteDistLine3Rectangle3.inl"

}
