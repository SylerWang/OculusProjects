// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

namespace gte
{

// A template class to provide 2D array access that conforms to row-major
// order (RowMajor = true) or column-major order (RowMajor = false).  The
template <bool RowMajor, typename Real, int... Dimensions>
class Array2 {};

// The array dimensions are known only at run time.
template <typename Real>
class Array2<true, Real>
{
public:
    inline Array2(int numRows, int numCols, Real* matrix);

    inline int GetNumRows() const;
    inline int GetNumCols() const;
    inline Real& operator()(int r, int c);
    inline Real const& operator()(int r, int c) const;

private:
    int mNumRows, mNumCols;
    Real* mMatrix;
};

template <typename Real>
class Array2<false, Real>
{
public:
    inline Array2(int numRows, int numCols, Real* matrix);

    inline int GetNumRows() const;
    inline int GetNumCols() const;
    inline Real& operator()(int r, int c);
    inline Real const& operator()(int r, int c) const;

private:
    int mNumRows, mNumCols;
    Real* mMatrix;
};

// The array dimensions are known at compile time.
template <typename Real, int NumRows, int NumCols>
class Array2<true, Real, NumRows, NumCols>
{
public:
    inline Array2(Real* matrix);

    inline int GetNumRows() const;
    inline int GetNumCols() const;
    inline Real& operator()(int r, int c);
    inline Real const& operator()(int r, int c) const;

private:
    Real* mMatrix;
};

template <typename Real, int NumRows, int NumCols>
class Array2<false, Real, NumRows, NumCols>
{
public:
    inline Array2(Real* matrix);

    inline int GetNumRows() const;
    inline int GetNumCols() const;
    inline Real& operator()(int r, int c);
    inline Real const& operator()(int r, int c) const;

private:
    Real* mMatrix;
};

#include "GteArray2.inl"

}
