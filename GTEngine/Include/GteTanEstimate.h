// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"
#include <cmath>

// Minimax polynomial approximations to tan(x).  The polynomial p(x) of
// degree D has only odd-power terms, is required to have linear term x,
// and p(pi/4) = tan(pi/4) = 1.  It minimizes the quantity
// maximum{|tan(x) - p(x)| : x in [-pi/4,pi/4]} over all polynomials of
// degree D subject to the constraints mentioned.

namespace gte
{

template <typename Real>
class TanEstimate
{
public:
    // The input constraint is x in [-pi/4,pi/4].  For example,
    //   float x; // in [-pi/4,pi/4]
    //   float result = TanEstimate<float>::Degree<3>(x);
    template <int D>
    inline static Real Degree(Real x);

    // The input x can be any real number.  Range reduction is used to
    // generate a value y in [-pi/2,pi/2].  If |y| <= pi/4, then the
    // polynomial is evaluated.  If y in (pi/4,pi/2), set z = y - pi/4
    // and use the identity
    //   tan(y) = tan(z + pi/4) = [1 + tan(z)]/[1 - tan(z)]
    // Be careful when evaluating at y nearly pi/2, because tan(y)
    // becomes infinite.  For example,
    //   float x;  // x any real number
    //   float result = TanEstimate<float>::DegreeRR<3>(x);
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

    // Support for range reduction.
    inline static void Reduce(Real x, Real& y);
};

#include "GteTanEstimate.inl"

}
