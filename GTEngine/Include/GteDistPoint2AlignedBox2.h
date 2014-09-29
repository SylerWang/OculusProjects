// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteAlignedBox2.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector2<Real>, AlignedBox2<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Vector2<Real> boxClosestPoint;
    };

    Result operator()(Vector2<Real> const& point,
        AlignedBox2<Real> const& box);

protected:
    // On input, 'point' is the difference of the query point and the box
    // center.  On output, 'point' is the point on the box closest to the
    // query point.
    void DoQuery(Vector2<Real>& point, Vector2<Real> const& boxExtent,
        Result& result);
};

#include "GteDistPoint2AlignedBox2.inl"

}
