// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteMatrix2x2.h"
#include "GteLogger.h"
#include <algorithm>

// Compute the minimum-area ellipse, (X-C)^T R D R^T (X-C) = 1, given the
// center C and the orientation matrix R.  The columns of R are the axes of
// the ellipse.  The algorithm computes the diagonal matrix D.  The minimum
// area is pi/sqrt(D[0]*D[1]), where D = diag(D[0],D[1]).  The problem is
// equivalent to maximizing the product D[0]*D[1] for a given C and R, and
// subject to the constraints
//   (P[i]-C)^T R D R^T (P[i]-C) <= 1
// for all input points P[i] with 0 <= i < N.  Each constraint has the form
//   A[0]*D[0] + A[1]*D[1] <= 1
// where A[0] >= 0 and A[1] >= 0.

namespace gte
{

template <typename Real>
class ContEllipse2MinCR
{
public:
    void operator()(int numPoints, Vector2<Real> const* points,
        Vector2<Real> const& C, Matrix2x2<Real> const& R, Real D[2]) const;

private:
    static void MaxProduct(std::vector<Vector2<Real>>& A, Real D[2]);
};

#include "GteContEllipse2MinCR.inl"

}
