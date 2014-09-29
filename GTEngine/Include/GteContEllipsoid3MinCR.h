// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteMatrix3x3.h"
#include "GteLogger.h"
#include <random>

// Compute the minimum-volume ellipsoid, (X-C)^T R D R^T (X-C) = 1, given the
// center C and orientation matrix R.  The columns of R are the axes of the
// ellipsoid.  The algorithm computes the diagonal matrix D.  The minimum
// volume is (4*pi/3)/sqrt(D[0]*D[1]*D[2]), where D = diag(D[0],D[1],D[2]).
// The problem is equivalent to maximizing the product D[0]*D[1]*D[2] for a
// given C and R, and subject to the constraints
//   (P[i]-C)^T R D R^T (P[i]-C) <= 1
// for all input points P[i] with 0 <= i < N.  Each constraint has the form
//   A[0]*D[0] + A[1]*D[1] + A[2]*D[2] <= 1
// where A[0] >= 0, A[1] >= 0, and A[2] >= 0.

namespace gte
{

template <typename Real>
class ContEllipsoid3MinCR
{
public:
    void operator()(int numPoints, Vector3<Real> const* points,
        Vector3<Real> const& C, Matrix3x3<Real> const& R, Real D[3]);

private:
    void FindEdgeMax(std::vector<Vector3<Real>>& A, int& plane0,
        int& plane1, Real D[3]);

    void FindFacetMax(std::vector<Vector3<Real>>& A, int& plane0,
        Real D[3]);

    void MaxProduct(std::vector<Vector3<Real>>& A, Real D[3]);
};

#include "GteContEllipsoid3MinCR.inl"

}
