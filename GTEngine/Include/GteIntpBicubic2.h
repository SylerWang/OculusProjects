// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

#include "GteLogger.h"

// The interpolator is for uniformly spaced (x,y)-values.  The input samples
// F must be stored in row-major order to represent f(x,y); that is,
// F[c + xBound*r] corresponds to f(x,y), where c is the index corresponding
// to x and r is the index corresponding to y.  Exact interpolation is
// achieved by setting catmullRom to 'true', giving you the Catmull-Rom
// blending matrix.  If a smooth interpolation is desired, set catmullRom to
// 'false' to obtain B-spline blending.

namespace gte
{

template <typename Real>
class IntpBicubic2
{
public:
    // Construction.
    IntpBicubic2(int xBound, int yBound, Real xMin, Real xSpacing,
        Real yMin, Real ySpacing, Real const* F, bool catmullRom);

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
    int mXBound, mYBound, mQuantity;
    Real mXMin, mXMax, mXSpacing, mInvXSpacing;
    Real mYMin, mYMax, mYSpacing, mInvYSpacing;
    Real const* mF;
    Real mBlend[4][4];
};

#include "GteIntpBicubic2.inl"

}
