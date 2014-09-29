// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"
#include <cmath>

// Minimax polynomial approximations to atan(x).  The polynomial p(x) of
// degree D has only odd-power terms, is required to have linear term x,
// and p(1) = atan(1) = pi/4.  It minimizes the quantity
// maximum{|atan(x) - p(x)| : x in [-1,1]} over all polynomials of
// degree D subject to the constraints mentioned.

namespace gte
{

template <typename Real>
class ATanEstimate
{
public:
    // The input constraint is x in [-1,1].  For example,
    //   float x; // in [-1,1]
    //   float result = ATanEstimate<float>::Degree<3>(x);
    template <int D>
    inline static Real Degree(Real x);

    // The input x can be any real number.  Range reduction is used via
    // the identities atan(x) = pi/2 - atan(1/x) for x > 0, and
    // atan(x) = -pi/2 - atan(1/x) for x < 0.  For example,
    //   float x;  // x any real number
    //   float result = ATanEstimate<float>::DegreeRR<3>(x);
    template <int D>
    inline static Real DegreeRR(Real x);

private:
    // Metaprogramming and private implementation to allow specialization of
    // a template member function.
    template <int D> struct degree {};
    inline static Real Evaluate(degree<3>, Real x);
    inline static Real Evaluate(degree<5>, Real x);
    inline static Real Evaluate(degree<7>, Real x);
    inline static Real Evaluate(degree<9>, Real x);
    inline static Real Evaluate(degree<11>, Real x);
    inline static Real Evaluate(degree<13>, Real x);
};

#include "GteATanEstimate.inl"

}
