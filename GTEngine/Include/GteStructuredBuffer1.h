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
class StructuredBuffer1 : public StructuredBuffer
{
public:
    // Construction.
    StructuredBuffer1(unsigned int length, bool createStorage = true);

    // Member access.  No range checking is performed by operator[].
    inline unsigned int GetLength() const;
    inline T& operator[](unsigned int i);
    inline T const& operator[](unsigned int i) const;

private:
    unsigned int mLength;
};

#include "GteStructuredBuffer1.inl"

}
