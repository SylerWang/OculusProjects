// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteResource.h"
#include "GteDataFormat.h"
#include <array>
#include <vector>

namespace gte
{

class GTE_IMPEXP Texture : public Resource
{
protected:
    // Abstract base class.  All items in the array have the same format,
    // number of dimensions, dimension values, and mipmap status.
    Texture(unsigned int numItems, DFType format, unsigned int numDimensions,
        unsigned int dim0, unsigned int dim1, unsigned int dim2,
        bool hasMipmaps, bool createStorage);

public:
    // Member access.
    inline unsigned int GetNumItems() const;
    inline DFType GetFormat() const;
    inline unsigned int GetNumDimensions() const;
    inline unsigned int GetDimension(int i) const;

    // Subresource information.
    struct Subresource
    {
        unsigned int item;
        unsigned int level;
        char* data;
        unsigned int rowPitch;
        unsigned int slicePitch;
    };

    // Mipmap information.
    enum { MAX_MIPMAP_LEVELS = 16 };
    inline bool HasMipmaps() const;
    inline unsigned int GetNumLevels() const;
    inline unsigned int GetDimensionFor(unsigned int level, int i) const;
    inline unsigned int GetNumElementsFor(unsigned int level) const;
    inline unsigned int GetNumBytesFor(unsigned int level) const;
    inline unsigned int GetOffsetFor(unsigned int item,
        unsigned int level) const;
    inline char const* GetDataFor(unsigned int item,
        unsigned int level) const;
    inline char* GetDataFor(unsigned int item, unsigned int level);
    template <typename T> inline T const* GetFor(unsigned int item,
        unsigned int level) const;
    template <typename T> inline T* GetFor(unsigned int item,
        unsigned int level);

    // Subresource indexing:  index = numLevels*item + level
    inline unsigned int GetNumSubresources() const;
    unsigned int GetIndex(unsigned int item, unsigned int level) const;
    Subresource GetSubresource(unsigned int index) const;

    // Request that the GPU compute mipmap levels when the base-level texture
    // data is modified.  The AutogenerateMipmaps call should be made before
    // binding the texture to the engine.  If the texture does not have mipmaps,
    // the AutogenerateMipmaps call will not set mAutogenerateMipmaps to true.
    void AutogenerateMipmaps();
    inline bool WantAutogenerateMipmaps() const;

protected:
    // Support for computing the numElements parameter for the Resource
    // constructor.  This is necessary when mipmaps are requested.
    static unsigned int GetTotalElements(unsigned int numItems,
        unsigned int dim0, unsigned int dim1, unsigned int dim2,
        bool hasMipmaps);

    unsigned int mNumItems;
    DFType mFormat;
    unsigned int mNumDimensions;
    unsigned int mNumLevels;
    std::array<std::array<unsigned int, 3>, MAX_MIPMAP_LEVELS> mLDimension;
    std::array<unsigned int, MAX_MIPMAP_LEVELS> mLNumBytes;
    std::vector<std::array<unsigned int, MAX_MIPMAP_LEVELS>> mLOffset;
    bool mHasMipmaps;
    bool mAutogenerateMipmaps;
};

#include "GteTexture.inl"

}
