// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteVector3.h"
#include <set>
#include <vector>

namespace gte
{

// The Polyhedron3 object represents a simple polyhedron.  The 'vertexPool'
// array can contain more points than needed to define the polyhedron, which
// allows the vertex pool to have multiple polyhedra associated with it.
// Thus, the programmer must ensure that the vertex pool persists as long as
// any Polyhedron3 objects exist that depend on the pool.  The number of
// polyhedron indices is 'numIndices' and must be 6 or larger  The 'indices'
// array refers to the points in 'vertexPool' that form the triangle faces,
// so 'numIndices' must be a multiple of 3.  The number of vertices is
// the number of unique elements in 'indices' and is determined during
// construction.  The programmer should ensure the polyhedron is simple.  The
// geometric queries are valid regardless of whether the polyhedron triangles
// are oriented clockwise or counterclockwise.
//
// NOTE:  Polyhedron3 is not derived from GeometricPrimitive, because the
// semantics of equal polyhedra is complicated and (at the moment) not useful.
// The vertex pools can be different and indices do not match, but the
// vertices they reference can match.  Even with a shared vertex pool, the
// indices can be permuted, leading to the same polyhedron abstractly but the
// data structures do not match.

template <typename Real>
class Polyhedron3
{
public:
    // Construction and destruction.  The constructor succeeds when
    // numIndices >= 6, numVertices >= 4 (determined from the indices), and
    // 'vertices' and 'indices' are not null; we cannot test whether you have
    // a valid number of elements in the input arrays.  A copy is made of
    // 'indices', but the 'vertexPool' is not copied.  If the constructor
    // fails, the internal vertex pointer is set to null, the number of
    // vertices is set to zero, the index array has no elements, and the
    // triangle face orientation is set to clockwise.
    ~Polyhedron3();
    Polyhedron3(Vector3<Real> const* vertices, int numIndices,
        int const* indices, bool counterClockwise);

    // To validate construction, create an object as shown:
    //     Polyhedron3<Real> polyhedron(parameters);
    //     if (!polyhedron) { <constructor failed, handle accordingly>; }
    inline operator bool() const;

    // Member access.
    inline Vector3<Real> const* GetVertexPool() const;
    inline std::set<int> const& GetVertices() const;
    inline std::vector<int> const& GetIndices() const;
    inline bool CounterClockwise() const;

    // Geometric queries.
    Vector3<Real> ComputeVertexAverage() const;
    Real ComputeSurfaceArea() const;
    Real ComputeVolume() const;

private:
    Vector3<Real> const* mVertexPool;
    std::set<int> mVertices;
    std::vector<int> mIndices;
    bool mCounterClockwise;
};

#include "GtePolyhedron3.inl"

}
