// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GTEngineDEF.h"
#include "GteArray2.h"
#include <cmath>
#include <vector>

namespace gte
{

template <typename Real>
class BandedMatrix
{
public:
    // Construction and destruction.
    ~BandedMatrix();
    BandedMatrix(int size, int numLBands, int numUBands);

    // Member access.
    inline int GetSize() const;
    inline std::vector<Real>& GetDBand();
    inline std::vector<Real> const& GetDBand() const;
    inline std::vector<std::vector<Real>>& GetLBands();
    inline std::vector<std::vector<Real>> const& GetLBands() const;
    inline std::vector<std::vector<Real>>& GetUBands();
    inline std::vector<std::vector<Real>> const& GetUBands() const;
    Real& operator()(int r, int c);
    Real const& operator()(int r, int c) const;

    // Factor the square banded matrix A into A = L*L^T, where L is a
    // lower-triangular matrix (L^T is an upper-triangular matrix).  This is
    // an LU decomposition that allows for stable inversion of A to solve
    // A*X = B.  The return value is 'true' iff the factorizing is successful
    // (L is invertible).  If successful, A contains the Cholesky
    // factorization: L in the lower-triangular part of A and L^T in the
    // upper-triangular part of A.
    bool CholeskyFactor();

    // Solve the linear system A*X = B, where A is an NxN banded matrix and B
    // is an Nx1 vector.  The unknown X is also Nx1.  The input to this
    // function is B.  The output X is computed and stored in B.  The return
    // value is 'true' iff the system has a solution.  The matrix A and the
    // vector B are both modified by this function.  If successful, A contains
    // the Cholesky factorization: L in the lower-triangular part of A and
    // L^T in the upper-triangular part of A.
    bool SolveSystem(Real* bVector);

    // Solve the linear system A*X = B, where A is an NxN banded matrix and
    // B is an NxM matrix.  The unknown X is also NxM.  The input to this
    // function is B.  The output X is computed and stored in B.  The return
    // value is 'true' iff the system has a solution.  The matrix A and the
    // vector B are both modified by this function.  If successful, A contains
    // the Cholesky factorization: L in the lower-triangular part of A and
    // L^T in the upper-triangular part of A.
    //
    // The storage convention for element lookup in bMatrix is determined by
    // GTE_USE_ROW_MAJOR or GTE_USE_COL_MAJOR, whichever is active.  This
    // class will correctly lookup the elements.
    bool SolveSystem(Real* bMatrix, int numBColumns);

    // Compute the inverse of the banded matrix.  The return value is 'true'
    // when the matrix is invertible, in which case the 'inverse' output is
    // valid.  The return value is 'false' when the matrix is not invertible,
    // in which case 'inverse' is invalid and should not be used.  The
    // input matrix 'inverse' must be the same size as 'this'.
    //
    // The storage convention for element lookup in inverse is determined by
    // GTE_USE_ROW_MAJOR or GTE_USE_COL_MAJOR, whichever is active.  This
    // class will correctly lookup the elements.
    bool ComputeInverse(Real* inverse) const;

private:
    // The linear system is L*U*X = B, where A = L*U and U = L^T,  Reduce this
    // to U*X = L^{-1}*B.  The return value is 'true' iff the operation is
    // successful.
    bool SolveLower(Real* dataVector) const;

    // The linear system is U*X = L^{-1}*B.  Reduce this to
    // X = U^{-1}*L^{-1}*B.  The return value is 'true' iff the operation is
    // successful.
    bool SolveUpper(Real* dataVector) const;

    // The linear system is L*U*X = B, where A = L*U and U = L^T,  Reduce this
    // to U*X = L^{-1}*B.  The return value is 'true' iff the operation is
    // successful.  See the comments for SolveSystem(Real*,int) about the
    // storage for dataMatrix.
    bool SolveLower(Real* dataMatrix, int numColumns) const;

    // The linear system is U*X = L^{-1}*B.  Reduce this to
    // X = U^{-1}*L^{-1}*B.  The return value is 'true' iff the operation is
    // successful.  See the comments for SolveSystem(Real*,int) about the
    // storage for dataMatrix.
    bool SolveUpper(Real* dataMatrix, int numColumns) const;

    int mSize;
    std::vector<Real> mDBand;
    std::vector<std::vector<Real>> mLBands, mUBands;

    // For return by operator()(int,int) for valid indices not in the bands,
    // in which case the matrix entries are zero,
    mutable Real mZero;
};

#include "GteBandedMatrix.inl"

}
