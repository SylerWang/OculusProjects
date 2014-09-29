// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#pragma once

#include <GTEngine.h>
using namespace gte;

//#define VERIFY_AUTO_RT_MIPMAPS_AND_RT_UAV

class MultipleRenderTargetsWindow : public Window
{
public:
    virtual ~MultipleRenderTargetsWindow();
    MultipleRenderTargetsWindow(Parameters& parameters);

    virtual void OnIdle();

private:
    bool SetEnvironment();
    bool CreateScene();
    bool CreateOverlays();

    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<DrawTarget> mDrawTarget;
    std::shared_ptr<Visual> mSquare;
    std::shared_ptr<Texture2> mLinearDepth;
    std::shared_ptr<OverlayEffect> mOverlay[2];

#ifdef VERIFY_AUTO_RT_MIPMAPS_AND_RT_UAV
    std::shared_ptr<Texture2> mVerifyAutoRT;
    std::shared_ptr<Texture2> mVerifyRTUAV;
#endif
};
