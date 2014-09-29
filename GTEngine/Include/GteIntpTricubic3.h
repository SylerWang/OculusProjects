// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

#include "GteLogger.h"

// The interpolator is for uniformly spaced(x,y z)-values.  The input samples
// must be stored in lexicographical order to represent f(x,y,z); that is,
// F[c + xBound*(r + yBound*s)] corresponds to f(x,y,z), where c is the index
// corresponding to x, r is the index corresponding to y, and s is the index
// corresponding to z.  Exact interpolation is achieved by setting catmullRom
// to 'true', giving you the Catmull-Rom blending matrix.  If a smooth
// interpolation is desired, set catmullRom to 'false' to obtain B-spline
// blending.

namespace gte
{

template <typename Real>
class IntpTricubic3
{
public:
    // Construction.
    IntpTricubic3(int xBound, int yBound, int zBound, Real xMin,
        Real xSpacing, Real yMin, Real ySpacing, Real zMin, Real zSpacing,
        Real const* F, bool catmullRom);

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
    int mXBound, mYBound, mZBound, mQuantity;
    Real mXMin, mXMax, mXSpacing, mInvXSpacing;
    Real mYMin, mYMax, mYSpacing, mInvYSpacing;
    Real mZMin, mZMax, mZSpacing, mInvZSpacing;
    Real const* mF;
    Real mBlend[4][4];
};

#include "GteIntpTricubic3.inl"

}
