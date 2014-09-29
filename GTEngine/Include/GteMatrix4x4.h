// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteMatrix.h"
#include "GteVector4.h"
#include "GteMatrix3x3.h"

namespace gte
{

template <typename Real>
class Matrix4x4 : public Matrix<4,4,Real>
{
public:
    // Construction and destruction.  The destructor hides the base-class
    // destructor, but the latter has no side effects.  Matrix4x4 is designed
    // to provide specialized constructors and geometric operations.  The
    // default constructor does not initialize its data.
    ~Matrix4x4();
    Matrix4x4();
    Matrix4x4(Matrix4x4 const& mat);
    Matrix4x4(Matrix<4,4,Real> const& mat);
    Matrix4x4(
        Real m00, Real m01, Real m02, Real m03,
        Real m10, Real m11, Real m12, Real m13,
        Real m20, Real m21, Real m22, Real m23,
        Real m30, Real m31, Real m32, Real m33);

    // Create matrices based on vector input.
    Matrix4x4(Vector4<Real> const& v0, Vector4<Real> const& v1,
        Vector4<Real> const& v2, Vector4<Real> const& v3, bool columns);
    Matrix4x4(Vector4<Real> const* v, bool columns);

    // Create a diagonal matrix.  Pass zeros to create the zero matrix.  Pass
    // ones to create the identity matrix.
    Matrix4x4(Real m00, Real m11, Real m22, Real m33);

    // Create special matrices.
    void MakeZero();
    void MakeIdentity();
    void MakeDiagonal(Real m00, Real m11, Real m22, Real m33);

    // Assignment.
    Matrix4x4& operator=(Matrix4x4 const& mat);
    Matrix4x4& operator=(Matrix<4,4,Real> const& mat);

    // Special matrices.
    static Matrix4x4 Zero();
    static Matrix4x4 Identity();
};

// Geometric operations.
template <typename Real>
Matrix4x4<Real> Inverse(Matrix4x4<Real> const& M,
    bool* reportInvertibility = nullptr);

template <typename Real>
Matrix4x4<Real> Adjoint(Matrix4x4<Real> const& M);

template <typename Real>
Real Determinant(Matrix4x4<Real> const& M);

template <typename Real>
Real Trace(Matrix4x4<Real> const& M);
    
template <typename Real>
Matrix3x3<Real> GetMatrix3x3(Matrix4x4<Real> const& M);

#include "GteMatrix4x4.inl"

}
