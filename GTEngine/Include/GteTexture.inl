// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline unsigned int Texture::GetNumItems() const
{
    return mNumItems;
}
//----------------------------------------------------------------------------
inline DFType Texture::GetFormat() const
{
    return mFormat;
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetNumDimensions() const
{
    return mNumDimensions;
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetDimension(int i) const
{
    return mLDimension[0][i];
}
//----------------------------------------------------------------------------
inline bool Texture::HasMipmaps() const
{
    return mHasMipmaps;
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetNumLevels() const
{
    return mNumLevels;
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetDimensionFor(unsigned int level, int i)
    const
{
    return mLDimension[level][i];
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetNumElementsFor(unsigned int level) const
{
    return mLNumBytes[level] / mElementSize;
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetNumBytesFor(unsigned int level) const
{
    return mLNumBytes[level];
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetOffsetFor(unsigned int item,
    unsigned int level) const
{
    return mLOffset[item][level];
}
//----------------------------------------------------------------------------
inline char const* Texture::GetDataFor(unsigned int item,
    unsigned int level) const
{
    return mData + mLOffset[item][level];
}
//----------------------------------------------------------------------------
inline char* Texture::GetDataFor(unsigned int item, unsigned int level)
{
    return mData + mLOffset[item][level];
}
//----------------------------------------------------------------------------
template <typename T> inline T
const* Texture::GetFor(unsigned int item, unsigned int level) const
{
    return reinterpret_cast<T const*>(GetDataFor(item, level));
}
//----------------------------------------------------------------------------
template <typename T> inline
T* Texture::GetFor(unsigned int item, unsigned int level)
{
    return reinterpret_cast<T*>(GetDataFor(item, level));
}
//----------------------------------------------------------------------------
inline unsigned int Texture::GetNumSubresources() const
{
    return mNumItems * mNumLevels;
}
//----------------------------------------------------------------------------
inline bool Texture::WantAutogenerateMipmaps() const
{
    return mAutogenerateMipmaps;
}
//----------------------------------------------------------------------------
