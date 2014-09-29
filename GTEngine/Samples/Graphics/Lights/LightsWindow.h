// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.2.0 (2014/08/26)

#pragma once

#include <GTEngine.h>
using namespace gte;

class LightsWindow : public Window
{
public:
    virtual ~LightsWindow();
    LightsWindow(Parameters& parameters);

    virtual void OnIdle();
    virtual bool OnCharPress(unsigned char key, int x, int y);

private:
    void CreateScene();
    void UseLightType(int type);
    void UpdateConstants();

    Vector4<float> mTextColor;
    std::shared_ptr<RasterizerState> mWireState;

    enum { LDIR, LPNT, LSPT, LNUM };
    enum { GPLN, GSPH, GNUM };
    enum { SVTX, SPXL, SNUM };
    std::shared_ptr<LightingEffect> mEffect[LNUM][GNUM][SNUM];
    std::shared_ptr<Visual> mPlane[SNUM], mSphere[SNUM];
    Vector4<float> mLightWorldPosition[2], mLightWorldDirection;
    std::string mCaption[LNUM];
    int mType;
};
