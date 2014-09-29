// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real>::GMatrix(int numRows, int numCols)
{
    SetSize(numRows, numCols);
}
//----------------------------------------------------------------------------
template <typename Real>
void GMatrix<Real>::MakeZero()
{
    std::fill(mElements.begin(), mElements.end(), (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
void GMatrix<Real>::SetSize(int numRows, int numCols)
{
    if (numRows > 0 && numCols > 0)
    {
        mNumRows = numRows;
        mNumCols = numCols;
        mElements.resize(mNumRows * mNumCols);
    }
    else
    {
        mNumRows = 0;
        mNumCols = 0;
        mElements.clear();
    }
}
//----------------------------------------------------------------------------
template <typename Real> inline
void GMatrix<Real>::GetSize(int& numRows, int& numCols) const
{
    numRows = mNumRows;
    numCols = mNumCols;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int GMatrix<Real>::GetNumRows() const
{
    return mNumRows;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int GMatrix<Real>::GetNumCols() const
{
    return mNumCols;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int GMatrix<Real>::GetNumElements() const
{
    return static_cast<int>(mElements.size());
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real const& GMatrix<Real>::operator()(int r, int c) const
{
    ValidateIndices(r, c);
#ifdef GTE_USE_ROW_MAJOR
    return mElements[c + mNumCols*r];
#else
    return mElements[r + mNumRows*c];
#endif
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real& GMatrix<Real>::operator()(int r, int c)
{
    ValidateIndices(r, c);
#ifdef GTE_USE_ROW_MAJOR
    return mElements[c + mNumCols*r];
#else
    return mElements[r + mNumRows*c];
#endif
}
//----------------------------------------------------------------------------
template <typename Real>
void GMatrix<Real>::SetRow(int r, GVector<Real> const& vec)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(vec.GetSize() == GetNumCols(), "Mismatched size.");
#endif
    for (int c = 0; c < mNumCols; ++c)
    {
        operator()(r,c) = vec[c];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void GMatrix<Real>::SetCol(int c, GVector<Real> const& vec)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(vec.GetSize() == GetNumRows(), "Mismatched size.");
#endif
    for (int r = 0; r < mNumRows; ++r)
    {
        operator()(r, c) = vec[r];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> GMatrix<Real>::GetRow(int r) const
{
    GVector<Real> vec(mNumCols);
    for (int c = 0; c < mNumCols; ++c)
    {
        vec[c] = operator()(r, c);
    }
    return vec;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> GMatrix<Real>::GetCol(int c) const
{
    GVector<Real> vec(mNumRows);
    for (int r = 0; r < mNumRows; ++r)
    {
        vec[r] = operator()(r, c);
    }
    return vec;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real const& GMatrix<Real>::operator[](int i) const
{
    return mElements[i];
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real& GMatrix<Real>::operator[](int i)
{
    return mElements[i];
}
//----------------------------------------------------------------------------
template <typename Real>
bool GMatrix<Real>::operator==(GMatrix const& mat) const
{
    ValidateSizes(mat);
    for (int i = 0; i < GetNumElements(); ++i)
    {
        if (operator[](i) != mat[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GMatrix<Real>::operator!=(GMatrix const& mat) const
{
    ValidateSizes(mat);
    for (int i = 0; i < GetNumElements(); ++i)
    {
        if (operator[](i) != mat[i])
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GMatrix<Real>::operator<(GMatrix const& mat) const
{
    ValidateSizes(mat);
    for (int i = 0; i < GetNumElements(); ++i)
    {
        if (operator[](i) < mat[i])
        {
            return true;
        }

        if (operator[](i) > mat[i])
        {
            return false;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GMatrix<Real>::operator<=(GMatrix const& mat) const
{
    ValidateSizes(mat);
    for (int i = 0; i < GetNumElements(); ++i)
    {
        if (operator[](i) < mat[i])
        {
            return true;
        }

        if (operator[](i) > mat[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GMatrix<Real>::operator>(GMatrix const& mat) const
{
    ValidateSizes(mat);
    for (int i = 0; i < GetNumElements(); ++i)
    {
        if (operator[](i) > mat[i])
        {
            return true;
        }

        if (operator[](i) < mat[i])
        {
            return false;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GMatrix<Real>::operator>=(GMatrix const& mat) const
{
    ValidateSizes(mat);
    for (int i = 0; i < GetNumElements(); ++i)
    {
        if (operator[](i) > mat[i])
        {
            return true;
        }

        if (operator[](i) < mat[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> GMatrix<Real>::Zero(int numRows, int numCols)
{
    GMatrix<Real> M(numRows, numCols);
    M.MakeZero();
    return M;
}
//----------------------------------------------------------------------------
template <typename Real> inline
void GMatrix<Real>::ValidateIndices(int r, int c) const
{
#ifdef GTE_ASSERT_ON_GMATRIX_INDEX_OUT_OF_RANGE
    LogAssert(0 <= r && r < GetNumRows() && 0 <= c && c < GetNumCols(),
        "Invalid index.");
#endif
    (void)r;
    (void)c;
}
//----------------------------------------------------------------------------
template <typename Real> inline
void GMatrix<Real>::ValidateSizes(GMatrix const& mat) const
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(GetNumRows() == mat.GetNumRows() && 
        GetNumCols() == mat.GetNumCols(), "Mismatched size.");
#endif
    (void)mat;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator+(GMatrix<Real> const& M)
{
    return M;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator-(GMatrix<Real> const& M)
{
    GMatrix<Real> result(M.GetNumRows(), M.GetNumCols());
    for (int i = 0; i < M.GetNumElements(); ++i)
    {
        result[i] = -M[i];
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator+(GMatrix<Real> const& M0, GMatrix<Real> const& M1)
{
    GMatrix<Real> result = M0;
    return result += M1;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator-(GMatrix<Real> const& M0, GMatrix<Real> const& M1)
{
    GMatrix<Real> result = M0;
    return result -= M1;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator*(GMatrix<Real> const& M, Real scalar)
{
    GMatrix<Real> result = M;
    return result *= scalar;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator*(Real scalar, GMatrix<Real> const& M)
{
    GMatrix<Real> result = M;
    return result *= scalar;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator/(GMatrix<Real> const& M, Real scalar)
{
    GMatrix<Real> result = M;
    return result /= scalar;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real>& operator+=(GMatrix<Real>& M0, GMatrix<Real> const& M1)
{
    M0.ValidateSizes(M1);
    for (int i = 0; i < M0.GetNumElements(); ++i)
    {
        M0[i] += M1[i];
    }
    return M0;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real>& operator-=(GMatrix<Real>& M0, GMatrix<Real> const& M1)
{
    M0.ValidateSizes(M1);
    for (int i = 0; i < M0.GetNumElements(); ++i)
    {
        M0[i] -= M1[i];
    }
    return M0;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real>& operator*=(GMatrix<Real>& M, Real scalar)
{
    for (int i = 0; i < M.GetNumElements(); ++i)
    {
        M[i] *= scalar;
    }
    return M;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real>& operator/=(GMatrix<Real>& M, Real scalar)
{
    if (scalar != (Real)0)
    {
        Real invScalar = ((Real)1)/scalar;
        for (int i = 0; i < M.GetNumElements(); ++i)
        {
            M[i] *= invScalar;
        }
    }
    else
    {
        for (int i = 0; i < M.GetNumElements(); ++i)
        {
            M[i] = (Real)0;
        }
    }
    return M;
}
//----------------------------------------------------------------------------
template <typename Real>
Real L1Norm(GMatrix<Real> const& M)
{
    Real sum = std::abs(M[0]);
    for (int i = 1; i < M.GetNumElements(); ++i)
    {
        sum += std::abs(M[i]);
    }
    return sum;
}
//----------------------------------------------------------------------------
template <typename Real>
Real L2Norm(GMatrix<Real> const& M)
{
    Real sum = M[0]*M[0];
    for (int i = 1; i < M.GetNumElements(); ++i)
    {
        sum += M[i]*M[i];
    }
    return sqrt(sum);
}
//----------------------------------------------------------------------------
template <typename Real>
Real LInfinityNorm(GMatrix<Real> const& M)
{
    Real maxAbsElement = M[0];
    for (int i = 1; i < M.GetNumElements(); ++i)
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
template <typename Real>
GMatrix<Real> Inverse(GMatrix<Real> const& M, bool* reportInvertibility)
{
    GMatrix<Real> invM(M.GetNumRows(), M.GetNumCols());
    if (M.GetNumRows() == M.GetNumCols())
    {
        Real determinant;
        bool invertible = GaussianElimination<Real>()(M.GetNumRows(), &M[0],
            &invM[0], determinant, nullptr, nullptr, nullptr, 0, nullptr);
        if (reportInvertibility)
        {
            *reportInvertibility = invertible;
        }
    }
    else
    {
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
        LogError("Matrix must be square.");
#endif
        invM.MakeZero();
        if (reportInvertibility)
        {
            *reportInvertibility = false;
        }
    }
    return invM;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Determinant(GMatrix<Real> const& M)
{
    Real determinant;
    if (M.GetNumRows() == M.GetNumCols())
    {
        GaussianElimination<Real>()(M.GetNumRows(), &M[0], nullptr,
            determinant, nullptr, nullptr, nullptr, 0, nullptr);
    }
    else
    {
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
        LogError("Matrix must be square.");
#endif
        determinant = (Real)0;
    }
    return determinant;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> Transpose(GMatrix<Real> const& M)
{
    GMatrix<Real> result(M.GetNumCols(), M.GetNumRows());
    for (int r = 0; r < M.GetNumRows(); ++r)
    {
        for (int c = 0; c < M.GetNumCols(); ++c)
        {
            result(c,r) = M(r,c);
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator*(GMatrix<Real> const& M, GVector<Real> const& V)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(V.GetSize() == M.GetNumRows(), "Mismatched size.");
#endif
    GVector<Real> result(M.GetNumRows());
    for (int r = 0; r < M.GetNumRows(); ++r)
    {
        result[r] = (Real)0;
        for (int c = 0; c < M.GetNumCols(); ++c)
        {
            result[r] += M(r,c) * V[c];
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator*(GVector<Real> const& V, GMatrix<Real> const& M)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(V.GetSize() == M.GetNumCols(), "Mismatched size.");
#endif
    GVector<Real> result(M.GetNumCols());
    for (int c = 0; c < M.GetNumCols(); ++c)
    {
        result[c] = (Real)0;
        for (int r = 0; r < M.GetNumRows(); ++r)
        {
            result[c] += V[r] * M(r,c);
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> operator*(GMatrix<Real> const& A, GMatrix<Real> const& B)
{
    return MultiplyAB(A, B);
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> MultiplyAB(GMatrix<Real> const& A, GMatrix<Real> const& B)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(A.GetNumCols() == B.GetNumRows(), "Mismatched size.");
#endif
    int const numCommon = A.GetNumCols();
    GMatrix<Real> result(A.GetNumRows(), B.GetNumCols());
    for (int r = 0; r < result.GetNumRows(); ++r)
    {
        for (int c = 0; c < result.GetNumCols(); ++c)
        {
            result(r,c) = (Real)0;
            for (int i = 0; i < numCommon; ++i)
            {
                result(r,c) += A(r,i) * B(i,c);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> MultiplyABT(GMatrix<Real> const& A, GMatrix<Real> const& B)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(A.GetNumCols() == B.GetNumCols(), "Mismatched size.");
#endif
    int const numCommon = A.GetNumCols();
    GMatrix<Real> result(A.GetNumRows(), B.GetNumRows());
    for (int r = 0; r < result.GetNumRows(); ++r)
    {
        for (int c = 0; c < result.GetNumCols(); ++c)
        {
            result(r,c) = (Real)0;
            for (int i = 0; i < numCommon; ++i)
            {
                result(r,c) += A(r,i) * B(c,i);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> MultiplyATB(GMatrix<Real> const& A, GMatrix<Real> const& B)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(A.GetNumRows() == B.GetNumRows(), "Mismatched size.");
#endif
    int const numCommon = A.GetNumRows();
    GMatrix<Real> result(A.GetNumCols(), B.GetNumCols());
    for (int r = 0; r < result.GetNumRows(); ++r)
    {
        for (int c = 0; c < result.GetNumCols(); ++c)
        {
            result(r,c) = (Real)0;
            for (int i = 0; i < numCommon; ++i)
            {
                result(r,c) += A(i,r) * B(i,c);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> MultiplyATBT(GMatrix<Real> const& A, GMatrix<Real> const& B)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(A.GetNumRows() == B.GetNumCols(), "Mismatched size.");
#endif
    int const numCommon = A.GetNumRows();
    GMatrix<Real> result(A.GetNumCols(), B.GetNumRows());
    for (int r = 0; r < result.GetNumRows(); ++r)
    {
        for (int c = 0; c < result.GetNumCols(); ++c)
        {
            result(r,c) = (Real)0;
            for (int i = 0; i < numCommon; ++i)
            {
                result(r,c) += A(i,r) * B(c,i);
            }
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> MultiplyMD(GMatrix<Real> const& M, GVector<Real> const& D)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(D.GetSize() == M.GetNumCols(), "Mismatched size.");
#endif
    GMatrix<Real> result(M.GetNumRows(), M.GetNumCols());
    for (int r = 0; r < result.GetNumRows(); ++r)
    {
        for (int c = 0; c < result.GetNumCols(); ++c)
        {
            result(r,c) = M(r,c) * D[c];
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> MultiplyDM(GVector<Real> const& D, GMatrix<Real> const& M)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(D.GetSize() == M.GetNumRows(), "Mismatched size.");
#endif
    GMatrix<Real> result(M.GetNumRows(), M.GetNumCols());
    for (int r = 0; r < result.GetNumRows(); ++r)
    {
        for (int c = 0; c < result.GetNumCols(); ++c)
        {
            result(r,c) = D[r] * M(r,c);
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GMatrix<Real> OuterProduct(GVector<Real> const& U, GVector<Real> const& V)
{
    GMatrix<Real> result(U.GetSize(), V.GetSize());
    for (int r = 0; r < result.GetNumRows(); ++r)
    {
        for (int c = 0; c < result.GetNumCols(); ++c)
        {
            result(r,c) = U[r] * V[c];
        }
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void MakeIdentity(GMatrix<Real>& M)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(M.GetNumRows() == M.GetNumCols(), "Mismatched size.");
#endif
    int const N = M.GetNumRows();
    for (int i = 0; i < N*N; ++i)
    {
        M[i] = (Real)0;
    }

    for (int i = 0; i < N; ++i)
    {
        M(i,i) = (Real)1;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void MakeDiagonal(GVector<Real> const& D, GMatrix<Real>& M)
{
#ifdef GTE_ASSERT_ON_GMATRIX_SIZE_MISMATCH
    LogAssert(M.GetNumRows() == M.GetNumCols(), "Mismatched size.");
#endif
    int const N = M.GetNumRows();
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
