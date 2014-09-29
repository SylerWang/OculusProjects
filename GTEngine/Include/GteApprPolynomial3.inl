// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
ApprPolynomial3<Real>::ApprPolynomial3(int xDegree, int yDegree)
    :
    mXDegree(xDegree),
    mYDegree(yDegree),
    mXDegreeP1(xDegree + 1),
    mYDegreeP1(yDegree + 1),
    mSize(mXDegreeP1 * mYDegreeP1),
    mParameters(mSize),
    mYCoefficient(mYDegreeP1)
{
    mXDomain[0] = std::numeric_limits<Real>::max();
    mXDomain[1] = -mXDomain[0];
    mYDomain[0] = std::numeric_limits<Real>::max();
    mYDomain[1] = -mYDomain[0];
    std::fill(mParameters.begin(), mParameters.end(), (Real)0);
    std::fill(mYCoefficient.begin(), mYCoefficient.end(), (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
int ApprPolynomial3<Real>::GetMinimumRequired() const
{
    return mSize;
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprPolynomial3<Real>::Fit(
    std::vector<std::array<Real, 3>> const& observations,
    std::vector<int> const& indices)
{
    if (indices.size() > 0)
    {
        int s, i0, j0, k0, i1, j1, k1;

        // Compute the powers of x and y.
        int numSamples = static_cast<int>(indices.size());
        int twoXDegree = 2 * mXDegree;
        int twoYDegree = 2 * mYDegree;
        Real** xPower = Allocate2<Real>(twoXDegree + 1, numSamples);
        Real** yPower = Allocate2<Real>(twoYDegree + 1, numSamples);
        for (s = 0; s < numSamples; ++s)
        {
            Real x = observations[indices[s]][0];
            Real y = observations[indices[s]][1];
            mXDomain[0] = std::min(x, mXDomain[0]);
            mXDomain[1] = std::max(x, mXDomain[1]);
            mYDomain[0] = std::min(y, mYDomain[0]);
            mYDomain[1] = std::max(y, mYDomain[1]);

            xPower[s][0] = (Real)1;
            for (i0 = 1; i0 <= twoXDegree; ++i0)
            {
                xPower[s][i0] = x * xPower[s][i0 - 1];
            }

            yPower[s][0] = (Real)1;
            for (j0 = 1; j0 <= twoYDegree; ++j0)
            {
                yPower[s][j0] = y * yPower[s][j0 - 1];
            }
        }

        // Matrix A is the Vandermonde matrix and vector B is the right-hand
        // side of the linear system A*X = B.
        GMatrix<Real> A(mSize, mSize);
        GVector<Real> B(mSize);
        for (j0 = 0; j0 <= mYDegree; ++j0)
        {
            for (i0 = 0; i0 <= mXDegree; ++i0)
            {
                Real sum = (Real)0;
                k0 = i0 + mXDegreeP1 * j0;
                for (s = 0; s < numSamples; ++s)
                {
                    Real w = observations[indices[s]][2];
                    sum += w * xPower[s][i0] * yPower[s][j0];
                }

                B[k0] = sum;

                for (j1 = 0; j1 <= mYDegree; ++j1)
                {
                    for (i1 = 0; i1 <= mXDegree; ++i1)
                    {
                        sum = (Real)0;
                        k1 = i1 + mXDegreeP1 * j1;
                        for (s = 0; s < numSamples; ++s)
                        {
                            sum += xPower[s][i0 + i1] * yPower[s][j0 + j1];
                        }

                        A(k0, k1) = sum;
                    }
                }
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
        Deallocate2<Real>(yPower);
        return hasNonzero;
    }

    std::fill(mParameters.begin(), mParameters.end(), (Real)0);
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprPolynomial3<Real>::Error(std::array<Real, 3> const& observation)
    const
{
    Real w = Evaluate(observation[0], observation[1]);
    Real error = std::abs(w - observation[2]);
    return error;
}
//----------------------------------------------------------------------------
template <typename Real>
std::vector<Real> const& ApprPolynomial3<Real>::GetParameters() const
{
    return mParameters;
}
//----------------------------------------------------------------------------
template <typename Real>
std::array<Real, 2> const& ApprPolynomial3<Real>::GetXDomain() const
{
    return mXDomain;
}
//----------------------------------------------------------------------------
template <typename Real>
std::array<Real, 2> const& ApprPolynomial3<Real>::GetYDomain() const
{
    return mYDomain;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprPolynomial3<Real>::Evaluate(Real x, Real y) const
{
    int i0, i1;
    Real w;

    for (i1 = 0; i1 <= mYDegree; ++i1)
    {
        i0 = mXDegree;
        w = mParameters[i0 + mXDegreeP1 * i1];
        while (--i0 >= 0)
        {
            w = mParameters[i0 + mXDegreeP1 * i1] + w * x;
        }
        mYCoefficient[i1] = w;
    }

    i1 = mYDegree;
    w = mYCoefficient[i1];
    while (--i1 >= 0)
    {
        w = mYCoefficient[i1] + w * y;
    }

    return w;
}
//----------------------------------------------------------------------------
