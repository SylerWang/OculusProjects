// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.2.1 (2014/08/31)

#pragma once

#include <GTEngine.h>
using namespace gte;

class PickingWindow : public Window
{
public:
    virtual ~PickingWindow();
    PickingWindow(Parameters& parameters);

    virtual void OnIdle();

    virtual bool OnMouseClick(MouseButton button, MouseState state,
        int x, int y, unsigned int modifiers);

private:
    bool SetEnvironment();
    void CreateScene();
    void DoPick(int x, int y);

    struct Vertex
    {
        Vector3<float> position;
        Vector2<float> tcoord;
    };

    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<Node> mScene;
    std::shared_ptr<Visual> mTorus;
    std::shared_ptr<Visual> mDodecahedron;
    std::shared_ptr<Visual> mPoints;
    std::shared_ptr<Visual> mSegments;
    enum { SPHERE_BUDGET = 16 };
    std::shared_ptr<Visual> mSphere[SPHERE_BUDGET];
    int mNumActiveSpheres;
    Picker mPicker;
};
