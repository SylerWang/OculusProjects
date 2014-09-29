// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#pragma once

#include <GTEngine.h>
using namespace gte;

class Fluids3DWindow : public Window
{
public:
    virtual ~Fluids3DWindow();
    Fluids3DWindow(Parameters& parameters);

    virtual void OnIdle();
    virtual bool OnCharPress(unsigned char key, int x, int y);

private:
    bool SetEnvironment();
    bool CreateNestedBoxes();
    void UpdateConstants();

    enum { GRID_SIZE = 128 };
    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<DepthStencilState> mNoDepthState;
    std::shared_ptr<RasterizerState> mNoCullingState;
    std::shared_ptr<SamplerState> mTrilinearClampSampler;
    std::shared_ptr<BlendState> mAlphaState;
    std::shared_ptr<ConstantBuffer> mPVWMatrixBuffer;
    std::vector<std::shared_ptr<Visual>> mVisible;
    Fluid3 mFluid;
};
