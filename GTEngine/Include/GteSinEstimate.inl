// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real SinEstimate<Real>::Degree(Real x)
{
    return Evaluate(degree<D>(), x);
}
//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real SinEstimate<Real>::DegreeRR(Real x)
{
    return Degree<D>(Reduce(x));
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real SinEstimate<Real>::Evaluate(degree<3>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_SIN_DEG3_C1;
    poly = (Real)GTE_C_SIN_DEG3_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real SinEstimate<Real>::Evaluate(degree<5>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_SIN_DEG5_C2;
    poly = (Real)GTE_C_SIN_DEG5_C1 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG5_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real SinEstimate<Real>::Evaluate(degree<7>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_SIN_DEG7_C3;
    poly = (Real)GTE_C_SIN_DEG7_C2 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG7_C1 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG7_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real SinEstimate<Real>::Evaluate(degree<9>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_SIN_DEG9_C4;
    poly = (Real)GTE_C_SIN_DEG9_C3 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG9_C2 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG9_C1 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG9_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real SinEstimate<Real>::Evaluate(degree<11>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_SIN_DEG11_C5;
    poly = (Real)GTE_C_SIN_DEG11_C4 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG11_C3 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG11_C2 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG11_C1 + poly * xsqr;
    poly = (Real)GTE_C_SIN_DEG11_C0 + poly * xsqr;
    poly = poly * x;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real SinEstimate<Real>::Reduce(Real x)
{
    // Map x to y in [-pi,pi], x = 2*pi*quotient + remainder.
    Real quotient = (Real)GTE_C_INV_TWO_PI * x;
    if (x >= (Real)0)
    {
        quotient = (Real)((int)(quotient + (Real)0.5));
    }
    else
    {
        quotient = (Real)((int)(quotient - (Real)0.5));
    }
    Real y = x - (Real)GTE_C_TWO_PI * quotient;

    // Map y to [-pi/2,pi/2] with sin(y) = sin(x).
    if (y > (Real)GTE_C_HALF_PI)
    {
        y = (Real)GTE_C_PI - y;
    }
    else if (y < (Real)-GTE_C_HALF_PI)
    {
        y = (Real)-GTE_C_PI - y;
    }
    return y;
}
//----------------------------------------------------------------------------
