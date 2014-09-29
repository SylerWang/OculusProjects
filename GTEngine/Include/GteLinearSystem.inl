// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
bool LinearSystem<Real>::Solve(Matrix2x2<Real> const& A,
    Vector2<Real> const& B, Vector2<Real>& X)
{
    bool invertible;
    Matrix2x2<Real> invA = Inverse(A, &invertible);
    if (invertible)
    {
        X = invA * B;
    }
    else
    {
        X = Vector2<Real>::Zero();
    }
    return invertible;
}
//----------------------------------------------------------------------------
template <typename Real>
bool LinearSystem<Real>::Solve(Matrix3x3<Real> const& A,
    Vector3<Real> const& B, Vector3<Real>& X)
{
    bool invertible;
    Matrix3x3<Real> invA = Inverse(A, &invertible);
    if (invertible)
    {
        X = invA * B;
    }
    else
    {
        X = Vector3<Real>::Zero();
    }
    return invertible;
}
//----------------------------------------------------------------------------
template <typename Real>
bool LinearSystem<Real>::Solve(Matrix4x4<Real> const& A,
    Vector4<Real> const& B, Vector4<Real>& X)
{
    bool invertible;
    Matrix4x4<Real> invA = Inverse(A, &invertible);
    if (invertible)
    {
        X = invA * B;
    }
    else
    {
        X = Vector4<Real>::Zero();
    }
    return invertible;
}
//----------------------------------------------------------------------------
template <typename Real>
bool LinearSystem<Real>::Solve(int N, Real const* A, Real const* B, Real* X)
{
    Real determinant;
    return GaussianElimination<Real>()(N, A, nullptr, determinant, B, X,
        nullptr, 0, nullptr);
}
//----------------------------------------------------------------------------
template <typename Real>
bool LinearSystem<Real>::Solve(int N, int M, Real const* A, Real const* B,
    Real* X)
{
    Real determinant;
    return GaussianElimination<Real>()(N, A, nullptr, determinant, nullptr,
        nullptr, B, M, X);
}
//----------------------------------------------------------------------------
template <typename Real>
bool LinearSystem<Real>::SolveTridiagonal(int N, Real const* subdiagonal,
    Real const* diagonal, Real const* superdiagonal, Real const* B,
    Real* X)
{
    if (diagonal[0] == (Real)0)
    {
        return false;
    }

    std::vector<Real> tmp(N - 1);
    Real expr = diagonal[0];
    Real invExpr = ((Real)1) / expr;
    X[0] = B[0] * invExpr;

    int i0, i1;
    for (i0 = 0, i1 = 1; i1 < N; ++i0, ++i1)
    {
        tmp[i0] = superdiagonal[i0] * invExpr;
        expr = diagonal[i1] - subdiagonal[i0] * tmp[i0];
        if (expr == (Real)0)
        {
            return false;
        }
        invExpr = ((Real)1) / expr;
        X[i1] = (B[i1] - subdiagonal[i0] * X[i0]) * invExpr;
    }

    for (i0 = N - 1, i1 = N - 2; i1 >= 0; --i0, --i1)
    {
        X[i1] -= tmp[i1] * X[i0];
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool LinearSystem<Real>::SolveConstantTridiagonal(int N, Real subdiagonal,
    Real diagonal, Real superdiagonal, Real const* B, Real* X)
{
    if (diagonal == (Real)0)
    {
        return false;
    }

    std::vector<Real> tmp(N - 1);
    Real expr = diagonal;
    Real invExpr = ((Real)1) / expr;
    X[0] = B[0] * invExpr;

    int i0, i1;
    for (i0 = 0, i1 = 1; i1 < N; ++i0, ++i1)
    {
        tmp[i0] = superdiagonal * invExpr;
        expr = diagonal - subdiagonal * tmp[i0];
        if (expr == (Real)0)
        {
            return false;
        }
        invExpr = ((Real)1) / expr;
        X[i1] = (B[i1] - subdiagonal * X[i0]) * invExpr;
    }

    for (i0 = N - 1, i1 = N - 2; i1 >= 0; --i0, --i1)
    {
        X[i1] -= tmp[i1] * X[i0];
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
unsigned int LinearSystem<Real>::SolveSymmetricCG(int N, Real const* A,
    Real const* B, Real* X, unsigned int maxIterations, Real tolerance)
{
    // The first iteration.
    std::vector<Real> tmpR(N), tmpP(N), tmpW(N);
    Real* R = &tmpR[0];
    Real* P = &tmpP[0];
    Real* W = &tmpW[0];
    size_t numBytes = N * sizeof(Real);
    memset(X, 0, numBytes);
#ifdef WIN32
    memcpy_s(R, numBytes, B, numBytes);
#else
    memcpy(R, B, numBytes);
#endif
    Real rho0 = Dot(N, R, R);
#ifdef WIN32
    memcpy_s(P, numBytes, R, numBytes);
#else
    memcpy(P, R, numBytes);
#endif
    Mul(N, A, P, W);
    Real alpha = rho0 / Dot(N, P, W);
    UpdateX(N, X, alpha, P);
    UpdateR(N, R, alpha, W);
    Real rho1 = Dot(N, R, R);

    // The remaining iterations.
    unsigned int iteration;
    for (iteration = 1; iteration <= maxIterations; ++iteration)
    {
        Real root0 = sqrt(rho1);
        Real norm = Dot(N, B, B);
        Real root1 = sqrt(norm);
        if (root0 <= tolerance*root1)
        {
            break;
        }

        Real beta = rho1 / rho0;
        UpdateP(N, P, beta, R);
        Mul(N, A, P, W);
        alpha = rho1 / Dot(N, P, W);
        UpdateX(N, X, alpha, P);
        UpdateR(N, R, alpha, W);
        rho0 = rho1;
        rho1 = Dot(N, R, R);
    }
    return iteration;
}
//----------------------------------------------------------------------------
template <typename Real>
unsigned int LinearSystem<Real>::SolveSymmetricCG(int N,
    SparseMatrix const& A, Real const* B, Real* X, unsigned int maxIterations,
    Real tolerance)
{
    // The first iteration.
    std::vector<Real> tmpR(N), tmpP(N), tmpW(N);
    Real* R = &tmpR[0];
    Real* P = &tmpP[0];
    Real* W = &tmpW[0];
    size_t numBytes = N * sizeof(Real);
    memset(X, 0, numBytes);
#ifdef WIN32
    memcpy_s(R, numBytes, B, numBytes);
#else
    memcpy(R, B, numBytes);
#endif
    Real rho0 = Dot(N, R, R);
#ifdef WIN32
    memcpy_s(P, numBytes, R, numBytes);
#else
    memcpy(P, R, numBytes);
#endif
    Mul(N, A, P, W);
    Real alpha = rho0 / Dot(N, P, W);
    UpdateX(N, X, alpha, P);
    UpdateR(N, R, alpha, W);
    Real rho1 = Dot(N, R, R);

    // The remaining iterations.
    unsigned int iteration;
    for (iteration = 1; iteration <= maxIterations; ++iteration)
    {
        Real root0 = sqrt(rho1);
        Real norm = Dot(N, B, B);
        Real root1 = sqrt(norm);
        if (root0 <= tolerance*root1)
        {
            break;
        }

        Real beta = rho1 / rho0;
        UpdateP(N, P, beta, R);
        Mul(N, A, P, W);
        alpha = rho1 / Dot(N, P, W);
        UpdateX(N, X, alpha, P);
        UpdateR(N, R, alpha, W);
        rho0 = rho1;
        rho1 = Dot(N, R, R);
    }
    return iteration;
}
//----------------------------------------------------------------------------
template <typename Real>
Real LinearSystem<Real>::Dot(int N, Real const* U, Real const* V)
{
    Real dot = (Real)0;
    for (int i = 0; i < N; ++i)
    {
        dot += U[i] * V[i];
    }
    return dot;
}
//----------------------------------------------------------------------------
template <typename Real>
void LinearSystem<Real>::Mul(int N, Real const* A, Real const* X, Real* P)
{
#if defined(GTE_USE_ROW_MAJOR)
    Array2<true, Real> matA(N, N, const_cast<Real*>(A));
#else
    Array2<false, Real> matA(N, N, const_cast<Real*>(A));
#endif

    memset(P, 0, N * sizeof(Real));
    for (int row = 0; row < N; ++row)
    {
        for (int col = 0; col < N; ++col)
        {
            P[row] += matA(row, col) * X[col];
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void LinearSystem<Real>::Mul(int N, SparseMatrix const& A, Real const* X,
    Real* P)
{
    memset(P, 0, N * sizeof(Real));
    for (auto const& element : A)
    {
        int i = element.first[0];
        int j = element.first[1];
        Real value = element.second;
        P[i] += value * X[j];
        if (i != j)
        {
            P[j] += value * X[i];
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void LinearSystem<Real>::UpdateX(int N, Real* X, Real alpha, Real const* P)
{
    for (int i = 0; i < N; ++i)
    {
        X[i] += alpha*P[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void LinearSystem<Real>::UpdateR(int N, Real* R, Real alpha, Real const* W)
{
    for (int i = 0; i < N; ++i)
    {
        R[i] -= alpha*W[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void LinearSystem<Real>::UpdateP(int N, Real* P, Real beta, Real const* R)
{
    for (int i = 0; i < N; ++i)
    {
        P[i] = R[i] + beta*P[i];
    }
}
//----------------------------------------------------------------------------
