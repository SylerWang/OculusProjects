// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteMatrix.h"
#include "GteVector2.h"

namespace gte
{

template <typename Real>
class Matrix2x2 : public Matrix<2,2,Real>
{
public:
    // Construction and destruction.  The destructor hides the base-class
    // destructor, but the latter has no side effects.  Matrix2x2 is designed
    // to provide specialized constructors and geometric operations.  The
    // default constructor does not initialize its data.
    ~Matrix2x2();
    Matrix2x2();
    Matrix2x2(Matrix2x2 const& mat);
    Matrix2x2(Matrix<2,2,Real> const& mat);
    Matrix2x2(Real m00, Real m01, Real m10, Real m11);

    // Create matrices based on vector input.
    Matrix2x2(Vector2<Real> const& v0, Vector2<Real> const& v1, bool columns);
    Matrix2x2(Vector2<Real> const* v, bool columns);

    // Create a diagonal matrix.  Pass zeros to create the zero matrix.  Pass
    // ones to create the identity matrix.
    Matrix2x2(Real m00, Real m11);

    // Create a rotation matrix from an angle (in radians).  The matrix is
    // [GTE_USE_MAT_VEC]
    //   R(t) = {{c,-s},{s,c}}
    // [GTE_USE_VEC_MAT]
    //   R(t) = {{c,s},{-s,c}}
    // where c = cos(t), s = sin(t), and the inner-brace pairs are rows of the
    // matrix.
    Matrix2x2(Real angle);

    // Create special matrices.
    void MakeZero();
    void MakeIdentity();
    void MakeDiagonal(Real m00, Real m11);
    void MakeRotation(Real angle);

    // Get the angle (radians) from a rotation matrix.  The caller is
    // responsible for ensuring the matrix is a rotation.
    void Get(Real& angle) const;

    // Assignment.
    Matrix2x2& operator=(Matrix2x2 const& mat);
    Matrix2x2& operator=(Matrix<2,2,Real> const& mat);

    // Special matrices.
    static Matrix2x2 Zero();
    static Matrix2x2 Identity();
};

// Geometric operations.
template <typename Real>
Matrix2x2<Real> Inverse(Matrix2x2<Real> const& M,
    bool* reportInvertibility = nullptr);

template <typename Real>
Matrix2x2<Real> Adjoint(Matrix2x2<Real> const& M);

template <typename Real>
Real Determinant(Matrix2x2<Real> const& M);

template <typename Real>
Real Trace(Matrix2x2<Real> const& M);

#include "GteMatrix2x2.inl"

}
