// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real CosEstimate<Real>::Degree(Real x)
{
    return Evaluate(degree<D>(), x);
}
//----------------------------------------------------------------------------
template <typename Real>
template <int D>
inline Real CosEstimate<Real>::DegreeRR(Real x)
{
    Real y, sign;
    Reduce(x, y, sign);
    Real poly = sign * Degree<D>(y);
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real CosEstimate<Real>::Evaluate(degree<2>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_COS_DEG2_C1;
    poly = (Real)GTE_C_COS_DEG2_C0 + poly * xsqr;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real CosEstimate<Real>::Evaluate(degree<4>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_COS_DEG4_C2;
    poly = (Real)GTE_C_COS_DEG4_C1 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG4_C0 + poly * xsqr;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real CosEstimate<Real>::Evaluate(degree<6>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_COS_DEG6_C3;
    poly = (Real)GTE_C_COS_DEG6_C2 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG6_C1 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG6_C0 + poly * xsqr;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real CosEstimate<Real>::Evaluate(degree<8>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_COS_DEG8_C4;
    poly = (Real)GTE_C_COS_DEG8_C3 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG8_C2 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG8_C1 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG8_C0 + poly * xsqr;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline Real CosEstimate<Real>::Evaluate(degree<10>, Real x)
{
    Real xsqr = x * x;
    Real poly;
    poly = (Real)GTE_C_COS_DEG10_C5;
    poly = (Real)GTE_C_COS_DEG10_C4 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG10_C3 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG10_C2 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG10_C1 + poly * xsqr;
    poly = (Real)GTE_C_COS_DEG10_C0 + poly * xsqr;
    return poly;
}
//----------------------------------------------------------------------------
template <typename Real>
inline void CosEstimate<Real>::Reduce(Real x, Real& y, Real& sign)
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
    y = x - (Real)GTE_C_TWO_PI * quotient;

    // Map y to [-pi/2,pi/2] with cos(y) = sign*cos(x).
    if (y > (Real)GTE_C_HALF_PI)
    {
        y = (Real)GTE_C_PI - y;
        sign = (Real)-1;
    }
    else if (y < (Real)-GTE_C_HALF_PI)
    {
        y = (Real)-GTE_C_PI - y;
        sign = (Real)-1;
    }
    else
    {
        sign = (Real)1;
    }
}
//----------------------------------------------------------------------------
