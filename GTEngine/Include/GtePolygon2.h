// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteVector2.h"
#include <set>
#include <vector>

namespace gte
{

// The Polygon2 object represents a simple polygon:  No duplicate vertices,
// closed (each vertex is shared by exactly two edges), and no
// self-intersections at interior edge points.  The 'vertexPool' array can
// contain more points than needed to define the polygon, which allows the
// vertex pool to have multiple polygons associated with it.  Thus, the
// programmer must ensure that the vertex pool persists as long as any
// Polygon2 objects exist that depend on the pool.  The number of polygon
// vertices is 'numIndices' and must be 3 or larger.  The 'indices' array
// refers to the points in 'vertexPool' that are part of the polygon and must
// have 'numIndices' unique elements.  The edges of the polygon are pairs of
// indices into 'vertexPool',
//   edge[0] = (indices[0], indices[1])
//   :
//   edge[numIndices-2] = (indices[numIndices-2], indices[numIndices-1])
//   edge[numIndices-1] = (indices[numIndices-1], indices[0])
// The programmer should ensure the polygon is simple.  The geometric
// queries are valid regardless of whether the polygon is oriented clockwise
// or counterclockwise.
//
// NOTE:  Polygon2 is not derived from GeometricPrimitive, because the
// semantics of equal polygons is complicated and (at the moment) not useful.
// The vertex pools can be different and indices do not match, but the
// vertices they reference can match.  Even with a shared vertex pool, the
// indices can be "rotated", leading to the same polygon abstractly but the
// data structures do not match.

template <typename Real>
class Polygon2
{
public:
    // Construction and destruction.  The constructor succeeds when
    // numVertices >= 3 and 'vertices' and 'indices' are not null; we
    // cannot test whether you have a valid number of elements in the input
    // arrays.  A copy is made of 'indices', but the 'vertexPool' is not
    // copied.  If the constructor fails, the internal vertex pointer is
    // set to null, the  index array has no elements, and the orientation
    // is set to clockwise.
    ~Polygon2();
    Polygon2(Vector2<Real> const* vertices, int numIndices,
        int const* indices, bool counterClockwise);

    // To validate construction, create an object as shown:
    //     Polygon2<Real> polygon(parameters);
    //     if (!polygon) { <constructor failed, handle accordingly>; }
    inline operator bool() const;

    // Member access.
    inline Vector2<Real> const* GetVertexPool() const;
    inline std::set<int> const& GetVertices() const;
    inline std::vector<int> const& GetIndices() const;
    inline bool CounterClockwise() const;

    // Geometric queries.
    Vector2<Real> ComputeVertexAverage() const;
    Real ComputePerimeterLength() const;
    Real ComputeArea() const;

private:
    Vector2<Real> const* mVertexPool;
    std::set<int> mVertices;
    std::vector<int> mIndices;
    bool mCounterClockwise;
};

#include "GtePolygon2.inl"

}
