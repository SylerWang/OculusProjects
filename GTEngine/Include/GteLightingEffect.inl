// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.2.0 (2014/08/26)

//----------------------------------------------------------------------------
inline void LightingEffect::SetPVWMatrix(Matrix4x4<float> const& pvwMatrix)
{
    *mPVWMatrix = pvwMatrix;
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& LightingEffect::GetPVWMatrix() const
{
    return *mPVWMatrix;
}
//----------------------------------------------------------------------------
inline Matrix4x4<float>& LightingEffect::GetPVWMatrix()
{
    return *mPVWMatrix;
}
//----------------------------------------------------------------------------
inline void LightingEffect::SetLighting(LightingConstants const& lighting)
{
    *mLighting = lighting;
}
//----------------------------------------------------------------------------
inline LightingConstants const& LightingEffect::GetLighting() const
{
    return *mLighting;
}
//----------------------------------------------------------------------------
inline LightingConstants& LightingEffect::GetLighting()
{
    return *mLighting;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<ConstantBuffer> const&
LightingEffect::GetPVWMatrixConstant() const
{
    return mPVWMatrixConstant;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<ConstantBuffer> const&
LightingEffect::GetLightingConstant() const
{
    return mLightingConstant;
}
//----------------------------------------------------------------------------
