// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real TanEstimate<Real>::Degree(Real x)
{
    return Evaluate(degree<D>(), x);
}
//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real TanEstimate<Real>::DegreeRR(Real x)
{
    Real y;
    Reduce(x, y);
    if (std::abs(y) <= (Real)GTE_C_QUARTER_PI)
    {
        return Degree<D>(y);
    }
    else if (y > (Real)GTE_C_QUARTER_PI)
    {
        Real poly = Degree<D>(y - (Real)GTE_C_QUARTER_PI);
        return ((Real)1 + poly) / ((Real)1 - poly);
    }
    else
    {
        Real poly = Degree<D>(y + (Real)GTE_C_QUARTER_PI);
        return -((Real)1 - poly) / ((Real)1 + poly);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real TanEstimate<Real>::Evaluate(degree<3>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_TAN_DEG3_C1;
    poly = (Real)GTE_C_TAN_DEG3_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real TanEstimate<Real>::Evaluate(degree<5>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_TAN_DEG5_C2;
    poly = (Real)GTE_C_TAN_DEG5_C1 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG5_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real TanEstimate<Real>::Evaluate(degree<7>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_TAN_DEG7_C3;
    poly = (Real)GTE_C_TAN_DEG7_C2 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG7_C1 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG7_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real TanEstimate<Real>::Evaluate(degree<9>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_TAN_DEG9_C4;
    poly = (Real)GTE_C_TAN_DEG9_C3 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG9_C2 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG9_C1 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG9_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real TanEstimate<Real>::Evaluate(degree<11>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_TAN_DEG11_C5;
    poly = (Real)GTE_C_TAN_DEG11_C4 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG11_C3 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG11_C2 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG11_C1 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG11_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real TanEstimate<Real>::Evaluate(degree<13>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_TAN_DEG13_C6;
    poly = (Real)GTE_C_TAN_DEG13_C5 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG13_C4 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG13_C3 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG13_C2 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG13_C1 + poly * xsqr;
    poly = (Real)GTE_C_TAN_DEG13_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline void TanEstimate<Real>::Reduce(Real x, Real& y)
{
    // Map x to y in [-pi,pi], x = pi*quotient + remainder.
    y = fmod(x, (Real)GTE_C_PI);

    // Map y to [-pi/2,pi/2] with tan(y) = tan(x).
    if (y > (Real)GTE_C_HALF_PI)
    {
        y -= (Real)GTE_C_PI;
    }
    else if (y < (Real)-GTE_C_HALF_PI)
    {
        y += (Real)GTE_C_PI;
    }
}
//----------------------------------------------------------------------------
