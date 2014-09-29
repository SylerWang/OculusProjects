// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrLine3Plane3.h"
#include "GteRay3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Ray3<Real>, Plane3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Ray3<Real> const& ray, Plane3<Real> const& plane);
};

template <typename Real>
class FIQuery<Real, Ray3<Real>, Plane3<Real>>
    :
    public FIQuery<Real, Line3<Real>, Plane3<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line3<Real>, Plane3<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Ray3<Real> const& ray, Plane3<Real> const& plane);

protected:
    void DoQuery(Vector3<Real> const& rayOrigin,
        Vector3<Real> const& rayDirection, Plane3<Real> const& plane,
        Result& result);
};

#include "GteIntrRay3Plane3.inl"

}
