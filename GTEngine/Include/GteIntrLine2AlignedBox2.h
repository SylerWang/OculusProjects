// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteLine2.h"
#include "GteAlignedBox2.h"
#include <limits>

// The queries consider the box to be a solid.
//
// The test-intersection queries use the method of separating axes.  The
// find-intersection queries use parametric clipping against the four edges of
// the box.

namespace gte
{

template <typename Real>
class TIQuery<Real, Line2<Real>, AlignedBox2<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(Line2<Real> const& line, AlignedBox2<Real> const& box);

protected:
    void DoQuery(Vector2<Real> const& lineOrigin,
        Vector2<Real> const& lineDirection, Vector2<Real> const& boxExtent,
        Result& result);
};

template <typename Real>
class FIQuery<Real, Line2<Real>, AlignedBox2<Real>>
{
public:
    struct Result
    {
        bool intersect;
        int numIntersections;
        std::array<Real, 2> parameter;
        std::array<Vector2<Real>, 2> point;
    };

    Result operator()(Line2<Real> const& line, AlignedBox2<Real> const& box);

protected:
    void DoQuery(Vector2<Real> const& lineOrigin,
        Vector2<Real> const& lineDirection, Vector2<Real> const& boxExtent,
        Result& result);

private:
    // Test whether the current clipped segment intersects the current test
    // plane.  If the return value is 'true', the segment does intersect the
    // plane and is clipped; otherwise, the segment is culled (no intersection
    // with box).
    static bool Clip(Real denom, Real numer, Real& t0, Real& t1);
};

#include "GteIntrLine2AlignedBox2.inl"

}
