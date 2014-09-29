// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/25)

//----------------------------------------------------------------------------
inline std::string Image::GetPixelType() const
{
    return mPixelType;
}
//----------------------------------------------------------------------------
inline size_t Image::GetPixelSize() const
{
    return mPixelSize;
}
//----------------------------------------------------------------------------
inline int Image::GetNumDimensions() const
{
    return mNumDimensions;
}
//----------------------------------------------------------------------------
inline int const* Image::GetDimensions() const
{
    return mDimensions;
}
//----------------------------------------------------------------------------
inline size_t const* Image::GetOffsets() const
{
    return mOffsets;
}
//----------------------------------------------------------------------------
inline size_t Image::GetNumPixels() const
{
    return mNumPixels;
}
//----------------------------------------------------------------------------
inline char const* Image::GetRawPixels() const
{
    return mRawPixels;
}
//----------------------------------------------------------------------------
inline char* Image::GetRawPixels()
{
    return mRawPixels;
}
//----------------------------------------------------------------------------
inline bool Image::IsNullImage() const
{
    // There are many tests for a null image, all equivalent.
    return mRawPixels == nullptr;
}
//----------------------------------------------------------------------------
inline void Image::SetImageMetaData(std::string const& metadata)
{
    mImageMetaData = metadata;
}
//----------------------------------------------------------------------------
inline std::string const& Image::GetImageMetaData() const
{
    return mImageMetaData;
}
//----------------------------------------------------------------------------
inline bool Image::HasPixelMetaData() const
{
    return mPixelMetaData != nullptr;
}
//----------------------------------------------------------------------------
