// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrLine2AlignedBox2.h"
#include "GteRay2.h"
#include "GteIntrIntervals.h"

// The queries consider the box to be a solid.
//
// The test-intersection queries use the method of separating axes.  The
// find-intersection queries use parametric clipping against the four edges of
// the box.

namespace gte
{

template <typename Real>
class TIQuery<Real, Ray2<Real>, AlignedBox2<Real>>
    :
    public TIQuery<Real, Line2<Real>, AlignedBox2<Real>>
{
public:
    struct Result
        :
        public TIQuery<Real, Line2<Real>, AlignedBox2<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Ray2<Real> const& ray, AlignedBox2<Real> const& box);

protected:
    void DoQuery(Vector2<Real> const& rayOrigin,
        Vector2<Real> const& rayDirection, Vector2<Real> const& boxExtent,
        Result& result);
};

template <typename Real>
class FIQuery<Real, Ray2<Real>, AlignedBox2<Real>>
    :
    public FIQuery<Real, Line2<Real>, AlignedBox2<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Line2<Real>, AlignedBox2<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Ray2<Real> const& ray, AlignedBox2<Real> const& box);

protected:
    void DoQuery(Vector2<Real> const& rayOrigin,
        Vector2<Real> const& rayDirection, Vector2<Real> const& boxExtent,
        Result& result);
};

#include "GteIntrRay2AlignedBox2.inl"

}
