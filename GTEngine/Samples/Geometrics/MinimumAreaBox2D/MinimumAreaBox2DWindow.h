// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class MinimumAreaBox2DWindow : public Window
{
public:
    virtual ~MinimumAreaBox2DWindow();
    MinimumAreaBox2DWindow(Parameters& parameters);

    virtual void OnDisplay();

private:
    void DrawPoint(int x, int y, unsigned int color);
    void DrawLine(int x0, int y0, int x1, int y1, unsigned int color);

    Vector4<float> mTextColor;
    std::shared_ptr<OverlayEffect> mOverlay;
    std::shared_ptr<Texture2> mScreenTexture;
    unsigned int* mScreenTexels;

    enum { NUM_POINTS = 256 };
    std::vector<Vector2<float>> mVertices;
    OrientedBox2<float> mMinimalBox, mSlowMinimalBox;
    MinimumAreaBox2<float, BSRational<std::vector<uint32_t>>> mMAB2;
    std::vector<int> mHull;
};
