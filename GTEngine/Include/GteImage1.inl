// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/25)

//----------------------------------------------------------------------------
template <typename PixelType>
Image1<PixelType>::~Image1()
{
    //static_assert(std::is_trivially_copyable<PixelType>::value,
    //    "PixelType must be trivially copyable.");
}
//----------------------------------------------------------------------------
template <typename PixelType>
Image1<PixelType>::Image1()
    :
    Image(typeid(PixelType).name(), sizeof(PixelType), 1, 0),
    mPixels(nullptr)
{
}
//----------------------------------------------------------------------------
template <typename PixelType>
Image1<PixelType>::Image1(Image1 const& image)
    :
    Image(image),
    mPixels((PixelType*)mRawPixels)
{
}
//----------------------------------------------------------------------------
template <typename PixelType>
Image1<PixelType>::Image1(int dimension)
    :
    Image(typeid(PixelType).name(), sizeof(PixelType), 1, dimension),
    mPixels((PixelType*)mRawPixels)
{
}
//----------------------------------------------------------------------------
template <typename PixelType>
Image1<PixelType>& Image1<PixelType>::operator= (Image1 const& image)
{
    bool compatible = Copy(image);
    if (!compatible)
    {
        mPixels = (PixelType*)mRawPixels;
    }
    return *this;
}
//----------------------------------------------------------------------------
template <typename PixelType>
inline PixelType* Image1<PixelType>::GetPixels1D()
{
    return mPixels;
}
//----------------------------------------------------------------------------
template <typename PixelType>
inline PixelType& Image1<PixelType>::operator[] (size_t i)
{
#if defined(GTE_IMAGICS_ASSERT_ON_INVALID_INDEX)
    if (mPixels && i < mNumPixels)
    {
        return mPixels[i];
    }
    LogError("No pixels or invalid index " + std::to_string(i) + ".");
    return mInvalidPixel;
#else
    return mPixels[i];
#endif
}
//----------------------------------------------------------------------------
template <typename PixelType>
inline PixelType const& Image1<PixelType>::operator[] (size_t i) const
{
#if defined(GTE_IMAGICS_ASSERT_ON_INVALID_INDEX)
    if (mPixels && i < mNumPixels)
    {
        return mPixels[i];
    }
    LogError("No pixels or invalid index " + std::to_string(i) + ".");
    return mInvalidPixel;
#else
    return mPixels[i];
#endif
}
//----------------------------------------------------------------------------
template <typename PixelType>
PixelType& Image1<PixelType>::Get(size_t i)
{
    if (mPixels)
    {
        if (i >= mNumPixels)
        {
            i = mNumPixels - 1;
        }
        return mPixels[i];
    }
    return mInvalidPixel;
}
//----------------------------------------------------------------------------
template <typename PixelType>
PixelType const& Image1<PixelType>::Get(size_t i) const
{
    if (mPixels)
    {
        if (i >= mNumPixels)
        {
            i = mNumPixels - 1;
        }
        return mPixels[i];
    }
    return mInvalidPixel;
}
//----------------------------------------------------------------------------
template <typename PixelType>
inline PixelType& Image1<PixelType>::operator() (int x)
{
#if defined(GTE_IMAGICS_ASSERT_ON_INVALID_INDEX)
    if (mPixels != 0 && 0 <= x && x < mDimensions[0])
    {
        return mPixels[x];
    }
    LogError("No pixels or invalid index " + std::to_string(x) + ".");
    return mInvalidPixel;
#else
    return mPixels[x];
#endif
}
//----------------------------------------------------------------------------
template <typename PixelType>
inline PixelType const& Image1<PixelType>::operator() (int x) const
{
#if defined(GTE_IMAGICS_ASSERT_ON_INVALID_INDEX)
    if (mPixels != 0 && 0 <= x && x < mDimensions[0])
    {
        return mPixels[x];
    }
    LogError("No pixels or invalid index " + std::to_string(x) + ".");
    return mInvalidPixel;
#else
    return mPixels[x];
#endif
}
//----------------------------------------------------------------------------
template <typename PixelType>
inline PixelType& Image1<PixelType>::operator() (
    std::array<int, 1> const& coord)
{
#if defined(GTE_IMAGICS_ASSERT_ON_INVALID_INDEX)
    if (mPixels != 0 && 0 <= coord[0] && coord[0] < mDimensions[0])
    {
        return mPixels[coord[0]];
    }
    LogError("No pixels or invalid index " + std::to_string(coord[0]) + ".");
    return mInvalidPixel;
#else
    return mPixels[coord[0]];
#endif
}
//----------------------------------------------------------------------------
template <typename PixelType>
inline PixelType const& Image1<PixelType>::operator() (
    std::array<int, 1> const& coord) const
{
#if defined(GTE_IMAGICS_ASSERT_ON_INVALID_INDEX)
    if (mPixels != 0 && 0 <= coord[0] && coord[0] < mDimensions[0])
    {
        return mPixels[coord[0]];
    }
    LogError("No pixels or invalid index " + std::to_string(coord[0]) + ".");
    return mInvalidPixel;
#else
    return mPixels[coord[0]];
#endif
}
//----------------------------------------------------------------------------
template <typename PixelType>
PixelType& Image1<PixelType>::Get(std::array<int, 1> coord)
{
    if (mPixels)
    {
        // Clamp to valid (x).
        if (coord[0] < 0)
        {
            coord[0] = 0;
        }
        else if (coord[0] >= mDimensions[0])
        {
            coord[0] = mDimensions[0] - 1;
        }

        return mPixels[coord[0]];
    }
    return mInvalidPixel;
}
//----------------------------------------------------------------------------
template <typename PixelType>
PixelType const& Image1<PixelType>::Get(std::array<int, 1> coord) const
{
    if (mPixels)
    {
        // Clamp to valid (x).
        if (coord[0] < 0)
        {
            coord[0] = 0;
        }
        else if (coord[0] >= mDimensions[0])
        {
            coord[0] = mDimensions[0] - 1;
        }

        return mPixels[coord[0]];
    }
    return mInvalidPixel;
}
//----------------------------------------------------------------------------
template <typename PixelType>
bool Image1<PixelType>::Resize(int dimension)
{
    if (Image::Resize(1, dimension))
    {
        mPixels = (PixelType*)mRawPixels;
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename PixelType>
void Image1<PixelType>::SetAllPixels(PixelType const& value)
{
    if (mPixels)
    {
        for (size_t i = 0; i < mNumPixels; ++i)
        {
            mPixels[i] = value;
        }
    }
}
//----------------------------------------------------------------------------
template <typename PixelType>
bool Image1<PixelType>::Load(std::string const& filename)
{
    std::vector<int> numDimensions(1);
    numDimensions[0] = mNumDimensions;

    std::vector<std::string> pixelTypes(1);
    pixelTypes[0] = mPixelType;

    if (Image::Load(filename, &numDimensions, &pixelTypes))
    {
        mPixels = (PixelType*)mRawPixels;
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
