// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline unsigned int TextureSingle::GetOffsetFor(unsigned int level) const
{
    return Texture::GetOffsetFor(0, level);
}
//----------------------------------------------------------------------------
inline char const* TextureSingle::GetDataFor(unsigned int level) const
{
    return Texture::GetDataFor(0, level);
}
//----------------------------------------------------------------------------
inline char* TextureSingle::GetDataFor(unsigned int level)
{
    return Texture::GetDataFor(0, level);
}
//----------------------------------------------------------------------------
template <typename T> inline
T const* TextureSingle::GetFor(unsigned int level) const
{
    return Texture::GetFor<T>(0, level);
}
//----------------------------------------------------------------------------
template <typename T> inline
T* TextureSingle::GetFor(unsigned int level)
{
    return Texture::GetFor<T>(0, level);
}
//----------------------------------------------------------------------------
