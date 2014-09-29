// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteEllipse2.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector2<Real>, Ellipse2<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Vector2<Real> ellipseClosestPoint;
    };

    Result operator()(Vector2<Real> const& point,
        Ellipse2<Real> const& ellipse);

private:
    // The ellipse is (x0/e0)^2 + (x1/e1)^2 = 1 with e0 >= e1.  The query
    // point is (y0,y1) with y0 >= 0 and y1 >= 0.  The function returns the
    // squared distance from the query point to the ellipse.  It also computes
    // the ellipse point (x0,x1) in the first quadrant that is closest to
    // (y0,y1).
    Real SqrDistanceSpecial(Real const e[2], Real const y[2], Real x[2]);

    // The ellipse is (x0/e0)^2 + (x1/e1)^2 = 1.  The query point is (y0,y1).
    // The function returns the squared distance from the query point to the
    // ellipse.  It also computes the ellipse point (x0,x1) that is closest to
    // (y0,y1).
    Real SqrDistance(Real const e[2], Real const y[2], Real x[2]);
};

#include "GteDistPoint2Ellipse2.inl"

}
