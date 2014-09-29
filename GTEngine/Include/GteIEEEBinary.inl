// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::~IEEEBinary ()
{
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::IEEEBinary ()
{
    // The member mEncoding is uninitialized.
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::IEEEBinary (
    IEEEBinary const& object)
    :
    encoding(object.encoding)
{
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::IEEEBinary (UInt inEncoding)
    :
    encoding(inEncoding)
{
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::IEEEBinary (UInt inSign,
    UInt inBiased, UInt inTrailing)
{
    SetEncoding(inSign, inBiased, inTrailing);
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::IEEEBinary (Float inNumber)
    :
    number(inNumber)
{
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::operator UInt () const
{
    return encoding;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>::operator Float () const
{
    return number;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
IEEEBinary<Float,UInt,NumBits,Precision>&
IEEEBinary<Float,UInt,NumBits,Precision>::operator= (IEEEBinary const& object)
{
    encoding = object.encoding;
    return *this;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
typename IEEEBinary<Float,UInt,NumBits,Precision>::Classification
IEEEBinary<Float,UInt,NumBits,Precision>::GetClassification () const
{
    UInt sign, biased, trailing;
    GetEncoding(sign, biased, trailing);

    if (biased == 0)
    {
        if (trailing == 0)
        {
            return (sign != 0 ? CLASS_NEG_ZERO : CLASS_POS_ZERO);
        }
        else
        {
            return (sign != 0 ? CLASS_NEG_SUBNORMAL : CLASS_POS_SUBNORMAL);
        }
    }
    else if (biased < MAX_BIASED_EXPONENT)
    {
        return (sign != 0 ? CLASS_NEG_NORMAL : CLASS_POS_NORMAL);
    }
    else if (trailing == 0)
    {
        return (sign != 0 ? CLASS_NEG_INFINITY : CLASS_POS_INFINITY);
    }
    else if (trailing & NAN_QUIET_MASK)
    {
        return CLASS_QUIET_NAN;
    }
    else
    {
        return CLASS_SIGNALING_NAN;
    }
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsZero () const
{
    return encoding == POS_ZERO || encoding == NEG_ZERO;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsSignMinus () const
{
    return (encoding & SIGN_MASK) != 0;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsSubnormal () const
{
    return GetBiased() == 0 && GetTrailing() > 0;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsNormal () const
{
    UInt biased = GetBiased();
    return 0 < biased && biased < MAX_BIASED_EXPONENT;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsFinite () const
{
    return GetBiased() < MAX_BIASED_EXPONENT;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsInfinite () const
{
    return GetBiased() == MAX_BIASED_EXPONENT && GetTrailing() == 0;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsNaN () const
{
    return GetBiased() == MAX_BIASED_EXPONENT && GetTrailing() != 0;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
bool IEEEBinary<Float,UInt,NumBits,Precision>::IsSignalingNaN () const
{
    UInt trailing = GetTrailing();
    return GetBiased() == MAX_BIASED_EXPONENT
        && (trailing & NAN_QUIET_MASK) == 0
        && (trailing & NAN_PAYLOAD_MASK) != 0;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
UInt IEEEBinary<Float,UInt,NumBits,Precision>::GetNextUp () const
{
    UInt sign, biased, trailing;
    GetEncoding(sign, biased, trailing);

    if (biased == 0)
    {
        if (trailing == 0)
        {
            // The next-up for both -0 and +0 is MIN_SUBNORMAL.
            return MIN_SUBNORMAL;
        }
        else
        {
            if (sign != 0)
            {
                // When trailing is 1, 'this' is -MIN_SUBNORMAL and next-up
                // is -0.
                --trailing;
                return SIGN_MASK | trailing;
            }
            else
            {
                // When trailing is MAX_TRAILING, 'this' is MAX_SUBNORMAL
                // and next-up is MIN_NORMAL.
                ++trailing;
                return trailing;
            }
        }
    }
    else if (biased < MAX_BIASED_EXPONENT)
    {
        UInt nonnegative = (encoding & NOT_SIGN_MASK);
        if (sign != 0)
        {
            --nonnegative;
            return SIGN_MASK | nonnegative;
        }
        else
        {
            ++nonnegative;
            return nonnegative;
        }
    }
    else if (trailing == 0)
    {
        if (sign != 0)
        {
            // The next-up of -INFINITY is -MAX_NORMAL.
            return SIGN_MASK | MAX_NORMAL;
        }
        else
        {
            // The next-up of +INFINITY is +INFINITY.
            return POS_INFINITY;
        }
    }
    else if (trailing & NAN_QUIET_MASK)
    {
        // TODO.  The IEEE standard is not clear what to do here.  Figure
        // out what it means.
        return 0;
    }
    else
    {
        // TODO.  The IEEE standard is not clear what to do here.  Figure
        // out what it means.
        return 0;
    }
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
UInt IEEEBinary<Float,UInt,NumBits,Precision>::GetNextDown () const
{
    UInt sign, biased, trailing;
    GetEncoding(sign, biased, trailing);

    if (biased == 0)
    {
        if (trailing == 0)
        {
            // The next-down for both -0 and +0 is -MIN_SUBNORMAL.
            return SIGN_MASK | MIN_SUBNORMAL;
        }
        else
        {
            if (sign == 0)
            {
                // When trailing is 1, 'this' is MIN_SUBNORMAL and next-down
                // is +0.
                --trailing;
                return trailing;
            }
            else
            {
                // When trailing is MAX_TRAILING, 'this' is -MAX_SUBNORMAL
                // and next-down is -MIN_NORMAL.
                ++trailing;
                return SIGN_MASK | trailing;
            }
        }
    }
    else if (biased < MAX_BIASED_EXPONENT)
    {
        UInt nonnegative = (encoding & NOT_SIGN_MASK);
        if (sign == 0)
        {
            --nonnegative;
            return nonnegative;
        }
        else
        {
            ++nonnegative;
            return SIGN_MASK | nonnegative;
        }
    }
    else if (trailing == 0)
    {
        if (sign == 0)
        {
            // The next-down of +INFINITY is +MAX_NORMAL.
            return MAX_NORMAL;
        }
        else
        {
            // The next-down of -INFINITY is -INFINITY.
            return NEG_INFINITY;
        }
    }
    else if (trailing & NAN_QUIET_MASK)
    {
        // TODO.  The IEEE standard is not clear what to do here.  Figure
        // out what it means.
        return 0;
    }
    else
    {
        // TODO.  The IEEE standard is not clear what to do here.  Figure
        // out what it means.
        return 0;
    }
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
UInt IEEEBinary<Float,UInt,NumBits,Precision>::GetSign () const
{
    return (encoding & SIGN_MASK) >> SIGN_SHIFT;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
UInt IEEEBinary<Float,UInt,NumBits,Precision>::GetBiased () const
{
    return (encoding & EXPONENT_MASK) >> NUM_TRAILING_BITS;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
UInt IEEEBinary<Float,UInt,NumBits,Precision>::GetTrailing () const
{
    return encoding & TRAILING_MASK;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
void IEEEBinary<Float,UInt,NumBits,Precision>::SetEncoding (UInt sign,
    UInt biased, UInt trailing)
{
    encoding =
        (sign << SIGN_SHIFT) | (biased << NUM_TRAILING_BITS) | trailing;
}
//----------------------------------------------------------------------------
template <typename Float, typename UInt, int NumBits, int Precision>
void IEEEBinary<Float,UInt,NumBits,Precision>::GetEncoding (UInt& sign,
    UInt& biased, UInt& trailing) const
{
    sign = GetSign();
    biased = GetBiased();
    trailing = GetTrailing();
}
//----------------------------------------------------------------------------
