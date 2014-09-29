// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/29)

#pragma once

#include <GTEngine.h>
using namespace gte;

class Delaunay3DWindow : public Window
{
public:
    virtual ~Delaunay3DWindow();
    Delaunay3DWindow(Parameters& parameters);

    virtual void OnIdle();
    virtual bool OnCharPress(unsigned char key, int x, int y);

private:
    bool SetEnvironment();
    bool CreateScene();
    void CreateSphere();
    void CreateTetra(int index);
    void SetAllTetraWire();
    void SetTetraSolid(int index, Vector4<float> const& color);
    void SetLastTetraSolid(Vector4<float> const& color,
        Vector4<float> const& oppositeColor);
    void DoSearch();

    Environment mEnvironment;
    Vector4<float> mTextColor, mLightGray;
    std::shared_ptr<RasterizerState> mNoCullState;
    std::shared_ptr<RasterizerState> mNoCullWireState;
    std::shared_ptr<BlendState> mBlendState;
    std::shared_ptr<VertexColorEffect> mVCEffect;

    struct Vertex
    {
        Vector3<float> position;
        Vector4<float> color;
    };

    std::shared_ptr<Node> mScene;
    std::shared_ptr<Visual> mSphere;
    std::vector<std::shared_ptr<Visual>> mWireTetra;
    std::vector<std::shared_ptr<Visual>> mSolidTetra;

    std::vector<Vector3<float>> mVertices;
    std::mt19937 mRandomGenerator;
    std::uniform_real_distribution<float> mRandom[3];

    // The choice of 12 is empirical.  All the data sets tested in this
    // sample require at most 11 elements in the BSUInteger array.
    Delaunay3<float, BSNumber<BSUInteger<12>>> mDelaunay;
    Delaunay3<float, BSNumber<BSUInteger<12>>>::SearchInfo mInfo;
};
