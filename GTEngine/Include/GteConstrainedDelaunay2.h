// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDelaunay2.h"
#include <list>

// Various parts of the code have this trap for error conditions.  With a
// correct algorithm and exact arithmetic, we do not expect to trigger the
// error.  However, with floating-point arithmetic, it is possible that the
// triangulation becomes malformed.  The constrained Delaunay triangulation
// implementation is designed to return gracefully with such a failure.  The
// following macros are used to make the code more readable.  Do NOT disable
// them, because they have necessary side effects.
#define GTE_CDT_REQUIRE(c) { if (!(c)) { Trap(); return false; } }
#define GTE_CDT_FAILURE { Trap(); return false; }
#define GTE_CDT_REQUIRE_RET(c, r)  { if (!(c)) { Trap(); return r; } }
#define GTE_CDT_FAILURE_RET(r) { Trap(); return r; }

namespace gte
{

template <typename InputType, typename ComputeType>
class ConstrainedDelaunay2 : public Delaunay2<InputType, ComputeType>
{
public:
    // The class is a functor to support computing the constrained Delaunay
    // triangulation of multiple data sets using the same class object.
    virtual ~ConstrainedDelaunay2();
    ConstrainedDelaunay2();

    // This operator computes the Delaunay triangulation only.  Read the
    // Delaunay2 constructor comments about 'vertices' and 'epsilon'.
    //The 'edges' array has indices into the 'vertices' array.
    // No two edges should intersect except at endpoints.
    bool operator()(int numVertices, Vector2<InputType> const* vertices,
        InputType epsilon);

    // Insert required edges into the triangulation.  For correctness of the
    // algorithm, if two edges passed to this function intersect, they must
    // do so only at vertices passed to operator().  If you have two edges
    // that intersect at a point not in the vertices, compute that point of
    // intersection and subdivide the edges at that intersection (to form
    // more edges), and add the point to the vertices before calling
    // operator().  This function has an output array that contains the
    // input edge when the only vertices on the edge are its endpoints.  If
    // the input edge passes through more vertices, the edge is subdivided
    // in this function.  The output edge is that subdivision with first
    // vertex edge[0] and last vertex edge[1], and the other vertices are
    // correctly ordered along the edge.
    bool Insert(std::array<int, 2> const& edge, std::vector<int>& outEdge);

private:
    // The top-level entry point for inserting an edge in the triangulation.
    bool Insert(std::array<int, 2> const& edge, int v0Triangle,
        std::vector<int>& outEdge);

    // Process the coincident edge.
    bool ProcessCoincident(int tri, int v0, int v1, int vOther,
        std::vector<int>& outEdge);

    // Process the triangle strip originating at the first endpoint of the
    // edge.
    bool ProcessInterior(int tri, int v0, int v1, int vNext, int vPrev,
        std::vector<int>& outEdge);

    // Remove the triangles in the triangle strip and retriangulate the
    // left and right polygons using the empty circumcircle condition.
    bool Retriangulate(std::vector<int>& polygon,
        std::vector<std::array<int, 2>> const& lBoundary,
        std::vector<std::array<int, 2>> const& rBoundary);

    int RetriangulateLRecurse(
        std::vector<std::array<int, 2>> const& lBoundary,
        int i0, int i1, int a0, std::vector<int>& polygon);

    int RetriangulateRRecurse(
        std::vector<std::array<int, 2>> const& rBoundary,
        int i0, int i1, int a0, std::vector<int>& polygon);

    int SelectSplit(std::vector<std::array<int, 2>> const& boundary, int i0,
        int i1) const;

    // Compute a pseudosquared distance from the vertex at v2 to the edge
    // <v0,v1>.
    ComputeType ComputePSD(int v0, int v1, int v2) const;

    // Search the triangulation for a triangle that contains the specified
    // vertex.
    int GetLinkTriangle(int v) const;

    // Determine the index in {0,1,2} for the triangle 'tri' that contains
    // the vertex 'v'.
    int GetIndexOfVertex(int tri, int v) const;

    // Given a triangle 'tri' with CCW-edge <v0,v1>, return <adj,v2> where
    // 'adj' is the index of the triangle adjacent to 'tri' that shares the
    // edge and 'v2' is the vertex of the adjacent triangle opposite the
    // edge.  This function supports traversing a triangle strip that contains
    // a constraint edge, so it is called only when an adjacent triangle
    // actually exists.
    std::array<int, 2> GetAdjInterior(int tri, int v0, int v1) const;

    // Given a triangle 'tri' of the triangle strip, the boundary edge must
    // contain the vertex with index 'needBndVertex'.  The input
    // 'needAdjVIndex' specifies where to look for the index of the triangle
    // outside the strip but adjacent to the boundary edge.  The return
    // value is <needBndVertex, adj> and is used to connect 'tri' and 'adj'
    // across a triangle strip boundary.
    std::array<int, 2> GetAdjBoundary(int tri, int needBndVertex,
        int needAdjVIndex) const;

    // Set the indices and adjacencies arrays so that 'tri' and 'adj' share
    // the common edge; 'tri' has CCW-edge <v0,v1> and 'adj' has CCW-edge
    // <v1,v0>.
    bool Connect(int tri, int adj, int v0, int v1);

    // Create an ordered list of triangles forming the link of a vertex.  The
    // pair of the list is <triangle,GetIndexOfV(triangle)>.  This allows us
    // to cache the index of v relative to each triangle in the link.  The
    // vertex v might be a boundary vertex, in which case the neighborhood is
    // open; otherwise, v is an interior vertex and the neighborhood is
    // closed.  The 'isOpen' parameter specifies the case.
    bool BuildLink(int v, int vTriangle, std::list<std::pair<int,int>>& link,
        bool& isOpen) const;

    // Support for return-false-on-error.  This allows us to investigate the
    // error by setting a break point, trigger an assert when the logger is
    // active, and get a call stack.
    void Trap() const;
};

#include "GteConstrainedDelaunay2.inl"

}
