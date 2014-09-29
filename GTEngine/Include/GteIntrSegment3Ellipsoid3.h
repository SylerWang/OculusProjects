// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrIntervals.h"
#include "GteIntrLine3Ellipsoid3.h"
#include "GteSegment3.h"

// The queries consider the ellipsoid to be a solid.

namespace gte
{

template <typename Real>
class TIQuery<Real, Segment3<Real>, Ellipsoid3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Segment3<Real> const& segment,
        Ellipsoid3<Real> const& ellipsoid);
};

template <typename Real>
class FIQuery<Real, Segment3<Real>, Ellipsoid3<Real>>
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

    Result operator()(Segment3<Real> const& segment,
        Ellipsoid3<Real> const& ellipsoid);

protected:
    void DoQuery(Vector3<Real> const& segOrigin,
        Vector3<Real> const& segDirection, Real segExtent,
        Ellipsoid3<Real> const& ellipsoid, Result& result);
};

#include "GteIntrSegment3Ellipsoid3.inl"

}
