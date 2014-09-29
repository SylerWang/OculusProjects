// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline void BoundingSphere::SetCenter (Vector4<float> const& center)
{
    mTuple[0] = center[0];
    mTuple[1] = center[1];
    mTuple[2] = center[2];
}
//----------------------------------------------------------------------------
inline void BoundingSphere::SetRadius (float radius)
{
    mTuple[3] = (radius >= 0.0f ? radius : 0.0f);
}
//----------------------------------------------------------------------------
inline Vector4<float> BoundingSphere::GetCenter () const
{
    return Vector4<float>(mTuple[0], mTuple[1], mTuple[2], 1.0f);
}
//----------------------------------------------------------------------------
inline float BoundingSphere::GetRadius () const
{
    return mTuple[3];
}
//----------------------------------------------------------------------------
