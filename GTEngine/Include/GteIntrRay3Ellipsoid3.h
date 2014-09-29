// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrIntervals.h"
#include "GteIntrLine3Ellipsoid3.h"
#include "GteRay3.h"

// The queries consider the ellipsoid to be a solid.

namespace gte
{

template <typename Real>
class TIQuery<Real, Ray3<Real>, Ellipsoid3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Ray3<Real> const& ray,
        Ellipsoid3<Real> const& ellipsoid);
};

template <typename Real>
class FIQuery<Real, Ray3<Real>, Ellipsoid3<Real>>
    :
    public FIQuery<Real, Line3<Real>, Ellipsoid3<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line3<Real>, Ellipsoid3<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Ray3<Real> const& ray,
        Ellipsoid3<Real> const& ellipsoid);

protected:
    void DoQuery(Vector3<Real> const& rayOrigin,
        Vector3<Real> const& rayDirection, Ellipsoid3<Real> const& ellipsoid,
        Result& result);
};

#include "GteIntrRay3Ellipsoid3.inl"

}
