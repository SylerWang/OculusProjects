// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/03)

#pragma once

#include "GTEngineDEF.h"
#include "GteEdgeKey.h"
#include "GteTriangleKey.h"
#include <map>

namespace gte
{

class GTE_IMPEXP ETManifoldMesh
{
public:
    // Edge data types.
    class Edge;
    typedef Edge* (*ECreator)(int, int);
    typedef std::map<EdgeKey<false>, Edge*> EMap;

    // Triangle data types.
    class Triangle;
    typedef Triangle* (*TCreator)(int, int, int);
    typedef std::map<TriangleKey<true>, Triangle*> TMap;

    // Edge object.
    class GTE_IMPEXP Edge
    {
    public:
        virtual ~Edge();
        Edge(int v0, int v1);

        // Vertices of the edge.
        int V[2];

        // Triangles sharing the edge.
        Triangle* T[2];
    };

    // Triangle object.
    class GTE_IMPEXP Triangle
    {
    public:
        virtual ~Triangle();
        Triangle(int v0, int v1, int v2);

        // Vertices, listed in counterclockwise order (V[0],V[1],V[2]).
        int V[3];

        // Adjacent edges.  E[i] points to edge (V[i],V[(i+1)%3]).
        Edge* E[3];

        // Adjacent triangles.  T[i] points to the adjacent triangle
        // sharing edge E[i].
        Triangle* T[3];
    };


    // Construction and destruction.
    virtual ~ETManifoldMesh();
    ETManifoldMesh(ECreator eCreator = nullptr, TCreator tCreator = nullptr);

    // Member access.
    EMap const& GetEdges() const;
    TMap const& GetTriangles() const;

    // If the insertion of a triangle fails because the mesh would become
    // nonmanifold, the default behavior is to trigger a LogError message.
    // You can disable this behavior in situations where you want the Logger
    // system on but you want to continue gracefully without an assertion.
    void AssertOnNonmanifoldInsertion(bool doAssert);

    // If <v0,v1,v2> is not in the mesh, a Triangle object is created and
    // returned; otherwise, <v0,v1,v2> is in the mesh and nullptr is returned.
    // If the insertion leads to a nonmanifold mesh, the call fails with a
    // nullptr returned.
    Triangle* Insert(int v0, int v1, int v2);

    // If <v0,v1,v2> is in the mesh, it is removed and 'true' is returned;
    // otherwise, <v0,v1,v2> is not in the mesh and 'false' is returned.
    bool Remove(int v0, int v1, int v2);

    // A manifold mesh is closed if each edge is shared twice.
    bool IsClosed() const;

    // For debugging.  The function returns 'true' iff the text file has been
    // created and saved.
    bool Print(std::string const& filename);

protected:
    // The edge data and default edge creation.
    static Edge* CreateEdge(int v0, int v1);
    ECreator mECreator;
    EMap mEMap;

    // The triangle data and default triangle creation.
    static Triangle* CreateTriangle(int v0, int v1, int v2);
    TCreator mTCreator;
    TMap mTMap;
    bool mAssertOnNonmanifoldInsertion;  // default: true
};

}
