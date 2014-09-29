// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline unsigned int Resource::GetNumElements() const
{
    return mNumElements;
}
//----------------------------------------------------------------------------
inline unsigned int Resource::GetElementSize() const
{
    return mElementSize;
}
//----------------------------------------------------------------------------
inline unsigned int Resource::GetNumBytes() const
{
    return mNumBytes;
}
//----------------------------------------------------------------------------
inline void Resource::SetUsage(Usage usage)
{
    mUsage = usage;
}
//----------------------------------------------------------------------------
inline Resource::Usage Resource::GetUsage() const
{
    return mUsage;
}
//----------------------------------------------------------------------------
inline void Resource::SetCopyType(CopyType copyType)
{
    mCopyType = copyType;
}
//----------------------------------------------------------------------------
inline Resource::CopyType Resource::GetCopyType() const
{
    return mCopyType;
}
//----------------------------------------------------------------------------
inline void Resource::ResetData()
{
    mData = (mStorage.size() > 0 ? &mStorage[0] : nullptr);
}
//----------------------------------------------------------------------------
inline void Resource::SetData(char* data)
{
    mData = data;
}
//----------------------------------------------------------------------------
inline char const* Resource::GetData() const
{
    return mData;
}
//----------------------------------------------------------------------------
inline char* Resource::GetData()
{
    return mData;
}
//----------------------------------------------------------------------------
template <typename T>
inline T const* Resource::Get() const
{
    return reinterpret_cast<T const*>(mData);
}
//----------------------------------------------------------------------------
template <typename T>
inline T* Resource::Get()
{
    return reinterpret_cast<T*>(mData);
}
//----------------------------------------------------------------------------
inline unsigned int Resource::GetOffset() const
{
    return mOffset;
}
//----------------------------------------------------------------------------
inline unsigned int Resource::GetNumActiveElements() const
{
    return mNumActiveElements;
}
//----------------------------------------------------------------------------
inline unsigned int Resource::GetNumActiveBytes() const
{
    return mNumActiveElements*mElementSize;
}
//----------------------------------------------------------------------------
