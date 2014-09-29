// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GteVisualEffect.h>
#include <GteEnvironment.h>
#include <GteMatrix4x4.h>
#include <GteVector2.h>
#include <GteTexture1.h>
#include <GteTexture2.h>

namespace gte
{

class BlendedTerrainEffect : public VisualEffect
{
public:
    // Construction and destruction.
    virtual ~BlendedTerrainEffect();
    BlendedTerrainEffect(Environment const& environment, bool& created);

    // Member access.
    inline void SetPVWMatrix(Matrix4x4<float> const& pvwMatrix);
    inline Matrix4x4<float> const& GetPVWMatrix() const;
    inline void SetFlowDirection(Vector2<float> const& flowDirection);
    inline Vector2<float> const& GetFlowDirection() const;
    inline void SetPowerFactor(float powerFactor);
    inline float GetPowerFactor() const;

    // Required to bind and update resources.
    inline std::shared_ptr<ConstantBuffer> const& GetPVWMatrixConstant()
        const;
    inline std::shared_ptr<ConstantBuffer> const& GetFlowDirectionConstant()
        const;
    inline std::shared_ptr<ConstantBuffer> const& GetPowerFactorConstant()
        const;
    inline std::shared_ptr<Texture1> const& GetBlendTexture() const;
    inline std::shared_ptr<Texture2> const& GetGrassTexture() const;
    inline std::shared_ptr<Texture2> const& GetStoneTexture() const;
    inline std::shared_ptr<Texture2> const& GetCloudTexture() const;
    inline std::shared_ptr<SamplerState> const& GetCommonSampler() const;
    inline std::shared_ptr<SamplerState> const& GetBlendSampler() const;

private:
    // Vertex shader parameters.
    std::shared_ptr<ConstantBuffer> mPVWMatrixConstant;
    std::shared_ptr<ConstantBuffer> mFlowDirectionConstant;

    // Pixel shader parameters.
    std::shared_ptr<ConstantBuffer> mPowerFactorConstant;
    std::shared_ptr<Texture1> mBlendTexture;
    std::shared_ptr<Texture2> mGrassTexture;
    std::shared_ptr<Texture2> mStoneTexture;
    std::shared_ptr<Texture2> mCloudTexture;
    std::shared_ptr<SamplerState> mCommonSampler;
    std::shared_ptr<SamplerState> mBlendSampler;

    // Convenience pointers.
    Matrix4x4<float>* mPVWMatrix;
    Vector2<float>* mFlowDirection;
    float* mPowerFactor;
};

#include "BlendedTerrainEffect.inl"

}
