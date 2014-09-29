// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.3 (2014/09/17)

#pragma once

#include "GteLogger.h"
#include "GteMemory.h"
#include <cmath>
#include <cstring>
#include <vector>

namespace gte
{

template <typename Real>
struct UniqueKnot
{
    Real t;
    int multiplicity;
};

template <typename Real>
struct BasisFunctionInput
{
    int numControls;
    int degree;
    bool uniform;
    bool periodic;
    int numUniqueKnots;
    UniqueKnot<Real>* uniqueKnots;
};

template <typename Real>
class BasisFunction
{
public:
    // Let n be the number of control points. Let d be the degree, where
    // 1 <= d <= n-1.  The number of knots is k = n + d + 1.  The knots are
    // t[i] for 0 <= i < k and must be nondecreasing, t[i] <= t[i+1], but a
    // knot value can be repeated.  Let s be the number of distinct knots.
    // Let the distinct knots be u[j] for 0 <= j < s, so u[j] < u[j+1] for
    // all j.  The set of u[j] is called a 'breakpoint sequence'.  Let
    // m[j] >= 1 be the multiplicity; that is, if t[i] is the first occurrence
    // of u[j], then t[i+r] = t[i] for 1 <= r < m[j].  The multiplicities have
    // the constraints m[0] <= d+1, m[s-1] <= d+1, and m[j] <= d for
    // 1 <= j <= s-2.  Also, k = sum_{j=0}^{s-1} m[j], which says the
    // multiplicities account for all k knots.
    //
    // Given a knot vector (t[0],...,t[n+d]), the domain of the corresponding
    // B-spline curve is the interval [t[d],t[n]].
    //
    // The corresponding B-spline or NURBS curve is characterized as follows.
    // See "Geometric Modeling with Splines: An Introduction" by Elaine Cohen,
    // Richard F. Riesenfeld, and Gershon Elber, AK Peters, 2001, Natick MA.
    // The curve is 'open' when m[0] = m[s-1] = d+1; otherwise, it is
    // 'floating'.  An open curve is uniform when the knots t[d] through
    // t[n] are equally spaced; that is, t[i+1] - t[i] are a common value
    // for d <= i <= n-1.  By implication, s = n-d-1 and m[j] = 1 for
    // 1 <= j <= s-2.  An open curve that does not satisfy these conditions
    // is said to be nonuniform.  The aforementioned book does not define
    // subclasses of 'floating' curves, but it is convenient to have a finer
    // classification.  Let us say that a floating curve is uniform when
    // m[j] = 1 for 0 <= j <= s-1 and t[i+1] - t[i] are a common value for
    // 0 <= i <= k-2; otherwise, the floating curve is nonuniform.
    //
    // A special case of a floating curve is a periodic curve.  The intent
    // is that the curve is closed, so the first and last control points
    // should be the same, which ensures C^{0} continuity.  Higher-order
    // continuity is obtained by repeating more control points.  If the
    // control points are P[0] through P[n-1], append the points P[0]
    // through P[d-1] to ensure C^{d-1} continuity.  Additionally the knots
    // must be chosen properly.  You may choose t[d] through t[n] as you
    // wish.  The other knots are defined by
    //   t[i] - t[i-1] = t[n-d+i] - t[n-d+i-1]
    //   t[n+i] - t[n+i-1] = t[d+i] - t[d+i-1]
    // for 1 <= i <= d.

    // Construction and destruction.  The determination that the curve is
    // open or floating is based on the multiplicities.  The 'uniform' input
    // is used to avoid misclassifications due to floating-point rounding
    // errors.  Specifically, the breakpoints might be equally spaced
    // (uniform) as real numbers, but the floating-point representations can
    // have rounding errors that cause the knot differences not to be exactly
    // the same constant.  A periodic curve can have uniform or nonuniform
    // knots.  This object makes copies of the input arrays.

    ~BasisFunction();
    BasisFunction();
    BasisFunction(BasisFunctionInput<Real> const& input);

    // Support for explicit creation in classes that have std::array
    // members involving BasisFunction.  This is a call-once function.
    void Create(BasisFunctionInput<Real> const& input);

    // The inputs have complicated validation tests.  You should create a
    // BasisFunction object as shown:
    //     BasisFunction<Real> function(parameters);
    //     if (!function) { <constructor failed, respond accordingly>; }
    inline operator bool() const;

    // Member access.
    inline int GetNumControls() const;
    inline int GetDegree() const;
    inline int GetNumUniqueKnots() const;
    inline int GetNumKnots() const;
    inline Real GetMinDomain() const;
    inline Real GetMaxDomain() const;
    inline bool IsOpen() const;
    inline bool IsUniform() const;
    inline bool IsPeriodic() const;
    inline UniqueKnot<Real> const* GetUniqueKnots() const;
    inline Real const* GetKnots() const;

    // Evaluation of the basis function and its derivatives through order 3.
    // For the function value only, pass order 0.  For the function and first
    // derivative, pass order 1, and so on.
    void Evaluate(Real t, unsigned int order, int& minIndex, int& maxIndex)
        const;

    // Access the results of the call to Evaluate(...).  The index i must
    // satisfy minIndex <= i <= maxIndex.  If it is not, the function returns
    // zero.  The separation of evaluation and access is based on local
    // control of the basis function; that is, only the accessible values are
    // (potentially) not zero.
    Real GetValue(unsigned int order, int i) const;

private:
    BasisFunction(BasisFunction const&) {}
    BasisFunction& operator=(BasisFunction const&) { return *this; }

    // Determine the index i for which knot[i] <= t < knot[i+1].  The t-value
    // is modified (wrapped for periodic splines, clamped for nonperiodic
    // splines).
    int GetIndex(Real& t) const;

    // Constructor inputs and values derived from them.
    int mNumControls;
    int mDegree;
    Real mTMin, mTMax, mTLength;
    bool mOpen;
    bool mUniform;
    bool mPeriodic;
    bool mConstructed;
    std::vector<UniqueKnot<Real>> mUniqueKnots;
    std::vector<Real> mKnots;

    // Lookup information for the GetIndex() function.  The first element of
    // the pair is a unique knot value.  The second element is the index in
    // mKnots[] for the last occurrence of that knot value.  NOTE:  This is
    // a heavily used function during Evaluate calls.  This member was
    // initially set to be std::vector<*>, but in debug mode the range-based
    // for-loop in GetIndex was taking an extremely long time due to checked
    // calls involving iterators.  We modified this to a regular array to
    // ensure that debug performance is better.
    int mNumKeys;
    std::pair<Real, int>* mKeys;

    // Storage for the basis functions and their first three derivatives.
    mutable Real** mValue[4];  // mValue[i] is array[d+1][n+d]
};

#include "GteBasisFunction.inl"

}
