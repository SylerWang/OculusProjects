// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/22)

#pragma once

#include <functional>

// Compute a root of a function F(t) on an interval [t0, t1].  The caller
// specifies the maximum number of iterations, in case you want limited
// accuracy for the root.  However, the function is designed for native types
// (Real = float/double).  If you specify a sufficiently large number of
// iterations, the root finder bisects until either F(t) is identically zero
// [a condition dependent on how you structure F(t) for evaluation] or the
// midpoint (t0 + t1)/2 rounds numerically to tmin or tmax.  Of course, it
// is required that t0 < t1.  The return value Find is the number of
// iterations actually used:  1 if an endpoint is the root, 2 or larger
// if a root is found using bisection, or 0 if invalid t0 and t1 are
// passed in or if F(t0)*F(t1) > 0 (no guaranteed root on the interval).

namespace gte
{

template <typename Real>
class RootsBisection
{
public:
    // It is necessary that F(t0)*F(t1) <= 0, in which case the function
    // returns a positive value and the 'root' is valid; otherwise, the
    // function returns 0 and 'root' is invalid (do not use it).  When
    // F(t0)*F(t1) > 0, the interval may very well contain a root but we
    // cannot know that, so 0 is returned.  The function also returns 0
    // when t0 >= t1.

    static unsigned int Find(std::function<Real(Real)> const& F, Real t0,
        Real t1,  unsigned int maxIterations, Real& root);

    // If f0 = F(t0) and f1 = F(t1) are already known, pass them to the
    // bisector.  This is useful when |f0| or |f1| is infinite, and you can
    // pass sign(f0) or sign(f1) rather than then infinity because the
    // bisector cares only about the signs of f.

    static unsigned int Find(std::function<Real(Real)> const& F, Real t0,
        Real t1, Real f0, Real f1, unsigned int maxIterations, Real& root);
};

#include "GteRootsBisection.inl"

}
