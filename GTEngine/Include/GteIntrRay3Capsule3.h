// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrIntervals.h"
#include "GteIntrLine3Capsule3.h"
#include "GteDistRay3Segment3.h"

// The queries consider the capsule to be a solid.
//
// The test-intersection queries are based on distance computations.

namespace gte
{

template <typename Real>
class TIQuery<Real, Ray3<Real>, Capsule3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Ray3<Real> const& ray, Capsule3<Real> const& capsule);
};

template <typename Real>
class FIQuery<Real, Ray3<Real>, Capsule3<Real>>
    :
    public FIQuery<Real, Line3<Real>, Capsule3<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line3<Real>, Capsule3<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Ray3<Real> const& ray, Capsule3<Real> const& capsule);

protected:
    void DoQuery(Vector3<Real> const& rayOrigin,
        Vector3<Real> const& rayDirection, Capsule3<Real> const& capsule,
        Result& result);
};

#include "GteIntrRay3Capsule3.inl"

}
