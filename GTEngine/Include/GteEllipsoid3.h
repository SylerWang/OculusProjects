// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteMatrix3x3.h"
#include "GteSymmetricEigensolver.h"

namespace gte
{

// An ellipsoid has center K; axis directions U[0], U[1], and U[2], all
// unit-length vectors; and extents e[0], e[1], and e[2], all positive
// numbers.  A point X = K+y[0]*U[0]+y[1]*U[1]+y[2]*U[2] is on the
// ellipsoid whenever (y[0]/e[0])^2+(y[1]/e[1])^2+(y[2]/e[2])^2 = 1.  An
// algebraic representation for the ellipsoid is
//   1 = (X-K)^T * (U[0]*U[0]^T/e[0]^2 + U[1]*U[1]^T/e[1]^2 +
//                  U[2]*U[2]^T/e[2]^2) * (X-K)
//     = (X-K)^T * M * (X-K)
// where the superscript T denotes transpose.  Observe that U[i]*U[i]^T is a
// matrix, not a scalar dot product.  The matrix M is symmetric.  The
// ellipsoid is also represented by a quadratic equation
//   0 = a0 + a1*x[0] + a2*x[1] + a3*x[2] + a4*x[0]^2 + a5*x[0]*x[1] +
//       a6*x[0]*x[2] + a7*x[1]^2 + a8*x[1]*x[2] + a9*x[2]^2
//     = a0 + [a1 a2 a3]*X + X^T*[a4   a5/2 a6/2]*X
//                               [a5/2 a7   a8/2]
//                               [a6/2 a8/2 a9  ]
//     = C + B^T*X + X^T*A*X
// where X = (x[0],x[1],x[2]).  This equation can be factored to the form
// (X-K)^T*M*(X-K) = 1, where K = -A^{-1}*B/2, M = A/(B^T*A^{-1}*B/4-C).  To
// be an ellipsoid, M must have all positive eigenvalues.

template <typename Real>
class Ellipsoid3 : public GeometricPrimitive<Ellipsoid3<Real>>
{
public:

    // Construction and destruction.  The default constructor sets the center
    // to (0,0,0), the axes to (1,0,0), (0,1,0), and (0,0,1), and all extents
    // to 1.
    Ellipsoid3();
    Ellipsoid3(Vector3<Real> const& inCenter, Vector3<Real> const inAxis[3],
        Vector3<Real> const& inExtent);
    Ellipsoid3(Vector3<Real> const& inCenter, Vector3<Real> const& axis0,
        Vector3<Real> const& axis1, Vector3<Real> const& axis2, Real extent0,
        Real extent1, Real extent2);

    // Compute M = sum_{i=0}^2 U[i]*U[i]^T/e[i]^2.
    void GetM(Matrix3x3<Real>& M) const;

    // Compute M^{-1} = sum_{i=0}^2 U[i]*U[i]^T*e[i]^2.
    void GetMInverse(Matrix3x3<Real>& MInverse) const;

    // Construct the coefficients in the quadratic equation that represents
    // the ellipsoid.  'coeff' stores a0 through a9.  'A', 'B', and 'C' are as
    // described in the comments before the constructors.
    void ToCoefficients(Real coeff[10]) const;
    void ToCoefficients(Matrix3x3<Real>& A, Vector3<Real>& B, Real& C) const;

    // Construct C, U[i], and e[i] from the equation.  The return value is
    // 'true' if and only if the input coefficients represent an ellipsoid.
    // If the function returns 'false', the ellipsoid data members are
    // undefined.  'coeff' stores a0 through a9.  'A', 'B', and 'C' are as
    // described in the comments before the constructors.
    bool FromCoefficients(Real const coeff[10]);
    bool FromCoefficients(Matrix3x3<Real> const& A,Vector3<Real> const& B,
        Real C);

    // Public member access.
    Vector3<Real> center;
    Vector3<Real> axis[3];
    Vector3<Real> extent;

private:
    static void Convert(Real const coeff[10], Matrix3x3<Real>& A,
        Vector3<Real>& B, Real& C);

    static void Convert(Matrix3x3<Real> const& A, Vector3<Real> const& B,
        Real C, Real coeff[10]);

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Ellipsoid3 const& ellipsoid) const;
    bool IsLessThan(Ellipsoid3 const& ellipsoid) const;
};

#include "GteEllipsoid3.inl"

}
