// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline void Visual::SetVertexBuffer (
    std::shared_ptr<VertexBuffer> const& vbuffer)
{
    mVBuffer = vbuffer;
}
//----------------------------------------------------------------------------
inline void Visual::SetIndexBuffer (
    std::shared_ptr<IndexBuffer> const& ibuffer)
{
    mIBuffer = ibuffer;
}
//----------------------------------------------------------------------------
inline void Visual::SetEffect (std::shared_ptr<VisualEffect> const& effect)
{
    mEffect = effect;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<VertexBuffer> const& Visual::GetVertexBuffer () const
{
    return mVBuffer;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<IndexBuffer> const& Visual::GetIndexBuffer () const
{
    return mIBuffer;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<VisualEffect> const& Visual::GetEffect () const
{
    return mEffect;
}
//----------------------------------------------------------------------------
inline void Visual::UpdateWorldBound ()
{
    modelBound.TransformBy(worldTransform, worldBound);
}
//----------------------------------------------------------------------------
inline void Visual::GetVisibleSet (Culler& culler, bool)
{
    culler.Insert(this);
}
//----------------------------------------------------------------------------
