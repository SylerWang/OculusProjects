// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteMatrix.h"
#include "GteVector3.h"

namespace gte
{

template <typename Real>
class Matrix3x3 : public Matrix<3,3,Real>
{
public:
    // Construction and destruction.  The destructor hides the base-class
    // destructor, but the latter has no side effects.  Matrix3x3 is designed
    // to provide specialized constructors and geometric operations.  The
    // default constructor does not initialize its data.
    ~Matrix3x3();
    Matrix3x3();
    Matrix3x3(Matrix3x3 const& mat);
    Matrix3x3(Matrix<3,3,Real> const& mat);
    Matrix3x3(
        Real m00, Real m01, Real m02,
        Real m10, Real m11, Real m12,
        Real m20, Real m21, Real m22);

    // Create matrices based on vector input.
    Matrix3x3(Vector3<Real> const& v0, Vector3<Real> const& v1,
        Vector3<Real> const& v2, bool columns);
    Matrix3x3(Vector3<Real> const* v, bool columns);

    // Create a diagonal matrix.  Pass zeros to create the zero matrix.  Pass
    // ones to create the identity matrix.
    Matrix3x3(Real m00, Real m11, Real m22);

    // Create special matrices.
    void MakeZero();
    void MakeIdentity();
    void MakeDiagonal(Real m00, Real m11, Real m22);

    // Assignment.
    Matrix3x3& operator=(Matrix3x3 const& mat);
    Matrix3x3& operator=(Matrix<3,3,Real> const& mat);

    // Special matrices.
    static Matrix3x3 Zero();
    static Matrix3x3 Identity();
};

// Geometric operations.
template <typename Real>
Matrix3x3<Real> Inverse(Matrix3x3<Real> const& M,
    bool* reportInvertibility = nullptr);

template <typename Real>
Matrix3x3<Real> Adjoint(Matrix3x3<Real> const& M);

template <typename Real>
Real Determinant(Matrix3x3<Real> const& M);

template <typename Real>
Real Trace(Matrix3x3<Real> const& M);

#include "GteMatrix3x3.inl"

}
