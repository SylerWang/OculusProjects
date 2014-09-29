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

// The samples are (x[i],y[i],w[i]) for 0 <= i < S.  Think of w as a function
// of x and y, say w = f(x,y).  The function fits the samples with a
// polynomial of degree d0 in x and degree d1 in y, say
//   w = sum_{i=0}^{d0} sum_{j=0}^{d1} c[i][j]*x^i*y^j
// The method is a least-squares fitting algorithm.  The mParameters stores
// c[i][j] = mParameters[i+(d0+1)*j] for a total of (d0+1)*(d1+1)
// coefficients.  The observation type is std::array<Real,3>, which represents
// a triple (x,y,w).
//
// WARNING.  The fitting algorithm for polynomial terms
//   (1,x,x^2,...,x^d0), (1,y,y^2,...,y^d1)
// is known to be nonrobust for large degrees and for large magnitude data.
// One alternative is to use orthogonal polynomials
//   (f[0](x),...,f[d0](x)), (g[0](y),...,g[d1](y))
// and apply the least-squares algorithm to these.  Another alternative is to
// transform
//   (x',y',w') = ((x-xcen)/rng, (y-ycen)/rng, w/rng)
// where xmin = min(x[i]), xmax = max(x[i]), xcen = (xmin+xmax)/2,
// ymin = min(y[i]), ymax = max(y[i]), ycen = (ymin+ymax)/2, and
// rng = max(xmax-xmin,ymax-ymin).  Fit the (x',y',w') points,
//   w' = sum_{i=0}^{d0} sum_{j=0}^{d1} c'[i][j]*(x')^i*(y')^j
// The original polynomial is evaluated as
//   w = rng * sum_{i=0}^{d0} sum_{j=0}^{d1} c'[i][j] *
//         ((x-xcen)/rng)^i * ((y-ycen)/rng)^j

namespace gte
{

template <typename Real>
class ApprPolynomial3
    :
    public ApprQuery<Real, ApprPolynomial3<Real>, std::array<Real, 3>>
{
public:
    // Initialize the model parameters to zero.
    ApprPolynomial3(int xDegree, int yDegree);

    // The minimum number of observations required to fit the model.
    int GetMinimumRequired() const;

    // Estimate the model parameters for all observations specified by the
    // indices.  This function is called by the base-class Fit(...) functions.
    bool Fit(std::vector<std::array<Real, 3>> const& observations,
        std::vector<int> const& indices);

    // Compute the model error for the specified observation for the current
    // model parameters.  The returned value for observation (x0,y0,w0) is
    // |w(x0,y0) - w0|, where w(x,y) is the fitted polynomial.
    Real Error(std::array<Real, 3> const& observation) const;

    // Get the parameters of the model.
    std::vector<Real> const& GetParameters() const;

    // Evaluate the polynomial.  The domain intervals are provided so you can
    // interpolate ((x,y) in domain) or extrapolate ((x,y) not in domain).
    std::array<Real, 2> const& GetXDomain() const;
    std::array<Real, 2> const& GetYDomain() const;
    Real Evaluate(Real x, Real y) const;

private:
    int mXDegree, mYDegree, mXDegreeP1, mYDegreeP1, mSize;
    std::array<Real, 2> mXDomain, mYDomain;
    std::vector<Real> mParameters;

    // This array is used by Evaluate() to avoid reallocation of the 'vector'
    // for each call.  The member is mutable because, to the user, the call
    // to Evaluate does not modify the polynomial.
    mutable std::vector<Real> mYCoefficient;
};

#include "GteApprPolynomial3.inl"

}
