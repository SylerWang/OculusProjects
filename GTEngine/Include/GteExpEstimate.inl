// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real ExpEstimate<Real>::Degree(Real x)
{
    return Exp2Estimate<Real>::Degree<D>((Real)GTE_C_LN_2 * x);
}
//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real ExpEstimate<Real>::DegreeRR(Real x)
{
    return Exp2Estimate<Real>::DegreeRR<D>((Real)GTE_C_LN_2 * x);
}
//----------------------------------------------------------------------------
