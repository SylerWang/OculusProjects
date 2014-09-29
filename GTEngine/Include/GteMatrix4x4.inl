// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::~Matrix4x4()
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::Matrix4x4()
{
    // Uninitialized.
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::Matrix4x4(Matrix4x4 const& mat)
    :
    Matrix<4,4,Real>(mat)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::Matrix4x4(Matrix<4,4,Real> const& mat)
    :
    Matrix<4,4,Real>(mat)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::Matrix4x4(
    Real m00, Real m01, Real m02, Real m03,
    Real m10, Real m11, Real m12, Real m13,
    Real m20, Real m21, Real m22, Real m23,
    Real m30, Real m31, Real m32, Real m33)
{
    this->mTable(0, 0) = m00;
    this->mTable(0, 1) = m01;
    this->mTable(0, 2) = m02;
    this->mTable(0, 3) = m03;
    this->mTable(1, 0) = m10;
    this->mTable(1, 1) = m11;
    this->mTable(1, 2) = m12;
    this->mTable(1, 3) = m13;
    this->mTable(2, 0) = m20;
    this->mTable(2, 1) = m21;
    this->mTable(2, 2) = m22;
    this->mTable(2, 3) = m23;
    this->mTable(3, 0) = m30;
    this->mTable(3, 1) = m31;
    this->mTable(3, 2) = m32;
    this->mTable(3, 3) = m33;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::Matrix4x4(Vector4<Real> const& v0, Vector4<Real> const& v1,
    Vector4<Real> const& v2, Vector4<Real> const& v3, bool columns)
{
    if (columns)
    {
        this->SetCol(0, v0);
        this->SetCol(1, v1);
        this->SetCol(2, v2);
        this->SetCol(3, v3);
    }
    else
    {
        this->SetRow(0, v0);
        this->SetRow(1, v1);
        this->SetRow(2, v2);
        this->SetRow(3, v3);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::Matrix4x4(Vector4<Real> const* v, bool columns)
{
    if (columns)
    {
        for (int i = 0; i < 4; ++i)
        {
            this->SetCol(i, v[i]);
        }
    }
    else
    {
        for (int i = 0; i < 4; ++i)
        {
            this->SetRow(i, v[i]);
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>::Matrix4x4(Real m00, Real m11, Real m22, Real m33)
{
    MakeDiagonal(m00, m11, m22, m33);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix4x4<Real>::MakeZero()
{
    MakeDiagonal((Real)0, (Real)0, (Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix4x4<Real>::MakeIdentity()
{
    MakeDiagonal((Real)1, (Real)1, (Real)1, (Real)1);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix4x4<Real>::MakeDiagonal(Real m00, Real m11, Real m22, Real m33)
{
    this->mTable(0, 0) = m00;
    this->mTable(0, 1) = (Real)0;
    this->mTable(0, 2) = (Real)0;
    this->mTable(0, 3) = (Real)0;
    this->mTable(1, 0) = (Real)0;
    this->mTable(1, 1) = m11;
    this->mTable(1, 2) = (Real)0;
    this->mTable(1, 3) = (Real)0;
    this->mTable(2, 0) = (Real)0;
    this->mTable(2, 1) = (Real)0;
    this->mTable(2, 2) = m22;
    this->mTable(2, 3) = (Real)0;
    this->mTable(3, 0) = (Real)0;
    this->mTable(3, 1) = (Real)0;
    this->mTable(3, 2) = (Real)0;
    this->mTable(3, 3) = m33;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>& Matrix4x4<Real>::operator=(Matrix4x4 const& mat)
{
    Matrix<4,4,Real>::operator=(mat);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real>& Matrix4x4<Real>::operator=(Matrix<4,4,Real> const& mat)
{
    Matrix<4,4,Real>::operator=(mat);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real> Matrix4x4<Real>::Zero()
{
    return Matrix4x4((Real)0, (Real)0, (Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real> Matrix4x4<Real>::Identity()
{
    return Matrix4x4((Real)1, (Real)1, (Real)1, (Real)1);
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real> Inverse(Matrix4x4<Real> const& M, bool* reportInvertibility)
{
    Matrix4x4<Real> inverse;
    bool invertible;
    Real a0 = M(0,0)*M(1,1) - M(0,1)*M(1,0);
    Real a1 = M(0,0)*M(1,2) - M(0,2)*M(1,0);
    Real a2 = M(0,0)*M(1,3) - M(0,3)*M(1,0);
    Real a3 = M(0,1)*M(1,2) - M(0,2)*M(1,1);
    Real a4 = M(0,1)*M(1,3) - M(0,3)*M(1,1);
    Real a5 = M(0,2)*M(1,3) - M(0,3)*M(1,2);
    Real b0 = M(2,0)*M(3,1) - M(2,1)*M(3,0);
    Real b1 = M(2,0)*M(3,2) - M(2,2)*M(3,0);
    Real b2 = M(2,0)*M(3,3) - M(2,3)*M(3,0);
    Real b3 = M(2,1)*M(3,2) - M(2,2)*M(3,1);
    Real b4 = M(2,1)*M(3,3) - M(2,3)*M(3,1);
    Real b5 = M(2,2)*M(3,3) - M(2,3)*M(3,2);
    Real det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    if (det != (Real)0)
    {
        Real invDet = ((Real)1)/det;
        inverse = Matrix4x4<Real>
        (
            (+ M(1,1)*b5 - M(1,2)*b4 + M(1,3)*b3)*invDet,
            (- M(0,1)*b5 + M(0,2)*b4 - M(0,3)*b3)*invDet,
            (+ M(3,1)*a5 - M(3,2)*a4 + M(3,3)*a3)*invDet,
            (- M(2,1)*a5 + M(2,2)*a4 - M(2,3)*a3)*invDet,
            (- M(1,0)*b5 + M(1,2)*b2 - M(1,3)*b1)*invDet,
            (+ M(0,0)*b5 - M(0,2)*b2 + M(0,3)*b1)*invDet,
            (- M(3,0)*a5 + M(3,2)*a2 - M(3,3)*a1)*invDet,
            (+ M(2,0)*a5 - M(2,2)*a2 + M(2,3)*a1)*invDet,
            (+ M(1,0)*b4 - M(1,1)*b2 + M(1,3)*b0)*invDet,
            (- M(0,0)*b4 + M(0,1)*b2 - M(0,3)*b0)*invDet,
            (+ M(3,0)*a4 - M(3,1)*a2 + M(3,3)*a0)*invDet,
            (- M(2,0)*a4 + M(2,1)*a2 - M(2,3)*a0)*invDet,
            (- M(1,0)*b3 + M(1,1)*b1 - M(1,2)*b0)*invDet,
            (+ M(0,0)*b3 - M(0,1)*b1 + M(0,2)*b0)*invDet,
            (- M(3,0)*a3 + M(3,1)*a1 - M(3,2)*a0)*invDet,
            (+ M(2,0)*a3 - M(2,1)*a1 + M(2,2)*a0)*invDet
        );
        invertible = true;
    }
    else
    {
        inverse = Matrix4x4<Real>::Zero();
        invertible = false;
    }

    if (reportInvertibility)
    {
        *reportInvertibility = invertible;
    }
    return inverse;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix4x4<Real> Adjoint(Matrix4x4<Real> const& M)
{
    Real a0 = M(0,0)*M(1,1) - M(0,1)*M(1,0);
    Real a1 = M(0,0)*M(1,2) - M(0,2)*M(1,0);
    Real a2 = M(0,0)*M(1,3) - M(0,3)*M(1,0);
    Real a3 = M(0,1)*M(1,2) - M(0,2)*M(1,1);
    Real a4 = M(0,1)*M(1,3) - M(0,3)*M(1,1);
    Real a5 = M(0,2)*M(1,3) - M(0,3)*M(1,2);
    Real b0 = M(2,0)*M(3,1) - M(2,1)*M(3,0);
    Real b1 = M(2,0)*M(3,2) - M(2,2)*M(3,0);
    Real b2 = M(2,0)*M(3,3) - M(2,3)*M(3,0);
    Real b3 = M(2,1)*M(3,2) - M(2,2)*M(3,1);
    Real b4 = M(2,1)*M(3,3) - M(2,3)*M(3,1);
    Real b5 = M(2,2)*M(3,3) - M(2,3)*M(3,2);

    return Matrix4x4<Real>
    (
        + M(1,1)*b5 - M(1,2)*b4 + M(1,3)*b3,
        - M(0,1)*b5 + M(0,2)*b4 - M(0,3)*b3,
        + M(3,1)*a5 - M(3,2)*a4 + M(3,3)*a3,
        - M(2,1)*a5 + M(2,2)*a4 - M(2,3)*a3,
        - M(1,0)*b5 + M(1,2)*b2 - M(1,3)*b1,
        + M(0,0)*b5 - M(0,2)*b2 + M(0,3)*b1,
        - M(3,0)*a5 + M(3,2)*a2 - M(3,3)*a1,
        + M(2,0)*a5 - M(2,2)*a2 + M(2,3)*a1,
        + M(1,0)*b4 - M(1,1)*b2 + M(1,3)*b0,
        - M(0,0)*b4 + M(0,1)*b2 - M(0,3)*b0,
        + M(3,0)*a4 - M(3,1)*a2 + M(3,3)*a0,
        - M(2,0)*a4 + M(2,1)*a2 - M(2,3)*a0,
        - M(1,0)*b3 + M(1,1)*b1 - M(1,2)*b0,
        + M(0,0)*b3 - M(0,1)*b1 + M(0,2)*b0,
        - M(3,0)*a3 + M(3,1)*a1 - M(3,2)*a0,
        + M(2,0)*a3 - M(2,1)*a1 + M(2,2)*a0
    );
}
//----------------------------------------------------------------------------
template <typename Real>
Real Determinant(Matrix4x4<Real> const& M)
{
    Real a0 = M(0,0)*M(1,1) - M(0,1)*M(1,0);
    Real a1 = M(0,0)*M(1,2) - M(0,2)*M(1,0);
    Real a2 = M(0,0)*M(1,3) - M(0,3)*M(1,0);
    Real a3 = M(0,1)*M(1,2) - M(0,2)*M(1,1);
    Real a4 = M(0,1)*M(1,3) - M(0,3)*M(1,1);
    Real a5 = M(0,2)*M(1,3) - M(0,3)*M(1,2);
    Real b0 = M(2,0)*M(3,1) - M(2,1)*M(3,0);
    Real b1 = M(2,0)*M(3,2) - M(2,2)*M(3,0);
    Real b2 = M(2,0)*M(3,3) - M(2,3)*M(3,0);
    Real b3 = M(2,1)*M(3,2) - M(2,2)*M(3,1);
    Real b4 = M(2,1)*M(3,3) - M(2,3)*M(3,1);
    Real b5 = M(2,2)*M(3,3) - M(2,3)*M(3,2);
    Real det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
    return det;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Trace(Matrix4x4<Real> const& M)
{
    Real trace = M(0,0) + M(1,1) + M(2,2) + M(3,3);
    return trace;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real> GetMatrix3x3(Matrix4x4<Real> const& M)
{
    return Matrix3x3<Real>(M(0,0), M(0,1), M(0,2),
                           M(1,0), M(1,1), M(1,2),
                           M(2,0), M(2,1), M(2,2));
}
//----------------------------------------------------------------------------
