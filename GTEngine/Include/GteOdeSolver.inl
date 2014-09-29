// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real, typename TVector>
OdeSolver<Real,TVector>::~OdeSolver()
{
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
OdeSolver<Real,TVector>::OdeSolver(Real tDelta,
    std::function<TVector(Real, TVector const&)> const& F)
    :
    mTDelta(tDelta),
    mFunction(F)
{
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector> inline
void OdeSolver<Real,TVector>::SetTDelta(Real tDelta)
{
    mTDelta = tDelta;
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector> inline
Real OdeSolver<Real,TVector>::GetTDelta() const
{
    return mTDelta;
}
//----------------------------------------------------------------------------
