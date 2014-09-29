// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
void Matrix<NumRows, NumCols, Real>::MakeZero()
{
    Real const zero = (Real)0;
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        mTable[i] = zero;
    }
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real const& Matrix<NumRows, NumCols, Real>::operator()(int r, int c) const
{
    return mTable(r, c);
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real& Matrix<NumRows, NumCols, Real>::operator()(int r, int c)
{
    return mTable(r, c);
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
void Matrix<NumRows, NumCols, Real>::SetRow(int r,
    Vector<NumCols, Real> const& vec)
{
    for (int c = 0; c < NumCols; ++c)
    {
        mTable(r, c) = vec[c];
    }
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
void Matrix<NumRows, NumCols, Real>::SetCol(int c,
    Vector<NumRows, Real> const& vec)
{
    for (int r = 0; r < NumRows; ++r)
    {
        mTable(r, c) = vec[r];
    }
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Vector<NumCols, Real> Matrix<NumRows, NumCols, Real>::GetRow(int r) const
{
    Vector<NumCols, Real> vec;
    for (int c = 0; c < NumCols; ++c)
    {
        vec[c] = mTable(r, c);
    }
    return vec;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Vector<NumRows, Real> Matrix<NumRows, NumCols, Real>::GetCol(int c) const
{
    Vector<NumRows, Real> vec;
    for (int r = 0; r < NumRows; ++r)
    {
        vec[r] = mTable(r, c);
    }
    return vec;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real const& Matrix<NumRows, NumCols, Real>::operator[](int i) const
{
    return mTable[i];
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real& Matrix<NumRows, NumCols, Real>::operator[](int i)
{
    return mTable[i];
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
bool Matrix<NumRows, NumCols, Real>::operator==(Matrix const& mat) const
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        if (mTable[i] != mat.mTable[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
bool Matrix<NumRows, NumCols, Real>::operator!=(Matrix const& mat) const
{
    return !operator==(mat);
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
bool Matrix<NumRows, NumCols, Real>::operator<(Matrix const& mat) const
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        if (mTable[i] < mat.mTable[i])
        {
            return true;
        }

        if (mTable[i] > mat.mTable[i])
        {
            return false;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
bool Matrix<NumRows, NumCols, Real>::operator<=(Matrix const& mat) const
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        if (mTable[i] < mat.mTable[i])
        {
            return true;
        }

        if (mTable[i] > mat.mTable[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
bool Matrix<NumRows, NumCols, Real>::operator>(Matrix const& mat) const
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        if (mTable[i] > mat.mTable[i])
        {
            return true;
        }

        if (mTable[i] < mat.mTable[i])
        {
            return false;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
bool Matrix<NumRows, NumCols, Real>::operator>=(Matrix const& mat) const
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        if (mTable[i] > mat.mTable[i])
        {
            return true;
        }

        if (mTable[i] < mat.mTable[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real> Matrix<NumRows, NumCols, Real>::Zero()
{
    Matrix M;
    M.MakeZero();
    return M;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
operator+(Matrix<NumRows, NumCols, Real> const& M)
{
    return M;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
operator-(Matrix<NumRows, NumCols, Real> const& M)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        result[i] = -M[i];
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
operator+(
Matrix<NumRows, NumCols, Real> const& M0,
Matrix<NumRows, NumCols, Real> const& M1)
{
    Matrix<NumRows, NumCols, Real> result = M0;
    return result += M1;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
operator-(
Matrix<NumRows, NumCols, Real> const& M0,
Matrix<NumRows, NumCols, Real> const& M1)
{
    Matrix<NumRows, NumCols, Real> result = M0;
    return result -= M1;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
operator*(Matrix<NumRows, NumCols, Real> const& M, Real scalar)
{
    Matrix<NumRows, NumCols, Real> result = M;
    return result *= scalar;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
operator*(Real scalar, Matrix<NumRows, NumCols, Real> const& M)
{
    Matrix<NumRows, NumCols, Real> result = M;
    return result *= scalar;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
operator/(Matrix<NumRows, NumCols, Real> const& M, Real scalar)
{
    Matrix<NumRows, NumCols, Real> result = M;
    return result /= scalar;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>&
operator+=(
Matrix<NumRows, NumCols, Real>& M0,
Matrix<NumRows, NumCols, Real> const& M1)
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        M0[i] += M1[i];
    }
    return M0;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>&
operator-=(
Matrix<NumRows, NumCols, Real>& M0,
Matrix<NumRows, NumCols, Real> const& M1)
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        M0[i] -= M1[i];
    }
    return M0;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>&
operator*=(Matrix<NumRows, NumCols, Real>& M, Real scalar)
{
    for (int i = 0; i < NumRows*NumCols; ++i)
    {
        M[i] *= scalar;
    }
    return M;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>&
operator/=(Matrix<NumRows, NumCols, Real>& M, Real scalar)
{
    if (scalar != (Real)0)
    {
        Real invScalar = ((Real)1) / scalar;
        for (int i = 0; i < NumRows*NumCols; ++i)
        {
            M[i] *= invScalar;
        }
    }
    else
    {
        for (int i = 0; i < NumRows*NumCols; ++i)
        {
            M[i] = (Real)0;
        }
    }
    return M;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Real L1Norm(Matrix<NumRows, NumCols, Real> const& M)
{
    Real sum = std::abs(M[0]);
    for (int i = 1; i < NumRows*NumCols; ++i)
    {
        sum += std::abs(M[i]);
    }
    return sum;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Real L2Norm(Matrix<NumRows, NumCols, Real> const& M)
{
    Real sum = M[0] * M[0];
    for (int i = 1; i < NumRows*NumCols; ++i)
    {
        sum += M[i] * M[i];
    }
    return sqrt(sum);
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Real LInfinityNorm(Matrix<NumRows, NumCols, Real> const& M)
{
    Real maxAbsElement = M[0];
    for (int i = 1; i < NumRows*NumCols; ++i)
    {
        Real absElement = std::abs(M[i]);
        if (absElement > maxAbsElement)
        {
            maxAbsElement = absElement;
        }
    }
    return maxAbsElement;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Matrix<N, N, Real> Inverse(Matrix<N, N, Real> const& M,
    bool* reportInvertibility)
{
    Matrix<N, N, Real> invM;
    Real determinant;
    bool invertible = GaussianElimination<Real>()(N, &M[0], &invM[0],
        determinant, nullptr, nullptr, nullptr, 0, nullptr);
    if (reportInvertibility)
    {
        *reportInvertibility = invertible;
    }
    return invM;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real Determinant(Matrix<N, N, Real> const& M)
{
    Real determinant;
    GaussianElimination<Real>()(N, &M[0], nullptr, determinant, nullptr,
        nullptr, nullptr, 0, nullptr);
    return determinant;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumCols, NumRows, Real>
Transpose(Matrix<NumRows, NumCols, Real> const& M)
{
    Matrix<NumCols, NumRows, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(c, r) = M(r, c);
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Vector<NumRows, Real>
operator*(
Matrix<NumRows, NumCols, Real> const& M,
Vector<NumCols, Real> const& V)
{
    Vector<NumRows, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        result[r] = (Real)0;
        for (int c = 0; c < NumCols; ++c)
        {
            result[r] += M(r, c) * V[c];
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Vector<NumCols, Real> operator*(Vector<NumRows, Real> const& V,
    Matrix<NumRows, NumCols, Real> const& M)
{
    Vector<NumCols, Real> result;
    for (int c = 0; c < NumCols; ++c)
    {
        result[c] = (Real)0;
        for (int r = 0; r < NumRows; ++r)
        {
            result[c] += V[r] * M(r, c);
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, int NumCommon, typename Real>
Matrix<NumRows, NumCols, Real>
operator*(
Matrix<NumRows, NumCommon, Real> const& A,
Matrix<NumCommon, NumCols, Real> const& B)
{
    return MultiplyAB(A, B);
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, int NumCommon, typename Real>
Matrix<NumRows, NumCols, Real>
MultiplyAB(
Matrix<NumRows, NumCommon, Real> const& A,
Matrix<NumCommon, NumCols, Real> const& B)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(r, c) = (Real)0;
            for (int i = 0; i < NumCommon; ++i)
            {
                result(r, c) += A(r, i) * B(i, c);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, int NumCommon, typename Real>
Matrix<NumRows, NumCols, Real>
MultiplyABT(
Matrix<NumRows, NumCommon, Real> const& A,
Matrix<NumCols, NumCommon, Real> const& B)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(r, c) = (Real)0;
            for (int i = 0; i < NumCommon; ++i)
            {
                result(r, c) += A(r, i) * B(c, i);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, int NumCommon, typename Real>
Matrix<NumRows, NumCols, Real>
MultiplyATB(
Matrix<NumCommon, NumRows, Real> const& A,
Matrix<NumCommon, NumCols, Real> const& B)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(r, c) = (Real)0;
            for (int i = 0; i < NumCommon; ++i)
            {
                result(r, c) += A(i, r) * B(i, c);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, int NumCommon, typename Real>
Matrix<NumRows, NumCols, Real>
MultiplyATBT(
Matrix<NumCommon, NumRows, Real> const& A,
Matrix<NumCols, NumCommon, Real> const& B)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(r, c) = (Real)0;
            for (int i = 0; i < NumCommon; ++i)
            {
                result(r, c) += A(i, r) * B(c, i);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
MultiplyMD(
Matrix<NumRows, NumCols, Real> const& M,
Vector<NumCols, Real> const& D)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(r, c) = M(r, c) * D[c];
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
MultiplyDM(
Vector<NumRows, Real> const& D,
Matrix<NumRows, NumCols, Real> const& M)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(r, c) = D[r] * M(r, c);
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real>
Matrix<NumRows, NumCols, Real>
OuterProduct(Vector<NumRows, Real> const& U, Vector<NumCols, Real> const& V)
{
    Matrix<NumRows, NumCols, Real> result;
    for (int r = 0; r < NumRows; ++r)
    {
        for (int c = 0; c < NumCols; ++c)
        {
            result(r, c) = U[r] * V[c];
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void MakeIdentity(Matrix<N, N, Real>& M)
{
    for (int i = 0; i < N*N; ++i)
    {
        M[i] = (Real)0;
    }

    for (int i = 0; i < N; ++i)
    {
        M(i, i) = (Real)1;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void MakeDiagonal(Vector<N, Real> const& D, Matrix<N, N, Real>& M)
{
    for (int i = 0; i < N*N; ++i)
    {
        M[i] = (Real)0;
    }

    for (int i = 0; i < N; ++i)
    {
        M(i, i) = D[i];
    }
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Matrix<N,C,Real>::Table
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real const& Matrix<NumRows, NumCols, Real>::Table::operator()(int r, int c)
const
{
#if defined(GTE_USE_ROW_MAJOR)
    return mStorage[r][c];
#else
    return mStorage[c][r];
#endif
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real& Matrix<NumRows, NumCols, Real>::Table::operator()(int r, int c)
{
#if defined(GTE_USE_ROW_MAJOR)
    return mStorage[r][c];
#else
    return mStorage[c][r];
#endif
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real const& Matrix<NumRows, NumCols, Real>::Table::operator[](int i) const
{
    Real const* elements = &mStorage[0][0];
    return elements[i];
}
//----------------------------------------------------------------------------
template <int NumRows, int NumCols, typename Real> inline
Real& Matrix<NumRows, NumCols, Real>::Table::operator[](int i)
{
    Real* elements = &mStorage[0][0];
    return elements[i];
}
//----------------------------------------------------------------------------
