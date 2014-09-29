// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteBuffer.h"

namespace gte
{

class GTE_IMPEXP IndirectArgumentsBuffer : public Buffer
{
public:
    // Construction.  Each element is a 4-byte value.  For storing a
    // single set of input parameters to a draw call, the layout of
    // the buffer should be as shown next.  The parameters are in the
    // order expected by the Draw* call without the 'Indirect' suffix.
    //
    // DrawInstancedIndirect:
    //   UINT VertexCountPerInstance;
    //   UINT InstanceCount;
    //   UINT StartVertexLocation;
    //   UINT StartInstanceLocation;
    //
    // DrawIndexedInstancedIndirect:
    //   UINT IndexCountPerInstance;
    //   UINT InstanceCount;
    //   UINT StartIndexLocation;
    //   INT  BaseVertexLocation;
    //   UINT StartInstanceLocation;
    //
    // DispatchIndirect:
    //   UINT ThreadsGroupCountX;
    //   UINT ThreadsGroupCountY;
    //   UINT ThreadsGroupCountZ;

    IndirectArgumentsBuffer(unsigned int numElements,
        bool createStorage = true);
};

}
