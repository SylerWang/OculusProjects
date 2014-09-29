// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDCPQuery.h"
#include "GteEllipsoid3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, Ellipsoid3<Real>>
{
public:
    struct Result
    {
        Real distance, sqrDistance;
        Vector3<Real> ellipsoidClosestPoint;
    };

    Result operator()(Vector3<Real> const& point,
        Ellipsoid3<Real> const& ellipsoid);

private:
    // The ellipsoid is (x0/e0)^2 + (x1/e1)^2 + (x2/e2)^2 = 1 with
    // e0 >= e1 >= e2.  The query point is (y0,y1,y2) with y0 >= 0, y1 >= 0,
    // and y2 >= 0.  The function returns the squared distance from the query
    // point to the ellipsoid.  It also computes the ellipsoid point
    // (x0,x1,x2) in the first octant that is closest to (y0,y1,y2).
    Real SqrDistanceSpecial(Real const e[3], Real const y[3], Real x[3]);

    // The ellipsoid is (x0/e0)^2 + (x1/e1)^2 + (x2/e2)^2 = 1.  The query
    // point is (y0,y1,y2).  The function returns the squared distance from
    // the query point to the ellipsoid.   It also computes the ellipsoid
    // point (x0,x1,x2) that is closest to (y0,y1,y2).
    Real SqrDistance(Real const e[3], Real const y[3], Real x[3]);

    // The bisection algorithm to find the unique root of F(t).
    Real Bisector(int numComponents, Real const* e, Real const* y, Real* x);
};

#include "GteDistPoint3Ellipsoid3.inl"

}
