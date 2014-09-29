// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"
#include <cmath>

// Minimax polynomial approximations to log2(x).  The polynomial p(x) of
// degree D minimizes the quantity maximum{|log2(x) - p(x)| : x in [1,2]}
// over all polynomials of degree D.

namespace gte
{

template <typename Real>
class Log2Estimate
{
public:
    // The input constraint is x in [1,2].  For example,
    //   float x; // in [1,2]
    //   float result = Log2Estimate<float>::Degree<3>(x);
    template <int D>
    inline static Real Degree(Real x);

    // The input constraint is x > 0.  Range reduction is used to generate a
    // value y in (0,1], call Degree(y), and add the exponent for the power
    // of two in the binary scientific representation of x.  For example,
    //   float x;  // x > 0
    //   float result = Log2Estimate<float>::DegreeRR<3>(x);
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
};

#include "GteLog2Estimate.inl"

}
