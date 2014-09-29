// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteHLSLShader.h"
#include "GteConstantBuffer.h"
#include "GteRawBuffer.h"
#include "GteSamplerState.h"
#include "GteStructuredBuffer.h"
#include "GteTexture1.h"
#include "GteTexture2.h"
#include "GteTexture3.h"
#include "GteTextureBuffer.h"
#include "GteTextureCube.h"
#include "GteTexture1Array.h"
#include "GteTexture2Array.h"
#include "GteTextureCubeArray.h"
#include <memory>

namespace gte
{

class GTE_IMPEXP Shader : public GraphicsObject
{
public:
    // Construction.
    Shader(HLSLShader const& program);

    // To avoid frequent string comparisons during run time, obtain a handle
    // for an object and use it instead for setting and getting the values.
    // If the named object exists, the returned handle is nonnegative;
    // otherwise, it is -1.
    int Get(std::string const& name) const;

    // Set or get the buffers.  If the set is successful, the return value is
    // nonnegative and is the index into the appropriate array.  This handle
    // may be passed to the Set(handle,*) and Get(handle,*) functions.  The
    // mechanism allows you to set directly by index and avoid the name
    // comparisons that occur with the Set(name,*) and Get(name,*) functions.
    template <typename T>
    int Set(std::string const& name, std::shared_ptr<T> const& object);

    template <typename T>
    std::shared_ptr<T> const Get(std::string const& name) const;

    template <typename T>
    void Set(int handle, std::shared_ptr<T> const& object);

    template <typename T>
    std::shared_ptr<T> const Get(int handle) const;

    // These specializations copy the member layouts of the shader program to the
    // buffer objects.
    template<>
    int Set(std::string const& name, std::shared_ptr<ConstantBuffer> const& object);

    template<>
    int Set(std::string const& name, std::shared_ptr<TextureBuffer> const& object);

    template<>
    void Set(int handle, std::shared_ptr<ConstantBuffer> const& object);

    template<>
    void Set(int handle, std::shared_ptr<TextureBuffer> const& object);

    inline unsigned int GetNumXThreads() const;
    inline unsigned int GetNumYThreads() const;
    inline unsigned int GetNumZThreads() const;

protected:
    // This structure provides the data necessary for the engine to attach
    // the associated resources to the shader, including name lookups and
    // resource validation.  Not all members are used for each graphics
    // object type:
    //   CB - constant buffer, lookup 0
    //   TB - texture buffer, lookup 1
    //   SB - structured buffer (and derived classes), lookup 2
    //   TODO:  typed buffer
    //   RB - raw buffer, lookup 3
    //   TX - texture (and derived classes), lookup 4
    //   TA - texture array (and derived classes, lookup 5
    //   SS - sampler state, lookup 6
    struct Data
    {
        Data(GraphicsObjectType inType, std::string const& inName,
            int inBindPoint, int inNumBytes, unsigned int inExtra,
            bool inIsGpuWritable);

        std::shared_ptr<GraphicsObject> object; // CB, TB, SB, RB, TX, TA, SS
        GraphicsObjectType type;                // CB, TB, SB, RB, TX, TA, SS
        std::string name;                       // CB, TB, SB, RB, TX, TA, SS
        int bindPoint;                          // CB, TB, SB, RB, TX, TA, SS
        int numBytes;                           // CB, TB, SB, RB
        unsigned int extra;                     // TX, TA (dims), SB (ctrtype)
        bool isGpuWritable;                     // SB, RB, TX, TA
    };

    bool IsValid(Data const& goal, ConstantBuffer* resource) const;
    bool IsValid(Data const& goal, TextureBuffer* resource) const;
    bool IsValid(Data const& goal, StructuredBuffer* resource) const;
    bool IsValid(Data const& goal, RawBuffer* resource) const;
    bool IsValid(Data const& goal, TextureSingle* resource) const;
    bool IsValid(Data const& goal, TextureArray* resource) const;
    bool IsValid(Data const& goal, SamplerState* state) const;

    enum { NUM_LOOKUP_INDICES = 7 };  // CB, TB, SB, RB, TX, TA, SS
    std::vector<Data> mData[NUM_LOOKUP_INDICES];
    std::vector<unsigned char> mCompiledCode;
    unsigned int mNumXThreads;
    unsigned int mNumYThreads;
    unsigned int mNumZThreads;

private:
    std::vector<std::vector<MemberLayout>> mCBufferLayouts;
    std::vector<std::vector<MemberLayout>> mTBufferLayouts;

public:
    // For use by the graphics engine.
    inline std::vector<unsigned char> const& GetCompiledCode() const;
    inline std::vector<Data> const& GetData(int lookup) const;
};

#include "GteShader.inl"

}
