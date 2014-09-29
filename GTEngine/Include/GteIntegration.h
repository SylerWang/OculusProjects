// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteRootsPolynomial.h"
#include <array>
#include <functional>
#include <vector>

namespace gte
{

template <typename Real>
class Integration
{
public:
    // A simple algorithm, but slow to converge as the number of samples is
    // increased.  The 'numSamples' needs to be two or larger.
    static Real TrapezoidRule(int numSamples, Real a, Real b,
        std::function<Real(Real)> const& integrand);

    // The trapezoid rule is used to generate initial estimates, but then
    // Richardson extrapolation is used to improve the estimates.  This is
    // preferred over TrapezoidRule.  The 'order' must be positive.
    static Real Romberg(int order, Real a, Real b,
        std::function<Real(Real)> const& integrand);

    // Gaussian quadrature estimates the integral of a function f(x) defined
    // on [-1,1] using
    //   integral_{-1}^{1} f(t) dt = sum_{i=0}^{n-1} c[i]*f(r[i])
    // where r[i] are the roots to the Legendre polynomial p(t) of degree n
    // and c[i] = integral_{-1}^{1} prod_{j=0,j!=i} (t-r[j]/(r[i]-r[j]) dt.
    // To integrate over [a,b], a transformation to [-1,1] is applied
    // internally:  x - ((b-a)*t + (b+a))/2.  The Legendre polynomials are
    // generated by
    //   P[0](x) = 1, P[1](x) = x,
    //   P[k](x) = ((2*k-1)*x*P[k-1](x) - (k-1)*P[k-2](x))/k, k >= 2
    // Implementing the polynomial generation is simple, and computing the
    // roots requires a numerical method for finding polynomial roots.  The
    // challenging task is to develop an efficient algorithm for computing
    // the coefficients c[i] for a specified degree.  The 'degree' must be
    // two or larger.

    static void ComputeQuadratureInfo(int degree, std::vector<Real>& roots,
        std::vector<Real>& coefficients);

    static Real GaussianQuadrature(std::vector<Real> const& roots,
        std::vector<Real>const & coefficients, Real a, Real b,
        std::function<Real(Real)> const& integrand);
};

#include "GteIntegration.inl"

}
