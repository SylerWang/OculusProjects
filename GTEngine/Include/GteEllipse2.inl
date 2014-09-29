// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Ellipse2<Real>::Ellipse2()
    :
    center(Vector2<Real>::Origin())
{
    for (int i = 0; i < 2; ++i)
    {
        axis[i] = Vector2<Real>::Unit(i);
        extent[i] = (Real)1;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Ellipse2<Real>::Ellipse2(Vector2<Real> const& inCenter,
    Vector2<Real> const inAxis[2], Vector2<Real> const& inExtent)
    :
    center(inCenter),
    extent(inExtent)
{
    for (int i = 0; i < 2; ++i)
    {
        axis[i] = inAxis[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Ellipse2<Real>::Ellipse2(Vector2<Real> const& inCenter,
    Vector2<Real> const& axis0, Vector2<Real> const& axis1, Real extent0,
    Real extent1)
    :
    center(inCenter)
{
    axis[0] = axis0;
    axis[1] = axis1;
    extent[0] = extent0;
    extent[1] = extent1;
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipse2<Real>::GetM(Matrix2x2<Real>& M) const
{
    Vector2<Real> ratio0 = axis[0] / extent[0];
    Vector2<Real> ratio1 = axis[1] / extent[1];
    M = OuterProduct<2, 2, Real>(ratio0, ratio0) +
        OuterProduct<2, 2, Real>(ratio1, ratio1);
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipse2<Real>::GetMInverse(Matrix2x2<Real>& MInverse) const
{
    Vector2<Real> product0 = axis[0] * extent[0];
    Vector2<Real> product1 = axis[1] * extent[1];
    MInverse = OuterProduct<2, 2, Real>(product0, product0) +
        OuterProduct<2, 2, Real>(product1, product1);
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipse2<Real>::ToCoefficients(Real coeff[6]) const
{
    Matrix2x2<Real> A;
    Vector2<Real> B;
    Real C;
    ToCoefficients(A, B, C);
    Convert(A, B, C, coeff);

    // Arrange for one of the x0^2 or x1^2 coefficients to be 1.
    Real maxValue = std::abs(coeff[3]);
    int maxIndex = 3;
    Real absValue = std::abs(coeff[5]);
    if (absValue > maxValue)
    {
        maxValue = absValue;
        maxIndex = 5;
    }

    Real invMaxValue = ((Real)1)/maxValue;
    for (int i = 0; i < 6; ++i)
    {
        if (i != maxIndex)
        {
            coeff[i] *= invMaxValue;
        }
        else
        {
            coeff[i] = (Real)1;
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipse2<Real>::ToCoefficients(Matrix2x2<Real>& A, Vector2<Real>& B,
    Real& C) const
{
    Vector2<Real> ratio0 = axis[0] / extent[0];
    Vector2<Real> ratio1 = axis[1] / extent[1];
    A = OuterProduct<2, 2, Real>(ratio0, ratio0) +
        OuterProduct<2, 2, Real>(ratio1, ratio1);
    B = ((Real)-2) * (A * center);
    C = Dot(center, A * center) - (Real)1;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipse2<Real>::FromCoefficients(Real const coeff[6])
{
    Matrix2x2<Real> A;
    Vector2<Real> B;
    Real C;
    Convert(coeff, A, B, C);
    return FromCoefficients(A, B, C);
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipse2<Real>::FromCoefficients(Matrix2x2<Real> const& A,
    Vector2<Real> const& B, Real C)
{
    // Compute the center K = -A^{-1}*B/2.
    Matrix2x2<Real> invA = Inverse(A);
    if (invA == Matrix2x2<Real>::Zero())
    {
        return false;
    }

    center = ((Real)-0.5) * (invA * B);

    // Compute B^T*A^{-1}*B/4 - C = K^T*A*K - C = -K^T*B/2 - C.
    Real rightSide = -((Real)0.5) * Dot(center, B) - C;
    if (rightSide == (Real)0)
    {
        return false;
    }

    // Compute M = A/(K^T*A*K - C).
    Real invRightSide = ((Real)1) / rightSide;
    Matrix2x2<Real> M = invRightSide * A;

    // Factor into M = R*D*R^T.  M is symmetric, so it does not matter whether
    // the matrix is stored in row-major or column-major order; they are
    // equivalent.  The output R, however, is in row-major order.
    SymmetricEigensolver<Real> es(2, 32);
    std::array<Real, 4> R;
    std::array<Real, 2> D;
    es.Solve(&M[0], +1);  // D[0] <= D[1]
    es.GetEigenvalues(&D[0]);
    es.GetEigenvectors(&R[0]);

    for (int i = 0; i < 2; ++i)
    {
        if (D[i] <= (Real)0)
        {
            return false;
        }

        extent[i] = ((Real)1) / sqrt(D[i]);
        axis[i] = Vector2<Real>(R[i], R[i + 2]);  // column i of R
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipse2<Real>::Convert(Real const coeff[6], Matrix2x2<Real>& A,
    Vector2<Real>& B, Real& C)
{
    C = coeff[0];
    B[0] = coeff[1];
    B[1] = coeff[2];
    A(0,0) = coeff[3];
    A(0,1) = ((Real)0.5) * coeff[4];
    A(1,0) = A(0,1);
    A(1,1) = coeff[5];
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipse2<Real>::Convert(Matrix2x2<Real> const& A,
    Vector2<Real> const& B, Real C, Real coeff[6])
{
    coeff[0] = C;
    coeff[1] = B[0];
    coeff[2] = B[1];
    coeff[3] = A(0,0);
    coeff[4] = ((Real)2) * A(0,1);
    coeff[5] = A(1,1);
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipse2<Real>::IsEqualTo(Ellipse2 const& ellipse) const
{
    if (center != ellipse.center)
    {
        return false;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (axis[i] != ellipse.axis[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        if (extent[i] != ellipse.extent[i])
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipse2<Real>::IsLessThan(Ellipse2 const& ellipse) const
{
    if (center < ellipse.center)
    {
        return true;
    }

    if (center > ellipse.center)
    {
        return false;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (axis[i] < ellipse.axis[i])
        {
            return true;
        }
        if (axis[i] > ellipse.axis[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        if (extent[i] < ellipse.extent[i])
        {
            return true;
        }
        if (extent[i] > ellipse.extent[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
