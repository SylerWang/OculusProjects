// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class Delaunay2DWindow : public Window
{
public:
    virtual ~Delaunay2DWindow();
    Delaunay2DWindow(Parameters& parameters);

    virtual void OnDisplay();
    virtual bool OnMouseClick(MouseButton button, MouseState state,
        int x, int y, unsigned int modifiers);

private:
    void DrawLine(int x0, int y0, int x1, int y1, unsigned int color);
    void Fill(int x, int y, unsigned int foreColor, unsigned int backColor);

    Vector4<float> mTextColor;
    std::shared_ptr<OverlayEffect> mOverlay;
    std::shared_ptr<Texture2> mScreenTexture;
    unsigned int* mScreenTexels;

    std::vector<Vector2<float>> mVertices;
    std::vector<int> mHull;
    Delaunay2<float, BSNumber<std::vector<uint32_t>>> mDelaunay;
    Delaunay2<float, BSNumber<std::vector<uint32_t>>>::SearchInfo mInfo;
    int mCurrentTriX, mCurrentTriY, mCurrentIndex;
};
