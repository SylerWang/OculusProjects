// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

// Given points (x0[i],y0[i]) which are mapped to (x1[i],y1[i]) for
// 0 <= i < N, interpolate positions (xIn,yIn) to (xOut,yOut).

#include "GteIntpQuadraticNonuniform2.h"
#include "GteDelaunay2Mesh.h"

namespace gte
{

template <typename InputType, typename ComputeType, typename RationalType>
class IntpVectorField2
{
public:
    // Construction and destruction.
    ~IntpVectorField2();
    IntpVectorField2(int numPoints, Vector2<InputType> const* domain,
        Vector2<InputType> const* range);

    // The return value is 'true' if and only if (xIn,yIn) is in the convex
    // hull of the input domain points, in which case the interpolation is
    // valid.
    bool operator()(Vector2<InputType> const& input,
        Vector2<InputType>& output) const;

protected:
    typedef Delaunay2Mesh<InputType, ComputeType, RationalType> TriangleMesh;
    Delaunay2<InputType, ComputeType> mDelaunay;
    TriangleMesh mMesh;

    std::vector<InputType> mXRange;
    std::vector<InputType> mYRange;
    IntpQuadraticNonuniform2<InputType, TriangleMesh>* mXInterp;
    IntpQuadraticNonuniform2<InputType, TriangleMesh>* mYInterp;
};

#include "GteIntpVectorField2.inl"

}
