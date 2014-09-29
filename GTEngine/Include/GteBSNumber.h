// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteIEEEBinary.h"
#include "GteBitHacks.h"
#include "GteLogger.h"
#include <algorithm>

// The class BSNumber (binary scientific number) is designed to provide exact
// arithmetic for robust algorithms, typically those for which we need to know
// the exact sign of determinants.  The template parameter UInteger must have
// support for at least the following public interface.
//
//      class UIntegerType
//      {
//      public:
//          UIntegerType();
//          UIntegerType(UInteger const& number);
//          UIntegerType(UInteger&& number);
//          UIntegerType(size_t size);
//          UIntegerType& operator=(UIntegerType const& number);
//          UIntegerType& operator=(UIntegerType&& number);
//          size_t size() const;
//          uint32_t& operator[](int32_t i);
//          uint32_t const& operator[](int32_t i) const;
//          uint32_t& back();
//          uint32_t const& back() const;
//      };
//
// For example, std::vector<uint32_t> may be used for arbitrary sized unsigned
// integers.  The design also allows you to choose your own "big integer"
// class.  It also allows you to choose a fixed-size UIntegerType class where
// the maximum size is known based on the requirements of your algorithm that
// uses BSNumber.  In this case, you should add a trap if UIntegerType(size_t)
// is passed too large a size.

// Uncomment this to collect statistics on how large the BSNumber storage
// becomes when using std::vector<uint32_t> for the UIntegerType of BSNumber.
// After a sequence of BSNumber operations,  look at gte::gBSNumberMaxSize in
// the debugger watch window.  If the number is not too large, you might be
// safe in replacing std::vector<uint32_t> by BSUInteger<N>, where N is the
// value of gte::gBSNumberMaxSize.  This leads to much faster code because
// you no longer have dynamic memory allocations and deallocations that occur
// regularly with std::vector<uint32_t> during BSNumber operations.  A safer
// choice is to argue mathematically that the maximum size is bounded by N.
// This requires an analysis of how many bits of precision you need for the
// types of computation you perform.
//
//#define GTE_COLLECT_BSNUMBER_STATISTICS

namespace gte
{

template <typename UIntegerType> class BSRational;

template <typename UIntegerType>
class BSNumber
{
public:
    // Construction.  The default constructor generates the zero BSNumber.
    BSNumber();
    BSNumber(BSNumber const& number);
    BSNumber(BSNumber&& number);
    BSNumber(float number);
    BSNumber(double number);
    BSNumber(int32_t number);
    BSNumber(uint32_t number);
    BSNumber(int64_t number);
    BSNumber(uint64_t number);

    // Implicit conversions.
    inline operator float() const;
    inline operator double() const;

    // Assignment.
    BSNumber& operator=(BSNumber const& number);
    BSNumber& operator=(BSNumber&& number);

    // Member access.
    inline int32_t GetSign() const;
    inline int32_t GetBiasedExponent() const;
    inline int32_t GetExponent() const;
    inline int32_t GetNumBits() const;
    inline uint32_t const* GetBits() const;

    // Comparisons.
    bool operator==(BSNumber const& number) const;
    bool operator!=(BSNumber const& number) const;
    bool operator< (BSNumber const& number) const;
    bool operator<=(BSNumber const& number) const;
    bool operator> (BSNumber const& number) const;
    bool operator>=(BSNumber const& number) const;

    // Unary operations.
    BSNumber operator+() const;
    BSNumber operator-() const;

    // Arithmetic.
    BSNumber operator+(BSNumber const& number) const;
    BSNumber operator-(BSNumber const& number) const;
    BSNumber operator*(BSNumber const& number) const;
    BSNumber& operator+=(BSNumber const& number);
    BSNumber& operator-=(BSNumber const& number);
    BSNumber& operator*=(BSNumber const& number);

private:
    // Constructor used to create mBits with a positive number of elements.
    // This is used in low-level integer arithmetic operations, so
    // mBiasedExponent is set to zero.  The 'sign' is not zero and the
    // 'numBits' is positive.
    BSNumber(int32_t sign, int32_t numBits);

    // Helpers for operator==, operator<, operator+, operator-.
    static bool EqualIgnoreSign(BSNumber const& n0, BSNumber const& n1);
    static bool LessThanIgnoreSign(BSNumber const& n0, BSNumber const& n1);

    // Helpers for addition and subtraction.

    // Multiply by a power of two by shifting.  The 'number' is odd and
    // 'shift' is positive.
    static BSNumber ShiftLeft(BSNumber const& number, int32_t shift);

    // The 'number' is even and positive.  It is shifted right to become
    // an odd number and the return value is the amount shifted.
    static int32_t Normalize(BSNumber& number);

    // Add to positive numbers.
    static BSNumber AddIgnoreSign(BSNumber const& n0, BSNumber const& n1,
        int32_t resultSign);

    // Subtract two positive numbers where 'number0' is greater than or equal
    // to 'number1'.
    static BSNumber SubIgnoreSign(BSNumber const& n0, BSNumber const& n1,
        int32_t resultSign);

    // The base-level arbitrary-size integer operations.
    static BSNumber Add(BSNumber const& n0, BSNumber const& n1);
    static BSNumber Sub(BSNumber const& n0, BSNumber const& n1);
    static BSNumber Mul(BSNumber const& n0, BSNumber const& n1);

    // Decrements mNumBits in arithmetic operations that allocated the
    // worst-case number of bits and a carry-out did not occur.  The mBits
    // array is potentially resized to one less block.
    void ReduceBits();

    // Decrements the number of blocks in Subtract due to two's-complement
    // algorithm.  The value of mNumBits is recomputed if there is a decrease.
    void ReduceBlocks(int32_t startBlock);

    // Get a block of numRequested bits starting with the leading 1-bit of the
    // nonzero number.  The returned number has the prefix stored in the
    // high-order bits.  Additional bits are copied and used by the caller for
    // rounding.
    uint64_t GetPrefix(int numRequested) const;

    // Support for conversions from floating-point numbers to BSNumber.
    template <typename IEEE>
    void ConvertFrom(typename IEEE::FloatType number);

    // Support for conversions from BSNumber to floating-point numbers.
    template <typename IEEE>
    typename IEEE::FloatType ConvertTo() const;

    // Set the bits corresponding to a float (mBits.size() == 1) or a double
    // (mBits.size() == 2).
    template <typename IEEE>
    void InitializeBits(int32_t numBits, typename IEEE::UIntType bits);

    template <typename IEEE>
    typename IEEE::UIntType GetTrailing(int32_t normal, int32_t sigma) const;

    // The number 0 is represented by: mSign == 0, mBiasedExponent == 0,
    // mNumBits == 0, and mBits.size() == 0.  For nonzero numbers, mSign != 0,
    // mNumBits > 0, mBits.front() must be odd, and mBits.back() must be
    // nonzero, in which case mBits.size() == 1 + (mNumBits-1)/32.
    int32_t mSign;
    int32_t mBiasedExponent;
    int32_t mNumBits;
    UIntegerType mBits;

    // Access to members to avoid exposing them publically when they are
    // needed only internally.
    friend class BSRational<UIntegerType>;

    friend class UnitTestBSNumber;
};

#if defined(GTE_COLLECT_BSNUMBER_STATISTICS)
extern std::atomic<size_t> gBSNumberMaxSize;
#define GET_BSNUMBER_MAXSIZE_UPDATE(bits) AtomicMax(gBSNumberMaxSize, bits.size())
#else
#define GET_BSNUMBER_MAXSIZE_UPDATE(bits)
#endif

#include "GteBSNumber.inl"

}

namespace std
{
    template <typename UIntegerType> inline
    gte::BSNumber<UIntegerType> abs(gte::BSNumber<UIntegerType> const& number)
    {
        return (number.GetSign() >= 0 ? number : -number);
    }
}
