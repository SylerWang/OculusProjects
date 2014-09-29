// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename T>
StructuredBuffer2<T>::StructuredBuffer2(unsigned int width,
    unsigned int height, bool createStorage)
    :
    StructuredBuffer(width*height, sizeof(T), createStorage),
    mWidth(width),
    mHeight(height)
{
}
//----------------------------------------------------------------------------
template <typename T> inline
unsigned int StructuredBuffer2<T>::GetWidth() const
{
    return mWidth;
}
//----------------------------------------------------------------------------
template <typename T> inline
unsigned int StructuredBuffer2<T>::GetHeight() const
{
    return mHeight;
}
//----------------------------------------------------------------------------
template <typename T> inline
T& StructuredBuffer2<T>::operator[](unsigned int i)
{
    return Get<T>()[i];
}
//----------------------------------------------------------------------------
template <typename T> inline
T const& StructuredBuffer2<T>::operator[](unsigned int i) const
{
    return Get<T>()[i];
}
//----------------------------------------------------------------------------
template <typename T> inline
T& StructuredBuffer2<T>::operator()(unsigned int x, unsigned int y)
{
    return Get<T>()[x + mWidth*y];
}
//----------------------------------------------------------------------------
template <typename T> inline
T const& StructuredBuffer2<T>::operator()(unsigned int x, unsigned int y) const
{
    return Get<T>()[x + mWidth*y];
}
//----------------------------------------------------------------------------
