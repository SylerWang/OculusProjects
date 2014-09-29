// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.3.4 (2014/09/25)

#pragma once

#include "GteComputeModel.h"
#include "GteConstants.h"
#include "GteETManifoldMesh.h"
#include "GteVector2.h"
#include "GteVector3.h"
#include <algorithm>
#include <cstring>
#include <functional>
#include <limits>
#include <set>
#include <thread>
#include <vector>

#if defined(WIN32)
#include "GteConstantBuffer.h"
#include "GteShaderFactory.h"
#include "GteStructuredBuffer.h"
extern std::string const gGenerateMeshUVsHLSLString;
#endif

// This class is an implementation of the barycentric mapping algorithm
// described in Section 5.3 of the book
//     Polygon Mesh Processing
//     Mario Botsch, Leif Kobbelt, Mark Pauly, Pierre Alliez, Bruno Levy
//     AK Peters, Ltd., Natick MA, 2010
// It uses the mean value weights described in Section 5.3.1 to allow the mesh
// geometry to influence the texture coordinate generation, and it uses
// Gauss-Seidel iteration to solve the sparse linear system.  The authors'
// advice is that the Gauss-Seidel approach works well for at most about 5000
// vertices, presumably the convergence rate degrading as the number of
// vertices increases.
//
// The algorithm implemented here has an additional preprocessing step that
// computes a topological distance transform of the vertices.  The boundary
// texture coordinates are propagated inward by updating the vertices in
// topological distance order, leading to fast convergence for large numbers
// of vertices.

namespace gte
{

template <typename Real>
class GenerateMeshUV
{
public:
    class UVComputeModel : public ComputeModel
    {
    public:
        virtual ~UVComputeModel();
        UVComputeModel();
        UVComputeModel(unsigned int inNumThreads,
            std::function<void(unsigned int)> const* inProgress);
#if defined(WIN32)
        UVComputeModel(DX11Engine* inEngine, unsigned int inNumThreads,
            std::function<void(unsigned int)> const* inProgress);
#endif
        std::function<void(unsigned int)> const* progress;
    };

    // Construction.
    GenerateMeshUV(std::shared_ptr<UVComputeModel> const& cmodel);

    // The incoming mesh must be edge-triangle manifold and have rectangle
    // topology (simply connected, closed polyline boundary).  The arrays
    // 'vertices' and 'tcoords' must both have 'numVertices' elements.  Set
    // 'useSquareTopology' to true for the generated coordinates to live
    // in the uv-square [0,1]^2.  Set it to false for the generated
    // coordinates to live in a convex polygon that inscribes the uv-disk
    // of center (1/2,1/2) and radius 1/2.
    void operator()(unsigned int numIterations, bool useSquareTopology,
        int numVertices, Vector3<Real> const* vertices, int numIndices,
        int const* indices, Vector2<Real>* tcoords);

private:
    void TopologicalVertexDistanceTransform();
    void AssignBoundaryTextureCoordinatesSquare();
    void AssignBoundaryTextureCoordinatesDisk();
    void ComputeMeanValueWeights();
    void SolveSystem(unsigned int numIterations);
    void SolveSystemCPUSingle(unsigned int numIterations);
    void SolveSystemCPUMultiple(unsigned int numIterations);

    // Convenience members that store the input parameters to operator().
    int mNumVertices;
    Vector3<Real> const* mVertices;
    Vector2<Real>* mTCoords;

    // The edge-triangle manifold graph, where each edge is shared by at most
    // two triangles.
    ETManifoldMesh mGraph;

    // The mVertexInfo array stores -1 for the interior vertices.  For a
    // boundary edge <v0,v1> that is counterclockwise, mVertexInfo[v0] = v1,
    // which gives us an orded boundary polyline.
    enum { INTERIOR_VERTEX = -1 };
    std::vector<int> mVertexInfo;
    int mNumBoundaryEdges, mBoundaryStart;
    std::set<ETManifoldMesh::Edge const*> mInteriorEdges;

    // The vertex graph required to set up a sparse linear system of equations
    // to determine the texture coordinates.
    struct Vertex
    {
        // The topological distance from the boundary of the mesh.
        int distance;

        // The value range[0] is the index into mVertexGraphData for the first
        // adjacent vertex.  The value range[1] is the number of adjacent
        // vertices.
        std::array<int, 2> range;
    };
    std::vector<Vertex> mVertexGraph;
    std::vector<std::pair<int, Real>> mVertexGraphData;

    // The vertices are listed in the order determined by a topological distance
    // transform.  Boundary vertices have 'distance' 0.  Any vertices that are
    // not boundary vertices but are edge-adjacent to boundary vertices have
    // 'distance' 1.  Neighbors of those have distance '2', and so on.  The
    // mOrderedVertices array stores distance-0 vertices first, distance-1
    // vertices second, and so on.
    std::vector<int> mOrderedVertices;

    std::shared_ptr<UVComputeModel> mCModel;

#if defined(WIN32)
    // Support for solving the sparse linear system on the GPU.
    void SolveSystemGPU(unsigned int numIterations);
    std::shared_ptr<ComputeShader> mSolveSystem;
    std::shared_ptr<ConstantBuffer> mBoundBuffer;
    std::shared_ptr<StructuredBuffer> mVGBuffer;
    std::shared_ptr<StructuredBuffer> mVGDBuffer;
    std::shared_ptr<StructuredBuffer> mOVBuffer;
    std::shared_ptr<StructuredBuffer> mTCoordsBuffer[2];
#endif
};

#include "GteGenerateMeshUV.inl"

}
