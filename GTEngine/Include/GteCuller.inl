// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline VisibleSet& Culler::GetVisibleSet ()
{
    return mVisibleSet;
}
//----------------------------------------------------------------------------
inline void Culler::SetPlaneState (unsigned int planeState)
{
    mPlaneState = planeState;
}
//----------------------------------------------------------------------------
inline unsigned int Culler::GetPlaneState () const
{
    return mPlaneState;
}
//----------------------------------------------------------------------------
