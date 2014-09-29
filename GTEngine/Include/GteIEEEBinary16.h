// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIEEEBinary.h"

namespace gte
{

struct _Float16 { int16_t _dummy; };

class IEEEBinary16 : public IEEEBinary<_Float16,uint16_t, 16, 11>
{
public:
    // Construction and destruction.  The base class destructor is hidden, but
    // this is safe because there are no side effects of the destruction.
    ~IEEEBinary16();
    IEEEBinary16();  // uninitialized
    IEEEBinary16(IEEEBinary16 const& object);
    IEEEBinary16(float number);
    IEEEBinary16(uint16_t encoding);

    // Explicit conversion to float.  The implicit conversion is not provided
    // to avoid problems resolving calls to the non-class members defined
    // later in this file.
    float Convert() const;

    // Assignment.
    IEEEBinary16& operator=(IEEEBinary16 const& object);

private:
    // Support for conversions between encodings.
    enum
    {
        F32_NUM_ENCODING_BITS = 32,
        F32_NUM_TRAILING_BITS = 23,
        F32_EXPONENT_BIAS = 127,
        F32_MAX_BIASED_EXPONENT = 255,
        F32_SIGN_MASK = 0x80000000,
        F32_NOT_SIGN_MASK = 0x7FFFFFFF,
        F32_BIASED_EXPONENT_MASK = 0x7F800000,
        F32_TRAILING_MASK = 0x007FFFFF,
        F16_AVR_MIN_SUBNORMAL_ZERO = 0x33000000,
        F16_MIN_SUBNORMAL = 0x33800000,
        F16_MIN_NORMAL = 0x38800000,
        F16_MAX_NORMAL = 0x477FE000,
        F16_AVR_MAX_NORMAL_INFINITY = 0x477FF000,
        DIFF_NUM_ENCODING_BITS = 16,
        DIFF_NUM_TRAILING_BITS = 13,
        DIFF_PAYLOAD_SHIFT = 13,
        INT_PART_MASK = 0x007FE000,
        FRC_PART_MASK = 0x00001FFF,
        FRC_HALF = 0x00001000
    };

    static uint16_t Convert32To16(uint32_t encoding);
    static uint32_t Convert16To32(uint16_t encoding);
};

// Arithmetic operations (high-precision).
IEEEBinary16 operator-(IEEEBinary16 x);
float operator+(IEEEBinary16 x, IEEEBinary16 y);
float operator-(IEEEBinary16 x, IEEEBinary16 y);
float operator*(IEEEBinary16 x, IEEEBinary16 y);
float operator/(IEEEBinary16 x, IEEEBinary16 y);
float operator+(IEEEBinary16 x, float y);
float operator-(IEEEBinary16 x, float y);
float operator*(IEEEBinary16 x, float y);
float operator/(IEEEBinary16 x, float y);
float operator+(float x, IEEEBinary16 y);
float operator-(float x, IEEEBinary16 y);
float operator*(float x, IEEEBinary16 y);
float operator/(float x, IEEEBinary16 y);

// Arithmetic updates.
IEEEBinary16& operator+=(IEEEBinary16& x, IEEEBinary16 y);
IEEEBinary16& operator-=(IEEEBinary16& x, IEEEBinary16 y);
IEEEBinary16& operator*=(IEEEBinary16& x, IEEEBinary16 y);
IEEEBinary16& operator/=(IEEEBinary16& x, IEEEBinary16 y);
IEEEBinary16& operator+=(IEEEBinary16& x, float y);
IEEEBinary16& operator-=(IEEEBinary16& x, float y);
IEEEBinary16& operator*=(IEEEBinary16& x, float y);
IEEEBinary16& operator/=(IEEEBinary16& x, float y);

#if 0
// TODO: Although IEEEBinary16 has no implicit conversion to 'float',
// the base class does.  This causes the compiler to call sqrt(IEEEBinary16)
// when sqrt is passed a 'float', which is incorrect.  Fix this.
//
// Functions (Abs, CopySign, Negate, and Sqrt are required).
IEEEBinary16 fabs(IEEEBinary16 x);                          // |x|
IEEEBinary16 sqrt(IEEEBinary16 x);                          // sqrt(x)
IEEEBinary16 exp(IEEEBinary16 x);                           // e^x
IEEEBinary16 log(IEEEBinary16 x);                           // log_e(x)
IEEEBinary16 log10(IEEEBinary16 x);                         // log_10(x)
IEEEBinary16 pow(IEEEBinary16 x, IEEEBinary16 y);           // x^y (x < 0 allowed)
IEEEBinary16 sin(IEEEBinary16 x);                           // sin(x)
IEEEBinary16 cos(IEEEBinary16 x);                           // cos(x)
IEEEBinary16 tan(IEEEBinary16 x);                           // tan(x)
IEEEBinary16 asin(IEEEBinary16 x);                          // asin(x)
IEEEBinary16 acos(IEEEBinary16 x);                          // acos(x)
IEEEBinary16 atan(IEEEBinary16 x);                          // atan(x)
IEEEBinary16 atan2(IEEEBinary16 y, IEEEBinary16 x);         // angle in [-pi,pi]
IEEEBinary16 sinh(IEEEBinary16 x);                          // sinh(x)
IEEEBinary16 cosh(IEEEBinary16 x);                          // cosh(x)
IEEEBinary16 tanh(IEEEBinary16 x);                          // tanh(x)

// Recommended by the IEEE 754-2008 Standard or convenient for applications.
IEEEBinary16 copysign(IEEEBinary16 x, IEEEBinary16 y);      // x with sign of y
IEEEBinary16 expm1(IEEEBinary16 x);                         // e^x - 1
IEEEBinary16 exp2(IEEEBinary16 x);                          // 2^x
IEEEBinary16 exp2m1(IEEEBinary16 x);                        // 2^x - 1
IEEEBinary16 exp10(IEEEBinary16 x);                         // 10^x
IEEEBinary16 exp10m1(IEEEBinary16 x);                       // 10^x - 1
IEEEBinary16 log2(IEEEBinary16 x);                          // log_2(x)
IEEEBinary16 logp1(IEEEBinary16 x);                         // log_e(1+x)
IEEEBinary16 log2p1(IEEEBinary16 x);                        // log_2(1+x)
IEEEBinary16 log10p1(IEEEBinary16 x);                       // log_10(1+x)
IEEEBinary16 hypot(IEEEBinary16 x, IEEEBinary16 y);         // sqrt(x^2+y^2)
IEEEBinary16 invsqrt(IEEEBinary16 x);                       // 1/sqrt(x)
IEEEBinary16 compound(IEEEBinary16 x, int32_t n);           // (1+x)^n
IEEEBinary16 rootn(IEEEBinary16 x, int32_t n);              // x^{1/n}
IEEEBinary16 pown(IEEEBinary16 x, int32_t n);               // x^n
IEEEBinary16 powr(IEEEBinary16 x, IEEEBinary16 y);          // x^y (x >= 0)
IEEEBinary16 sinpi(IEEEBinary16 x);                         // sin(pi*x)
IEEEBinary16 cospi(IEEEBinary16 x);                         // cos(pi*x)
IEEEBinary16 atanpi(IEEEBinary16 x);                        // atan(x)/pi
IEEEBinary16 atan2pi(IEEEBinary16 y, IEEEBinary16 x);       // atan2(y,x)/pi
IEEEBinary16 asinh(IEEEBinary16 x);                         // asinh(x)
IEEEBinary16 acosh(IEEEBinary16 x);                         // acosh(x)
IEEEBinary16 atanh(IEEEBinary16 x);                         // atanh(x)
#endif
}
