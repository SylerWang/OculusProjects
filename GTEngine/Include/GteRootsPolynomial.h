// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <cmath>
#include <vector>

// The Find functions return the number of roots, if any, and this number
// of elements of the outputs are valid.  If the polynomial is identically
// zero, FindX returns 1.
//
// Some root-bounding algorithms for real-valued roots are mentioned next for
// the polynomial p(t) = c[0] + c[1]*t + ... + c[d-1]*t^{d-1} + c[d]*t^d.
//
// 1. The roots must be contained by the interval [-M,M] where
//   M = 1 + max{|c[0]|, ..., |c[d-1]|}/|c[d]| >= 1
// is called the Cauchy bound.  If the polynomial is identically a constant,
// GetCauchyBound returns 0, which is invalid.
//
// 2. You may search for roots in the interval [-1,1].  Define
//   q(t) = t^d*p(1/t) = c[0]*t^d + c[1]*t^{d-1} + ... + c[d-1]*t + c[d]
// The roots of p(t) not in [-1,1] are the roots of q(t) in [-1,1].
//
// 3. Between two consecutive roots of the derivative p'(t), say, r0 < r1,
// the function p(t) is strictly monotonic on the open interval (r0,r1).
// If additionally, p(r0) * p(r1) <= 0, then p(x) has a unique root on
// the closed interval [r0,r1].  Thus, one can compute the derivatives
// through order d for p(t), find roots for the derivative of order k+1,
// then use these to bound roots for the derivative of order k.
//
// 4. Sturm sequences of polynomials may be used to determine bounds on the
// roots.  This is a more sophisticated approach to root bounding than item 3.
// Moreover, a Sturm sequence allows you to compute the number of real-valued
// roots on a specified interval.

namespace gte
{

template <typename Real>
class RootsPolynomial
{
public:
    // Linear equations c0 + c1*t = 0.  The array 'root' must have storage
    // for at least one element.
    static int Find(Real c0, Real c1, Real* roots);

    // Quadratic equations c0 + c1*t + c2*t^2 = 0.  The array 'root' must have
    // storage for at least two elements.
    static int Find(Real c0, Real c1, Real c2, Real* roots);

    // Cubic equations c0 + c1*t + c2*t^2 + c3*t^3 = 0.  The array 'root' must
    // have storage for at least three elements.
    static int Find(Real c0, Real c1, Real c2, Real c3, Real* roots);

    // Quartic equations c0 + c1*t + c2*t^2 + c3*t^3 + c4*t^4 = 0.  The array
    // 'root' must have storage for at least four elements.
    static int Find(Real c0, Real c1, Real c2, Real c3, Real c4, Real* roots);

    // General equations: sum_{i=0}^{d} c(i)*t^i = 0.  The input array 'c'
    // must have at least d+1 elements and the output array 'root' must have
    // at least d elements.

    // Find the roots on (-infinity,+infinity).
    static int Find(int degree, Real const* c, unsigned int maxIterations,
        Real* roots);

    // If you know that p(tmin) * p(tmax) <= 0, then there must be at least
    // one root in [tmin, tmax].  Compute it using bisection.
    static bool Find(int degree, Real const* c, Real tmin, Real tmax,
        unsigned int maxIterations, Real& root);

private:
    static int FindRecursive(int degree, Real const* c, Real tmin, Real tmax,
        unsigned int maxIterations, Real* roots);

    static Real Evaluate(int degree, Real const* c, Real t);
};

#include "GteRootsPolynomial.inl"

}
