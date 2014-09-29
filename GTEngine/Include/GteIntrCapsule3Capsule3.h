// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteDistSegment3Segment3.h"
#include "GteCapsule3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Capsule3<Real>, Capsule3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Capsule3<Real> const& capsule0,
        Capsule3<Real> const& capsule1);
};

#include "GteIntrCapsule3Capsule3.inl"

}
