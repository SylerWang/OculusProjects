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

// The interpolator is for uniformly spaced(x,y z)-values.  The input samples
// must be stored in lexicographical order to represent f(x,y,z); that is,
// F[c + xBound*(r + yBound*s)] corresponds to f(x,y,z), where c is the index
// corresponding to x, r is the index corresponding to y, and s is the index
// corresponding to z.

namespace gte
{

template <typename Real>
class IntpAkimaUniform3
{
public:
    // Construction and destruction.
    ~IntpAkimaUniform3();
    IntpAkimaUniform3(int xBound, int yBound, int zBound, Real xMin,
        Real xSpacing, Real yMin, Real ySpacing, Real zMin, Real zSpacing,
        Real const* F);

    // Member access.
    inline int GetXBound() const;
    inline int GetYBound() const;
    inline int GetZBound() const;
    inline int GetQuantity() const;
    inline Real const* GetF() const;
    inline Real GetXMin() const;
    inline Real GetXMax() const;
    inline Real GetXSpacing() const;
    inline Real GetYMin() const;
    inline Real GetYMax() const;
    inline Real GetYSpacing() const;
    inline Real GetZMin() const;
    inline Real GetZMax() const;
    inline Real GetZSpacing() const;

    // Evaluate the function and its derivatives.  The functions clamp the
    // inputs to xmin <= x <= xmax, ymin <= y <= ymax, and zmin <= z <= zmax.
    // The first operator is for function evaluation.  The second operator is
    // for function or derivative evaluations.  The xOrder argument is the
    // order of the x-derivative, the yOrder argument is the order of the
    // y-derivative, and the zOrder argument is the order of the z-derivative.
    // All orders are zero to get the function value itself.
    Real operator()(Real x, Real y, Real z) const;
    Real operator()(int xOrder, int yOrder, int zOrder, Real x, Real y,
        Real z) const;

private:
    class Polynomial
    {
    public:
        Polynomial();

        // P(x,y,z) = sum_{i=0}^3 sum_{j=0}^3 sum_{k=0}^3 a_{ijk} x^i y^j z^k.
        // The tensor term A[ix][iy][iz] corresponds to the polynomial term
        // x^{ix} y^{iy} z^{iz}.
        Real& A(int ix, int iy, int iz);
        Real operator()(Real x, Real y, Real z) const;
        Real operator()(int xOrder, int yOrder, int zOrder, Real x, Real y,
            Real z) const;

    private:
        Real mCoeff[4][4][4];
    };

    // Support for construction.
    Real*** GetFX(Real*** F);
    Real*** GetFY(Real*** F);
    Real*** GetFZ(Real*** F);
    Real*** GetFXY(Real*** F);
    Real*** GetFXZ(Real*** F);
    Real*** GetFYZ(Real*** F);
    Real*** GetFXYZ(Real*** F);
    void GetPolynomials(Real*** F, Real*** FX, Real*** FY, Real*** FZ,
        Real*** FXY, Real*** FXZ, Real*** FYZ, Real*** FXYZ);

    Real ComputeDerivative(Real const* slope) const;
    void Construct(Polynomial& poly, Real const F[2][2][2],
        Real const FX[2][2][2], Real const FY[2][2][2],
        Real const FZ[2][2][2], Real const FXY[2][2][2],
        Real const FXZ[2][2][2], Real const FYZ[2][2][2],
        Real const FXYZ[2][2][2]);

    void XLookup(Real x, int& xIndex, Real& dx) const;
    void YLookup(Real y, int& yIndex, Real& dy) const;
    void ZLookup(Real z, int& zIndex, Real& dz) const;

    int mXBound, mYBound, mZBound, mQuantity;
    Real mXMin, mXMax, mXSpacing;
    Real mYMin, mYMax, mYSpacing;
    Real mZMin, mZMax, mZSpacing;
    Real const* mF;
    Polynomial*** mPoly;
};

#include "GteIntpAkimaUniform3.inl"

}
