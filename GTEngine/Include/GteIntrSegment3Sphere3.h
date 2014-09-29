// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrIntervals.h"
#include "GteIntrLine3Sphere3.h"
#include "GteSegment3.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Segment3<Real>, Sphere3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Segment3<Real> const& segment,
        Sphere3<Real> const& sphere);
};

template <typename Real>
class FIQuery<Real, Segment3<Real>, Sphere3<Real>>
    :
    public FIQuery<Real, Line3<Real>, Sphere3<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line3<Real>, Sphere3<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Segment3<Real> const& segment,
        Sphere3<Real> const& sphere);

protected:
    void DoQuery(Vector3<Real> const& segOrigin,
        Vector3<Real> const& segDirection, Real segExtent,
        Sphere3<Real> const& sphere, Result& result);
};

#include "GteIntrSegment3Sphere3.inl"

}
