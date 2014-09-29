// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteGMatrix.h"
#include "GteLogger.h"
#include <array>

// Fit the data with a polynomial of the form
//     w = sum_{i=0}^{n-1} c[i]*x^{p[i]}*y^{q[i]}
// where <p[i],q[i]> are distinct pairs of nonnegative powers provided by the
// caller.  A least-squares fitting algorithm is used, but the input data is
// first mapped to (x,y,w) in [-1,1]^3 for numerical robustness.

namespace gte
{

template <typename Real>
class ApprPolynomialSpecial3
    :
    public ApprQuery<Real, ApprPolynomialSpecial3<Real>, std::array<Real, 3>>
{
public:
    // Initialize the model parameters to zero.  The degrees must be
    // nonnegative and strictly increasing.
    ApprPolynomialSpecial3(std::vector<int> const& xDegrees,
        std::vector<int> const& yDegrees);

    // The minimum number of observations required to fit the model.
    int GetMinimumRequired() const;

    // Estimate the model parameters for all observations specified by the
    // indices.  This function is called by the base-class Fit(...) functions.
    bool Fit(std::vector<std::array<Real, 3>> const& observations,
        std::vector<int> const& indices);

    // Compute the model error for the specified observation for the current
    // model parameters.  The returned value for observation (x0,w0) is
    // |w(x0) - w0|, where w(x) is the fitted polynomial.
    Real Error(std::array<Real, 3> const& observation) const;

    // Get the parameters of the model.
    std::vector<Real> const& GetParameters() const;

    // Evaluate the polynomial.  The domain interval is provided so you can
    // interpolate ((x,y) in domain) or extrapolate ((x,y) not in domain).
    std::array<Real, 2> const& GetXDomain() const;
    std::array<Real, 2> const& GetYDomain() const;
    Real Evaluate(Real x, Real y) const;

private:
    // Transform the (x,y,w) values to (x',y',w') in [-1,1]^3.
    void Transform(std::vector<std::array<Real, 3>> const& observations,
        std::vector<int> const& indices,
        std::vector<std::array<Real, 3>>& transformed);

    // The least-squares fitting algorithm for the transformed data.
    bool DoLeastSquares(std::vector<std::array<Real, 3>>& transformed);

    std::vector<int> mXDegrees, mYDegrees;
    std::vector<Real> mParameters;

    // Support for evaluation.  The coefficients were generated for the
    // samples mapped to [-1,1]^3.  The Evaluate() function must transform
    // (x,y) to (x',y') in [-1,1]^2, compute w' in [-1,1], then transform w'
    // to w.
    std::array<Real, 2> mXDomain, mYDomain, mWDomain;
    std::array<Real, 3> mScale;
    Real mInvTwoWScale;

    // This array is used by Evaluate() to avoid reallocation of the 'vector's
    // for each call.  The members are mutable because, to the user, the call
    // to Evaluate does not modify the polynomial.
    mutable std::vector<Real> mXPowers, mYPowers;
};

#include "GteApprPolynomialSpecial3.inl"

}
