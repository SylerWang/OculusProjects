// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"
#include <cmath>

// Minimax polynomial approximations to 1/sqrt(x).  The polynomial p(x) of
// degree D minimizes the quantity maximum{|1/sqrt(x) - p(x)| : x in [1,2]}
// over all polynomials of degree D.

namespace gte
{

template <typename Real>
class InvSqrtEstimate
{
public:
    // The input constraint is x in [1,2].  For example,
    //   float x; // in [1,2]
    //   float result = InvSqrtEstimate<float>::Degree<3>(x);
    template <int D>
    inline static Real Degree(Real x);

    // The input constraint is x > 0.  Range reduction is used to generate a
    // value y in [1,2], call Evaluate(y), and combine the output with the
    // proper exponent to obtain the approximation.  For example,
    //   float x;  // x > 0
    //   float result = InvSqrtEstimate<float>::DegreeRR<3>(x);
    template <int D>
    inline static Real DegreeRR(Real x);

private:
    // Metaprogramming and private implementation to allow specialization of
    // a template member function.
    template <int D> struct degree {};
    inline static Real Evaluate(degree<1>, Real t);
    inline static Real Evaluate(degree<2>, Real t);
    inline static Real Evaluate(degree<3>, Real t);
    inline static Real Evaluate(degree<4>, Real t);
    inline static Real Evaluate(degree<5>, Real t);
    inline static Real Evaluate(degree<6>, Real t);
    inline static Real Evaluate(degree<7>, Real t);
    inline static Real Evaluate(degree<8>, Real t);

    // Support for range reduction.
    inline static void Reduce(Real x, Real& adj, Real& y, int& p);
    inline static Real Combine(Real adj, Real y, int p);
};

#include "GteInvSqrtEstimate.inl"

}
