// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real ATanEstimate<Real>::Degree(Real x)
{
    return Evaluate(degree<D>(), x);
}
//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real ATanEstimate<Real>::DegreeRR(Real x)
{
    if (std::abs(x) <= (Real)1)
    {
        return Degree<D>(x);
    }
    else if (x > (Real)1)
    {
        return (Real)GTE_C_HALF_PI - Degree<D>((Real)1 / x);
    }
    else
    {
        return (Real)-GTE_C_HALF_PI - Degree<D>((Real)1 / x);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real ATanEstimate<Real>::Evaluate(degree<3>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_ATAN_DEG3_C1;
    poly = (Real)GTE_C_ATAN_DEG3_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real ATanEstimate<Real>::Evaluate(degree<5>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_ATAN_DEG5_C2;
    poly = (Real)GTE_C_ATAN_DEG5_C1 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG5_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real ATanEstimate<Real>::Evaluate(degree<7>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_ATAN_DEG7_C3;
    poly = (Real)GTE_C_ATAN_DEG7_C2 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG7_C1 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG7_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real ATanEstimate<Real>::Evaluate(degree<9>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_ATAN_DEG9_C4;
    poly = (Real)GTE_C_ATAN_DEG9_C3 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG9_C2 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG9_C1 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG9_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real ATanEstimate<Real>::Evaluate(degree<11>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_ATAN_DEG11_C5;
    poly = (Real)GTE_C_ATAN_DEG11_C4 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG11_C3 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG11_C2 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG11_C1 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG11_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real ATanEstimate<Real>::Evaluate(degree<13>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_ATAN_DEG13_C6;
    poly = (Real)GTE_C_ATAN_DEG13_C5 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG13_C4 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG13_C3 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG13_C2 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG13_C1 + poly * xsqr;
    poly = (Real)GTE_C_ATAN_DEG13_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
