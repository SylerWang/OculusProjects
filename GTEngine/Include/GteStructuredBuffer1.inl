// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename T>
StructuredBuffer1<T>::StructuredBuffer1(unsigned int length,
    bool createStorage)
    :
    StructuredBuffer(length, sizeof(T), createStorage),
    mLength(length)
{
}
//----------------------------------------------------------------------------
template <typename T> inline
unsigned int StructuredBuffer1<T>::GetLength() const
{
    return mLength;
}
//----------------------------------------------------------------------------
template <typename T> inline
T& StructuredBuffer1<T>::operator[](unsigned int i)
{
    return Get<T>()[i];
}
//----------------------------------------------------------------------------
template <typename T> inline
T const& StructuredBuffer1<T>::operator[](unsigned int i) const
{
    return Get<T>()[i];
}
//----------------------------------------------------------------------------
