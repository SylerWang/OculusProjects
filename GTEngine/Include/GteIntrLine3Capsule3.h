// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteDistLine3Segment3.h"
#include "GteCapsule3.h"

// The queries consider the capsule to be a solid.
//
// The test-intersection queries are based on distance computations.

namespace gte
{

template <typename Real>
class TIQuery<Real, Line3<Real>, Capsule3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Line3<Real> const& line, Capsule3<Real> const& capsule);
};

template <typename Real>
class FIQuery<Real, Line3<Real>, Capsule3<Real>>
{
public:
    struct Result
    {
        bool intersect;
        int numIntersections;
        std::array<Real, 2> parameter;
        std::array<Vector3<Real>, 2> point;
    };

    Result operator()(Line3<Real> const& line, Capsule3<Real> const& capsule);

protected:
    void DoQuery(Vector3<Real> const& lineOrigin,
        Vector3<Real> const& lineDirection, Capsule3<Real> const& capsule,
        Result& result);
};

#include "GteIntrLine3Capsule3.inl"

}
