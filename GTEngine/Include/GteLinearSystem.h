// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteGaussianElimination.h"
#include "GteMatrix2x2.h"
#include "GteMatrix3x3.h"
#include "GteMatrix4x4.h"
#include <map>

// Solve linear systems of equations where the matrix A is NxN.  The return
// value of a function is 'true' when A is invertible.  In this case the
// solution X and the solution is valid.  If the return value is 'false', A
// is not invertible and X and Y are invalid, so do not use them.  When a
// matrix is passed as Real*, the storage order is assumed to be the one
// consistent with your choice of GTE_USE_ROW_MAJOR or GTE_USE_COL_MAJOR.
//
// The linear solvers that use the conjugate gradient algorithm are based
// on the discussion in "Matrix Computations, 2nd edition" by G. H. Golub
// and Charles F. Van Loan, The Johns Hopkins Press, Baltimore MD, Fourth
// Printing 1993.

namespace gte
{

template <typename Real>
class LinearSystem
{
public:
    // Solve 2x2, 3x3, and 4x4 systems by inverting the matrix directly.  This
    // avoids the overhead of Gaussian elimination in small dimensions.
    static bool Solve(Matrix2x2<Real> const& A, Vector2<Real> const& B,
        Vector2<Real>& X);

    static bool Solve(Matrix3x3<Real> const& A, Vector3<Real> const& B,
        Vector3<Real>& X);

    static bool Solve(Matrix4x4<Real> const& A, Vector4<Real> const& B,
        Vector4<Real>& X);

    // Solve A*X = B, where B is Nx1 and the solution X is Nx1.
    static bool Solve(int N, Real const* A, Real const* B, Real* X);

    // Solve A*X = B, where B is NxM and the solution X is NxM.
    static bool Solve(int N, int M, Real const* A, Real const* B, Real* X);

    // Solve A*X = B, where A is tridiagonal.  The function expects the
    // subdiagonal, diagonal, and superdiagonal of A.  The diagonal input
    // must have N elements.  The subdiagonal and superdiagonal inputs must
    // have N-1 elements.
    static bool SolveTridiagonal(int N, Real const* subdiagonal,
        Real const* diagonal, Real const* superdiagonal, Real const* B,
        Real* X);

    // Solve A*X = B, where A is tridiagonal.  The function expects the
    // subdiagonal, diagonal, and superdiagonal of A.  Moreover, the
    // subdiagonal elements are a constant, the diagonal elements are a
    // constant, and the superdiagonal elements are a constant.
    static bool SolveConstantTridiagonal(int N, Real subdiagonal,
        Real diagonal, Real superdiagonal, Real const* B, Real* X);

    // Solve A*X = B using the conjugate gradient method, where A is
    // symmetric.  You must specify the maximum number of iterations and a
    // tolerance for terminating the iterations.  Reasonable choices for
    // tolerance are 1e-06f for 'float' or 1e-08 for 'double'.
    static unsigned int SolveSymmetricCG(int N, Real const* A, Real const* B,
        Real* X, unsigned int maxIterations, Real tolerance);

    // Solve A*X = B using the conjugate gradient method, where A is sparse
    // and symmetric.  The nonzero entries of the symmetrix matrix A are
    // stored in a map whose keys are pairs (i,j) and whose values are real
    // numbers.  The pair (i,j) is the location of the value in the array.
    // Only one of (i,j) and (j,i) should be stored since A is symmetric.
    // The column vector B is stored as an array of contiguous values.  You
    // must specify the maximum number of iterations and a tolerance for
    // terminating the iterations.  Reasonable choices for tolerance are
    // 1e-06f for 'float' or 1e-08 for 'double'.
    typedef std::map<std::array<int, 2>, Real> SparseMatrix;
    static unsigned int SolveSymmetricCG(int N, SparseMatrix const& A,
        Real const* B, Real* X, unsigned int maxIterations, Real tolerance);

private:
    // Support for the conjugate gradient method.
    static Real Dot(int N, Real const* U, Real const* V);
    static void Mul(int N, Real const* A, Real const* X, Real* P);
    static void Mul(int N, SparseMatrix const& A, Real const* X, Real* P);
    static void UpdateX(int N, Real* X, Real alpha, Real const* P);
    static void UpdateR(int N, Real* R, Real alpha, Real const* W);
    static void UpdateP(int N, Real* P, Real beta, Real const* R);
};

#include "GteLinearSystem.inl"

}
