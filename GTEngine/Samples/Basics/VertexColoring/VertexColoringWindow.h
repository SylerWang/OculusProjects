// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#pragma once

#include <GTEngine.h>
using namespace gte;

//#define SAVE_RENDERING_TO_DISK

class VertexColoringWindow : public Window
{
public:
    virtual ~VertexColoringWindow();
    VertexColoringWindow(Parameters& parameters);

    virtual void OnIdle();

private:
    void CreateScene();

    std::shared_ptr<Visual> mTriangle;

#ifdef SAVE_RENDERING_TO_DISK
    std::shared_ptr<DrawTarget> mTarget;
#endif
};
