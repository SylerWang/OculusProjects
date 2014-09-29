// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class MinimumVolumeSphere3DWindow : public Window
{
public:
    virtual ~MinimumVolumeSphere3DWindow();
    MinimumVolumeSphere3DWindow(Parameters& parameters);

    virtual void OnIdle();
    virtual bool OnCharPress(unsigned char key, int x, int y);

private:
    void CreateScene();
    void UpdateScene();

    enum { NUM_POINTS = 256 };
    Vector4<float> mTextColor;

    std::array<std::shared_ptr<Visual>, NUM_POINTS> mPoints;
    std::shared_ptr<Visual> mSegments, mSphere;
    std::shared_ptr<RasterizerState> mNoCullWireState;
    Matrix4x4<float> mIdentity;

    int mNumActive;
    std::vector<Vector3<float>> mVertices;
    Sphere3<float> mMinimalSphere;
    MinimumVolumeSphere3<float, BSRational<std::vector<uint32_t>>> mMVS3;
};
