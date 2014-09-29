// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

//----------------------------------------------------------------------------
inline HWND Window::GetHandle () const
{
    return mHandle;
}
//----------------------------------------------------------------------------
inline std::wstring Window::GetTitle () const
{
    return mTitle;
}
//----------------------------------------------------------------------------
inline int Window::GetXOrigin () const
{
    return mXOrigin;
}
//----------------------------------------------------------------------------
inline int Window::GetYOrigin () const
{
    return mYOrigin;
}
//----------------------------------------------------------------------------
inline int Window::GetXSize () const
{
    return mXSize;
}
//----------------------------------------------------------------------------
inline int Window::GetYSize () const
{
    return mYSize;
}
//----------------------------------------------------------------------------
inline bool Window::IsMinimized () const
{
    return mIsMinimized;
}
//----------------------------------------------------------------------------
inline bool Window::IsMaximized () const
{
    return mIsMaximized;
}
//----------------------------------------------------------------------------
inline float Window::GetAspectRatio () const
{
    return (float)mXSize/(float)mYSize;
}
//----------------------------------------------------------------------------
inline void Window::ResetTime ()
{
    mLastTime = -1.0;
}
//----------------------------------------------------------------------------
inline void Window::UpdateFrameCount ()
{
    ++mFrameCount;
}
//----------------------------------------------------------------------------
inline void Window::DisableCameraMotion ()
{
    mCameraMovable = false;
}
//----------------------------------------------------------------------------
inline void Window::EnableObjectMotion ()
{
    mUseTrackball = true;
}
//----------------------------------------------------------------------------
inline void Window::DisableObjectMotion ()
{
    mUseTrackball = false;
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& Window::GetTrackballRotation() const
{
    return mTrackballNode->worldTransform;
}
//----------------------------------------------------------------------------
