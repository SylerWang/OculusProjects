// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrIntervals.h"
#include "GteIntrLine2Circle2.h"
#include "GteRay2.h"

// The queries consider the circle to be a solid (disk).

namespace gte
{

template <typename Real>
class TIQuery<Real, Ray2<Real>, Circle2<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Ray2<Real> const& ray, Circle2<Real> const& circle);
};

template <typename Real>
class FIQuery<Real, Ray2<Real>, Circle2<Real>>
    :
    public FIQuery<Real, Line2<Real>, Circle2<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line2<Real>, Circle2<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Ray2<Real> const& ray, Circle2<Real> const& circle);

protected:
    void DoQuery(Vector2<Real> const& rayOrigin,
        Vector2<Real> const& rayDirection, Circle2<Real> const& circle,
        Result& result);
};

#include "GteIntrRay2Circle2.inl"

}
