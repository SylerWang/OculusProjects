// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/17)

#pragma once

#include "GteETManifoldMesh.h"
#include "GteLine2.h"
#include "GtePrimalQuery2.h"
#include "GteLogger.h"
#include <vector>

// Delaunay triangulation of points (intrinsic dimensionality 2).
//   VQ = number of vertices
//   V  = array of vertices
//   TQ = number of triangles
//   I  = Array of 3-tuples of indices into V that represent the triangles
//        (3*TQ total elements).  Access via GetIndices(*).
//   A  = Array of 3-tuples of indices into I that represent the adjacent
//        triangles (3*TQ total elements).  Access via GetAdjacencies(*).
// The i-th triangle has vertices
//   vertex[0] = V[I[3*i+0]]
//   vertex[1] = V[I[3*i+1]]
//   vertex[2] = V[I[3*i+2]]
// and edge index pairs
//   edge[0] = <I[3*i+0],I[3*i+1]>
//   edge[1] = <I[3*i+1],I[3*i+2]>
//   edge[2] = <I[3*i+2],I[3*i+0]>
// The triangles adjacent to these edges have indices
//   adjacent[0] = A[3*i+0] is the triangle sharing edge[0]
//   adjacent[1] = A[3*i+1] is the triangle sharing edge[1]
//   adjacent[2] = A[3*i+2] is the triangle sharing edge[2]
// If there is no adjacent triangle, the A[*] value is set to -1.  The
// triangle adjacent to edge[j] has vertices
//   adjvertex[0] = V[I[3*adjacent[j]+0]]
//   adjvertex[1] = V[I[3*adjacent[j]+1]]
//   adjvertex[2] = V[I[3*adjacent[j]+2]]
// The only way to ensure a correct result for the input vertices (assumed to
// be exact) is to choose ComputeType for exact rational arithmetic.  You may
// use BSNumber.  No divisions are performed in this computation, so you do
// not have to use BSRational.

namespace gte
{

template <typename InputType, typename ComputeType>
class Delaunay2
{
public:
    // The class is a functor to support computing the Delaunay triangulation
    // of multiple data sets using the same class object.
    virtual ~Delaunay2();
    Delaunay2();

    // The input is the array of vertices whose Delaunay triangulation is
    // required.  The epsilon value is used to determine the intrinsic
    // dimensionality of the vertices (d = 0, 1, or 2).  When epsilon is
    // positive, the determination is fuzzy--vertices approximately the same
    // point, approximately on a line, or planar.  The return value is 'true'
    // if and only if the hull construction is successful.
    bool operator()(int numVertices, Vector2<InputType> const* vertices,
        InputType epsilon);

    // Dimensional information.  If GetDimension() returns 1, the points lie
    // on a line P+t*D (fuzzy comparison when epsilon > 0).  You can sort
    // these if you need a polyline output by projecting onto the line each
    // vertex X = P+t*D, where t = Dot(D,X-P).
    inline InputType GetEpsilon() const;
    inline int GetDimension() const;
    inline Line2<InputType> const& GetLine() const;

    // Member access.
    inline int GetNumVertices() const;
    inline int GetNumUniqueVertices() const;
    inline int GetNumTriangles() const;
    inline Vector2<InputType> const* GetVertices() const;
    inline PrimalQuery2<ComputeType> const& GetQuery() const;
    inline ETManifoldMesh const& GetGraph() const;
    inline std::vector<int> const& GetIndices() const;
    inline std::vector<int> const& GetAdjacencies() const;

    // If 'vertices' has no duplicates, GetDuplicates()[i] = i for all i.
    // If vertices[i] is the first occurrence of a vertex and if vertices[j]
    // is found later, then GetDuplicates()[j] = i.
    inline std::vector<int> const& GetDuplicates() const;

    // Locate those triangle edges that do not share other triangles.  The
    // returned array has hull.size() = 2*numEdges, each pair representing an
    // edge.  The edges are not ordered, but the pair of vertices for an edge
    // is ordered so that they conform to a counterclockwise traversal of the
    // hull.  The return value is 'true' iff the dimension is 2.
    bool GetHull(std::vector<int>& hull) const;

    // Get the vertex indices for triangle i.  The function returns 'true'
    // when the dimension is 2 and i is a valid triangle index, in which case
    // the vertices are valid; otherwise, the function returns 'false' and the
    // vertices are invalid.
    bool GetIndices(int i, std::array<int, 3>& indices) const;

    // Get the indices for triangles adjacent to triangle i.  The function
    // returns 'true' when the dimension is 2 and if i is a valid triangle
    // index, in which case the adjacencies are valid; otherwise, the function
    // returns 'false' and the adjacencies are invalid.
    bool GetAdjacencies(int i, std::array<int, 3>& adjacencies) const;

    // Support for searching the triangulation for a triangle that contains
    // a point.  If there is a containing triangle, the returned value is a
    // triangle index i with 0 <= i < GetNumTriangles().  If there is not a
    // containing triangle, -1 is returned.  The computations are performed
    // using exact rational arithmetic.
    //
    // The SearchInfo input stores information about the triangle search when
    // looking for the triangle (if any) that contains p.  The first triangle
    // searched is 'initialTriangle'.  On return 'path' stores those (ordered)
    // triangle indices visited during the search.  The last visited triangle
    // has index 'finalTriangle and vertex indices 'finalV[0,1,2]', stored in
    // counterclockwise order.  The last edge of the search is
    // <finalV[0],finalV[1]>.  For spatially coherent inputs p for numerous
    // calls to this function, you will want to specify 'finalTriangle' from
    // the previous call as 'initialTriangle' for the next call, which should
    // reduce search times.
    struct SearchInfo
    {
        int initialTriangle;
        int numPath;
        std::vector<int> path;
        int finalTriangle;
        std::array<int, 3> finalV;
    };
    int GetContainingTriangle(Vector2<InputType> const& p,
        SearchInfo& info) const;

protected:
    // Support for incremental Delaunay triangulation.
    typedef ETManifoldMesh::Triangle Triangle;
    bool GetContainingTriangle(int i, Triangle*& tri) const;
    void GetAndRemoveInsertionPolygon(int i,
        std::set<Triangle*>& candidates, std::set<EdgeKey<true>>& boundary);
    void Update(int i);

    // The epsilon value is used for fuzzy determination of intrinsic
    // dimensionality.  If the dimension is 0 or 1, the constructor returns
    // early.  The caller is responsible for retrieving the dimension and
    // taking an alternate path should the dimension be smaller than 2.
    // If the dimension is 0, the caller may as well treat all vertices[]
    // as a single point, say, vertices[0].  If the dimension is 1, the
    // caller can query for the approximating line and project vertices[]
    // onto it for further processing.
    InputType mEpsilon;
    int mDimension;
    Line2<InputType> mLine;

    // The array of vertices used for geometric queries.  If you want to be
    // certain of a correct result, choose ComputeType to be BSNumber.
    std::vector<Vector2<ComputeType>> mComputeVertices;
    PrimalQuery2<ComputeType> mQuery;

    // The graph information.
    int mNumVertices;
    int mNumUniqueVertices;
    int mNumTriangles;
    Vector2<InputType> const* mVertices;
    ETManifoldMesh mGraph;
    std::vector<int> mIndices;
    std::vector<int> mAdjacencies;

    // If a vertex occurs multiple times in the 'vertices' input to the
    // constructor, the first processed occurrence of that vertex has an
    // index stored in this array.  If there are no duplicates, then
    // mDuplicates[i] = i for all i.

    struct ProcessedVertex
    {
        ProcessedVertex();
        ProcessedVertex(Vector2<InputType> const& inVertex, int inLocation);
        bool operator<(ProcessedVertex const& v) const;

        Vector2<InputType> vertex;
        int location;
    };

    std::vector<int> mDuplicates;

    // Indexing for the vertices of the triangle adjacent to a vertex.  The
    // edge adjacent to vertex j is <mIndex[j][0], mIndex[j][1]> and is listed
    // so that the triangle interior is to your left as you walk around the
    // edges.  TODO: Use the "opposite edge" to be consistent with that of
    // TetrahedronKey.  The "opposite" idea extends easily to higher
    // dimensions.
    std::array<std::array<int, 2>, 3> mIndex;
};

#include "GteDelaunay2.inl"

}
