// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteMatrix2x2.h"
#include "GteSymmetricEigensolver.h"

namespace gte
{

// An ellipse has center K; axis directions U[0] and U[1], both unit-length
// vectors; and extents e[0] and e[1], both positive numbers.  A point
// X = K+y[0]*U[0]+y[1]*U[1] is on the ellipse whenever
// (y[0]/e[0])^2+(y[1]/e[1])^2 = 1.  An algebraic representation for the
// ellipse is
//   1 = (X-K)^T * (U[0]*U[0]^T/e[0]^2 + U[1]*U[1]^T/e[1]^2) * (X-K)
//     = (X-K)^T * M * (X-K)
// where the superscript T denotes transpose.  Observe that U[i]*U[i]^T is a
// matrix, not a scalar dot product.  The matrix M is symmetric.  The ellipse
// is also represented by a quadratic equation
//   0 = a0 + a1*x[0] + a2*x[1] + a3*x[0]^2 + a4*x[0]*x[1] + a5*x[1]^2
//     = a0 + [a1 a2]*X + X^T*[a3   a4/2]*X
//                            [a4/2 a5  ]
//     = C + B^T*X + X^T*A*X
// where X = (x[0],x[1]).  This equation can be factored to the form
// (X-K)^T*M*(X-K) = 1, where K = -A^{-1}*B/2, M = A/(B^T*A^{-1}*B/4-C).  To
// be an ellipse, M must have all positive eigenvalues.

template <typename Real>
class Ellipse2 : public GeometricPrimitive<Ellipse2<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the center
    // to (0,0), the axes to (1,0) and (0,1), and both extents to 1.
    Ellipse2();
    Ellipse2(Vector2<Real> const& inCenter, Vector2<Real> const inAxis[2],
        Vector2<Real> const& inExtent);
    Ellipse2(Vector2<Real> const& inCenter, Vector2<Real> const& axis0,
        Vector2<Real> const& axis1, Real extent0, Real extent1);

    // Compute M = sum_{i=0}^1 U[i]*U[i]^T/e[i]^2.
    void GetM(Matrix2x2<Real>& M) const;

    // Compute M^{-1} = sum_{i=0}^1 U[i]*U[i]^T*e[i]^2.
    void GetMInverse(Matrix2x2<Real>& MInverse) const;

    // Construct the coefficients in the quadratic equation that represents
    // the ellipse.  'coeff' stores a0 through a5.  'A', 'B', and 'C' are as
    // described in the comments before the constructors.
    void ToCoefficients(Real coeff[6]) const;
    void ToCoefficients(Matrix2x2<Real>& A, Vector2<Real>& B, Real& C) const;

    // Construct C, U[i], and e[i] from the quadratic equation.  The return
    // value is 'true' if and only if the input coefficients represent an
    // ellipse.  If the function returns 'false', the ellipse data members
    // are undefined.  'coeff' stores a0 through a5.  'A', 'B', and 'C' are as
    // described in the comments before the constructors.
    bool FromCoefficients(Real const coeff[6]);
    bool FromCoefficients(Matrix2x2<Real> const& A, Vector2<Real> const& B,
        Real C);

    // Public member access.
    Vector2<Real> center;
    Vector2<Real> axis[2];
    Vector2<Real> extent;

private:
    static void Convert(Real const coeff[6], Matrix2x2<Real>& A,
        Vector2<Real>& B, Real& C);

    static void Convert(Matrix2x2<Real> const& A, Vector2<Real> const& B,
        Real C, Real coeff[6]);

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Ellipse2 const& ellipse) const;
    bool IsLessThan(Ellipse2 const& ellipse) const;
};

#include "GteEllipse2.inl"

}
