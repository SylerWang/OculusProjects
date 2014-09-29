// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
MinimizeN<Real>::MinimizeN(int dimensions,
    std::function<Real(Real const*)> const& F, int maxLevel, int maxBracket,
    int maxIterations)
    :
    mDimensions(dimensions),
    mFunction(F),
    mMaxIterations(maxIterations),
    mDirections(dimensions + 1),
    mDConjIndex(dimensions),
    mDCurrIndex(0),
    mTCurr(dimensions),
    mTSave(dimensions),
    mMinimizer(
        [this](Real t)
        {
            return mFunction(&(mTCurr + t*mDirections[mDCurrIndex])[0]);
        },
        maxLevel, maxBracket)
{
    for (auto& direction : mDirections)
    {
        direction.SetSize(dimensions);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void MinimizeN<Real>::GetMinimum(Real const* t0, Real const* t1,
    Real const* tInitial, Real* tMin, Real& fMin)
{
    // The initial guess.
    size_t numBytes = mDimensions*sizeof(Real);
    mFCurr = mFunction(tInitial);
#ifdef WIN32
    memcpy_s(&mTSave[0], numBytes, tInitial, numBytes);
    memcpy_s(&mTCurr[0], numBytes, tInitial, numBytes);
#else
    memcpy(&mTSave[0], tInitial, numBytes);
    memcpy(&mTCurr[0], tInitial, numBytes);
#endif

    // Initialize the direction set to the standard Euclidean basis.
    for (int i = 0; i < mDimensions; ++i)
    {
        mDirections[i].MakeUnit(i);
    }

    Real ell0, ell1, ellMin;
    for (int iter = 0; iter < mMaxIterations; ++iter)
    {
        // Find minimum in each direction and update current location.
        for (int i = 0; i < mDimensions; ++i)
        {
            mDCurrIndex = i;
            ComputeDomain(t0, t1, ell0, ell1);
            mMinimizer.GetMinimum(ell0, ell1, (Real)0, ellMin, mFCurr);
            mTCurr += ellMin*mDirections[i];
        }

        // Estimate a unit-length conjugate direction.  TODO: Expose
        // epsilon to the caller.
        mDirections[mDConjIndex] = mTCurr - mTSave;
        Real length = Length(mDirections[mDConjIndex]);
        Real const epsilon = (Real)1e-06;
        if (length < epsilon)
        {
            // New position did not change significantly from old one.
            // Should there be a better convergence criterion here?
            break;
        }

        mDirections[mDConjIndex] /= length;

        // Minimize in conjugate direction.
        mDCurrIndex = mDConjIndex;
        ComputeDomain(t0, t1, ell0, ell1);
        mMinimizer.GetMinimum(ell0, ell1, (Real)0, ellMin, mFCurr);
        mTCurr += ellMin*mDirections[mDCurrIndex];

        // Cycle the directions and add conjugate direction to set.
        mDConjIndex = 0;
        for (int i = 0; i < mDimensions; ++i)
        {
            mDirections[i] = mDirections[i+1];
        }

        // Set parameters for next pass.
        mTSave = mTCurr;
    }

#ifdef WIN32
    memcpy_s(tMin, numBytes, &mTCurr[0], numBytes);
#else
    memcpy(tMin, &mTCurr[0], numBytes);
#endif
    fMin = mFCurr;
}
//----------------------------------------------------------------------------
template <typename Real>
void MinimizeN<Real>::ComputeDomain(Real const* t0, Real const* t1,
    Real& ell0, Real& ell1)
{
    ell0 = -std::numeric_limits<Real>::max();
    ell1 = +std::numeric_limits<Real>::max();

    for (int i = 0; i < mDimensions; ++i)
    {
        Real value = mDirections[mDCurrIndex][i];
        if (value != (Real)0)
        {
            Real b0 = t0[i] - mTCurr[i];
            Real b1 = t1[i] - mTCurr[i];
            Real inv = ((Real)1) / value;
            if (value > (Real)0)
            {
                // The valid t-interval is [b0,b1].
                b0 *= inv;
                if (b0 > ell0)
                {
                    ell0 = b0;
                }
                b1 *= inv;
                if (b1 < ell1)
                {
                    ell1 = b1;
                }
            }
            else
            {
                // The valid t-interval is [b1,b0].
                b0 *= inv;
                if (b0 < ell1)
                {
                    ell1 = b0;
                }
                b1 *= inv;
                if (b1 > ell0)
                {
                    ell0 = b1;
                }
            }
        }
    }

    // Correction if numerical errors lead to values nearly zero.
    if (ell0 > (Real)0)
    {
        ell0 = (Real)0;
    }
    if (ell1 < (Real)0)
    {
        ell1 = (Real)0;
    }
}
//----------------------------------------------------------------------------
