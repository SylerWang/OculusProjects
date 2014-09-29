// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
#include <GteAMDPerformance.h>
using namespace gte;

class PerformanceAMDWindow : public Window
{
public:
    virtual ~PerformanceAMDWindow();
    PerformanceAMDWindow(Parameters& parameters);

    virtual void OnIdle();

private:
    void CreateCamera();
    void CreateTextureGenerator();
    void CreateScene();
    void UpdateConstants();

    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<RasterizerState> mNoCullingState;
    std::shared_ptr<Visual> mTriangles;
    std::shared_ptr<Texture2> mOriginalTexture;
    std::shared_ptr<Texture2> mBlurredTexture;
    std::shared_ptr<ConstantBuffer> mPVWMatrix;
    std::shared_ptr<ComputeShader> mGenerateTexture;
    unsigned int mNumXGroups, mNumYGroups;

    // Support for AMD GPU performance library.
    static void Listener(GPA_Logging_Type type, char const* message);
    AMDPerformance mPerformance;
};
