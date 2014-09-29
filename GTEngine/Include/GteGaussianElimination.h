// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GTEngineDEF.h"
#include "GteArray2.h"
#include "GteLogger.h"
#include <cmath>
#include <cstring>
#include <vector>

// The input matrix M must be NxN.  The storage convention for element lookup
// is determined by GTE_USE_ROW_MAJOR or GTE_USE_COL_MAJOR, whichever is
// active.  If you want the inverse of M, pass a nonnull pointer inverseM;
// this matrix must also be NxN and use the same storage convention as M.  If
// you do not want the inverse of M, pass a nullptr for inverseM.  If you want
// to solve M*X = B for X, where X and B are Nx1, pass nonnull pointers for B
// and X.  If you want to solve M*Y = C for Y, where X and C are NxK, pass
// nonnull pointers for C and Y and pass K to numCols.  In all cases, pass
// N to numRows.

namespace gte
{

template <typename Real>
class GaussianElimination
{
public:
    bool operator()(int numRows,
        Real const* M, Real* inverseM, Real& determinant,
        Real const* B, Real* X,
        Real const* C, int numCols, Real* Y) const;

private:
    // Support for copying source to target or to set target to zero.  If
    // source is nullptr, then target is set to zero; otherwise source is
    // copied to target.  This function hides the type traits used to
    // determine whether Real is native floating-point or otherwise (such
    // as BSNumber or BSRational).
    void Set(int numElements, Real const* source, Real* target) const;
};

#include "GteGaussianElimination.inl"

}
