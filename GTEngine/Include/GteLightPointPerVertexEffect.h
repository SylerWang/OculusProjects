// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/26)

#pragma once

#include "GTEngineDEF.h"
#include "GteLightingEffect.h"

// LightPointPerVertexEffect uses the LightingConstants members
//   materialEmissive
//   materialAmbient
//   materialDiffuse
//   materialSpecular
//   lightAmbient
//   lightDiffuse
//   lightSpecular
//   lightAttenuation
//   cameraModelPosition
//   lightModelPosition
//   wMatrix

namespace gte
{

class GTE_IMPEXP LightPointPerVertexEffect : public LightingEffect
{
public:
    // Construction and destruction.
    virtual ~LightPointPerVertexEffect();
    LightPointPerVertexEffect(LightingConstants const& lighting);

private:
    static std::string const msHLSLString;
};

}
