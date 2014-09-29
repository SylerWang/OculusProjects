// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real Exp2Estimate<Real>::Degree(Real x)
{
    return Evaluate(degree<D>(), x);
}
//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real Exp2Estimate<Real>::DegreeRR(Real x)
{
    Real p = floor(x);
    Real y = x - p;
    Real poly = Degree<D>(y);
    Real result = ldexp(poly, (int)p);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real Exp2Estimate<Real>::Evaluate(degree<1>, Real t)
{
    Real poly;
    poly = (Real)GTE_C_EXP2_DEG1_C1;
    poly = (Real)GTE_C_EXP2_DEG1_C0 + poly * t;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real Exp2Estimate<Real>::Evaluate(degree<2>, Real t)
{
    Real poly;
    poly = (Real)GTE_C_EXP2_DEG2_C2;
    poly = (Real)GTE_C_EXP2_DEG2_C1 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG2_C0 + poly * t;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real Exp2Estimate<Real>::Evaluate(degree<3>, Real t)
{
    Real poly;
    poly = (Real)GTE_C_EXP2_DEG3_C3;
    poly = (Real)GTE_C_EXP2_DEG3_C2 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG3_C1 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG3_C0 + poly * t;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real Exp2Estimate<Real>::Evaluate(degree<4>, Real t)
{
    Real poly;
    poly = (Real)GTE_C_EXP2_DEG4_C4;
    poly = (Real)GTE_C_EXP2_DEG4_C3 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG4_C2 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG4_C1 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG4_C0 + poly * t;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real Exp2Estimate<Real>::Evaluate(degree<5>, Real t)
{
    Real poly;
    poly = (Real)GTE_C_EXP2_DEG5_C5;
    poly = (Real)GTE_C_EXP2_DEG5_C4 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG5_C3 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG5_C2 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG5_C1 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG5_C0 + poly * t;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real Exp2Estimate<Real>::Evaluate(degree<6>, Real t)
{
    Real poly;
    poly = (Real)GTE_C_EXP2_DEG6_C6;
    poly = (Real)GTE_C_EXP2_DEG6_C5 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG6_C4 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG6_C3 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG6_C2 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG6_C1 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG6_C0 + poly * t;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real Exp2Estimate<Real>::Evaluate(degree<7>, Real t)
{
    Real poly;
    poly = (Real)GTE_C_EXP2_DEG7_C7;
    poly = (Real)GTE_C_EXP2_DEG7_C6 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG7_C5 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG7_C4 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG7_C3 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG7_C2 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG7_C1 + poly * t;
    poly = (Real)GTE_C_EXP2_DEG7_C0 + poly * t;
    return poly;
}
//----------------------------------------------------------------------------
