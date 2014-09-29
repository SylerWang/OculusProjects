// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <size_t N>
BSUInteger<N>::BSUInteger(size_t size)
    :
    mSize(size)
{
#if defined(GTE_ASSERT_ON_BSUINTEGER_OUT_OF_RANGE)
    LogAssert(size <= N, "Class is not large enough to store size.");
#endif
}
//----------------------------------------------------------------------------
template <size_t N>
BSUInteger<N>::BSUInteger(BSUInteger const& number)
    :
    mSize(number.mSize),
    mElements(number.mElements)
{
}
//----------------------------------------------------------------------------
template <size_t N>
BSUInteger<N>::BSUInteger(BSUInteger&& number)
    :
    mSize(number.mSize),
    mElements(number.mElements)
{
    // There is no 'move' to apply to number.mElements, so this is a copy.
}
//----------------------------------------------------------------------------
template <size_t N>
BSUInteger<N>& BSUInteger<N>::operator=(BSUInteger const& number)
{
    mSize = number.mSize;
    mElements = number.mElements;
    return *this;
}
//----------------------------------------------------------------------------
template <size_t N>
BSUInteger<N>& BSUInteger<N>::operator=(BSUInteger&& number)
{
    // There is no 'move' to apply to number.mElements, so this is a copy.
    mSize = number.mSize;
    mElements = number.mElements;
    return *this;
}
//----------------------------------------------------------------------------
template <size_t N> inline
size_t BSUInteger<N>::size() const
{
    return mSize;
}
//----------------------------------------------------------------------------
template <size_t N>
uint32_t& BSUInteger<N>::operator[](int32_t i)
{
#if defined(GTE_ASSERT_ON_BSUINTEGER_OUT_OF_RANGE)
    if (0 <= i && i < static_cast<int>(mSize))
    {
        return mElements[i];
    }
    else
    {
        LogError("Invalid index in BSUInteger::operator[].");
        return mElements[0];
    }
#else
    return mElements[i];
#endif
}
//----------------------------------------------------------------------------
template <size_t N>
uint32_t const& BSUInteger<N>::operator[](int32_t i) const
{
#if defined(GTE_ASSERT_ON_BSUINTEGER_OUT_OF_RANGE)
    if (0 <= i && i < static_cast<int>(mSize))
    {
        return mElements[i];
    }
    else
    {
        LogError("Invalid index in BSUInteger::operator[].");
        return mElements[0];
    }
#else
    return mElements[i];
#endif
}
//----------------------------------------------------------------------------
template <size_t N>
uint32_t& BSUInteger<N>::back()
{
#if defined(GTE_ASSERT_ON_BSUINTEGER_OUT_OF_RANGE)
    LogAssert(mSize > 0, "Empty BSUInteger, cannot get back element.");
#endif
    return mElements[mSize - 1];
}
//----------------------------------------------------------------------------
template <size_t N>
uint32_t const& BSUInteger<N>::back() const
{
#if defined(GTE_ASSERT_ON_BSUINTEGER_OUT_OF_RANGE)
    LogAssert(mSize > 0, "Empty BSUInteger, cannot get back element.");
#endif
    return mElements[mSize - 1];
}
//----------------------------------------------------------------------------
