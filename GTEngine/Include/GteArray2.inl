// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real> inline
Array2<true, Real>::Array2(int numRows, int numCols, Real* matrix)
    :
    mNumRows(numRows),
    mNumCols(numCols),
    mMatrix(matrix)
{
}
//----------------------------------------------------------------------------
template <typename Real> inline
int Array2<true, Real>::GetNumRows() const
{
    return mNumRows;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int Array2<true, Real>::GetNumCols() const
{
    return mNumCols;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real& Array2<true, Real>::operator()(int r, int c)
{
    return mMatrix[c + mNumCols*r];
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real const& Array2<true, Real>::operator()(int r, int c) const
{
    return mMatrix[c + mNumCols*r];
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real> inline
Array2<false, Real>::Array2(int numRows, int numCols, Real* matrix)
    :
    mNumRows(numRows),
    mNumCols(numCols),
    mMatrix(matrix)
{
}
//----------------------------------------------------------------------------
template <typename Real> inline
int Array2<false, Real>::GetNumRows() const
{
    return mNumRows;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int Array2<false, Real>::GetNumCols() const
{
    return mNumCols;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real& Array2<false, Real>::operator()(int r, int c)
{
    return mMatrix[r + mNumRows*c];
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real const& Array2<false, Real>::operator()(int r, int c) const
{
    return mMatrix[r + mNumRows*c];
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
Array2<true, Real, NumRows, NumCols>::Array2(Real* matrix)
    :
    mMatrix(matrix)
{
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
int Array2<true, Real, NumRows, NumCols>::GetNumRows() const
{
    return NumRows;
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
int Array2<true, Real, NumRows, NumCols>::GetNumCols() const
{
    return NumCols;
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
Real& Array2<true, Real, NumRows, NumCols>::operator()(int r, int c)
{
    return mMatrix[c + NumCols*r];
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
Real const& Array2<true, Real, NumRows, NumCols>::operator()(int r, int c)
    const
{
    return mMatrix[c + NumCols*r];
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
Array2<false, Real, NumRows, NumCols>::Array2(Real* matrix)
    :
    mMatrix(matrix)
{
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
int Array2<false, Real, NumRows, NumCols>::GetNumRows() const
{
    return NumRows;
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
int Array2<false, Real, NumRows, NumCols>::GetNumCols() const
{
    return NumCols;
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
Real& Array2<false, Real, NumRows, NumCols>::operator()(int r, int c)
{
    return mMatrix[r + NumRows*c];
}
//----------------------------------------------------------------------------
template <typename Real, int NumRows, int NumCols> inline
Real const& Array2<false, Real, NumRows, NumCols>::operator()(int r, int c)
    const
{
    return mMatrix[r + NumRows*c];
}
//----------------------------------------------------------------------------
