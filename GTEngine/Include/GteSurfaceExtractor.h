// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteMarchingCubes.h"
#include <cstring>

namespace gte
{

template <typename Real>
class SurfaceExtractor : public MarchingCubes
{
public:
    // Construction and destruction.
    virtual ~SurfaceExtractor();
    SurfaceExtractor();

    // The input function values must be stored as
    //  F[0] = function(0,0,0), F[4] = function(0,0,1),
    //  F[1] = function(1,0,0), F[5] = function(1,0,1),
    //  F[2] = function(0,1,0), F[6] = function(0,1,1),
    //  F[3] = function(1,1,0), F[7] = function(1,1,1).
    // Thus, F[k] = function(k & 1, (k & 2) >> 1, (k & 4) >> 2).
    // The return value is 'true' iff the F[] values are all nonzero.
    // If they are not, the returned 'mesh' has no vertices and no
    // triangles--as if F[] had all positive or all negative values.

    struct Mesh
    {
        int numVertices;
        int numTriangles;
        int vpair[2*MAX_VERTICES];
        int itriple[3*MAX_TRIANGLES];
        Real vertices[MAX_VERTICES][3];
    };

    bool Extract(Real const F[8], Mesh& mesh) const;
};

#include "GteSurfaceExtractor.inl"

}
