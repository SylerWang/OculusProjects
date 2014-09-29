// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
ApprPolynomial2<Real>::ApprPolynomial2(int degree)
    :
    mDegree(degree),
    mSize(degree + 1),
    mParameters(mSize)
{
    mXDomain[0] = std::numeric_limits<Real>::max();
    mXDomain[1] = -mXDomain[0];
    std::fill(mParameters.begin(), mParameters.end(), (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
int ApprPolynomial2<Real>::GetMinimumRequired() const
{
    return mSize;
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprPolynomial2<Real>::Fit(
    std::vector<std::array<Real, 2>> const& observations,
    std::vector<int> const& indices)
{
    if (indices.size() > 0)
    {
        int s, i0, i1;

        // Compute the powers of x.
        int numSamples = static_cast<int>(indices.size());
        int twoDegree = 2 * mDegree;
        Real** xPower = Allocate2<Real>(twoDegree + 1, numSamples);
        for (s = 0; s < numSamples; ++s)
        {
            Real x = observations[indices[s]][0];
            mXDomain[0] = std::min(x, mXDomain[0]);
            mXDomain[1] = std::max(x, mXDomain[1]);

            xPower[s][0] = (Real)1;
            for (i0 = 1; i0 <= twoDegree; ++i0)
            {
                xPower[s][i0] = x * xPower[s][i0 - 1];
            }
        }

        // Matrix A is the Vandermonde matrix and vector B is the right-hand
        // side of the linear system A*X = B.
        GMatrix<Real> A(mSize, mSize);
        GVector<Real> B(mSize);
        for (i0 = 0; i0 <= mDegree; ++i0)
        {
            Real sum = (Real)0;
            for (s = 0; s < numSamples; ++s)
            {
                Real w = observations[indices[s]][1];
                sum += w * xPower[s][i0];
            }

            B[i0] = sum;

            for (i1 = 0; i1 <= mDegree; ++i1)
            {
                sum = (Real)0;
                for (s = 0; s < numSamples; ++s)
                {
                    sum += xPower[s][i0 + i1];
                }

                A(i0, i1) = sum;
            }
        }

        // Solve for the polynomial coefficients.
        GVector<Real> coefficients = Inverse(A) * B;
        bool hasNonzero = false;
        for (int i = 0; i < mSize; ++i)
        {
            mParameters[i] = coefficients[i];
            if (coefficients[i] != (Real)0)
            {
                hasNonzero = true;
            }
        }
        Deallocate2<Real>(xPower);
        return hasNonzero;

    }

    std::fill(mParameters.begin(), mParameters.end(), (Real)0);
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprPolynomial2<Real>::Error(std::array<Real, 2> const& observation)
    const
{
    Real w = Evaluate(observation[0]);
    Real error = std::abs(w - observation[1]);
    return error;
}
//----------------------------------------------------------------------------
template <typename Real>
std::vector<Real> const& ApprPolynomial2<Real>::GetParameters() const
{
    return mParameters;
}
//----------------------------------------------------------------------------
template <typename Real>
std::array<Real, 2> const& ApprPolynomial2<Real>::GetXDomain() const
{
    return mXDomain;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprPolynomial2<Real>::Evaluate(Real x) const
{
    int i = mDegree;
    Real w = mParameters[i];
    while (--i >= 0)
    {
        w = mParameters[i] + w * x;
    }
    return w;
}
//----------------------------------------------------------------------------
