// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/17)

#pragma once

#include "GteTSManifoldMesh.h"
#include "GteLine3.h"
#include "GtePlane3.h"
#include "GtePrimalQuery3.h"
#include "GteLogger.h"
#include <vector>

// Delaunay tetrahedralization of points (intrinsic dimensionality 3).
//   VQ = number of vertices
//   V  = array of vertices
//   TQ = number of tetrahedra
//   I  = Array of 4-tuples of indices into V that represent the tetrahedra
//        (4*TQ total elements).  Access via GetIndices(*).
//   A  = Array of 4-tuples of indices into I that represent the adjacent
//        tetrahedra (4*TQ total elements).  Access via GetAdjacencies(*).
// The i-th tetrahedron has vertices
//   vertex[0] = V[I[4*i+0]]
//   vertex[1] = V[I[4*i+1]]
//   vertex[2] = V[I[4*i+2]]
//   vertex[3] = V[I[4*i+3]]
// and face index triples listed below.  The face vertex ordering when
// viewed from outside the tetrahedron is counterclockwise.
//   face[0] = <I[4*i+1],I[4*i+2],I[4*i+3]>
//   face[1] = <I[4*i+0],I[4*i+3],I[4*i+2]>
//   face[2] = <I[4*i+0],I[4*i+1],I[4*i+3]>
//   face[3] = <I[4*i+0],I[4*i+2],I[4*i+1]>
// The tetrahedra adjacent to these faces have indices
//   adjacent[0] = A[4*i+0] is the tetrahedron opposite vertex[0], so it
//                 is the tetrahedron sharing face[0].
//   adjacent[1] = A[4*i+1] is the tetrahedron opposite vertex[1], so it
//                 is the tetrahedron sharing face[1].
//   adjacent[2] = A[4*i+2] is the tetrahedron opposite vertex[2], so it
//                 is the tetrahedron sharing face[2].
//   adjacent[3] = A[4*i+3] is the tetrahedron opposite vertex[3], so it
//                 is the tetrahedron sharing face[3].
// If there is no adjacent tetrahedron, the A[*] value is set to -1.  The
// tetrahedron adjacent to face[j] has vertices
//   adjvertex[0] = V[I[4*adjacent[j]+0]]
//   adjvertex[1] = V[I[4*adjacent[j]+1]]
//   adjvertex[2] = V[I[4*adjacent[j]+2]]
//   adjvertex[3] = V[I[4*adjacent[j]+3]]
// The only way to ensure a correct result for the input vertices (assumed to
// be exact) is to choose ComputeType for exact rational arithmetic.  You may
// use BSNumber.  No divisions are performed in this computation, so you do
// not have to use BSRational.

namespace gte
{

template <typename InputType, typename ComputeType>
class Delaunay3
{
public:
    // The class is a functor to support computing the Delaunay
    // tetrahedralization of multiple data sets using the same class object.
    Delaunay3();

    // The input is the array of vertices whose Delaunay tetrahedralization
    // is required.  The epsilon value is used to determine the intrinsic
    // dimensionality of the vertices (d = 0, 1, 2, or 3).  When epsilon is
    // positive, the determination is fuzzy--vertices approximately the same
    // point, approximately on a line, approximately planar, or volumetric.
    bool operator()(int numVertices, Vector3<InputType> const* vertices,
        InputType epsilon);

    // Dimensional information.  If GetDimension() returns 1, the points lie
    // on a line P+t*D (fuzzy comparison when epsilon > 0).  You can sort
    // these if you need a polyline output by projecting onto the line each
    // vertex X = P+t*D, where t = Dot(D,X-P).  If GetDimension() returns 2,
    // the points line on a plane P+s*U+t*V (fuzzy comparison when
    // epsilon > 0).  You can project each vertex X = P+s*U+t*V, where
    // s = Dot(U,X-P) and t = Dot(V,X-P), then apply Delaunay2 to the (s,t)
    // tuples.
    inline InputType GetEpsilon() const;
    inline int GetDimension() const;
    inline Line3<InputType> const& GetLine() const;
    inline Plane3<InputType> const& GetPlane() const;

    // Member access.
    inline int GetNumVertices() const;
    inline int GetNumUniqueVertices() const;
    inline int GetNumTetrahedra() const;
    inline Vector3<InputType> const* GetVertices() const;
    inline PrimalQuery3<ComputeType> const& GetQuery() const;
    inline TSManifoldMesh const& GetGraph() const;
    inline std::vector<int> const& GetIndices() const;
    inline std::vector<int> const& GetAdjacencies() const;

    // Locate those tetrahedra faces that do not share other tetrahedra.  The
    // returned array has hull.size() = 3*numFaces indices, each triple
    // representing a triangle.  The triangles are counterclockwise ordered
    // when viewed from outside the hull.  The return value is 'true' iff the
    // dimension is 3.
    bool GetHull(std::vector<int>& hull) const;

    // Get the vertex indices for tetrahedron i.  The function returns 'true'
    // when the dimension is 3 and i is a valid tetrahedron index, in which
    // case the vertices are valid; otherwise, the function returns 'false'
    // and the vertices are invalid.
    bool GetIndices(int i, std::array<int, 4>& indices) const;

    // Get the indices for tetrahedra adjacent to tetrahedron i.  The function
    // returns 'true' when the dimension is 3 and i is a valid tetrahedron
    // index, in which case the adjacencies are valid; otherwise, the function
    // returns 'false' and the adjacencies are invalid.
    bool GetAdjacencies(int i, std::array<int, 4>& adjacencies) const;

    // Support for searching the tetrahedralization for a tetrahedron that
    // contains a point.  If there is a containing tetrahedron, the returned
    // value is a tetrahedron index i with 0 <= i < GetNumTetrahedra().  If
    // there is not a containing tetrahedron, -1 is returned.  The
    // computations are performed using exact rational arithmetic.
    //
    // The SearchInfo input stores information about the tetrahedron search
    // when looking for the tetrahedron (if any) that contains p.  The first
    // tetrahedron searched is 'initialTetrahedron'.  On return 'path' stores
    // those (ordered) tetrahedron indices visited during the search.  The
    // last visited tetrahedron has index 'finalTetrahedron and vertex indices
    // 'finalV[0,1,2,3]', stored in volumetric counterclockwise order.  The
    // last face of the search is <finalV[0],finalV[1],finalV[2]>.  For
    // spatially coherent inputs p for numerous calls to this function, you
    // will want to specify 'finalTetrahedron' from the previous call as
    // 'initialTetrahedron' for the next call, which should reduce search
    // times.
    struct SearchInfo
    {
        int initialTetrahedron;
        int numPath;
        std::vector<int> path;
        int finalTetrahedron;
        std::array<int, 4> finalV;
    };
    int GetContainingTetrahedron(Vector3<InputType> const& p,
        SearchInfo& info) const;

private:
    // Support for incremental Delaunay tetrahedralization.
    typedef TSManifoldMesh::Tetrahedron Tetrahedron;
    bool GetContainingTetrahedron(int i, Tetrahedron*& tetra) const;
    void GetAndRemoveInsertionPolyhedron(int i,
        std::set<Tetrahedron*>& candidates,
        std::set<TriangleKey<true>>& boundary);
    void Update (int i);

    // The epsilon value is used for fuzzy determination of intrinsic
    // dimensionality.  If the dimension is 0, 1, or 2, the constructor
    // returns early.  The caller is responsible for retrieving the dimension
    // and taking an alternate path should the dimension be smaller than 3.
    // If the dimension is 0, the caller may as well treat all vertices[]
    // as a single point, say, vertices[0].  If the dimension is 1, the
    // caller can query for the approximating line and project vertices[]
    // onto it for further processing.  If the dimension is 2, the caller can
    // query for the approximating plane and project vertices[] onto it for
    // further processing.
    InputType mEpsilon;
    int mDimension;
    Line3<InputType> mLine;
    Plane3<InputType> mPlane;

    // The array of vertices used for geometric queries.  If you want to be
    // certain of a correct result, choose ComputeType to be BSNumber.
    std::vector<Vector3<ComputeType>> mComputeVertices;
    PrimalQuery3<ComputeType> mQuery;

    // The graph information.
    int mNumVertices;
    int mNumUniqueVertices;
    int mNumTetrahedra;
    Vector3<InputType> const* mVertices;
    TSManifoldMesh mGraph;
    std::vector<int> mIndices;
    std::vector<int> mAdjacencies;
};

#include "GteDelaunay3.inl"

}
