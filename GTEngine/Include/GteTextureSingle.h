// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteTexture.h"

namespace gte
{

class GTE_IMPEXP TextureSingle : public Texture
{
protected:
    // Abstract base class.
    TextureSingle(DFType format, unsigned int numDimensions,
        unsigned int dim0, unsigned int dim1, unsigned int dim2,
        bool hasMipmaps, bool createStorage);

public:
    // Mipmap information.
    inline unsigned int GetOffsetFor(unsigned int level) const;
    inline char const* GetDataFor(unsigned int level) const;
    inline char* GetDataFor(unsigned int level);
    template <typename T> inline T const* GetFor(unsigned int level) const;
    template <typename T> inline T* GetFor(unsigned int level);

public:
    // For use by the Shader class for storing reflection information.
    static int const shaderDataLookup = 4;
};

#include "GteTextureSingle.inl"

}
