// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <GTEngine.h>
using namespace gte;

class MedianFilteringWindow : public Window
{
public:
    virtual ~MedianFilteringWindow();
    MedianFilteringWindow(Parameters& parameters);

    virtual void OnIdle();
    virtual bool OnCharPress(unsigned char key, int x, int y);

private:
    bool SetEnvironment();

    Vector4<float> mTextColor;
    Environment mEnvironment;
    std::shared_ptr<Texture2> mOriginal;
    std::shared_ptr<Texture2> mImage[2];
    std::shared_ptr<OverlayEffect> mOverlay[2];

    // 0 = median 3x3 by insertion sort
    // 1 = median 3x3 by min-max
    // 2 = median 5x5 by insertion sort
    // 3 = median 5x5 by min-max
    unsigned int mSelection;
    std::shared_ptr<ComputeShader> mMedianShader[4];
    unsigned int mNumXGroups, mNumYGroups;
    static std::string msName[4];
};
