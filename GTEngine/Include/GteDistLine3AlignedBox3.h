// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDistPoint3AlignedBox3.h"
#include "GteLine3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Line3<Real>, AlignedBox3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Real lineParameter;
        Vector3<Real> closestPoint[2];
    };

    Result operator()(Line3<Real> const& line, AlignedBox3<Real> const& box);

protected:
    // Compute the distance and closest point between a line and an
    // axis-aligned box whose center is the origin.  On input, 'point' is the
    // line origin and 'direction' is the line direction.  On output, 'point'
    // is the point on the box closest to the line.  The 'direction' is
    // non-const to allow transforming the problem into the first octant.
    void DoQuery(Vector3<Real>& point, Vector3<Real>& direction,
        Vector3<Real> const& boxExtent, Result& result);

private:
    void Face(int i0, int i1, int i2, Vector3<Real>& pnt,
        Vector3<Real> const& dir, Vector3<Real> const& PmE,
        Vector3<Real> const& boxExtent, Result& result);

    void CaseNoZeros(Vector3<Real>& pnt, Vector3<Real> const& dir,
        Vector3<Real> const& boxExtent, Result& result);

    void Case0(int i0, int i1, int i2, Vector3<Real>& pnt,
        Vector3<Real> const& dir, Vector3<Real> const& boxExtent,
        Result& result);

    void Case00(int i0, int i1, int i2, Vector3<Real>& pnt,
        Vector3<Real> const& dir, Vector3<Real> const& boxExtent,
        Result& result);

    void Case000(Vector3<Real>& pnt, Vector3<Real> const& boxExtent,
        Result& result);
};

#include "GteDistLine3AlignedBox3.inl"

}
