// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.1 (2014/08/19)

#pragma once

#include "GteLogger.h"
#include <algorithm>
#include <cmath>
#include <vector>

namespace gte
{

template <typename Real>
class IntpAkima1
{
protected:
    // Construction (abstract base class).
    IntpAkima1(int quantity, Real const* F);
public:
    // Abstract base class.
    virtual ~IntpAkima1();

    // Member access.
    inline int GetQuantity() const;
    inline Real const* GetF() const;
    virtual Real GetXMin() const = 0;
    virtual Real GetXMax() const = 0;

    // Evaluate the function and its derivatives.  The functions clamp the
    // inputs to xmin <= x <= xmax.  The first operator is for function
    // evaluation.  The second operator is for function or derivative
    // evaluations.  The 'order' argument is the order of the derivative or
    // zero for the function itself.
    Real operator()(Real x) const;
    Real operator()(int order, Real x) const;

protected:
    class Polynomial
    {
    public:
        // P(x) = c[0] + c[1]*x + c[2]*x^2 + c[3]*x^3
        inline Real& operator[](int i);
        Real operator()(Real x) const;
        Real operator()(int order, Real x) const;

    private:
        Real mCoeff[4];
    };

    Real ComputeDerivative(Real* slope) const;
    virtual void Lookup(Real x, int& index, Real& dx) const = 0;

    int mQuantity;
    Real const* mF;
    std::vector<Polynomial> mPoly;
};

#include "GteIntpAkima1.inl"

}
