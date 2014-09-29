// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline GraphicsObjectType GraphicsObject::GetType() const
{
    return mType;
}
//----------------------------------------------------------------------------
inline bool GraphicsObject::IsBuffer() const
{
    return GT_BUFFER <= mType && mType <= GT_INDIRECT_ARGUMENTS_BUFFER;
}
//----------------------------------------------------------------------------
inline bool GraphicsObject::IsTexture() const
{
    return GT_TEXTURE_SINGLE <= mType && mType <= GT_TEXTURE3;
}
//----------------------------------------------------------------------------
inline bool GraphicsObject::IsTextureArray() const
{
    return GT_TEXTURE_ARRAY <= mType && mType <= GT_TEXTURE_CUBE_ARRAY;
}
//----------------------------------------------------------------------------
inline bool GraphicsObject::IsShader() const
{
    return GT_SHADER <= mType && mType <= GT_COMPUTE_SHADER;
}
//----------------------------------------------------------------------------
inline bool GraphicsObject::IsDrawingState() const
{
    return GT_DRAWING_STATE <= mType && mType <= GT_RASTERIZER_STATE;
}
//----------------------------------------------------------------------------
inline void GraphicsObject::SetName(std::string const& name)
{
    mName = name;
}
//----------------------------------------------------------------------------
inline std::string const& GraphicsObject::GetName() const
{
    return mName;
}
//----------------------------------------------------------------------------
