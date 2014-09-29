// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteLightingEffect.h"

// LightDirectionPerPixelEffect uses the LightingConstants members
//   materialEmissive
//   materialAmbient
//   materialDiffuse
//   materialSpecular
//   lightAmbient
//   lightDiffuse
//   lightSpecular
//   lightAttenuation
//   cameraModelPosition
//   lightModelDirection

namespace gte
{

class GTE_IMPEXP LightDirectionPerPixelEffect : public LightingEffect
{
public:
    // Construction and destruction.
    virtual ~LightDirectionPerPixelEffect();
    LightDirectionPerPixelEffect(LightingConstants const& lighting);

private:
    static std::string const msHLSLString;
};

}
