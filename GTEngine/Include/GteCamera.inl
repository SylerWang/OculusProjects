// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline Vector4<float> const& Camera::GetPosition() const
{
    return mPosition;
}
//----------------------------------------------------------------------------
inline Vector4<float> const& Camera::GetDVector() const
{
    return mDVector;
}
//----------------------------------------------------------------------------
inline Vector4<float> const& Camera::GetUVector() const
{
    return mUVector;
}
//----------------------------------------------------------------------------
inline Vector4<float> const& Camera::GetRVector() const
{
    return mRVector;
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& Camera::GetViewMatrix() const
{
    return mViewMatrix;
}
//----------------------------------------------------------------------------
inline bool Camera::IsPerspective() const
{
    return mIsPerspective;
}
//----------------------------------------------------------------------------
inline float const* Camera::GetFrustum() const
{
    return mFrustum;
}
//----------------------------------------------------------------------------
inline float Camera::GetDMin() const
{
    return mFrustum[VF_DMIN];
}
//----------------------------------------------------------------------------
inline float Camera::GetDMax() const
{
    return mFrustum[VF_DMAX];
}
//----------------------------------------------------------------------------
inline float Camera::GetUMin() const
{
    return mFrustum[VF_UMIN];
}
//----------------------------------------------------------------------------
inline float Camera::GetUMax() const
{
    return mFrustum[VF_UMAX];
}
//----------------------------------------------------------------------------
inline float Camera::GetRMin() const
{
    return mFrustum[VF_RMIN];
}
//----------------------------------------------------------------------------
inline float Camera::GetRMax() const
{
    return mFrustum[VF_RMAX];
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& Camera::GetProjectionMatrix() const
{
    return mProjectionMatrix;
}
//----------------------------------------------------------------------------
inline void Camera::SetProjectionMatrix(Matrix4x4<float> const& projMatrix)
{
    mProjectionMatrix = projMatrix;
    UpdatePVMatrix();
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& Camera::GetProjectionViewMatrix() const
{
    return mProjectionViewMatrix;
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& Camera::GetPreViewMatrix() const
{
    return mPreViewMatrix;
}
//----------------------------------------------------------------------------
inline bool Camera::PreViewIsIdentity() const
{
    return mPreViewIsIdentity;
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& Camera::GetPostProjectionMatrix() const
{
    return mPostProjectionMatrix;
}
//----------------------------------------------------------------------------
inline bool Camera::PostProjectionIsIdentity() const
{
    return mPostProjectionIsIdentity;
}
//----------------------------------------------------------------------------
