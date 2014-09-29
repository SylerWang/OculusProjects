// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteStructuredBuffer.h"

namespace gte
{

template <typename T>
class StructuredBuffer2 : public StructuredBuffer
{
public:
    // Construction.
    StructuredBuffer2(unsigned int width, unsigned int height,
        bool createStorage = true);

    // Member access.
    inline unsigned int GetWidth() const;
    inline unsigned int GetHeight() const;

    // The elements are accessed as if they are in row-major order; that is,
    // i = x + width*y.  No range checking is performed by the operators.
    inline T& operator[](unsigned int i);
    inline T const& operator[](unsigned int i) const;
    inline T& operator()(unsigned int x, unsigned int y);
    inline T const& operator()(unsigned int x, unsigned int y) const;

private:
    unsigned int mWidth, mHeight;
};

#include "GteStructuredBuffer2.inl"

}
