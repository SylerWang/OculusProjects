// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/15)

//----------------------------------------------------------------------------
template <int N, typename Real>
ParametricCurve<N, Real>::ParametricCurve(Real tmin, Real tmax)
    :
    mTime(2),
    mSegmentLength(1),
    mAccumulatedLength(1),
    mRombergOrder(DEFAULT_ROMBERG_ORDER),
    mMaxBisections(DEFAULT_MAX_BISECTIONS),
    mConstructed(false)
{
    mTime[0] = tmin;
    mTime[1] = tmax;
    mSegmentLength[0] = (Real)0;
    mAccumulatedLength[0] = (Real)0;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
ParametricCurve<N, Real>::ParametricCurve(int numSegments, Real const* times)
    :
    mTime(numSegments + 1),
    mSegmentLength(numSegments),
    mAccumulatedLength(numSegments),
    mRombergOrder(DEFAULT_ROMBERG_ORDER),
    mMaxBisections(DEFAULT_MAX_BISECTIONS),
    mConstructed(false)
{
    std::copy(times, times + numSegments + 1, mTime.begin());
    mSegmentLength[0] = (Real)0;
    mAccumulatedLength[0] = (Real)0;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
ParametricCurve<N, Real>::~ParametricCurve()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
ParametricCurve<N, Real>::operator bool() const
{
    return mConstructed;
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real ParametricCurve<N, Real>::GetTMin() const
{
    return mTime.front();
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real ParametricCurve<N, Real>::GetTMax() const
{
    return mTime.back();
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
int ParametricCurve<N, Real>::GetNumSegments() const
{
    return static_cast<int>(mSegmentLength.size());
}
//----------------------------------------------------------------------------
template <int N, typename Real> inline
Real const* ParametricCurve<N, Real>::GetTimes() const
{
    return &mTime[0];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void ParametricCurve<N, Real>::SetRombergOrder(int order)
{
    mRombergOrder = std::max(order, 1);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void ParametricCurve<N, Real>::SetMaxBisections(unsigned int maxBisections)
{
    mMaxBisections = std::max(maxBisections, 1u);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> ParametricCurve<N, Real>::GetPosition(Real t) const
{
    Vector<N, Real> values[4];
    Evaluate(t, 0, values);
    return values[0];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> ParametricCurve<N, Real>::GetTangent(Real t) const
{
    Vector<N, Real> values[4];
    Evaluate(t, 1, values);
    Normalize(values[1]);
    return values[1];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real ParametricCurve<N, Real>::GetSpeed(Real t) const
{
    Vector<N, Real> values[4];
    Evaluate(t, 1, values);
    return Length(values[1]);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real ParametricCurve<N, Real>::GetLength(Real t0, Real t1) const
{
    std::function<Real(Real)> speed = [this](Real t)
    {
        return GetSpeed(t);
    };

    if (mSegmentLength[0] == (Real)0)
    {
        // Lazy initialization of lengths of segments.
        int const numSegments = static_cast<int>(mSegmentLength.size());
        Real accumulated = (Real)0;
        for (int i = 0; i < numSegments; ++i)
        {
            mSegmentLength[i] = Integration<Real>::Romberg(mRombergOrder,
                mTime[i], mTime[i + 1], speed);
            accumulated += mSegmentLength[i];
            mAccumulatedLength[i] = accumulated;
        }
    }

    t0 = std::max(t0, GetTMin());
    t1 = std::min(t1, GetTMax());
    auto iter0 = std::lower_bound(mTime.begin(), mTime.end(), t0);
    int index0 = static_cast<int>(iter0 - mTime.begin());
    auto iter1 = std::lower_bound(mTime.begin(), mTime.end(), t1);
    int index1 = static_cast<int>(iter1 - mTime.begin());

    Real length;
    if (index0 < index1)
    {
        length = (Real)0;
        if (t0 < *iter0)
        {
            length += Integration<Real>::Romberg(mRombergOrder, t0,
                mTime[index0], speed);
        }

        int isup;
        if (t1 < *iter1)
        {
            length += Integration<Real>::Romberg(mRombergOrder,
                mTime[index1 - 1], t1, speed);
            isup = index1 - 1;
        }
        else
        {
            isup = index1;
        }
        for (int i = index0; i < isup; ++i)
        {
            length += mSegmentLength[i];
        }
    }
    else
    {
        length = Integration<Real>::Romberg(mRombergOrder, t0, t1, speed);
    }
    return length;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real ParametricCurve<N, Real>::GetTotalLength() const
{
    if (mAccumulatedLength.back() == (Real)0)
    {
        // Lazy evaluation of the accumulated length array.
        return GetLength(mTime.front(), mTime.back());
    }

    return mAccumulatedLength.back();
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real ParametricCurve<N, Real>::GetTime(Real length) const
{
    if (length > (Real)0)
    {
        if (length < GetTotalLength())
        {
            std::function<Real(Real)> F = [this, &length](Real t)
            {
                return Integration<Real>::Romberg(mRombergOrder,
                    mTime.front(), t, [this](Real z){ return GetSpeed(z); })
                    - length;
            };

            // We know that F(tmin) < 0 and F(tmax) > 0, which allows us to
            // use bisection.  Rather than bisect the entire interval, let's
            // narrow it down with a reasonable initial guess.
            Real ratio = length / GetTotalLength();
            Real omratio = (Real)1 - ratio;
            Real tmid = omratio * mTime.front() + ratio * mTime.back();
            Real fmid = F(tmid);
            if (fmid > (Real)0)
            {
                RootsBisection<Real>::Find(F, mTime.front(), tmid, (Real)-1,
                    (Real)1, mMaxBisections, tmid);
            }
            else if (fmid < (Real)0)
            {
                RootsBisection<Real>::Find(F, tmid, mTime.back(), (Real)-1,
                    (Real)1, mMaxBisections, tmid);
            }
            return tmid;
        }
        else
        {
            return mTime.back();
        }
    }
    else
    {
        return mTime.front();
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void ParametricCurve<N, Real>::SubdivideByTime(int numPoints,
    Vector<N, Real>* points) const
{
    Real delta = (mTime.back() - mTime.front()) / (Real)(numPoints - 1);
    for (int i = 0; i < numPoints; ++i)
    {
        Real t = mTime.front() + delta * i;
        points[i] = GetPosition(t);
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void ParametricCurve<N, Real>::SubdivideByLength(int numPoints,
    Vector<N, Real>* points) const
{
    Real delta = GetTotalLength() / (Real)(numPoints - 1);
    for (int i = 0; i < numPoints; ++i)
    {
        Real length = delta * i;
        Real t = GetTime(length);
        points[i] = GetPosition(t);
    }
}
//----------------------------------------------------------------------------
