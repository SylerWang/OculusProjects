// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.1 (2014/08/19)

#pragma once

#include "GteLogger.h"
#include "GteMemory.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// The interpolator is for uniformly spaced (x,y)-values.  The input samples
// F must be stored in row-major order to represent f(x,y); that is,
// F[c + xBound*r] corresponds to f(x,y), where c is the index corresponding
// to x and r is the index corresponding to y.

namespace gte
{

template <typename Real>
class IntpAkimaUniform2
{
public:
    // Construction and destruction.
    ~IntpAkimaUniform2();
    IntpAkimaUniform2(int xBound, int yBound, Real xMin, Real xSpacing,
        Real yMin, Real ySpacing, Real const* F);

    // Member access.
    inline int GetXBound() const;
    inline int GetYBound() const;
    inline int GetQuantity() const;
    inline Real const* GetF() const;
    inline Real GetXMin() const;
    inline Real GetXMax() const;
    inline Real GetXSpacing() const;
    inline Real GetYMin() const;
    inline Real GetYMax() const;
    inline Real GetYSpacing() const;

    // Evaluate the function and its derivatives.  The functions clamp the
    // inputs to xmin <= x <= xmax and ymin <= y <= ymax.  The first operator
    // is for function evaluation.  The second operator is for function or
    // derivative evaluations.  The xOrder argument is the order of the
    // x-derivative and the yOrder argument is the order of the y-derivative.
    // Both orders are zero to get the function value itself.
    Real operator()(Real x, Real y) const;
    Real operator()(int xOrder, int yOrder, Real x, Real y) const;

private:
    class Polynomial
    {
    public:
        Polynomial();

        // P(x,y) = (1,x,x^2,x^3)*A*(1,y,y^2,y^3).  The matrix term A[ix][iy]
        // corresponds to the polynomial term x^{ix} y^{iy}.
        Real& A(int ix, int iy);
        Real operator()(Real x, Real y) const;
        Real operator()(int xOrder, int yOrder, Real x, Real y) const;

    private:
        Real mCoeff[4][4];
    };

    // Support for construction.
    Real** GetFX(Real** F);
    Real** GetFY(Real** F);
    Real** GetFXY(Real** F);
    void GetPolynomials(Real** F, Real** FX, Real** FY, Real** FXY);
    Real ComputeDerivative(Real const* slope) const;
    void Construct(Polynomial& poly, Real const F[2][2], Real const FX[2][2],
        Real const FY[2][2], Real const FXY[2][2]);

    // Support for evaluation.
    void XLookup(Real x, int& xIndex, Real& dx) const;
    void YLookup(Real y, int& yIndex, Real& dy) const;

    int mXBound, mYBound, mQuantity;
    Real mXMin, mXMax, mXSpacing;
    Real mYMin, mYMax, mYSpacing;
    Real const* mF;
    Polynomial** mPoly;
};

#include "GteIntpAkimaUniform2.inl"

}
