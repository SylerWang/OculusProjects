// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline void Histogram::Insert (int value)
{
    ++mBuckets[value];
}
//----------------------------------------------------------------------------
inline int Histogram::GetNumBuckets () const
{
    return mNumBuckets;
}
//----------------------------------------------------------------------------
inline int const* Histogram::GetBuckets () const
{
    return mBuckets;
}
//----------------------------------------------------------------------------
inline int Histogram::GetExcessLess () const
{
    return mExcessLess;
}
//----------------------------------------------------------------------------
inline int Histogram::GetExcessGreater () const
{
    return mExcessGreater;
}
//----------------------------------------------------------------------------
