// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename T>
StructuredBuffer3<T>::StructuredBuffer3(unsigned int width,
    unsigned int height, unsigned int thickness, bool createStorage)
    :
    StructuredBuffer(width*height*thickness, sizeof(T), createStorage),
    mWidth(width),
    mHeight(height),
    mThickness(thickness)
{
}
//----------------------------------------------------------------------------
template <typename T> inline
unsigned int StructuredBuffer3<T>::GetWidth() const
{
    return mWidth;
}
//----------------------------------------------------------------------------
template <typename T> inline
unsigned int StructuredBuffer3<T>::GetHeight() const
{
    return mHeight;
}
//----------------------------------------------------------------------------
template <typename T> inline
unsigned int StructuredBuffer3<T>::GetThickness() const
{
    return mThickness;
}
//----------------------------------------------------------------------------
template <typename T> inline
T& StructuredBuffer3<T>::operator[](unsigned int i)
{
    return Get<T>()[i];
}
//----------------------------------------------------------------------------
template <typename T> inline
T const& StructuredBuffer3<T>::operator[](unsigned int i) const
{
    return Get<T>()[i];
}
//----------------------------------------------------------------------------
template <typename T> inline
T& StructuredBuffer3<T>::operator()(unsigned int x, unsigned int y,
    unsigned int z)
{
    return Get<T>()[x + mWidth*(y + mHeight*z)];
}
//----------------------------------------------------------------------------
template <typename T> inline
T const& StructuredBuffer3<T>::operator()(unsigned int x, unsigned int y,
    unsigned int z) const
{
    return Get<T>()[x + mWidth*(y + mHeight*z)];
}
//----------------------------------------------------------------------------
