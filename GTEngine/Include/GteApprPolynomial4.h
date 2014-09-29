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

// The samples are (x[i],y[i],z[i],w[i]) for 0 <= i < S.  Think of w as a
// function of x, y, and z, say w = f(x,y,z).  The function fits the samples
// with a polynomial of degree d0 in x, degree d1 in y, and degree d2 in z,
// say
//   w = sum_{i=0}^{d0} sum_{j=0}^{d1} sum_{k=0}^{d2} c[i][j][k]*x^i*y^j*z^k
// The method is a least-squares fitting algorithm.  The mParameters stores
// c[i][j][k] = mParameters[i+(d0+1)*(j+(d1+1)*k)] for a total of
// (d0+1)*(d1+1)*(d2+1) coefficients.  The observation type is
// std::array<Real,4>, which represents a tuple (x,y,z,w).
//
// WARNING.  The fitting algorithm for polynomial terms
//   (1,x,x^2,...,x^d0), (1,y,y^2,...,y^d1), (1,z,z^2,...,z^d2)
// is known to be nonrobust for large degrees and for large magnitude data.
// One alternative is to use orthogonal polynomials
//   (f[0](x),...,f[d0](x)), (g[0](y),...,g[d1](y)), (h[0](z),...,h[d2](z))
// and apply the least-squares algorithm to these.  Another alternative is to
// transform
//   (x',y',z',w') = ((x-xcen)/rng, (y-ycen)/rng, (z-zcen)/rng, w/rng)
// where xmin = min(x[i]), xmax = max(x[i]), xcen = (xmin+xmax)/2,
// ymin = min(y[i]), ymax = max(y[i]), ycen = (ymin+ymax)/2, zmin = min(z[i]),
// zmax = max(z[i]), zcen = (zmin+zmax)/2, and
// rng = max(xmax-xmin,ymax-ymin,zmax-zmin).  Fit the (x',y',z',w') points,
//   w' = sum_{i=0}^{d0} sum_{j=0}^{d1} sum_{k=0}^{d2} c'[i][j][k] *
//          (x')^i*(y')^j*(z')^k
// The original polynomial is evaluated as
//   w = rng * sum_{i=0}^{d0} sum_{j=0}^{d1} sum_{k=0}^{d2} c'[i][j][k] *
//         ((x-xcen)/rng)^i * ((y-ycen)/rng)^j * ((z-zcen)/rng)^k

namespace gte
{

template <typename Real>
class ApprPolynomial4
    :
    public ApprQuery<Real, ApprPolynomial4<Real>, std::array<Real, 4>>
{
public:
    // Initialize the model parameters to zero.
    ApprPolynomial4(int xDegree, int yDegree, int zDegree);

    // The minimum number of observations required to fit the model.
    int GetMinimumRequired() const;

    // Estimate the model parameters for all observations specified by the
    // indices.  This function is called by the base-class Fit(...) functions.
    bool Fit(std::vector<std::array<Real, 4>> const& observations,
        std::vector<int> const& indices);

    // Compute the model error for the specified observation for the current
    // model parameters.  The returned value for observation (x0,y0,z0,w0) is
    // |w(x0,y0,z0) - w0|, where w(x,y,z) is the fitted polynomial.
    Real Error(std::array<Real, 4> const& observation) const;

    // Get the parameters of the model.
    std::vector<Real> const& GetParameters() const;

    // Evaluate the polynomial.  The domain intervals are provided so you can
    // interpolate ((x,y,z) in domain) or extrapolate ((x,y,z) not in domain).
    std::array<Real, 2> const& GetXDomain() const;
    std::array<Real, 2> const& GetYDomain() const;
    std::array<Real, 2> const& GetZDomain() const;
    Real Evaluate(Real x, Real y, Real z) const;

private:
    int mXDegree, mYDegree, mZDegree;
    int mXDegreeP1, mYDegreeP1, mZDegreeP1, mSize;
    std::array<Real, 2> mXDomain, mYDomain, mZDomain;
    std::vector<Real> mParameters;

    // These arrays are used by Evaluate() to avoid reallocation of the
    // 'vector's for each call.  The member is mutable because, to the
    // user, the call to Evaluate does not modify the polynomial.
    mutable std::vector<Real> mYZCoefficient;
    mutable std::vector<Real> mZCoefficient;
};

#include "GteApprPolynomial4.inl"

}
