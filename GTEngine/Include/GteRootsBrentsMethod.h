// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include <cmath>
#include <functional>

// This is an implementation of Brent's Method for computing a root of a
// function on an interval [t0,t1] for which F(t0)*F(t1) < 0.  The method
// uses inverse quadratic interpolation to generate a root estimate but
// falls back to inverse linear interpolation (secant method) if
// necessary.  Moreover, based on previous iterates, the method will fall
// back to bisection when it appears the interpolated estimate is not of
// sufficient quality.
//
//   maxIterations:
//       The maximum number of iterations used to locate a root.  This
//       should be positive.
//   negFTolerance, posFTolerance:
//       The root estimate t is accepted when the function value F(t)
//       satisfies negFTolerance <= F(t) <= posFTolerance.  The values
//       must satisfy:  negFTolerance <= 0, posFTolerance >= 0.
//   stepTTolerance:
//       Brent's Method requires additional tests before an interpolated
//       t-value is accepted as the next root estimate.  One of these
//       tests compares the difference of consecutive iterates and
//       requires it to be larger than a user-specified t-tolerance (to
//       ensure progress is made).  This parameter is that tolerance
//       and should be nonnegative.
//   convTTolerance:
//       The root search is allowed to terminate when the current
//       subinterval [tsub0,tsub1] is sufficiently small, say,
//       |tsub1 - tsub0| <= tolerance.  This parameter is that tolerance
//       and should be nonnegative.

namespace gte
{

template <typename Real>
class RootsBrentsMethod
{
public:
    // It is necessary that F(t0)*F(t1) <= 0, in which case the function
    // returns 'true' and the 'root' is valid; otherwise, the function returns
    // 'false' and 'root' is invalid (do not use it).  When F(t0)*F(t1) > 0,
    // the interval may very well contain a root but we cannot know that.  The
    // function also returns 'false' if t0 >= t1.

    static bool Find(std::function<Real(Real)> const& F, Real t0, Real t1,
        unsigned int maxIterations, Real negFTolerance, Real posFTolerance,
        Real stepTTolerance, Real convTTolerance, Real& root);
};

#include "GteRootsBrentsMethod.inl"

}
