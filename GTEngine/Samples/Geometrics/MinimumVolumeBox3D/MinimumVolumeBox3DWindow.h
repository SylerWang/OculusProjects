// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#pragma once

#include <GTEngine.h>
using namespace gte;

class MinimumVolumeBox3DWindow : public Window
{
public:
    virtual ~MinimumVolumeBox3DWindow();
    MinimumVolumeBox3DWindow(Parameters& parameters);

    virtual void OnIdle();

private:
    void CreateScene();

    Vector4<float> mTextColor;
    enum { NUM_POINTS = 256 };
    std::vector<Vector3<double>> mVertices;
    std::shared_ptr<Node> mScene;
    std::shared_ptr<Visual> mPoints;
    std::shared_ptr<Visual> mPolytope;
    std::shared_ptr<Visual> mBoxMesh;
    std::shared_ptr<RasterizerState> mWireState;

    MinimumVolumeBox3<double, BSRational<std::vector<uint32_t>>> mMVB3;
};
