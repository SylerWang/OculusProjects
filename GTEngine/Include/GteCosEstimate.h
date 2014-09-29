// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"

// Minimax polynomial approximations to cos(x).  The polynomial p(x) of
// degree D has only even-power terms, is required to have constant term 1,
// and p(pi/2) = cos(pi/2) = 0.  It minimizes the quantity
// maximum{|cos(x) - p(x)| : x in [-pi/2,pi/2]} over all polynomials of
// degree D subject to the constraints mentioned.

namespace gte
{

template <typename Real>
class CosEstimate
{
public:
    // The input constraint is x in [-pi/2,pi/2].  For example,
    //   float x; // in [-pi/2,pi/2]
    //   float result = CosEstimate<float>::Degree<4>(x);
    template <int D>
    inline static Real Degree(Real x);

    // The input x can be any real number.  Range reduction is used to
    // generate a value y in [-pi/2,pi/2] and a sign s for which
    // cos(y) = s*cos(x).  For example,
    //   float x;  // x any real number
    //   float result = CosEstimate<float>::DegreeRR<3>(x);
    template <int D>
    inline static Real DegreeRR(Real x);

private:
    // Metaprogramming and private implementation to allow specialization of
    // a template member function.
    template <int D> struct degree {};
    inline static Real Evaluate(degree<2>, Real x);
    inline static Real Evaluate(degree<4>, Real x);
    inline static Real Evaluate(degree<6>, Real x);
    inline static Real Evaluate(degree<8>, Real x);
    inline static Real Evaluate(degree<10>, Real x);

    // Support for range reduction.
    inline static void Reduce(Real x, Real& y, Real& sign);
};

#include "GteCosEstimate.inl"

}
