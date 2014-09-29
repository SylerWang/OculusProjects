// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Ellipsoid3<Real>::Ellipsoid3()
    :
    center(Vector3<Real>::Origin())
{
    for (int i = 0; i < 3; ++i)
    {
        axis[i] = Vector3<Real>::Unit(i);
        extent[i] = (Real)1;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Ellipsoid3<Real>::Ellipsoid3(Vector3<Real> const& inCenter,
    Vector3<Real> const inAxis[3], Vector3<Real> const& inExtent)
    :
    center(inCenter),
    extent(inExtent)
{
    for (int i = 0; i < 3; ++i)
    {
        axis[i] = inAxis[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Ellipsoid3<Real>::Ellipsoid3(Vector3<Real> const& inCenter,
    Vector3<Real> const& axis0, Vector3<Real> const& axis1,
    Vector3<Real> const& axis2, Real extent0, Real extent1, Real extent2)
    :
    center(inCenter)
{
    axis[0] = axis0;
    axis[1] = axis1;
    axis[2] = axis2;
    extent[0] = extent0;
    extent[1] = extent1;
    extent[2] = extent2;
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipsoid3<Real>::GetM(Matrix3x3<Real>& M) const
{
    Vector3<Real> ratio0 = axis[0] / extent[0];
    Vector3<Real> ratio1 = axis[1] / extent[1];
    Vector3<Real> ratio2 = axis[2] / extent[2];
    M = OuterProduct<3, 3, Real>(ratio0, ratio0) +
        OuterProduct<3, 3, Real>(ratio1, ratio1) +
        OuterProduct<3, 3, Real>(ratio2, ratio2);
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipsoid3<Real>::GetMInverse(Matrix3x3<Real>& MInverse) const
{
    Vector3<Real> product0 = axis[0] * extent[0];
    Vector3<Real> product1 = axis[1] * extent[1];
    Vector3<Real> product2 = axis[2] * extent[2];
    MInverse = OuterProduct<3, 3, Real>(product0, product0) +
        OuterProduct<3, 3, Real>(product1, product1) +
        OuterProduct<3, 3, Real>(product2, product2);
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipsoid3<Real>::ToCoefficients(Real coeff[10]) const
{
    Matrix3x3<Real> A;
    Vector3<Real> B;
    Real C;
    ToCoefficients(A, B, C);
    Convert(A, B, C, coeff);

    // Arrange for one of the x0^2, x1^2, or x2^2 coefficients to be 1.
    Real maxValue = std::abs(coeff[4]);
    int maxIndex = 4;
    Real absValue = std::abs(coeff[7]);
    if (absValue > maxValue)
    {
        maxValue = absValue;
        maxIndex = 7;
    }
    absValue = std::abs(coeff[9]);
    if (absValue > maxValue)
    {
        maxValue = absValue;
        maxIndex = 9;
    }

    Real invMaxValue = ((Real)1) / maxValue;
    for (int i = 0; i < 10; ++i)
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
void Ellipsoid3<Real>::ToCoefficients(Matrix3x3<Real>& A, Vector3<Real>& B,
    Real& C) const
{
    Vector3<Real> ratio0 = axis[0] / extent[0];
    Vector3<Real> ratio1 = axis[1] / extent[1];
    Vector3<Real> ratio2 = axis[2] / extent[2];
    A = OuterProduct<3, 3, Real>(ratio0, ratio0) +
        OuterProduct<3, 3, Real>(ratio1, ratio1) +
        OuterProduct<3, 3, Real>(ratio2, ratio2);

    B = ((Real)-2) * (A * center);
    C = Dot(center, A * center) - (Real)1;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipsoid3<Real>::FromCoefficients(Real const coeff[10])
{
    Matrix3x3<Real> A;
    Vector3<Real> B;
    Real C;
    Convert(coeff, A, B, C);
    return FromCoefficients(A, B, C);
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipsoid3<Real>::FromCoefficients(Matrix3x3<Real> const& A,
    Vector3<Real> const& B, Real C)
{
    // Compute the center K = -A^{-1}*B/2.
    Matrix3x3<Real> invA = Inverse(A);
    if (invA == Matrix3x3<Real>::Zero())
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
    Matrix3x3<Real> M = invRightSide * A;

    // Factor into M = R*D*R^T.  M is symmetric, so it does not matter whether
    // the matrix is stored in row-major or column-major order; they are
    // equivalent.  The output R, however, is in row-major order.
    SymmetricEigensolver<Real> es(3, 32);
    std::array<Real, 9> R;
    std::array<Real, 3> D;
    es.Solve(&M[0], +1);  // D[0] <= D[1] <= D[2]
    es.GetEigenvalues(&D[0]);
    es.GetEigenvectors(&R[0]);

    for (int i = 0; i < 3; ++i)
    {
        if (D[i] <= (Real)0)
        {
            return false;
        }

        extent[i] = ((Real)1) / sqrt(D[i]);
        axis[i] = Vector3<Real>(R[i], R[i + 3], R[i + 6]);  // column i of R
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipsoid3<Real>::Convert(Real const coeff[10], Matrix3x3<Real>& A,
    Vector3<Real>& B, Real& C)
{
    C = coeff[0];
    B[0] = coeff[1];
    B[1] = coeff[2];
    B[2] = coeff[3];
    A(0,0) = coeff[4];
    A(0,1) = ((Real)0.5) * coeff[5];
    A(0,2) = ((Real)0.5) * coeff[6];
    A(1,0) = A(0,1);
    A(1,1) = coeff[7];
    A(1,2) = ((Real)0.5) * coeff[8];
    A(2,0) = A(0,2);
    A(2,1) = A(1,2);
    A(2,2) = coeff[9];
}
//----------------------------------------------------------------------------
template <typename Real>
void Ellipsoid3<Real>::Convert(Matrix3x3<Real> const& A,
    Vector3<Real> const& B, Real C, Real coeff[10])
{
    coeff[0] = C;
    coeff[1] = B[0];
    coeff[2] = B[1];
    coeff[3] = B[2];
    coeff[4] = A(0,0);
    coeff[5] = ((Real)2) * A(0,1);
    coeff[6] = ((Real)2) * A(0,2);
    coeff[7] = A(1,1);
    coeff[8] = ((Real)2) * A(1,2);
    coeff[9] = A(2,2);
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipsoid3<Real>::IsEqualTo(Ellipsoid3 const& ellipsoid) const
{
    if (center != ellipsoid.center)
    {
        return false;
    }

    for (int i = 0; i < 3; ++i)
    {
        if (axis[i] != ellipsoid.axis[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (extent[i] != ellipsoid.extent[i])
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipsoid3<Real>::IsLessThan(Ellipsoid3 const& ellipsoid) const
{
    if (center < ellipsoid.center)
    {
        return true;
    }

    if (center > ellipsoid.center)
    {
        return false;
    }

    for (int i = 0; i < 3; ++i)
    {
        if (axis[i] < ellipsoid.axis[i])
        {
            return true;
        }
        if (axis[i] > ellipsoid.axis[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 3; ++i)
    {
        if (extent[i] < ellipsoid.extent[i])
        {
            return true;
        }
        if (extent[i] > ellipsoid.extent[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
