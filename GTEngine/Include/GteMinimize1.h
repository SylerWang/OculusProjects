// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteLogger.h"
#include <cmath>
#include <functional>

// The interval [t0,t1] provided to GetMinimum(Real,Real,Real,Real&,Real&)
// is processed by examining subintervals.  On each subinteral [a,b], the
// values f0 = F(a), f1 = F((a+b)/2), and f2 = F(b) are examined.  If
// {f0,f1,f2} is monotonic, then [a,b] is subdivided and processed.  The
// maximum depth of the recursion is limited by 'maxLevel'.  If {f0,f1,f2}
// is not monotonic, then two cases arise.  First, if f1 = min{f0,f1,f2},
// then {f0,f1,f2} is said to "bracket a minimum" and GetBracketedMinimum(*)
// is called to locate the function minimum.  The process uses a form of
// bisection called "parabolic interpolation" and the maximum number of
// bisection steps is 'maxBracket'.  Second, if f1 = max{f0,f1,f2}, then
// {f0,f1,f2} brackets a maximum.  The minimum search continues recursively
// as before on [a,(a+b)/2] and [(a+b)/2,b].

namespace gte
{

template <typename Real>
class Minimize1
{
public:
    // Construction.
    Minimize1(std::function<Real(Real)> const& F, int maxLevel,
        int maxBracket);

    // Search for a minimum of 'function' on the interval [t0,t1] using an
    // initial guess of 'tInitial'.  The location of the minimum is 'tMin' and
    // the value of the minimum is 'fMin'.
    void GetMinimum(Real t0, Real t1, Real tInitial, Real& tMin, Real& fMin);

private:
    // This is called to start the search on [t0,tInitial] and [tInitial,t1].
    void GetMinimum(Real t0, Real f0, Real t1, Real f1, int level);

    // This is called recursively to search [a,(a+b)/2] and [(a+b)/2,b].
    void GetMinimum(Real t0, Real f0, Real tm, Real fm, Real t1, Real f1,
        int level);

    // This is called when {f0,f1,f2} brackets a minimum.
    void GetBracketedMinimum(Real t0, Real f0, Real tm, Real fm, Real t1,
        Real f1, int level);

    std::function<Real(Real)> mFunction;
    int mMaxLevel;
    int mMaxBracket;
    Real mTMin, mFMin;
};

#include "GteMinimize1.inl"

}
