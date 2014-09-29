// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline void OverlayEffect::SetOverlayRectangle(
    std::array<int, 4> const& rectangle)
{
    mOverlayRectangle = rectangle;
    UpdateVertexBuffer();
}
//----------------------------------------------------------------------------
inline std::array<int,4> OverlayEffect::GetOverlayRectangle() const
{
    return mOverlayRectangle;
}
//----------------------------------------------------------------------------
inline std::array<int,4> OverlayEffect::GetTextureRectangle() const
{
    return mTextureRectangle;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<VertexBuffer> const&
OverlayEffect::GetVertexBuffer() const
{
    return mVBuffer;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<IndexBuffer> const&
OverlayEffect::GetIndexBuffer() const
{
    return mIBuffer;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<VisualEffect> const&
OverlayEffect::GetEffect() const
{
    return mEffect;
}
//----------------------------------------------------------------------------
inline std::string const& OverlayEffect::GetName() const
{
    return mName;
}
//----------------------------------------------------------------------------
