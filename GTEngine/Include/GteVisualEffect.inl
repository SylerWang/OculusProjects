// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline void VisualEffect::SetVertexShader(
    std::shared_ptr<VertexShader> const& shader)
{
    mVShader = shader;
}
//----------------------------------------------------------------------------
inline void VisualEffect::SetGeometryShader(
    std::shared_ptr<GeometryShader> const& shader)
{
    mGShader = shader;
}
//----------------------------------------------------------------------------
inline void VisualEffect::SetPixelShader(
    std::shared_ptr<PixelShader> const& shader)
{
    mPShader = shader;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<VertexShader> const&
VisualEffect::GetVertexShader() const
{
    return mVShader;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<GeometryShader> const&
VisualEffect::GetGeometryShader() const
{
    return mGShader;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<PixelShader> const&
VisualEffect::GetPixelShader() const
{
    return mPShader;
}
//----------------------------------------------------------------------------
inline std::string const& VisualEffect::GetName() const
{
    return mName;
}
//----------------------------------------------------------------------------
