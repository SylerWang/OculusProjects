// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

// WARNING.  The implementation allows you to transform the inputs (x,y) to
// the unit square and perform the interpolation in that space.  The idea is
// to keep the floating-point numbers to order 1 for numerical stability of
// the algorithm.  The classical thin-plate spline algorithm does not include
// this transformation.  The interpolation is invariant to translations and
// rotations of (x,y) but not to scaling.

#include "GteGMatrix.h"
#include <algorithm>
#include <cmath>
#include <limits>

namespace gte
{

template <typename Real>
class IntpThinPlateSpline2
{
public:
    // Construction.  Data points are (x,y,f(x,y)).  The smoothing parameter
    // must be nonnegative.
    IntpThinPlateSpline2(int numPoints, Real const* X, Real const* Y,
        Real const* F, Real smooth, bool transformToUnitSquare);

    // Check this after the constructor call to see whether the thin plate
    // spline coefficients were successfully computed.  If so, then calls to
    // operator()(Real,Real) will work properly.
    inline bool IsInitialized() const;

    // Evaluate the interpolator.  If IsInitialized() returns 'false', the
    // operator will return std::numeric_limits<Real>::max().
    Real operator()(Real x, Real y) const;

    // Compute the functional value a^T*M*a when lambda is zero or
    // lambda*w^T*(M+lambda*I)*w when lambda is positive.  See the thin plate
    // splines PDF for a description of these quantities.
    Real ComputeFunctional() const;

private:
    // Kernel(t) = t^2 * log(t^2)
    static Real Kernel(Real t);

    // Input data.
    int mNumPoints;
    std::vector<Real> mX;
    std::vector<Real> mY;
    Real mSmooth;

    // Thin plate spline coefficients.  The A[] coefficients are associated
    // with the Green's functions G(x,y,*) and the B[] coefficients are
    // associated with the affine term B[0] + B[1]*x + B[2]*y.
    std::vector<Real> mA;  // mNumPoints elements
    Real mB[3];

    // Extent of input data.
    Real mXMin, mXMax, mXInvRange;
    Real mYMin, mYMax, mYInvRange;

    bool mInitialized;
};

#include "GteIntpThinPlateSpline2.inl"

}
