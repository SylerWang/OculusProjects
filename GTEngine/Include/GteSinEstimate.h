// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"

// Minimax polynomial approximations to sin(x).  The polynomial p(x) of
// degree D has only odd-power terms, is required to have linear term x,
// and p(pi/2) = sin(pi/2) = 1.  It minimizes the quantity
// maximum{|sin(x) - p(x)| : x in [-pi/2,pi/2]} over all polynomials of
// degree D subject to the constraints mentioned.

namespace gte
{

template <typename Real>
class SinEstimate
{
public:
    // The input constraint is x in [-pi/2,pi/2].  For example,
    //   float x; // in [-pi/2,pi/2]
    //   float result = SinEstimate<float>::Degree<3>(x);
    template <int D>
    inline static Real Degree(Real x);

    // The input x can be any real number.  Range reduction is used to
    // generate a value y in [-pi/2,pi/2] for which sin(y) = sin(x).
    // For example,
    //   float x;  // x any real number
    //   float result = SinEstimate<float>::DegreeRR<3>(x);
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

    // Support for range reduction.
    inline static Real Reduce(Real x);
};

#include "GteSinEstimate.inl"

}
