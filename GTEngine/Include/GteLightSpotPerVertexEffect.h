// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/26)

#pragma once

#include "GTEngineDEF.h"
#include "GteLightingEffect.h"

// LightSpotPerVertexEffect uses the LightingConstants members
//   materialEmissive
//   materialAmbient
//   materialDiffuse
//   materialSpecular
//   lightAmbient
//   lightDiffuse
//   lightSpecular
//   lightSpotCutoff
//   lightAttenuation
//   cameraModelPosition
//   lightModelPosition
//   lightModelDirection
//   wMatrix

namespace gte
{

class GTE_IMPEXP LightSpotPerVertexEffect : public LightingEffect
{
public:
    // Construction and destruction.
    virtual ~LightSpotPerVertexEffect();
    LightSpotPerVertexEffect(LightingConstants const& lighting);

private:
    static std::string const msHLSLString;
};

}
