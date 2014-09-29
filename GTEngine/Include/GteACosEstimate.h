// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"
#include <cmath>

// Approximations to acos(x) of the form f(x) = sqrt(1-x)*p(x)
// where the polynomial p(x) of degree D minimizes the quantity
// maximum{|acos(x)/sqrt(1-x) - p(x)| : x in [0,1]} over all
// polynomials of degree D.

namespace gte
{

template <typename Real>
class ACosEstimate
{
public:
    // The input constraint is x in [0,1].  For example,
    //   float x; // in [0,1]
    //   float result = ACosEstimate<float>::Degree<3>(x);
    template <int D>
    inline static Real Degree(Real x);

private:
    // Metaprogramming and private implementation to allow specialization of
    // a template member function.
    template <int D> struct degree {};
    inline static Real Evaluate(degree<1>, Real x);
    inline static Real Evaluate(degree<2>, Real x);
    inline static Real Evaluate(degree<3>, Real x);
    inline static Real Evaluate(degree<4>, Real x);
    inline static Real Evaluate(degree<5>, Real x);
    inline static Real Evaluate(degree<6>, Real x);
    inline static Real Evaluate(degree<7>, Real x);
    inline static Real Evaluate(degree<8>, Real x);
};

#include "GteACosEstimate.inl"

}
