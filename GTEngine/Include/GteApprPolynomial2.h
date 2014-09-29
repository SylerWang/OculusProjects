// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteGMatrix.h"
#include "GteMemory.h"
#include <array>

// The samples are (x[i],w[i]) for 0 <= i < S.  Think of w as a function of
// x, say w = f(x).  The function fits the samples with a polynomial of
// degree d, say w = sum_{i=0}^d c[i]*x^i.  The method is a least-squares
// fitting algorithm.  The mParameters stores the coefficients c[i] for
// 0 <= i <= d.  The observation type is std::array<Real,2>, which represents
// a pair (x,w).
//
// WARNING.  The fitting algorithm for polynomial terms
//   (1,x,x^2,...,x^d)
// is known to be nonrobust for large degrees and for large magnitude data.
// One alternative is to use orthogonal polynomials
//   (f[0](x),...,f[d](x))
// and apply the least-squares algorithm to these.  Another alternative is to
// transform
//   (x',w') = ((x-xcen)/rng, w/rng)
// where xmin = min(x[i]), xmax = max(x[i]), xcen = (xmin+xmax)/2, and
// rng = xmax-xmin.  Fit the (x',w') points,
//   w' = sum_{i=0}^d c'[i]*(x')^i.
// The original polynomial is evaluated as
//   w = rng*sum_{i=0}^d c'[i]*((x-xcen)/rng)^i

namespace gte
{

template <typename Real>
class ApprPolynomial2
    :
    public ApprQuery<Real, ApprPolynomial2<Real>, std::array<Real, 2>>
{
public:
    // Initialize the model parameters to zero.
    ApprPolynomial2(int degree);

    // The minimum number of observations required to fit the model.
    int GetMinimumRequired() const;

    // Estimate the model parameters for all observations specified by the
    // indices.  This function is called by the base-class Fit(...) functions.
    bool Fit(std::vector<std::array<Real, 2>> const& observations,
        std::vector<int> const& indices);

    // Compute the model error for the specified observation for the current
    // model parameters.  The returned value for observation (x0,w0) is
    // |w(x0) - w0|, where w(x) is the fitted polynomial.
    Real Error(std::array<Real, 2> const& observation) const;

    // Get the parameters of the model.
    std::vector<Real> const& GetParameters() const;

    // Evaluate the polynomial.  The domain interval is provided so you can
    // interpolate (x in domain) or extrapolate (x not in domain).
    std::array<Real, 2> const& GetXDomain() const;
    Real Evaluate(Real x) const;

private:
    int mDegree, mSize;
    std::array<Real, 2> mXDomain;
    std::vector<Real> mParameters;
};

#include "GteApprPolynomial2.inl"

}
