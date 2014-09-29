// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
bool RootsBrentsMethod<Real>::Find(std::function<Real(Real)> const& F,
    Real t0, Real t1, unsigned int maxIterations, Real negFTolerance,
    Real posFTolerance, Real stepTTolerance, Real convTTolerance, Real& root)
{
    // Parameter validation.
    if (t1 <= t0
        || maxIterations == 0
        || negFTolerance > (Real)0
        || posFTolerance < (Real)0
        || stepTTolerance < (Real)0
        || convTTolerance < (Real)0)
    {
        // The input is invalid.
        return false;
    }

    Real f0 = F(t0);
    if (negFTolerance <= f0 && f0 <= posFTolerance)
    {
        // This endpoint is an approximate root that satisfies the function
        // tolerance.
        root = t0;
        return true;
    }

    Real f1 = F(t1);
    if (negFTolerance <= f1 && f1 <= posFTolerance)
    {
        // This endpoint is an approximate root that satisfies the function
        // tolerance.
        root = t1;
        return true;
    }

    if (f0*f1 > (Real)0)
    {
        // The input interval must bound a root.
        return false;
    }

    if (std::abs(f0) < std::abs(f1))
    {
        // Swap t0 and t1 so that |F(t1)| <= |F(t0)|.  The number t1 is
        // considered to be the best estimate of the root.
        std::swap(t0, t1);
        std::swap(f0, f1);
    }

    // Initialize values for the root search.
    Real t2 = t0, t3 = t0, f2 = f0;
    bool prevBisected = true;

    // The root search.
    for (unsigned int i = 0; i < maxIterations; ++i)
    {
        Real fDiff01 = f0 - f1, fDiff02 = f0 - f2, fDiff12 = f1 - f2;
        Real invFDiff01 = ((Real)1) / fDiff01;
        Real s;
        if (fDiff02 != (Real)0 && fDiff12 != (Real)0)
        {
            // Use inverse quadratic interpolation.
            Real infFDiff02 = ((Real)1) / fDiff02;
            Real invFDiff12 = ((Real)1) / fDiff12;
            s =
                t0 * f1 * f2 * invFDiff01 * infFDiff02 -
                t1 * f0 * f2 * invFDiff01 * invFDiff12 +
                t2 * f0 * f1 * infFDiff02 * invFDiff12;
        }
        else
        {
            // Use inverse linear interpolation (secant method).
            s = (t1 * f0 - t0 * f1) * invFDiff01;
        }

        // Compute values need in the accept-or-reject tests.
        Real tDiffSAvr = s - ((Real)0.75) * t0 - ((Real)0.25) * t1;
        Real tDiffS1 = s - t1;
        Real absTDiffS1 = std::abs(tDiffS1);
        Real absTDiff12 = std::abs(t1 - t2);
        Real absTDiff23 = std::abs(t2 - t3);

        bool currBisected = false;
        if (tDiffSAvr * tDiffS1 > (Real)0)
        {
            // The value s is not between 0.75*t0 + 0.25*t1 and t1.  NOTE:
            // The algorithm sometimes has t0 < t1 but sometimes t1 < t0, so
            // the between-ness test does not use simple comparisons.
            currBisected = true;
        }
        else if (prevBisected)
        {
            // The first of Brent's tests to determine whether to accept the
            // interpolated s-value.
            currBisected =
                (absTDiffS1 >= ((Real)0.5) * absTDiff12) ||
                (absTDiff12 <= stepTTolerance);
        }
        else
        {
            // The second of Brent's tests to determine whether to accept the
            // interpolated s-value.
            currBisected =
                (absTDiffS1 >= ((Real)0.5) * absTDiff23) ||
                (absTDiff23 <= stepTTolerance);
        }

        if (currBisected)
        {
            // One of the additional tests failed, so reject the interpolated
            // s-value and use bisection instead.
            s = ((Real)0.5) * (t0 + t1);
            if (s == t0 || s == t1)
            {
                // The numbers t0 and t1 are consecutive floating-point
                // numbers.
                root = s;
                return true;
            }
            prevBisected = true;
        }
        else
        {
            prevBisected = false;
        }

        // Evaluate the function at the new estimate and test for convergence.
        Real fs = F(s);
        if (negFTolerance <= fs && fs <= posFTolerance)
        {
            root = s;
            return true;
        }

        // Update the subinterval to include the new estimate as an endpoint.
        t3 = t2;
        t2 = t1;
        f2 = f1;
        if (f0 * fs < (Real)0)
        {
            t1 = s;
            f1 = fs;
        }
        else
        {
            t0 = s;
            f0 = fs;
        }

        // Allow the algorithm to terminate when the subinterval is
        // sufficiently small.
        if (std::abs(t1 - t0) <= convTTolerance)
        {
            root = t1;
            return true;
        }

        // A loop invariant is that t1 is the root estimate, F(t0)*F(t1) < 0,
        // and |F(t1)| <= |F(t0)|.
        if (std::abs(f0) < std::abs(f1))
        {
            std::swap(t0, t1);
            std::swap(f0, f1);
        }
    }

    // Failed to converge in the specified number of iterations.
    return false;
}
//----------------------------------------------------------------------------
