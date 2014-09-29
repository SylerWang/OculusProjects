// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline void BlendedTerrainEffect::SetPVWMatrix(
    Matrix4x4<float> const& pvwMatrix)
{
    *mPVWMatrix = pvwMatrix;
}
//----------------------------------------------------------------------------
inline Matrix4x4<float> const& BlendedTerrainEffect::GetPVWMatrix() const
{
    return *mPVWMatrix;
}
//----------------------------------------------------------------------------
inline void BlendedTerrainEffect::SetFlowDirection(
    Vector2<float> const& flowDirection)
{
    *mFlowDirection = flowDirection;
}
//----------------------------------------------------------------------------
inline Vector2<float> const& BlendedTerrainEffect::GetFlowDirection() const
{
    return *mFlowDirection;
}
//----------------------------------------------------------------------------
inline void BlendedTerrainEffect::SetPowerFactor(float powerFactor)
{
    *mPowerFactor = powerFactor;
}
//----------------------------------------------------------------------------
inline float BlendedTerrainEffect::GetPowerFactor() const
{
    return *mPowerFactor;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<ConstantBuffer> const&
BlendedTerrainEffect::GetPVWMatrixConstant() const
{
    return mPVWMatrixConstant;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<ConstantBuffer> const&
BlendedTerrainEffect::GetFlowDirectionConstant() const
{
    return mFlowDirectionConstant;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<ConstantBuffer> const&
BlendedTerrainEffect::GetPowerFactorConstant() const
{
    return mPowerFactorConstant;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<Texture1> const&
BlendedTerrainEffect::GetBlendTexture() const
{
    return mBlendTexture;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<Texture2> const&
BlendedTerrainEffect::GetGrassTexture() const
{
    return mGrassTexture;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<Texture2> const&
BlendedTerrainEffect::GetStoneTexture() const
{
    return mStoneTexture;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<Texture2> const&
BlendedTerrainEffect::GetCloudTexture() const
{
    return mCloudTexture;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<SamplerState> const&
BlendedTerrainEffect::GetCommonSampler() const
{
    return mCommonSampler;
}
//----------------------------------------------------------------------------
inline std::shared_ptr<SamplerState> const&
BlendedTerrainEffect::GetBlendSampler() const
{
    return mBlendSampler;
}
//----------------------------------------------------------------------------
