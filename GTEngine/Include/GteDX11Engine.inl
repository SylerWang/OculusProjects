// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline IDXGIAdapter* DX11Engine::GetAdapter() const
{
    return mAdapter;
}
//----------------------------------------------------------------------------
inline D3D_DRIVER_TYPE DX11Engine::GetDriverType() const
{
    return mDriverType;
}
//----------------------------------------------------------------------------
inline HMODULE DX11Engine::GetSoftwareModule() const
{
    return mSoftwareModule;
}
//----------------------------------------------------------------------------
inline UINT DX11Engine::GetFlags() const
{
    return mFlags;
}
//----------------------------------------------------------------------------
inline D3D_FEATURE_LEVEL DX11Engine::GetMinFeatureLevel() const
{
    return mMinFeatureLevel;
}
//----------------------------------------------------------------------------
inline ID3D11Device* DX11Engine::GetDevice() const
{
    return mDevice;
}
//----------------------------------------------------------------------------
inline ID3D11DeviceContext* DX11Engine::GetImmediate() const
{
    return mImmediate;
}
//----------------------------------------------------------------------------
inline D3D_FEATURE_LEVEL DX11Engine::GetFeatureLevel() const
{
    return mFeatureLevel;
}
//----------------------------------------------------------------------------
inline void DX11Engine::SetClearColor(Vector4<float> const& clearColor)
{
    mClearColor = clearColor;
}
//----------------------------------------------------------------------------
inline void DX11Engine::SetClearDepth(float clearDepth)
{
    mClearDepth = clearDepth;
}
//----------------------------------------------------------------------------
inline void DX11Engine::SetClearStencil(unsigned int clearStencil)
{
    mClearStencil = clearStencil;
}
//----------------------------------------------------------------------------
inline Vector4<float> const& DX11Engine::GetClearColor() const
{
    return mClearColor;
}
//----------------------------------------------------------------------------
inline float DX11Engine::GetClearDepth() const
{
    return mClearDepth;
}
//----------------------------------------------------------------------------
inline unsigned int DX11Engine::GetClearStencil() const
{
    return mClearStencil;
}
//----------------------------------------------------------------------------
inline void DX11Engine::SetDefaultBlendState()
{
    SetBlendState(mDefaultBlendState);
}
//----------------------------------------------------------------------------
inline std::shared_ptr<BlendState> const&
DX11Engine::GetDefaultBlendState() const
{
    return mDefaultBlendState;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<BlendState> const& DX11Engine::GetBlendState() const
{
    return mActiveBlendState;
}
//----------------------------------------------------------------------------
inline void DX11Engine::SetDefaultDepthStencilState()
{
    SetDepthStencilState(mDefaultDepthStencilState);
}
//----------------------------------------------------------------------------
inline std::shared_ptr<DepthStencilState> const&
DX11Engine::GetDefaultDepthStencilState() const
{
    return mDefaultDepthStencilState;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<DepthStencilState> const&
DX11Engine::GetDepthStencilState() const
{
    return mActiveDepthStencilState;
}
//----------------------------------------------------------------------------
inline void DX11Engine::SetDefaultRasterizerState()
{
    SetRasterizerState(mDefaultRasterizerState);
}
//----------------------------------------------------------------------------
inline std::shared_ptr<RasterizerState> const&
DX11Engine::GetDefaultRasterizerState() const
{
    return mDefaultRasterizerState;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<RasterizerState> const&
DX11Engine::GetRasterizerState() const
{
    return mActiveRasterizerState;
}
//----------------------------------------------------------------------------
inline void DX11Engine::SetDefaultFont()
{
    SetFont(mDefaultFont);
}
//----------------------------------------------------------------------------
inline std::shared_ptr<Font> const& DX11Engine::GetDefaultFont() const
{
    return mDefaultFont;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<Font> const& DX11Engine::GetFont() const
{
    return mActiveFont;
}
//----------------------------------------------------------------------------
inline void DX11Engine::AllowOcclusionQuery(bool allow)
{
    mAllowOcclusionQuery = allow;
}
//----------------------------------------------------------------------------
inline void DX11Engine::WarnOnNonemptyBridges(bool warn)
{
    mWarnOnNonemptyBridges = warn;
}
//----------------------------------------------------------------------------
inline DWORD DX11Engine::GetDeviceThread() const
{
    return mThreadID;
}
//----------------------------------------------------------------------------
inline bool DX11Engine::IsDeviceThread(DWORD threadID) const
{
    return mThreadID == threadID;
}
//----------------------------------------------------------------------------
inline bool DX11Engine::Unbind(std::shared_ptr<GraphicsObject> const& object)
{
    return Unbind(object.get());
}
//----------------------------------------------------------------------------
inline bool DX11Engine::Unbind(std::shared_ptr<DrawTarget> const& target)
{
    return Unbind(target.get());
}
//----------------------------------------------------------------------------
