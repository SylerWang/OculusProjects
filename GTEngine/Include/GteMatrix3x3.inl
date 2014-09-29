// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::~Matrix3x3()
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::Matrix3x3()
{
    // Uninitialized.
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::Matrix3x3(Matrix3x3 const& mat)
    :
    Matrix<3,3,Real>(mat)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::Matrix3x3(Matrix<3,3,Real> const& mat)
    :
    Matrix<3,3,Real>(mat)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::Matrix3x3(
    Real m00, Real m01, Real m02,
    Real m10, Real m11, Real m12,
    Real m20, Real m21, Real m22)
{
    this->mTable(0, 0) = m00;
    this->mTable(0, 1) = m01;
    this->mTable(0, 2) = m02;
    this->mTable(1, 0) = m10;
    this->mTable(1, 1) = m11;
    this->mTable(1, 2) = m12;
    this->mTable(2, 0) = m20;
    this->mTable(2, 1) = m21;
    this->mTable(2, 2) = m22;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::Matrix3x3(Vector3<Real> const& v0, Vector3<Real> const& v1,
    Vector3<Real> const& v2, bool columns)
{
    if (columns)
    {
        this->SetCol(0, v0);
        this->SetCol(1, v1);
        this->SetCol(2, v2);
    }
    else
    {
        this->SetRow(0, v0);
        this->SetRow(1, v1);
        this->SetRow(2, v2);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::Matrix3x3(Vector3<Real> const* v, bool columns)
{
    if (columns)
    {
        for (int i = 0; i < 3; ++i)
        {
            this->SetCol(i, v[i]);
        }
    }
    else
    {
        for (int i = 0; i < 3; ++i)
        {
            this->SetRow(i, v[i]);
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>::Matrix3x3(Real m00, Real m11, Real m22)
{
    MakeDiagonal(m00, m11, m22);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix3x3<Real>::MakeZero()
{
    MakeDiagonal((Real)0, (Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix3x3<Real>::MakeIdentity()
{
    MakeDiagonal((Real)1, (Real)1, (Real)1);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix3x3<Real>::MakeDiagonal(Real m00, Real m11, Real m22)
{
    this->mTable(0, 0) = m00;
    this->mTable(0, 1) = (Real)0;
    this->mTable(0, 2) = (Real)0;
    this->mTable(1, 0) = (Real)0;
    this->mTable(1, 1) = m11;
    this->mTable(1, 2) = (Real)0;
    this->mTable(2, 0) = (Real)0;
    this->mTable(2, 1) = (Real)0;
    this->mTable(2, 2) = m22;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>& Matrix3x3<Real>::operator=(Matrix3x3 const& mat)
{
    Matrix<3,3,Real>::operator=(mat);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real>& Matrix3x3<Real>::operator=(Matrix<3,3,Real> const& mat)
{
    Matrix<3,3,Real>::operator=(mat);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real> Matrix3x3<Real>::Zero()
{
    return Matrix3x3((Real)0, (Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real> Matrix3x3<Real>::Identity()
{
    return Matrix3x3((Real)1, (Real)1, (Real)1);
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real> Inverse(Matrix3x3<Real> const& M, bool* reportInvertibility)
{
    Matrix3x3<Real> inverse;
    bool invertible;
    Real c00 = M(1,1)*M(2,2) - M(1,2)*M(2,1);
    Real c10 = M(1,2)*M(2,0) - M(1,0)*M(2,2);
    Real c20 = M(1,0)*M(2,1) - M(1,1)*M(2,0);
    Real det = M(0,0)*c00 + M(0,1)*c10 + M(0,2)*c20;
    if (det != (Real)0)
    {
        Real invDet = ((Real)1)/det;
        inverse = Matrix3x3<Real>
        (
            c00*invDet,
            (M(0,2)*M(2,1) - M(0,1)*M(2,2))*invDet,
            (M(0,1)*M(1,2) - M(0,2)*M(1,1))*invDet,
            c10*invDet,
            (M(0,0)*M(2,2) - M(0,2)*M(2,0))*invDet,
            (M(0,2)*M(1,0) - M(0,0)*M(1,2))*invDet,
            c20*invDet,
            (M(0,1)*M(2,0) - M(0,0)*M(2,1))*invDet,
            (M(0,0)*M(1,1) - M(0,1)*M(1,0))*invDet
        );
        invertible = true;
    }
    else
    {
        inverse = Matrix3x3<Real>::Zero();
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
Matrix3x3<Real> Adjoint(Matrix3x3<Real> const& M)
{
    return Matrix3x3<Real>
    (
        M(1,1)*M(2,2) - M(1,2)*M(2,1),
        M(0,2)*M(2,1) - M(0,1)*M(2,2),
        M(0,1)*M(1,2) - M(0,2)*M(1,1),
        M(1,2)*M(2,0) - M(1,0)*M(2,2),
        M(0,0)*M(2,2) - M(0,2)*M(2,0),
        M(0,2)*M(1,0) - M(0,0)*M(1,2),
        M(1,0)*M(2,1) - M(1,1)*M(2,0),
        M(0,1)*M(2,0) - M(0,0)*M(2,1),
        M(0,0)*M(1,1) - M(0,1)*M(1,0)
    );
}
//----------------------------------------------------------------------------
template <typename Real>
Real Determinant(Matrix3x3<Real> const& M)
{
    Real c00 = M(1,1)*M(2,2) - M(1,2)*M(2,1);
    Real c10 = M(1,2)*M(2,0) - M(1,0)*M(2,2);
    Real c20 = M(1,0)*M(2,1) - M(1,1)*M(2,0);
    Real det = M(0,0)*c00 + M(0,1)*c10 + M(0,2)*c20;
    return det;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Trace(Matrix3x3<Real> const& M)
{
    Real trace = M(0,0) + M(1,1) + M(2,2);
    return trace;
}
//----------------------------------------------------------------------------
