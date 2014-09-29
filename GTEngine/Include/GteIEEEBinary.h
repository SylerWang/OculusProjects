// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <cstdint>

namespace gte
{

template <typename Float, typename UInt, int NumBits, int Precision>
class IEEEBinary
{
public:
    // For generic access of the template types.
    typedef Float FloatType;
    typedef UInt UIntType;

    // Construction from an encoding.  Copy constructor, destructor, and
    // assignment operator are implicitly generated.  For the 3-parameter
    // constructor, see the comments for SetEncoding(...).
    ~IEEEBinary ();
    IEEEBinary (); // The encoding is uninitialized.
    IEEEBinary (IEEEBinary const& object);
    IEEEBinary (UInt inEncoding);
    IEEEBinary (UInt inSign, UInt inBiased, UInt inTrailing);
    IEEEBinary (Float inNumber);

    // Implicit conversion to floating-point type.
    operator UInt () const;
    operator Float () const;

    // Assignment.
    IEEEBinary& operator= (IEEEBinary const& object);

    // Special constants.
    static int const NUM_ENCODING_BITS    = NumBits;
    static int const NUM_EXPONENT_BITS    = NumBits - Precision;
    static int const NUM_SIGNIFICAND_BITS = Precision;
    static int const NUM_TRAILING_BITS    = Precision - 1;
    static int const EXPONENT_BIAS        = (1 << (NUM_EXPONENT_BITS - 1)) - 1;
    static int const MAX_BIASED_EXPONENT  = (1 << NUM_EXPONENT_BITS) - 1;
    static int const MIN_SUB_EXPONENT     = 1 - EXPONENT_BIAS;
    static int const MIN_EXPONENT         = MIN_SUB_EXPONENT - NUM_TRAILING_BITS;
    static int const SIGN_SHIFT           = NumBits - 1;

    static UInt const SIGN_MASK           = (UInt(1) << (NumBits - 1));   
    static UInt const NOT_SIGN_MASK       = UInt(~SIGN_MASK);
    static UInt const TRAILING_MASK       = (UInt(1) << NUM_TRAILING_BITS) - 1;
    static UInt const EXPONENT_MASK       = NOT_SIGN_MASK & ~TRAILING_MASK;
    static UInt const NAN_QUIET_MASK      = (UInt(1) << (NUM_TRAILING_BITS - 1));
    static UInt const NAN_PAYLOAD_MASK    = (TRAILING_MASK >> 1);
    static UInt const MAX_TRAILING        = TRAILING_MASK;
    static UInt const SUP_TRAILING        = (UInt(1) << NUM_TRAILING_BITS);
    static UInt const POS_ZERO            = UInt(0);
    static UInt const NEG_ZERO            = SIGN_MASK;
    static UInt const MIN_SUBNORMAL       = UInt(1);
    static UInt const MAX_SUBNORMAL       = TRAILING_MASK;
    static UInt const MIN_NORMAL          = SUP_TRAILING;
    static UInt const MAX_NORMAL          = NOT_SIGN_MASK & ~SUP_TRAILING;
    static UInt const POS_INFINITY        = EXPONENT_MASK;
    static UInt const NEG_INFINITY        = SIGN_MASK | EXPONENT_MASK;

    // The types of numbers.
    enum Classification
    {
        CLASS_NEG_INFINITY,
        CLASS_NEG_SUBNORMAL,
        CLASS_NEG_NORMAL,
        CLASS_NEG_ZERO,
        CLASS_POS_ZERO,
        CLASS_POS_SUBNORMAL,
        CLASS_POS_NORMAL,
        CLASS_POS_INFINITY,
        CLASS_QUIET_NAN,
        CLASS_SIGNALING_NAN
    };

    Classification GetClassification () const;
    bool IsZero () const;
    bool IsSignMinus () const;
    bool IsSubnormal () const;
    bool IsNormal () const;
    bool IsFinite () const;
    bool IsInfinite () const;
    bool IsNaN () const;
    bool IsSignalingNaN () const;

    // Get neighboring numbers.
    UInt GetNextUp () const;
    UInt GetNextDown () const;

    // Encode and decode the binary representation.  The sign is 0 (number
    // is nonnegative) or 1 (number is negative).  The biased exponent is in
    // the range [0,MAX_BIASED_EXPONENT].  The trailing significand is in the
    // range [0,MAX_TRAILING].
    UInt GetSign () const;
    UInt GetBiased () const;
    UInt GetTrailing () const;
    void SetEncoding (UInt sign, UInt biased, UInt trailing);
    void GetEncoding (UInt& sign, UInt& biased, UInt& trailing) const;

    // Access for direct manipulation of the object.
    union
    {
        UInt encoding;
        Float number;
    };
};

#include "GteIEEEBinary.inl"

typedef IEEEBinary<float,uint32_t,32,24> IEEEBinary32;
typedef IEEEBinary<double,uint64_t,64,53> IEEEBinary64;

}
