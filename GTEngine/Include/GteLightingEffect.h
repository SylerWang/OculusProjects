// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.2.0 (2014/08/26)

#pragma once

#include "GTEngineDEF.h"
#include "GteVisualEffect.h"
#include "GteLightingConstants.h"

namespace gte
{

class GTE_IMPEXP LightingEffect : public VisualEffect
{
public:
    // Abstract base class.
    virtual ~LightingEffect();
protected:
    // Construction.  The shader is selected either for per-vertex lighting
    // or per-pixel lighting.
    LightingEffect(LightingConstants const& lighting,
        std::string const& hlslString, bool perVertex);

public:
    // Member access.
    inline void SetPVWMatrix(Matrix4x4<float> const& pvwMatrix);
    inline Matrix4x4<float> const& GetPVWMatrix() const;
    inline Matrix4x4<float>& GetPVWMatrix();
    inline void SetLighting(LightingConstants const& lighting);
    inline LightingConstants const& GetLighting() const;
    inline LightingConstants& GetLighting();

    // Required to bind and update resources.
    inline std::shared_ptr<ConstantBuffer> const& GetPVWMatrixConstant()
        const;
    inline std::shared_ptr<ConstantBuffer> const& GetLightingConstant() const;

    // Naming support, used in the DX11 debug layer.  The default name is "".
    // If you want the name to show up in the DX11 destruction messages when
    // the associated DX11GraphicsObject is destroyed, set the name to
    // something other than "".
    virtual void SetName(std::string const& name);

protected:
    // Vertex shader parameters.
    std::shared_ptr<ConstantBuffer> mPVWMatrixConstant;
    std::shared_ptr<ConstantBuffer> mLightingConstant;

    // Convenience pointers.
    Matrix4x4<float>* mPVWMatrix;
    LightingConstants* mLighting;
};

#include "GteLightingEffect.inl"

}
