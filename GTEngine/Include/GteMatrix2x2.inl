// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::~Matrix2x2()
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2()
{
    // Uninitialized.
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2(Matrix2x2 const& mat)
    :
    Matrix<2,2,Real>(mat)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2(Matrix<2,2,Real> const& mat)
    :
    Matrix<2,2,Real>(mat)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2(Real m00, Real m01, Real m10, Real m11)
{
    this->mTable(0, 0) = m00;
    this->mTable(0, 1) = m01;
    this->mTable(1, 0) = m10;
    this->mTable(1, 1) = m11;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2(Vector2<Real> const& v0, Vector2<Real> const& v1,
    bool columns)
{
    if (columns)
    {
        this->SetCol(0, v0);
        this->SetCol(1, v1);
    }
    else
    {
        this->SetRow(0, v0);
        this->SetRow(1, v1);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2(Vector2<Real> const* v, bool columns)
{
    if (columns)
    {
        for (int i = 0; i < 2; ++i)
        {
            this->SetCol(i, v[i]);
        }
    }
    else
    {
        for (int i = 0; i < 2; ++i)
        {
            this->SetRow(i, v[i]);
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2(Real m00, Real m11)
{
    MakeDiagonal(m00, m11);
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>::Matrix2x2(Real angle)
{
    MakeRotation(angle);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix2x2<Real>::MakeZero()
{
    MakeDiagonal((Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix2x2<Real>::MakeIdentity()
{
    MakeDiagonal((Real)1, (Real)1);
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix2x2<Real>::MakeDiagonal(Real m00, Real m11)
{
    this->mTable(0, 0) = m00;
    this->mTable(0, 1) = (Real)0;
    this->mTable(1, 0) = (Real)0;
    this->mTable(1, 1) = m11;
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix2x2<Real>::MakeRotation(Real angle)
{
    Real cs = cos(angle);
    Real sn = sin(angle);
#if defined(GTE_USE_MAT_VEC)
    this->mTable(0, 0) = cs;
    this->mTable(0, 1) = -sn;
    this->mTable(1, 0) = sn;
    this->mTable(1, 1) = cs;
#else
    this->mTable(0,0) =  cs;
    this->mTable(0,1) =  sn;
    this->mTable(1,0) = -sn;
    this->mTable(1,1) =  cs;
#endif
}
//----------------------------------------------------------------------------
template <typename Real>
void Matrix2x2<Real>::Get(Real& angle) const
{
#if defined(GTE_USE_MAT_VEC)
    angle = atan2(this->mTable(1, 0), this->mTable(0, 0));
#else
    angle = atan2(this->mTable(0,1), this->mTable(0,0));
#endif
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>& Matrix2x2<Real>::operator=(Matrix2x2 const& mat)
{
    Matrix<2,2,Real>::operator=(mat);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real>& Matrix2x2<Real>::operator=(Matrix<2,2,Real> const& mat)
{
    Matrix<2,2,Real>::operator=(mat);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real> Matrix2x2<Real>::Zero()
{
    return Matrix2x2((Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real> Matrix2x2<Real>::Identity()
{
    return Matrix2x2((Real)1, (Real)1);
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix2x2<Real> Inverse(Matrix2x2<Real> const& M, bool* reportInvertibility)
{
    Matrix2x2<Real> inverse;
    bool invertible;
    Real det = M(0,0)*M(1,1) - M(0,1)*M(1,0);
    if (det != (Real)0)
    {
        Real invDet = ((Real)1)/det;
        inverse = Matrix2x2<Real>
        (
             M(1,1)*invDet, -M(0,1)*invDet,
            -M(1,0)*invDet,  M(0,0)*invDet
        );
        invertible = true;
    }
    else
    {
        inverse = Matrix2x2<Real>::Zero();
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
Matrix2x2<Real> Adjoint(Matrix2x2<Real> const& M)
{
    return Matrix2x2<Real>(
        M(1,1), -M(0,1),
       -M(1,0),  M(0,0));
}
//----------------------------------------------------------------------------
template <typename Real>
Real Determinant(Matrix2x2<Real> const& M)
{
    Real det = M(0,0)*M(1,1) - M(0,1)*M(1,0);
    return det;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Trace(Matrix2x2<Real> const& M)
{
    Real trace = M(0,0) + M(1,1);
    return trace;
}
//----------------------------------------------------------------------------
