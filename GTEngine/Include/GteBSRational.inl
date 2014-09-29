// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational()
    :
    mNumerator(0),
    mDenominator(1)
{
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(BSRational const& rational)
{
    *this = rational;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(BSRational&& rational)
{
    *this = std::move(rational);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(float numerator)
    :
    mNumerator(numerator),
    mDenominator(1.0f)
{

}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(double numerator)
    :
    mNumerator(numerator),
    mDenominator(1.0)
{

}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(int32_t numerator)
    :
    mNumerator(numerator),
    mDenominator(1)
{

}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(uint32_t numerator)
    :
    mNumerator(numerator),
    mDenominator(1)
{

}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(int64_t numerator)
    :
    mNumerator(numerator),
    mDenominator(1)
{

}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(uint64_t numerator)
    :
    mNumerator(numerator),
    mDenominator(1)
{

}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(BSNumber<UIntegerType> const& numerator)
    :
    mNumerator(numerator),
    mDenominator(1)
{
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(float numerator, float denominator)
    :
    mNumerator(numerator),
    mDenominator(denominator)
{
    LogAssert(mDenominator.mSign != 0, "Division by zero not allowed.");
    if (mDenominator.mSign < 0)
    {
        mNumerator.mSign = -mNumerator.mSign;
        mDenominator.mSign = 1;
    }
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(double numerator, double denominator)
    :
    mNumerator(numerator),
    mDenominator(denominator)
{
    LogAssert(mDenominator.mSign != 0, "Division by zero not allowed.");
    if (mDenominator.mSign < 0)
    {
        mNumerator.mSign = -mNumerator.mSign;
        mDenominator.mSign = 1;
    }
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::BSRational(BSNumber<UIntegerType> const& numerator,
    BSNumber<UIntegerType> const& denominator)
    :
    mNumerator(numerator),
    mDenominator(denominator)
{
    LogAssert(mDenominator.mSign != 0, "Division by zero not allowed.");
    if (mDenominator.mSign < 0)
    {
        mNumerator.mSign = -mNumerator.mSign;
        mDenominator.mSign = 1;
    }

    // Set the exponent of the denominator to zero, but you can do so only
    // by modifying the biased exponent.  Adjust the numerator accordingly.
    // This prevents large growth of the exponents in both numerator and
    // denominator simultaneously.  NOTE:  This is important until the TODOs
    // in 'operator float()' and 'operator double()' are implemented.
    mNumerator.mBiasedExponent -= mDenominator.GetExponent();
    mDenominator.mBiasedExponent = -(mDenominator.GetNumBits() - 1);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::operator float() const
{
    // TODO:  The number is abstractly of the form 1.u*2^p/1.v*2^q (ignoring
    // the sign).  Use a standard division algorithm to get a correctly
    // rounded result according to IEEE 74-2008 standards.
    return (float)mNumerator / (float)mDenominator;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>::operator double() const
{
    // TODO:  The number is abstractly of the form 1.u*2^p/1.v*2^q (ignoring
    // the sign).  Use a standard division algorithm to get a correctly
    // rounded result according to IEEE 74-2008 standards.
    return (double)mNumerator / (double)mDenominator;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>& BSRational<UIntegerType>::operator=(
    BSRational const& rational)
{
    if (this != &rational)
    {
        mNumerator = rational.mNumerator;
        mDenominator = rational.mDenominator;
    }
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>& BSRational<UIntegerType>::operator=(
    BSRational&& rational)
{
    if (this != &rational)
    {
        mNumerator = std::move(rational.mNumerator);
        mDenominator = std::move(rational.mDenominator);
    }
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
int BSRational<UIntegerType>::GetSign() const
{
    return mNumerator.GetSign() * mDenominator.GetSign();
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
BSNumber<UIntegerType> const& BSRational<UIntegerType>::GetNumerator() const
{
    return mNumerator;
}
//----------------------------------------------------------------------------
template <typename UIntegerType> inline
BSNumber<UIntegerType> const& BSRational<UIntegerType>::GetDenomator() const
{
    return mDenominator;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSRational<UIntegerType>::operator==(BSRational const& rational) const
{
    BSNumber<UIntegerType> product0 = mNumerator * rational.mDenominator;
    BSNumber<UIntegerType> product1 = mDenominator * rational.mNumerator;
    return product0 == product1;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSRational<UIntegerType>::operator!=(BSRational const& rational) const
{
    return !operator==(rational);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSRational<UIntegerType>::operator< (BSRational const& rational) const
{
    BSNumber<UIntegerType> product0 = mNumerator * rational.mDenominator;
    BSNumber<UIntegerType> product1 = mDenominator * rational.mNumerator;
    if (mDenominator.mSign > 0)
    {
        if (rational.mDenominator.mSign > 0)
        {
            return product0 < product1;
        }
        else
        {
            return product0 > product1;
        }
    }
    else
    {
        if (rational.mDenominator.mSign > 0)
        {
            return product0 > product1;
        }
        else
        {
            return product0 < product1;
        }
    }
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSRational<UIntegerType>::operator<=(BSRational const& rational) const
{
    return operator<(rational) || operator==(rational);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSRational<UIntegerType>::operator> (BSRational const& rational) const
{
    return !operator<=(rational);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
bool BSRational<UIntegerType>::operator>=(BSRational const& rational) const
{
    return !operator<(rational);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType> BSRational<UIntegerType>::operator+() const
{
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType> BSRational<UIntegerType>::operator-() const
{
    return BSRational(-mNumerator, mDenominator);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType> BSRational<UIntegerType>::operator+(
    BSRational const& rational) const
{
    BSNumber<UIntegerType> product0 = mNumerator * rational.mDenominator;
    BSNumber<UIntegerType> product1 = mDenominator * rational.mNumerator;
    BSNumber<UIntegerType> numerator = product0 + product1;
    BSNumber<UIntegerType> denominator = mDenominator * rational.mDenominator;
    return BSRational(numerator, denominator);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType> BSRational<UIntegerType>::operator-(
    BSRational const& rational) const
{
    BSNumber<UIntegerType> product0 = mNumerator * rational.mDenominator;
    BSNumber<UIntegerType> product1 = mDenominator * rational.mNumerator;
    BSNumber<UIntegerType> numerator = product0 - product1;
    BSNumber<UIntegerType> denominator = mDenominator * rational.mDenominator;
    return BSRational(numerator, denominator);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType> BSRational<UIntegerType>::operator*(
    BSRational const& rational) const
{
    BSNumber<UIntegerType> numerator = mNumerator * rational.mNumerator;
    BSNumber<UIntegerType> denominator = mDenominator * rational.mDenominator;
    return BSRational(numerator, denominator);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType> BSRational<UIntegerType>::operator/(
    BSRational const& rational) const
{
    LogAssert(rational.mNumerator.mSign != 0,
        "Division by zero not allowed.");

    BSNumber<UIntegerType> numerator = mNumerator * rational.mDenominator;
    BSNumber<UIntegerType> denominator = mDenominator * rational.mNumerator;
    if (denominator.mSign < 0)
    {
        numerator.mSign = -numerator.mSign;
        denominator.mSign = 1;
    }
    return BSRational(numerator, denominator);
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>& BSRational<UIntegerType>::operator+=(
    BSRational const& rational)
{
    *this = operator+(rational);
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>& BSRational<UIntegerType>::operator-=(
    BSRational const& rational)
{
    *this = operator-(rational);
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>& BSRational<UIntegerType>::operator*=(
    BSRational const& rational)
{
    *this = operator*(rational);
    return *this;
}
//----------------------------------------------------------------------------
template <typename UIntegerType>
BSRational<UIntegerType>& BSRational<UIntegerType>::operator/=(
    BSRational const& rational)
{
    *this = operator/(rational);
    return *this;
}
//----------------------------------------------------------------------------
