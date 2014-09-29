// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/11)

//----------------------------------------------------------------------------
template <typename Real>
BasisFunction<Real>::~BasisFunction()
{
    delete[] mKeys;
    for (int i = 0; i < 4; ++i)
    {
        Deallocate2<Real>(mValue[i]);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
BasisFunction<Real>::BasisFunction()
    :
    mNumControls(0),
    mDegree(0),
    mTMin((Real)0),
    mTMax((Real)0),
    mTLength((Real)0),
    mOpen(false),
    mUniform(false),
    mPeriodic(false),
    mConstructed(false),
    mNumKeys(0),
    mKeys(nullptr)
{
    for (int i = 0; i < 4; ++i)
    {
        mValue[i] = nullptr;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
BasisFunction<Real>::BasisFunction(BasisFunctionInput<Real> const& input)
    :
    mConstructed(false)
{
    Create(input);
}
//----------------------------------------------------------------------------
template <typename Real> inline
void BasisFunction<Real>::Create(BasisFunctionInput<Real> const& input)
{
    if (mConstructed)
    {
        LogError("Object already created.");
        return;
    }

    mNumControls = (input.periodic ? input.numControls + input.degree :
        input.numControls);
    mDegree = input.degree;
    mTMin = (Real)0;
    mTMax = (Real)0;
    mTLength = (Real)0;
    mOpen = false;
    mUniform = input.uniform;
    mPeriodic = input.periodic;
    for (int i = 0; i < 4; ++i)
    {
        mValue[i] = nullptr;
    }

    if (input.numControls < 2)
    {
        LogError("Invalid number of control points.");
        return;
    }

    if (input.degree < 1 || input.degree >= input.numControls)
    {
        LogError("Invalid degree.");
        return;
    }

    if (input.numUniqueKnots < 2)
    {
        LogError("Invalid number of unique knots.");
        return;
    }

    if (!input.uniqueKnots)
    {
        LogError("Invalid unique-knots pointer.");
        return;
    }

    mUniqueKnots.resize(input.numUniqueKnots);
    std::copy(input.uniqueKnots, input.uniqueKnots + input.numUniqueKnots,
        mUniqueKnots.begin());

    Real u = mUniqueKnots.front().t;
    for (int i = 1; i < input.numUniqueKnots - 1; ++i)
    {
        Real uNext = mUniqueKnots[i].t;
        if (u >= uNext)
        {
            LogError("Unique knots are not strictly increasing.");
            return;
        }
        u = uNext;
    }

    int mult0 = mUniqueKnots.front().multiplicity;
    if (mult0 < 1 || mult0 > mDegree + 1)
    {
        LogError("Invalid first multiplicity.");
        return;
    }

    int mult1 = mUniqueKnots.back().multiplicity;
    if (mult1 < 1 || mult1 > mDegree + 1)
    {
        LogError("Invalid last multiplicity.");
        return;
    }

    for (int i = 1; i <= input.numUniqueKnots - 2; ++i)
    {
        int mult = mUniqueKnots[i].multiplicity;
        if (mult < 1 || mult > mDegree)
        {
            LogError("Invalid interior multiplicity.");
            return;
        }
    }

    mOpen = (mult0 == mult1 && mult0 == mDegree + 1);

    mKnots.resize(mNumControls + mDegree + 1);
    mNumKeys = input.numUniqueKnots;
    mKeys = new std::pair<Real, int>[mNumKeys];
    int sum = 0;
    for (int i = 0, j = 0; i < input.numUniqueKnots; ++i)
    {
        Real tCommon = mUniqueKnots[i].t;
        int mult = mUniqueKnots[i].multiplicity;
        for (int k = 0; k < mult; ++k, ++j)
        {
            mKnots[j] = tCommon;
        }

        mKeys[i].first = tCommon;
        mKeys[i].second = sum - 1;
        sum += mult;
    }

    mTMin = mKnots[mDegree];
    mTMax = mKnots[mNumControls];
    mTLength = mTMax - mTMin;

    size_t numRows = mDegree + 1;
    size_t numCols = mNumControls + mDegree;
    size_t numBytes = numRows * numCols * sizeof(Real);
    for (int i = 0; i < 4; ++i)
    {
        mValue[i] = Allocate2<Real>(numCols, numRows);
        memset(mValue[i][0], 0, numBytes);
    }

    mConstructed = true;
}
//----------------------------------------------------------------------------
template <typename Real> inline
BasisFunction<Real>::operator bool() const
{
    return mConstructed;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int BasisFunction<Real>::GetNumControls() const
{
    return mNumControls;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int BasisFunction<Real>::GetDegree() const
{
    return mDegree;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int BasisFunction<Real>::GetNumUniqueKnots() const
{
    return static_cast<int>(mUniqueKnots.size());
}
//----------------------------------------------------------------------------
template <typename Real> inline
int BasisFunction<Real>::GetNumKnots() const
{
    return static_cast<int>(mKnots.size());
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real BasisFunction<Real>::GetMinDomain() const
{
    return mTMin;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real BasisFunction<Real>::GetMaxDomain() const
{
    return mTMax;
}
//----------------------------------------------------------------------------
template <typename Real> inline
bool BasisFunction<Real>::IsOpen() const
{
    return mOpen;
}
//----------------------------------------------------------------------------
template <typename Real> inline
bool BasisFunction<Real>::IsUniform() const
{
    return mUniform;
}
//----------------------------------------------------------------------------
template <typename Real> inline
bool BasisFunction<Real>::IsPeriodic() const
{
    return mPeriodic;
}
//----------------------------------------------------------------------------
template <typename Real> inline
UniqueKnot<Real> const* BasisFunction<Real>::GetUniqueKnots() const
{
    return &mUniqueKnots[0];
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real const* BasisFunction<Real>::GetKnots() const
{
    return &mKnots[0];
}
//----------------------------------------------------------------------------
template <typename Real>
void BasisFunction<Real>::Evaluate(Real t, unsigned int order, int& minIndex,
    int& maxIndex) const
{
    if (!mConstructed)
    {
        // Errors were already generated during construction.  Return an index
        // range that leads to zero-valued positions and derivatives.
        minIndex = -1;
        maxIndex = -1;
        return;
    }

    if (order > 3)
    {
        LogError("Only derivatives through order 3 are supported.");
        minIndex = 0;
        maxIndex = 0;
        return;
    }

    // Renaming for readability of code.
    Real** v[4] = { mValue[0], mValue[1], mValue[2], mValue[3] };

    int i = GetIndex(t);
    v[0][0][i] = (Real)1;

    if (order >= 1)
    {
        v[1][0][i] = (Real)0;
        if (order >= 2)
        {
            v[2][0][i] = (Real)0;
            if (order >= 3)
            {
                v[3][0][i] = (Real)0;
            }
        }
    }

    Real n0 = t - mKnots[i], n1 = mKnots[i + 1] - t;
    Real e0, e1, d0, d1, invD0, invD1;
    int j;
    for (j = 1; j <= mDegree; j++)
    {
        d0 = mKnots[i + j] - mKnots[i];
        d1 = mKnots[i + 1] - mKnots[i - j + 1];
        invD0 = (d0 > (Real)0 ? (Real)1 / d0 : (Real)0);
        invD1 = (d1 > (Real)0 ? (Real)1 / d1 : (Real)0);

        e0 = n0*v[0][j - 1][i];
        v[0][j][i] = e0*invD0;
        e1 = n1*v[0][j - 1][i - j + 1];
        v[0][j][i - j] = e1*invD1;

        if (order >= 1)
        {
            e0 = n0*v[1][j - 1][i] + v[0][j - 1][i];
            v[1][j][i] = e0*invD0;
            e1 = n1*v[1][j - 1][i - j + 1] - v[0][j - 1][i - j + 1];
            v[1][j][i - j] = e1*invD1;

            if (order >= 2)
            {
                e0 = n0*v[2][j - 1][i] + ((Real)2)*v[1][j - 1][i];
                v[2][j][i] = e0*invD0;
                e1 = n1*v[2][j - 1][i - j + 1] -
                    ((Real)2)*v[1][j - 1][i - j + 1];
                v[2][j][i - j] = e1*invD1;

                if (order >= 3)
                {
                    e0 = n0*v[3][j - 1][i] + ((Real)3)*v[2][j - 1][i];
                    v[3][j][i] = e0*invD0;
                    e1 = n1*v[3][j - 1][i - j + 1] -
                        ((Real)3)*v[2][j - 1][i - j + 1];
                    v[3][j][i - j] = e1*invD1;
                }
            }
        }
    }

    for (j = 2; j <= mDegree; ++j)
    {
        for (int k = i - j + 1; k < i; ++k)
        {
            n0 = t - mKnots[k];
            n1 = mKnots[k + j + 1] - t;
            d0 = mKnots[k + j] - mKnots[k];
            d1 = mKnots[k + j + 1] - mKnots[k + 1];
            invD0 = (d0 >(Real)0 ? (Real)1 / d0 : (Real)0);
            invD1 = (d1 > (Real)0 ? (Real)1 / d1 : (Real)0);

            e0 = n0*v[0][j - 1][k];
            e1 = n1*v[0][j - 1][k + 1];
            v[0][j][k] = e0*invD0 + e1*invD1;

            if (order >= 1)
            {
                e0 = n0*v[1][j - 1][k] + v[0][j - 1][k];
                e1 = n1*v[1][j - 1][k + 1] - v[0][j - 1][k + 1];
                v[1][j][k] = e0*invD0 + e1*invD1;

                if (order >= 2)
                {
                    e0 = n0*v[2][j - 1][k] + ((Real)2)*v[1][j - 1][k];
                    e1 = n1*v[2][j - 1][k + 1] -
                        ((Real)2)*v[1][j - 1][k + 1];
                    v[2][j][k] = e0*invD0 + e1*invD1;

                    if (order >= 3)
                    {
                        e0 = n0*v[3][j - 1][k] + ((Real)3)*v[2][j - 1][k];
                        e1 = n1*v[3][j - 1][k + 1] -
                            ((Real)3)*v[2][j - 1][k + 1];
                        v[3][j][k] = e0*invD0 + e1*invD1;
                    }
                }
            }
        }
    }

    minIndex = i - mDegree;
    maxIndex = i;
}
//----------------------------------------------------------------------------
template <typename Real>
Real BasisFunction<Real>::GetValue(unsigned int order, int i) const
{
    if (!mConstructed)
    {
        // Errors were already generated during construction.  Return a value
        // that leads to zero-valued positions and derivatives.
        return (Real)0;
    }

    if (order < 4)
    {
        if (0 <= i && i < mNumControls + mDegree)
        {
            return mValue[order][mDegree][i];
        }
    }

    LogError("Invalid input.");
    return (Real)0;
}
//----------------------------------------------------------------------------
template <typename Real>
int BasisFunction<Real>::GetIndex(Real& t) const
{
    // Find the index i for which knot[i] <= t < knot[i+1].
    if (mPeriodic)
    {
        // Wrap to [tmin,tmax].
        Real r = fmod(t - mTMin, mTLength);
        if (r < (Real)0)
        {
            r += mTLength;
        }
        t = mTMin + r;
    }

    // Clamp to [tmin,tmax].  For the periodic case, this handles small
    // numerical rounding errors near the domain endpoints.
    if (t <= mTMin)
    {
        t = mTMin;
        return mDegree;
    }
    if (t >= mTMax)
    {
        t = mTMax;
        return mNumControls - 1;
    }

    // At this point, tmin < t < tmax.
    for (int i = 0; i < mNumKeys; ++i)
    {
        if (t < mKeys[i].first)
        {
            return mKeys[i].second;
        }
    }

    // We should not reach this code.
    LogError("Unexpected condition.");
    t = mTMin;
    return mDegree;
}
//----------------------------------------------------------------------------
