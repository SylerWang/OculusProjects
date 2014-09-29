// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteContPointInPolygon2.h"
#include "GteIntrRay3Plane3.h"
#include "GteIntrRay3Triangle3.h"
#include "GteLogger.h"
#include <vector>

// This class contains various implementations for point-in-polyhedron
// queries.  The planes stored with the faces are used in all cases to
// reject ray-face intersection tests, a quick culling operation.
//
// The algorithm is to cast a ray from the input point P and test for
// intersection against each face of the polyhedron.  If the ray only
// intersects faces at interior points (not vertices, not edge points),
// then the point is inside when the number of intersections is odd and
// the point is outside when the number of intersections is even.  If the
// ray intersects an edge or a vertex, then the counting must be handled
// differently.  The details are tedious.  As an alternative, the approach
// here is to allow you to specify 2*N+1 rays, where N >= 0.  You should
// choose these rays randomly.  Each ray reports "inside" or "outside".
// Whichever result occurs N+1 or more times is the "winner".  The input
// rayQuantity is 2*N+1.  The input array Direction must have rayQuantity
// elements.  If you are feeling lucky, choose rayQuantity to be 1.

namespace gte
{

template <typename Real>
class PointInPolyhedron3
{
public:
    // For simple polyhedra with triangle faces.
    class TriangleFace
    {
    public:
        // When you view the face from outside, the vertices are
        // counterclockwise ordered.  The Indices array stores the indices
        // into the vertex array.
        int indices[3];

        // The normal vector is unit length and points to the outside of the
        // polyhedron.
        Plane3<Real> plane;
    };

    // The Contains query will use ray-triangle intersection queries.
    PointInPolyhedron3(int numPoints, Vector3<Real> const* points,
        int numFaces, TriangleFace const* faces, int numRays,
        Vector3<Real> const* directions);

    // For simple polyhedra with convex polygon faces.
    class ConvexFace
    {
    public:
        // When you view the face from outside, the vertices are
        // counterclockwise ordered.  The Indices array stores the indices
        // into the vertex array.
        std::vector<int> indices;

        // The normal vector is unit length and points to the outside of the
        // polyhedron.
        Plane3<Real> plane;
    };

    // The Contains query will use ray-convexpolygon intersection queries.  A
    // ray-convexpolygon intersection query can be implemented in many ways.
    // In this context, uiMethod is one of three value:
    //   0 : Use a triangle fan and perform a ray-triangle intersection query
    //       for each triangle.
    //   1 : Find the point of intersection of ray and plane of polygon.  Test
    //       whether that point is inside the convex polygon using an O(N)
    //       test.
    //   2 : Find the point of intersection of ray and plane of polygon.  Test
    //       whether that point is inside the convex polygon using an O(log N)
    //       test.
    PointInPolyhedron3(int numPoints, Vector3<Real> const* points,
        int numFaces, ConvexFace const* faces, int numRays,
        Vector3<Real> const* directions, unsigned int method);

    // For simple polyhedra with simple polygon faces that are generally
    // not all convex.
    class SimpleFace
    {
    public:
        // When you view the face from outside, the vertices are
        // counterclockwise ordered.  The Indices array stores the indices
        // into the vertex array.
        std::vector<int> indices;

        // The normal vector is unit length and points to the outside of the
        // polyhedron.
        Plane3<Real> plane;

        // Each simple face may be triangulated.  The indices are relative to
        // the vertex array.  Each triple of indices represents a triangle in
        // the triangulation.
        std::vector<int> triangles;
    };

    // The Contains query will use ray-simplepolygon intersection queries.  A
    // ray-simplepolygon intersection query can be implemented in a couple of
    // ways.  In this context, uiMethod is one of two value:
    //   0 : Iterate over the triangles of each face and perform a
    //       ray-triangle intersection query for each triangle.  This requires
    //       that the SimpleFace::Triangles array be initialized for each
    //       face.
    //   1 : Find the point of intersection of ray and plane of polygon.  Test
    //       whether that point is inside the polygon using an O(N) test.  The
    //       SimpleFace::Triangles array is not used for this method, so it
    //       does not have to be initialized for each face.
    PointInPolyhedron3(int numPoints, Vector3<Real> const* points,
        int numFaces, SimpleFace const* faces, int numRays,
        Vector3<Real> const* directions, unsigned intmethod);

    // This function will select the actual algorithm based on which
    // constructor you used for this class.
    bool Contains(Vector3<Real> const& p) const;

private:
    // For all types of faces.  The ray origin is the test point.  The ray
    // direction is one of those passed to the constructors.  The plane origin
    // is a point on the plane of the face.  The plane normal is a unit-length
    // normal to the face and that points outside the polyhedron.
    static bool FastNoIntersect(Ray3<Real> const& ray,
        Plane3<Real> const& plane);

    // For triangle faces.
    bool ContainsT0(Vector3<Real> const& p) const;

    // For convex faces.
    bool ContainsC0(Vector3<Real> const& p) const;
    bool ContainsC1C2(Vector3<Real> const& p, unsigned int method) const;

    // For simple faces.
    bool ContainsS0(Vector3<Real> const& p) const;
    bool ContainsS1(Vector3<Real> const& p) const;

    int mNumPoints;
    Vector3<Real> const* mPoints;

    int mNumFaces;
    TriangleFace const* mTFaces;
    ConvexFace const* mCFaces;
    SimpleFace const* mSFaces;

    unsigned int mMethod;
    int mNumRays;
    Vector3<Real> const* mDirections;

    // Temporary storage for those methods that reduce the problem to 2D
    // point-in-polygon queries.  The array stores the projections of
    // face vertices onto the plane of the face.  It is resized as needed.
    mutable std::vector<Vector2<Real>> mProjVertices;
};

#include "GteContPointInPolyhedron3.inl"

}
