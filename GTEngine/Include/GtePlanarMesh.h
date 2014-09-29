// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.3.0 (2014/09/11)

#pragma once

#include "GteETManifoldMesh.h"
#include "GtePrimalQuery2.h"
#include "GteLogger.h"
#include <algorithm>
#include <vector>

namespace gte
{

template <typename InputType, typename ComputeType, typename RationalType>
class PlanarMesh
{
public:
    // Construction.  The inputs must represent a manifold mesh of triangles
    // in the plane.  The index array must have 3*numTriangles elements, each
    // triple of indices representing a triangle in the mesh.  Each index is
    // into the 'vertices' array.
    PlanarMesh(int numVertices, Vector2<InputType> const* vertices,
        int numTriangles, int const* indices);

    PlanarMesh(int numVertices, Vector2<InputType> const* vertices,
        ETManifoldMesh const& mesh);

    // Mesh information.
    inline int GetNumVertices() const;
    inline int GetNumTriangles() const;
    inline Vector2<InputType> const* GetVertices() const;
    inline int const* GetIndices() const;
    inline int const* GetAdjacencies() const;

    // Containment queries.  The function GetContainingTriangle works
    // correctly when the planar mesh is a convex set.  If the mesh is not
    // convex, it is possible that the linear-walk search algorithm exits the
    // mesh before finding a containing triangle.  For example, a C-shaped
    // mesh can contain a point in the top branch of the "C".  A starting
    // point in the bottom branch of the "C" will lead to the search exiting
    // the bottom branch and having no path to walk to the top branch.  If
    // your mesh is not convex and you want a correct containment query, you
    // will have to append "outside" triangles to your mesh to form a convex
    // set.
    int GetContainingTriangle(Vector2<InputType> const& P,
        int startTriangle = 0) const;
    bool GetVertices(int t, std::array<Vector2<InputType>, 3>& vertices)
        const;
    bool GetIndices(int t, std::array<int, 3>& indices) const;
    bool GetAdjacencies(int t, std::array<int, 3>& adjacencies) const;
    bool GetBarycentrics(int t, Vector2<InputType> const& P,
        std::array<InputType, 3>& bary) const;

private:
    void CreateVertices(int numVertices, Vector2<InputType> const* vertices);

    int mNumVertices;
    Vector2<InputType> const* mVertices;
    int mNumTriangles;
    std::vector<int> mIndices;
    std::vector<int> mAdjacencies;
    std::vector<Vector2<ComputeType>> mComputeVertices;
    PrimalQuery2<ComputeType> mQuery;
};

#include "GtePlanarMesh.inl"

}
