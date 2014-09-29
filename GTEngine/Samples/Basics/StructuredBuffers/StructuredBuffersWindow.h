// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#pragma once

#include <GTEngine.h>
using namespace gte;

class StructuredBuffersWindow : public Window
{
public:
    virtual ~StructuredBuffersWindow();
    StructuredBuffersWindow(Parameters& parameters);

    virtual void OnIdle();

private:
    bool SetEnvironment();
    bool CreateScene();

    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<Visual> mSquare;
    std::shared_ptr<StructuredBuffer> mDrawnPixels;
    Texture2* mDrawnPixelsTexture;
};
