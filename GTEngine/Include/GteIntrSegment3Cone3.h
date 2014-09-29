// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrLine3Cone3.h"
#include "GteSegment3.h"

// The queries consider the cone to be single sided and solid.

namespace gte
{

template <typename Real>
class FIQuery<Real, Segment3<Real>, Cone3<Real>>
    :
    public FIQuery<Real, Line3<Real>, Cone3<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line3<Real>, Cone3<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Segment3<Real> const& segment, Cone3<Real> const& cone);

protected:
    void DoQuery(Vector3<Real> const& segOrigin,
        Vector3<Real> const& segDirection, Real segExtent,
        Cone3<Real> const& cone, Result& result);
};

#include "GteIntrSegment3Cone3.inl"

}
