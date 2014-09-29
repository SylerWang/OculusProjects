// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber()
    :
    mSign(0),
    mBiasedExponent(0),
    mNumBits(0)
{
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(BSNumber const& number)
{
    *this = number;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(BSNumber&& number)
{
    *this = std::move(number);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(float number)
    :
    mBits(1)
{
    ConvertFrom<IEEEBinary32>(number);

    GET_BSNUMBER_MAXSIZE_UPDATE(mBits);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(double number)
    :
    mBits(2)
{
    ConvertFrom<IEEEBinary64>(number);

    GET_BSNUMBER_MAXSIZE_UPDATE(mBits);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(int32_t number)
    :
    mBits(1)
{
    if (number == 0)
    {
        mSign = 0;
        mBiasedExponent = 0;
        mNumBits = 0;
    }
    else
    {
        if (number < 0)
        {
            mSign = -1;
            number = -number;
        }
        else
        {
            mSign = 1;
        }

        int32_t first = GetLeadingBit(number);
        int32_t last = GetTrailingBit(number);
        mBiasedExponent = last;
        mNumBits = first - last + 1;
        mBits[0] = (number >> last);
    }

    GET_BSNUMBER_MAXSIZE_UPDATE(mBits);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(uint32_t number)
    :
    mBits(1)
{
    if (number == 0)
    {
        mSign = 0;
        mBiasedExponent = 0;
        mNumBits = 0;
    }
    else
    {
        mSign = 1;
        int32_t first = GetLeadingBit(number);
        int32_t last = GetTrailingBit(number);
        mBiasedExponent = last;
        mNumBits = first - last + 1;
        mBits[0] = (number >> last);
    }

    GET_BSNUMBER_MAXSIZE_UPDATE(mBits);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(int64_t number)
    :
    mBits(2)
{
    if (number == 0)
    {
        mSign = 0;
        mBiasedExponent = 0;
        mNumBits = 0;
    }
    else
    {
        if (number < 0)
        {
            mSign = -1;
            number = -number;
        }
        else
        {
            mSign = 1;
        }

        int32_t first = GetLeadingBit(number);
        int32_t last = GetTrailingBit(number);
        mBiasedExponent = last;
        mNumBits = first - last + 1;
        number >>= last;
        mBits[0] = GTE_GET_LO_U64(number);
        mBits[1] = GTE_GET_HI_U64(number);
    }

    GET_BSNUMBER_MAXSIZE_UPDATE(mBits);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(uint64_t number)
    :
    mBits(2)
{
    if (number == 0)
    {
        mSign = 0;
        mBiasedExponent = 0;
        mNumBits = 0;
    }
    else
    {
        mSign = 1;
        int32_t first = GetLeadingBit(number);
        int32_t last = GetTrailingBit(number);
        mBiasedExponent = last;
        mNumBits = first - last + 1;
        number >>= last;
        mBits[0] = GTE_GET_LO_U64(number);
        mBits[1] = GTE_GET_HI_U64(number);
    }

    GET_BSNUMBER_MAXSIZE_UPDATE(mBits);
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
BSNumber<UIntegerType>::operator float() const
{
    return ConvertTo<IEEEBinary32>();
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
inline BSNumber<UIntegerType>::operator double() const
{
    return ConvertTo<IEEEBinary64>();
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>& BSNumber<UIntegerType>::operator=(
    BSNumber const& number)
{
    if (this != &number)
    {
        mSign = number.mSign;
        mBiasedExponent = number.mBiasedExponent;
        mNumBits = number.mNumBits;
        mBits = number.mBits;
    }
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>& BSNumber<UIntegerType>::operator=(BSNumber&& number)
{
    if (this != &number)
    {
        mSign = number.mSign;
        mBiasedExponent = number.mBiasedExponent;
        mNumBits = number.mNumBits;
        mBits = std::move(number.mBits);
    }
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
int32_t BSNumber<UIntegerType>::GetSign() const
{
    return mSign;
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
int32_t BSNumber<UIntegerType>::GetBiasedExponent() const
{
    return mBiasedExponent;
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
int32_t BSNumber<UIntegerType>::GetExponent() const
{
    return mBiasedExponent + mNumBits - 1;
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
int32_t BSNumber<UIntegerType>::GetNumBits() const
{
    return mNumBits;
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
uint32_t const* BSNumber<UIntegerType>::GetBits() const
{
    return &mBits[0];
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::operator==(BSNumber const& number) const
{
    return (mSign == number.mSign ? EqualIgnoreSign(*this, number) : false);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::operator!=(BSNumber const& number) const
{
    return !operator==(number);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::operator<(BSNumber const& number) const
{
    if (mSign > 0)
    {
        if (number.mSign <= 0)
        {
            return false;
        }

        // Both numbers are positive.
        return LessThanIgnoreSign(*this, number);
    }
    else if (mSign < 0)
    {
        if (number.mSign >= 0)
        {
            return true;
        }

        // Both numbers are negative.
        return LessThanIgnoreSign(number, *this);
    }
    else
    {
        return number.mSign > 0;
    }
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::operator<=(BSNumber const& number) const
{
    return operator<(number) || operator==(number);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::operator>(BSNumber const& number) const
{
    return !operator<=(number);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::operator>=(BSNumber const& number) const
{
    return !operator<(number);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::operator+() const
{
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::operator-() const
{
    BSNumber result = *this;
    result.mSign = -result.mSign;
    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::operator+(BSNumber const& n1)
    const
{
    BSNumber const& n0 = *this;

    if (n0.mSign == 0)
    {
        return n1;
    }

    if (n1.mSign == 0)
    {
        return n0;
    }

    if (n0.mSign > 0)
    {
        if (n1.mSign > 0)
        {
            // n0 + n1 = |n0| + |n1|
            return AddIgnoreSign(n0, n1, +1);
        }
        else // n1.mSign < 0
        {
            if (!EqualIgnoreSign(n0, n1))
            {
                if (LessThanIgnoreSign(n1, n0))
                {
                    // n0 + n1 = |n0| - |n1| > 0
                    return SubIgnoreSign(n0, n1, +1);
                }
                else
                {
                    // n0 + n1 = -(|n1| - |n0|) < 0
                    return SubIgnoreSign(n1, n0, -1);
                }
            }
            // else n0 + n1 = 0
        }
    }
    else // n0.mSign < 0
    {
        if (n1.mSign < 0)
        {
            // n0 + n1 = -(|n0| + |n1|)
            return AddIgnoreSign(n0, n1, -1);
        }
        else // n1.mSign > 0
        {
            if (!EqualIgnoreSign(n0, n1))
            {
                if (LessThanIgnoreSign(n1, n0))
                {
                    // n0 + n1 = -(|n0| - |n1|) < 0
                    return SubIgnoreSign(n0, n1, -1);
                }
                else
                {
                    // n0 + n1 = |n1| - |n0| > 0
                    return SubIgnoreSign(n1, n0, +1);
                }
            }
            // else n0 + n1 = 0
        }
    }

    return BSNumber();  // = 0
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::operator-(BSNumber const& n1)
    const
{
    BSNumber const& n0 = *this;

    if (n0.mSign == 0)
    {
        return -n1;
    }

    if (n1.mSign == 0)
    {
        return n0;
    }

    if (n0.mSign > 0)
    {
        if (n1.mSign < 0)
        {
            // n0 - n1 = |n0| + |n1|
            return AddIgnoreSign(n0, n1, +1);
        }
        else // n1.mSign > 0
        {
            if (!EqualIgnoreSign(n0, n1))
            {
                if (LessThanIgnoreSign(n1, n0))
                {
                    // n0 - n1 = |n0| - |n1| > 0
                    return SubIgnoreSign(n0, n1, +1);
                }
                else
                {
                    // n0 - n1 = -(|n1| - |n0|) < 0
                    return SubIgnoreSign(n1, n0, -1);
                }
            }
            // else n0 - n1 = 0
        }
    }
    else // n0.mSign < 0
    {
        if (n1.mSign > 0)
        {
            // n0 - n1 = -(|n0| + |n1|)
            return AddIgnoreSign(n0, n1, -1);
        }
        else // n1.mSign < 0
        {
            if (!EqualIgnoreSign(n0, n1))
            {
                if (LessThanIgnoreSign(n1, n0))
                {
                    // n0 - n1 = -(|n0| - |n1|) < 0
                    return SubIgnoreSign(n0, n1, -1);
                }
                else
                {
                    // n0 - n1 = |n1| - |n0| > 0
                    return SubIgnoreSign(n1, n0, +1);
                }
            }
            // else n0 - n1 = 0
        }
    }

    return BSNumber();  // = 0
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::operator*(
    BSNumber const& number) const
{
    BSNumber result;  // = 0
    int sign = mSign*number.mSign;
    if (sign != 0)
    {
        // The sign must be set after the multiplication, because Mul applies
        // to two positive numbers.
        result = Mul(*this, number);
        result.mSign = sign;
        result.mBiasedExponent = mBiasedExponent + number.mBiasedExponent;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>& BSNumber<UIntegerType>::operator+=(
    BSNumber const& number)
{
    *this = operator+(number);
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>& BSNumber<UIntegerType>::operator-=(
    BSNumber const& number)
{
    *this = operator-(number);
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>& BSNumber<UIntegerType>::operator*= (
    BSNumber const& number)
{
    *this = operator*(number);
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType>::BSNumber(int32_t sign, int32_t numBits)
    :
    mSign(sign),
    mBiasedExponent(0),
    mNumBits(numBits),
    mBits(1 + (numBits - 1) / 32)
{
    GET_BSNUMBER_MAXSIZE_UPDATE(mBits);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::EqualIgnoreSign(BSNumber const& n0,
    BSNumber const& n1)
{
    if (n0.mBiasedExponent != n1.mBiasedExponent
        || n0.mNumBits != n1.mNumBits)
    {
        return false;
    }

    if (n0.mNumBits > 0)
    {
        int32_t const last = (n0.mNumBits - 1) / 32;
        for (int32_t i = last; i >= 0; --i)
        {
            if (n0.mBits[i] != n1.mBits[i])
            {
                return false;
            }
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSNumber<UIntegerType>::LessThanIgnoreSign(BSNumber const& n0,
    BSNumber const& n1)
{
    // This function acts as if both inputs are positive.
    int32_t e0 = n0.GetExponent(), e1 = n1.GetExponent();
    if (e0 < e1)
    {
        return true;
    }
    if (e0 > e1)
    {
        return false;
    }

    // The exponents are equal.  Compare the bits one 32-bit block at a time.
    // LessThanIgnoreSign is called only when n0 and n1 are not zero, so
    // block0 and block1 are initially nonnegative.
    int bitIndex0 = n0.mNumBits - 1;
    int bitIndex1 = n1.mNumBits - 1;
    int block0 = bitIndex0 / 32;
    int block1 = bitIndex1 / 32;
    int numBlockBits0 = 1 + (bitIndex0 % 32);
    int numBlockBits1 = 1 + (bitIndex1 % 32);
    uint64_t n0shift = n0.mBits[block0];
    uint64_t n1shift = n1.mBits[block1];
    while (block0 >= 0 && block1 >= 0)
    {
        // Shift the bits in the leading blocks to the high-order bit.
        uint32_t value0 = GTE_GET_LO_U64(n0shift << (32 - numBlockBits0));
        uint32_t value1 = GTE_GET_LO_U64(n1shift << (32 - numBlockBits1));

        // Shift bits in the next block (if any) to fill the current
        // block.
        if (--block0 >= 0)
        {
            n0shift = n0.mBits[block0];
            value0 |= GTE_GET_LO_U64(n0shift >> numBlockBits0);
        }
        if (--block1 >= 0)
        {
            n1shift = n1.mBits[block1];
            value1 |= GTE_GET_LO_U64(n1shift >> numBlockBits1);
        }
        if (value0 < value1)
        {
            return true;
        }
        if (value0 > value1)
        {
            return false;
        }
    }
    return block0 < block1;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::ShiftLeft(
    BSNumber const& number, int32_t shift)
{
    // Shift the 'number' considered as an odd positive integer.
    BSNumber result(1, number.mNumBits + shift);

    // Set the low-order bits to zero.
    int32_t const shiftBlock = shift / 32;
    for (int32_t i = 0; i < shiftBlock; ++i)
    {
        result.mBits[i] = 0;
    }

    // Get the location of the low-order 1-bit within the result.
    int32_t const numInElements = static_cast<int>(number.mBits.size());
    int32_t const numOutElements = static_cast<int>(result.mBits.size());
    int32_t const lshift = shift % 32;
    if (lshift > 0)
    {
        int32_t const rshift = 32 - lshift;
        uint32_t prev = 0;
        for (int32_t i = shiftBlock, j = 0; i < numOutElements; ++i, ++j)
        {
            uint32_t curr = (j < numInElements ? number.mBits[j] : 0);
            result.mBits[i] = (curr << lshift) | (prev >> rshift);
            prev = curr;
        }
    }
    else
    {
        for (int32_t i = shiftBlock, j = 0; i < numOutElements; ++i, ++j)
        {
            result.mBits[i] = number.mBits[j];
        }
    }

    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
int32_t BSNumber<UIntegerType>::Normalize(BSNumber& number)
{
    int32_t const numElements = static_cast<int>(number.mBits.size());

    // Get the leading 1-bit.
    int32_t firstBitIndex = -1;
    for (int32_t block = numElements - 1; block >= 0; --block)
    {
        uint32_t value = number.mBits[block];
        if (value > 0)
        {
            firstBitIndex = 32 * block + GetLeadingBit(value);
            break;
        }
    }

    // Get the trailing 1-bit.
    int32_t lastBitIndex = -1;
    for (int32_t block = 0; block < numElements; ++block)
    {
        uint32_t value = number.mBits[block];
        if (value > 0)
        {
            lastBitIndex = 32 * block + GetTrailingBit(value);
            break;
        }
    }

    int32_t const numBits = firstBitIndex - lastBitIndex + 1;
    int32_t const numBlocks = 1 + (numBits - 1) / 32;
    UIntegerType shiftedBits(numBlocks);

    // Get the location of the low-order 1-bit within the result.
    int32_t const shiftBlock = lastBitIndex / 32;
    int32_t rshift = lastBitIndex % 32;
    if (rshift > 0)
    {
        int32_t const lshift = 32 - rshift;
        int32_t j = shiftBlock;
        uint32_t curr = number.mBits[j++];
        for (int32_t i = 0; i < numBlocks; ++i, ++j)
        {
            uint32_t next = (j < numElements ? number.mBits[j] : 0);
            shiftedBits[i] = (curr >> rshift) | (next << lshift);
            curr = next;
        }
    }
    else
    {
        for (int32_t i = 0, j = shiftBlock; i < numBlocks; ++i, ++j)
        {
            shiftedBits[i] = number.mBits[j];
        }
    }

    number.mNumBits = numBits;
    number.mBits = std::move(shiftedBits);
    GET_BSNUMBER_MAXSIZE_UPDATE(number.mBits);
    return rshift + 32 * shiftBlock;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::AddIgnoreSign(
    BSNumber const& n0, BSNumber const& n1, int32_t resultSign)
{
    BSNumber result;

    int32_t diff = n0.mBiasedExponent - n1.mBiasedExponent;
    if (diff > 0)
    {
        result = std::move(Add(ShiftLeft(n0, diff), n1));
        result.mBiasedExponent = n1.mBiasedExponent;
    }
    else if (diff < 0)
    {
        result = std::move(Add(n0, ShiftLeft(n1, -diff)));
        result.mBiasedExponent = n0.mBiasedExponent;
    }
    else
    {
        result = std::move(Add(n0, n1));
        result.mBiasedExponent = n0.mBiasedExponent + Normalize(result);
    }

    result.mSign = resultSign;
    GET_BSNUMBER_MAXSIZE_UPDATE(result.mBits);
    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::SubIgnoreSign(
    BSNumber const& n0, BSNumber const& n1, int32_t resultSign)
{
    BSNumber result;

    int32_t diff = n0.mBiasedExponent - n1.mBiasedExponent;
    if (diff > 0)
    {
        result = std::move(Sub(ShiftLeft(n0, diff), n1));
        result.mBiasedExponent = n1.mBiasedExponent;
    }
    else if (diff < 0)
    {
        result = std::move(Sub(n0, ShiftLeft(n1, -diff)));
        result.mBiasedExponent = n0.mBiasedExponent;
    }
    else
    {
        result = std::move(Sub(n0, n1));
        result.mBiasedExponent = n0.mBiasedExponent + Normalize(result);
    }

    result.mSign = resultSign;
    GET_BSNUMBER_MAXSIZE_UPDATE(result.mBits);
    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::Add(BSNumber const& n0,
    BSNumber const& n1)
{
    // Add the numbers considered as positive integers.  Set the last block to
    // zero in case no carry-out occurs.
    BSNumber result(1, std::max(n0.mNumBits, n1.mNumBits) + 1);
    result.mBits.back() = 0;

    // Get the input array sizes.
    int32_t numElements0 = 1 + (n0.mNumBits - 1) / 32;
    int32_t numElements1 = 1 + (n1.mNumBits - 1) / 32;

    // Order the inputs so that the first has the most blocks.
    UIntegerType& v = result.mBits;
    UIntegerType const& u0 =
        (numElements0 >= numElements1 ? n0.mBits : n1.mBits);
    UIntegerType const& u1 =
        (numElements0 >= numElements1 ? n1.mBits : n0.mBits);
    auto numElements = std::minmax(numElements0, numElements1);

    // Add the u1-blocks to u0-blocks.
    uint64_t carry = 0, sum;
    int32_t i;
    for (i = 0; i < numElements.first; ++i)
    {
        sum = u0[i] + (u1[i] + carry);
        v[i] = GTE_GET_LO_U64(sum);
        carry = GTE_GET_HI_U64(sum);
    }

    // We have no more u1-blocks. Propagate the carry-out, if there is one, or
    // copy the remaining blocks if there is not.
    if (carry > 0)
    {
        for (/**/; i < numElements.second; ++i)
        {
            sum = u0[i] + carry;
            v[i] = GTE_GET_LO_U64(sum);
            carry = GTE_GET_HI_U64(sum);
        }
        if (carry > 0)
        {
            v[i] = GTE_GET_LO_U64(carry);
        }
    }
    else
    {
        for (/**/; i < numElements.second; ++i)
        {
            v[i] = u0[i];
        }
    }

    result.ReduceBits();
    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::Sub(BSNumber const& n0,
    BSNumber const& n1)
{
    // Subtract the numbers considered as positive integers.  We know that
    // n0 >= n1, so create a number n2 that has the same number of bits as
    // n0 and use two's-complement to generate -n2, and then add n0 and -n2.
    // The result is nonnegative, so we do not need to apply two's complement
    // to a negative result to extract the sign and absolute value.

    // Get the input array sizes.  We know numElements0 >= numElements1.
    int32_t numElements0 = 1 + (n0.mNumBits - 1) / 32;
    int32_t numElements1 = 1 + (n1.mNumBits - 1) / 32;

    // Create the two's-complement number n2.  We allocate one extra bit to
    // ensure the the high-order bit is truly a two's-complement sign bit;
    // that is, a high-order 1-bit is part of the number n1, so we need an
    // additional bit for the sign bit.
    BSNumber n2(1, n0.mNumBits + 1);
    int32_t numElements2 = static_cast<int>(n2.mBits.size());
    int32_t i;
    for (i = 0; i < numElements1; ++i)
    {
        n2.mBits[i] = ~n1.mBits[i];
    }
    for (/**/; i < numElements2; ++i)
    {
        n2.mBits[i] = ~0u;
    }

    // Now add 1 to the bit-negated result to obtain -n1.
    uint64_t carry = 1, sum;
    for (i = 0; i < numElements2; ++i)
    {
        sum = n2.mBits[i] + carry;
        n2.mBits[i] = GTE_GET_LO_U64(sum);
        carry = GTE_GET_HI_U64(sum);
    }

    // Add the numbers considered as positive integers.  Set the last block to
    // zero in case no carry-out occurs.
    BSNumber result(1, n2.mNumBits + 1);
    result.mBits.back() = 0;

    // Add the n0-blocks to n2-blocks.
    for (i = 0, carry = 0; i < numElements0; ++i)
    {
        sum = n2.mBits[i] + (n0.mBits[i] + carry);
        result.mBits[i] = GTE_GET_LO_U64(sum);
        carry = GTE_GET_HI_U64(sum);
    }

    // We have no more n0-blocks. Propagate the carry-out, if there is
    // one, or copy the remaining blocks if there is not.
    if (carry > 0)
    {
        for (/**/; i < numElements2; ++i)
        {
            sum = n2.mBits[i] + carry;
            result.mBits[i] = GTE_GET_LO_U64(sum);
            carry = GTE_GET_HI_U64(sum);
        }
    }
    else
    {
        for (/**/; i < numElements2; ++i)
        {
            result.mBits[i] = n2.mBits[i];
        }
    }

    // Strip off the bits introduced by two's-complement.
    result.ReduceBlocks(numElements0 - 1);
    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSNumber<UIntegerType> BSNumber<UIntegerType>::Mul(BSNumber const& n0,
    BSNumber const& n1)
{
    // Multiply the numbers consider as positive integers.

    // The number of bits is at most this, possibly one bit smaller.
    // TODO: It would be nice to avoid the std::fill, but 'result' is used as
    // an accumulator later, which assumes it is zeroed.  We would have to
    // copy p[] to v[] when i0 = 0 but then accumulate on subsequent
    // passes.
    BSNumber result(1, n0.mNumBits + n1.mNumBits);
    int32_t const n = static_cast<int>(result.mBits.size());
    std::fill(&result.mBits[0], &result.mBits[0] + n, 0);

    // Product of a single-block number with a multiple-block number.
    UIntegerType product(n);

    // Get the input array sizes.
    int32_t const numElements0 = 1 + (n0.mNumBits - 1) / 32;
    int32_t const numElements1 = 1 + (n1.mNumBits - 1) / 32;

    // Compute the product v = u0*u1.
    for (int32_t i0 = 0; i0 < numElements0; ++i0)
    {
        // Compute the product p = u0[i0]*u1.
        uint64_t block0 = n0.mBits[i0];
        uint64_t carry = 0;
        int32_t i1, i2;
        for (i1 = 0, i2 = i0; i1 < numElements1; ++i1, ++i2)
        {
            uint64_t block1 = n1.mBits[i1];
            uint64_t term = block0 * block1 + carry;
            product[i2] = GTE_GET_LO_U64(term);
            carry = GTE_GET_HI_U64(term);
        }
        if (i2 < n)
        {
            product[i2] = static_cast<uint32_t>(carry);
        }

        // Add p to the accumulator v.
        carry = 0;
        for (i1 = 0, i2 = i0; i1 < numElements1; ++i1, ++i2)
        {
            uint64_t sum = product[i2] + (result.mBits[i2] + carry);
            result.mBits[i2] = GTE_GET_LO_U64(sum);
            carry = GTE_GET_HI_U64(sum);
        }
        if (i2 < n)
        {
            uint64_t sum = product[i2] + (result.mBits[i2] + carry);
            result.mBits[i2] = GTE_GET_LO_U64(sum);
        }
    }

    result.ReduceBits();
    return result;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
void BSNumber<UIntegerType>::ReduceBits()
{
    uint32_t firstBitIndex = (mNumBits - 1) % 32;
    uint32_t mask = (1 << firstBitIndex);
    if ((mask & mBits.back()) == 0)
    {
        --mNumBits;
    }
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
void BSNumber<UIntegerType>::ReduceBlocks(int32_t startBlock)
{
    int32_t block;
    for (block = startBlock; block >= 0; --block)
    {
        if (mBits[block] > 0)
        {
            break;
        }
    }
    mNumBits = 32 * block + GetLeadingBit(mBits[block]) + 1;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
uint64_t BSNumber<UIntegerType>::GetPrefix(int numRequested) const
{
    // Copy to 'prefix' the leading 32-bit block that is nonzero.
    int32_t bitIndex = mNumBits - 1;
    int32_t blockIndex = bitIndex / 32;
    uint64_t prefix = mBits[blockIndex];

    // Get the number of bits in the block starting with the leading 1-bit.
    int32_t firstBitIndex = bitIndex % 32;
    int32_t numBlockBits = firstBitIndex + 1;

    // Shift the leading 1-bit to bit-63 of prefix.  We have consumed
    // numBlockBits, which not be the entire budget.
    int32_t targetIndex = 63;
    prefix <<= targetIndex - firstBitIndex;
    numRequested -= numBlockBits;
    targetIndex -= numBlockBits;

    if (numRequested > 0 && --blockIndex >= 0)
    {
        // More bits are available.  Copy and shift the entire 32-bit next
        // block and OR it into the 'prefix'.  For 'float', we will have
        // consumed the entire budget.  For 'double', we might have to get
        // bits from a third block.
        uint64_t nextBlock = mBits[blockIndex];
        nextBlock <<= targetIndex - 31;  // Shift amount is positive.
        prefix |= nextBlock;
        numRequested -= 32;
        targetIndex -= 32;

        if (numRequested > 0 && --blockIndex >= 0)
        {
            // We know that targetIndex > 0; only 'double' allows us to get
            // here, so numRequested is at most 53.  We also know that
            // targetIndex < 32 because we started with 63 and subtracted
            // at least 32 from it.  Thus, the shift amount is positive.
            nextBlock = mBits[blockIndex];
            nextBlock >>= 31 - targetIndex;
            prefix |= nextBlock;
        }
    }

    return prefix;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
template <typename IEEE>
void BSNumber<UIntegerType>::ConvertFrom(typename IEEE::FloatType number)
{
    IEEE x(number);

    // Extract sign s, biased exponent e, and trailing significand t.
    typename IEEE::UIntType s = x.GetSign();
    typename IEEE::UIntType e = x.GetBiased();
    typename IEEE::UIntType t = x.GetTrailing();

    if (e == 0)
    {
        if (t == 0)  // zeros
        {
            // x = (-1)^s * 0
            mSign = 0;
            mBiasedExponent = 0;
            mNumBits = 0;
        }
        else  // subnormal numbers
        {
            // x = (-1)^s * 0.t * 2^{1-EXPONENT_BIAS}
            int32_t first = GetLeadingBit(t);
            int32_t last = GetTrailingBit(t);
            int32_t diff = IEEE::NUM_TRAILING_BITS - last;
            mSign = (s > 0 ? -1 : 1);
            mBiasedExponent = IEEE::MIN_SUB_EXPONENT - diff;
            InitializeBits<IEEE>(first - last + 1, t >> last);
        }
    }
    else if (e < IEEE::MAX_BIASED_EXPONENT)  // normal numbers
    {
        // x = (-1)^s * 1.t * 2^{e-EXPONENT_BIAS}
        if (t > 0)
        {
            int32_t last = GetTrailingBit(t);
            int32_t diff = IEEE::NUM_TRAILING_BITS - last;
            mSign = (s > 0 ? -1 : 1);
            mBiasedExponent =
                static_cast<int32_t>(e) - IEEE::EXPONENT_BIAS - diff;
            InitializeBits<IEEE>(diff + 1, (t | IEEE::SUP_TRAILING) >> last);
        }
        else
        {
            mSign = (s > 0 ? -1 : 1);
            mBiasedExponent = static_cast<int32_t>(e) - IEEE::EXPONENT_BIAS;
            InitializeBits<IEEE>(1, 1);
        }
    }
    else  // e == MAX_BIASED_EXPONENT, special numbers
    {
        if (t == 0)  // infinities
        {
            // x = (-1)^s * infinity
            LogWarning("Input is " + std::string(s > 0 ? "-" : "+") +
                "infinity.");

            // Return (-1)^s * 2^{1+EXPONENT_BIAS} for a graceful exit.
            mSign = (s > 0 ? -1 : 1);
            mBiasedExponent = 1 + IEEE::EXPONENT_BIAS;
            InitializeBits<IEEE>(1, 1);
        }
        else  // not-a-number (NaN)
        {
            LogError("Input is a " +
                std::string(t & IEEE::NAN_QUIET_MASK ?
                "quiet" : "signaling") + " NaN with payload " +
                std::to_string(t & IEEE::NAN_PAYLOAD_MASK) + ".");

            // Return 0 for a graceful exit.
            mSign = 0;
            mBiasedExponent = 0;
            mNumBits = 0;
        }
    }
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
template <typename IEEE>
typename IEEE::FloatType BSNumber<UIntegerType>::ConvertTo() const
{
    typename IEEE::UIntType s = (mSign < 0 ? 1 : 0);
    typename IEEE::UIntType e, t;

    if (mSign != 0)
    {
        // The conversions use round-to-nearest-ties-to-even semantics.
        int32_t exponent = GetExponent();
        if (exponent < IEEE::MIN_EXPONENT)
        {
            if (exponent < IEEE::MIN_EXPONENT - 1
                || mNumBits == 1)  // x = 1.0*2^{MIN_EXPONENT-1}
            {
                // Round to zero.
                e = 0;
                t = 0;
            }
            else
            {
                // Round to min subnormal.
                e = 0;
                t = 1;
            }
        }
        else if (exponent < IEEE::MIN_SUB_EXPONENT)
        {
            // The second input is in {0, ..., NUM_TRAILING_BITS-1}.
            t = GetTrailing<IEEE>(0, IEEE::MIN_SUB_EXPONENT - exponent - 1);
            if (t & IEEE::SUP_TRAILING)
            {
                // Leading NUM_SIGNIFICAND_BITS bits were all 1, so round to
                // min normal.
                e = 1;
                t = 0;
            }
            else
            {
                e = 0;
            }
        }
        else if (exponent <= IEEE::EXPONENT_BIAS)
        {
            e = static_cast<uint32_t>(exponent + IEEE::EXPONENT_BIAS);
            t = GetTrailing<IEEE>(1, 0);
            if (t & (IEEE::SUP_TRAILING << 1))
            {
                // Carry-out occurred, so increase exponent by 1 and
                // shift right to compensate.
                ++e;
                t >>= 1;
            }
            // Eliminate the leading 1 (implied for normals).
            t &= ~IEEE::SUP_TRAILING;
        }
        else
        {
            // Set to infinity.
            e = IEEE::MAX_BIASED_EXPONENT;
            t = 0;
        }
    }
    else
    {
        // The input is zero.
        e = 0;
        t = 0;
    }

    IEEE x(s, e, t);
    return x.number;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
template <typename IEEE>
void BSNumber<UIntegerType>::InitializeBits(int32_t numBits,
    typename IEEE::UIntType bits)
{
    uint64_t localBits = bits;
    mNumBits = numBits;
    mBits[0] = GTE_GET_LO_U64(localBits);
    if (mBits.size() > 1)
    {
        mBits[1] = GTE_GET_HI_U64(localBits);
    }
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
template <typename IEEE>
typename IEEE::UIntType BSNumber<UIntegerType>::GetTrailing(int32_t normal,
    int32_t sigma) const
{
    int32_t const numRequested = IEEE::NUM_SIGNIFICAND_BITS + normal;

    // We need numRequested bits to determine rounding direction.  These are
    // stored in the high-order bits of 'prefix'.
    uint64_t prefix = GetPrefix(numRequested);

    // The first bit index after the implied binary point for rounding.
    int32_t diff = numRequested - sigma;
    int32_t roundBitIndex = 64 - diff;

    // Determine rounding value based on round-to-nearest-ties-to-even.
    uint64_t mask = (GTE_U64(1) << roundBitIndex);
    uint64_t round;
    if (prefix & mask)
    {
        // The first bit of the remainder is 1.
        if (mNumBits == diff)
        {
            // The first bit of the remainder is the lowest-order bit of
            // mBits[0].  Apply the ties-to-even rule.
            if (prefix & (mask << 1))
            {
                // The last bit of the trailing significand is odd, so
                // round up.
                round = 1;
            }
            else
            {
                // The last bit of the trailing significand is even, so
                // round down.
                round = 0;
            }
        }
        else
        {
            // The first bit of the remainder is not the lowest-order bit of
            // mBits[0].  The remainder as a fraction is larger than 1/2, so
            // round up.
            round = 1;
        }
    }
    else
    {
        // The first bit of the remainder is 0, so round down.
        round = 0;
    }

    // Get the unrounded trailing significand.
    uint64_t trailing = prefix >> (roundBitIndex + 1);

    // Apply the rounding.
    trailing += round;
    return static_cast<typename IEEE::UIntType>(trailing);
}
//----------------------------------------------------------------------------
