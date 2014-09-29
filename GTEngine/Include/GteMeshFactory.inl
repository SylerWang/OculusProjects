// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline void MeshFactory::SetVertexFormat(VertexFormat const& format)
{
    mVFormat = format;
}
//----------------------------------------------------------------------------
inline void MeshFactory::SetVertexBufferUsage(Resource::Usage usage)
{
    mVBUsage = usage;
}
//----------------------------------------------------------------------------
inline void MeshFactory::SetIndexFormat(bool use32Bit)
{
    mIndexSize = (use32Bit ? sizeof(unsigned int) : sizeof(unsigned short));
}
//----------------------------------------------------------------------------
inline void MeshFactory::SetIndexBufferUsage(Resource::Usage usage)
{
    mIBUsage = usage;
}
//----------------------------------------------------------------------------
inline void MeshFactory::SetOutside(bool outside)
{
    mOutside = outside;
}
//----------------------------------------------------------------------------
inline Vector3<float>& MeshFactory::Position(unsigned int i)
{
    return *reinterpret_cast<Vector3<float>*>(
        mPositions + i*mVFormat.GetVertexSize());
}
//----------------------------------------------------------------------------
inline Vector3<float>& MeshFactory::Normal(unsigned int i)
{
    return *reinterpret_cast<Vector3<float>*>(
        mNormals + i*mVFormat.GetVertexSize());
}
//----------------------------------------------------------------------------
inline Vector3<float>& MeshFactory::Tangent(unsigned int i)
{
    return *reinterpret_cast<Vector3<float>*>(
        mTangents + i*mVFormat.GetVertexSize());
}
//----------------------------------------------------------------------------
inline Vector3<float>& MeshFactory::Binormal(unsigned int i)
{
    return *reinterpret_cast<Vector3<float>*>(
        mBinormals + i*mVFormat.GetVertexSize());
}
//----------------------------------------------------------------------------
inline Vector2<float>& MeshFactory::TCoord(unsigned int unit, unsigned int i)
{
    return *reinterpret_cast<Vector2<float>*>(
        mTCoords[unit] + i*mVFormat.GetVertexSize());
}
//----------------------------------------------------------------------------
