// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

// The ellipse in general form is  X^t A X + B^t X + C = 0 where A is a
// positive definite 2x2 matrix, B is a 2x1 vector, C is a scalar, and X is
// a 2x1 vector X.  Completing the square, (X-U)^t A (X-U) = U^t A U - C
// where U = -0.5 A^{-1} B.  Define M = A/(U^t A U - C).  The ellipse is
// (X-U)^t M (X-U) = 1.  Factor M = R^t D R where R is orthonormal and D is
// diagonal with positive diagonal terms.  The ellipse in factored form is
// (X-U)^t R^t D^t R (X-U) = 1.
//
// Find the least squares fit of a set of N points P[0] through P[N-1].
// The return value is the least-squares energy function at (U,R,D).

#include "GteConstants.h"
#include "GteContOrientedBox2.h"
#include "GteDistPoint2Ellipse2.h"
#include "GteMinimizeN.h"

namespace gte
{

template <typename Real>
class ApprEllipse2
{
public:
    Real operator()(int numPoints, Vector2<Real> const* points,
        Vector2<Real>& center, Matrix2x2<Real>& rotate, Real diagonal[2]);

private:
    static Real Energy(int numPoints, Vector2<Real> const* points,
        Real const* input);
};

#include "GteApprEllipse2.inl"

}
