// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class PlaneEstimationWindow : public Window
{
public:
    virtual ~PlaneEstimationWindow();
    PlaneEstimationWindow(Parameters& parameters);

    virtual void OnIdle ();

private:
    bool SetEnvironment();
    std::shared_ptr<ConstantBuffer> CreateBezierControls();

    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<Texture2> mPositions;
    std::shared_ptr<Texture2> mPlanes;
    std::shared_ptr<ComputeShader> mPositionShader;
    std::shared_ptr<ComputeShader> mPlaneShader;
    unsigned int mNumXGroups, mNumYGroups;
    std::shared_ptr<OverlayEffect> mOverlay[2];
};
