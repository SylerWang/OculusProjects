// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteBSNumber.h"

// See the comments in GteBSNumber.h about the UIntegerType requirements.

namespace gte
{

template <typename UIntegerType>
class BSRational
{
public:
    // Construction.  The default constructor generates the zero BSRational.
    // The constructors that take only numerators set the denominators to one.
    BSRational();
    BSRational(BSRational const& rational);
    BSRational(BSRational&& rational);
    BSRational(float numerator);
    BSRational(double numerator);
    BSRational(int32_t numerator);
    BSRational(uint32_t numerator);
    BSRational(int64_t numerator);
    BSRational(uint64_t numerator);
    BSRational(BSNumber<UIntegerType> const& numerator);
    BSRational(float numerator, float denominator);
    BSRational(double numerator, double denominator);
    BSRational(BSNumber<UIntegerType> const& numerator,
        BSNumber<UIntegerType> const& denominator);

    // Implicit conversions.  These convert numerator and denominator to
    // floating-point, then the division is applied.  TODO: To obtain
    // correctly rounded results, these should be implemented where the
    // division of BSNumbers is performed (with an integer-arithmetic
    // division algorithm) to obtain the bits of the floating-point number.
    operator float() const;
    operator double() const;

    // Assignment.
    BSRational& operator=(BSRational const& rational);
    BSRational& operator=(BSRational&& rational);

    // Member access.
    inline int GetSign() const;
    inline BSNumber<UIntegerType> const& GetNumerator() const;
    inline BSNumber<UIntegerType> const& GetDenomator() const;

    // Comparisons.
    bool operator==(BSRational const& rational) const;
    bool operator!=(BSRational const& rational) const;
    bool operator< (BSRational const& rational) const;
    bool operator<=(BSRational const& rational) const;
    bool operator> (BSRational const& rational) const;
    bool operator>=(BSRational const& rational) const;

    // Unary operations.
    BSRational operator+() const;
    BSRational operator-() const;

    // Arithmetic.
    BSRational operator+(BSRational const& rational) const;
    BSRational operator-(BSRational const& rational) const;
    BSRational operator*(BSRational const& rational) const;
    BSRational operator/(BSRational const& rational) const;
    BSRational& operator+=(BSRational const& rational);
    BSRational& operator-=(BSRational const& rational);
    BSRational& operator*=(BSRational const& rational);
    BSRational& operator/=(BSRational const& rational);

private:
    BSNumber<UIntegerType> mNumerator, mDenominator;

    friend class UnitTestBSRational;
};

#include "GteBSRational.inl"

}

namespace std
{
    template <typename UIntegerType>
    inline gte::BSRational<UIntegerType> abs(
        gte::BSRational<UIntegerType> const& number)
    {
        return (number.GetSign() >= 0 ? number : -number);
    }
}
