// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real, typename TVector>
OdeMidpoint<Real,TVector>::~OdeMidpoint()
{
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
OdeMidpoint<Real,TVector>::OdeMidpoint(Real tDelta,
    std::function<TVector(Real, TVector const&)> const& F)
    :
    OdeSolver<Real, TVector>(tDelta, F)
{
}
//----------------------------------------------------------------------------
template <typename Real, typename TVector>
void OdeMidpoint<Real, TVector>::Update(Real tIn, TVector const& xIn,
    Real& tOut, TVector& xOut)
{
    // Compute the first step.
    Real halfTDelta = ((Real)0.5) * this->mTDelta;
    TVector fVector = this->mFunction(tIn, xIn);
    TVector xTemp = xIn + halfTDelta * fVector;

    // Compute the second step.
    Real halfT = tIn + halfTDelta;
    fVector = this->mFunction(halfT, xTemp);
    tOut = tIn + this->mTDelta;
    xOut = xIn + this->mTDelta * fVector;
}
//----------------------------------------------------------------------------
