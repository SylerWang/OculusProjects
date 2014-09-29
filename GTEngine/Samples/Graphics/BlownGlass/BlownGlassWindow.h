// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#pragma once

#include <GTEngine.h>
using namespace gte;

class BlownGlassWindow : public Window
{
public:
    virtual ~BlownGlassWindow();
    BlownGlassWindow(Parameters& parameters);

    virtual void OnIdle();

private:
    bool SetEnvironment();
    bool CreateScene();

    enum { GRID_SIZE = 128 };
    Environment mEnvironment;
    Vector4<float> mTextColor;
    std::shared_ptr<Texture3Effect> mDrawEffect;
    std::shared_ptr<Visual> mMesh;
    Fluid3* mFluid;
};
