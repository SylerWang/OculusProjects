// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/16)

#pragma once

#include <GTEngine.h>
#include "PhysicsModule.h"
using namespace gte;

class RopeWindow : public Window
{
public:
    virtual ~RopeWindow();
    RopeWindow(Parameters& parameters);

    virtual void OnIdle();
    virtual bool OnCharPress(unsigned char key, int x, int y);

private:
    bool SetEnvironment();
    void CreateSprings();
    void CreateRope();
    void PhysicsTick();
    void GraphicsTick();

    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<RasterizerState> mWireState;

    struct Vertex
    {
        Vector3<float> position;
        Vector2<float> tcoord;
    };

    std::shared_ptr<Visual> mRope;

    // The masses are located at the control points of a spline curve.  The
    // control points are connected by a mass-spring system.
    std::shared_ptr<PhysicsModule> mModule;
    std::shared_ptr<BSplineCurve<3, float>> mSpline;
    std::shared_ptr<TubeSurface<float>> mSurface;

    Timer mTimer;
    double mLastIdle;
};
