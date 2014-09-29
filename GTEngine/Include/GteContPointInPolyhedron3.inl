// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
PointInPolyhedron3<Real>::PointInPolyhedron3(int numPoints,
    Vector3<Real> const* points, int numFaces, TriangleFace const* faces,
    int numRays, Vector3<Real> const* directions)
    :
    mNumPoints(numPoints),
    mPoints(points),
    mNumFaces(numFaces),
    mTFaces(faces),
    mCFaces(nullptr),
    mSFaces(nullptr),
    mMethod(0),
    mNumRays(numRays),
    mDirections(directions)
{
}
//----------------------------------------------------------------------------
template <typename Real>
PointInPolyhedron3<Real>::PointInPolyhedron3(int numPoints,
    Vector3<Real> const* points, int numFaces, ConvexFace const* faces,
    int numRays, Vector3<Real> const* directions, unsigned int method)
    :
    mNumPoints(numPoints),
    mPoints(points),
    mNumFaces(numFaces),
    mTFaces(nullptr),
    mCFaces(faces),
    mSFaces(nullptr),
    mMethod(method),
    mNumRays(numRays),
    mDirections(directions)
{
}
//----------------------------------------------------------------------------
template <typename Real>
PointInPolyhedron3<Real>::PointInPolyhedron3(int numPoints,
    Vector3<Real> const* points, int numFaces, SimpleFace const* faces,
    int numRays, Vector3<Real> const* directions, unsigned int method)
    :
    mNumPoints(numPoints),
    mPoints(points),
    mNumFaces(numFaces),
    mTFaces(nullptr),
    mCFaces(nullptr),
    mSFaces(faces),
    mMethod(method),
    mNumRays(numRays),
    mDirections(directions)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolyhedron3<Real>::Contains(Vector3<Real> const& p) const
{
    if (mTFaces)
    {
        return ContainsT0(p);
    }

    if (mCFaces)
    {
        if (mMethod == 0)
        {
            return ContainsC0(p);
        }

        return ContainsC1C2(p, mMethod);
    }

    if (mSFaces)
    {
        if (mMethod == 0)
        {
            return ContainsS0(p);
        }

        if (mMethod == 1)
        {
            return ContainsS1(p);
        }
    }

    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolyhedron3<Real>::FastNoIntersect(Ray3<Real> const& ray,
    Plane3<Real> const& plane)
{
    Real planeDistance = Dot(plane.normal, ray.origin) - plane.constant;
    Real planeAngle = Dot(plane.normal, ray.direction);

    if (planeDistance < (Real)0)
    {
        // The ray origin is on the negative side of the plane.
        if (planeAngle <= (Real)0)
        {
            // The ray points away from the plane.
            return true;
        }
    }

    if (planeDistance > (Real)0)
    {
        // The ray origin is on the positive side of the plane.
        if (planeAngle >= (Real)0)
        {
            // The ray points away from the plane.
            return true;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolyhedron3<Real>::ContainsT0(Vector3<Real> const& p) const
{
    int insideCount = 0;

    TIQuery<Real, Ray3<Real>, Triangle3<Real>> rtQuery;
    Triangle3<Real> triangle;
    Ray3<Real> ray;
    ray.origin = p;

    for (int j = 0; j < mNumRays; ++j)
    {
        ray.direction = mDirections[j];

        // Zero intersections to start with.
        bool odd = false;

        TriangleFace const* face = mTFaces;
        for (int i = 0; i < mNumFaces; ++i, ++face)
        {
            // Attempt to quickly cull the triangle.
            if (FastNoIntersect(ray, face->plane))
            {
                continue;
            }

            // Get the triangle vertices.
            for (int k = 0; k < 3; ++k)
            {
                triangle.v[k] = mPoints[face->indices[k]];
            }

            // Test for intersection.
            if (rtQuery(ray, triangle).intersect)
            {
                // The ray intersects the triangle.
                odd = !odd;
            }
        }

        if (odd)
        {
            insideCount++;
        }
    }

    return insideCount > mNumRays/2;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolyhedron3<Real>::ContainsC0(Vector3<Real> const& p) const
{
    int insideCount = 0;

    TIQuery<Real, Ray3<Real>, Triangle3<Real>> rtQuery;
    Triangle3<Real> triangle;
    Ray3<Real> ray;
    ray.origin = p;

    for (int j = 0; j < mNumRays; ++j)
    {
        ray.direction = mDirections[j];

        // Zero intersections to start with.
        bool odd = false;

        ConvexFace const* face = mCFaces;
        for (int i = 0; i < mNumFaces; ++i, ++face)
        {
            // Attempt to quickly cull the triangle.
            if (FastNoIntersect(ray, face->plane))
            {
                continue;
            }

            // Process the triangles in a trifan of the face.
            size_t numVerticesM1 = face->indices.size() - 1;
            triangle.v[0] = mPoints[face->indices[0]];
            for (size_t k = 1; k < numVerticesM1; ++k)
            {
                triangle.v[1] = mPoints[face->indices[k]];
                triangle.v[2] = mPoints[face->indices[k + 1]];

                if (rtQuery(ray, triangle).intersect)
                {
                    // The ray intersects the triangle.
                    odd = !odd;
                }
            }
        }

        if (odd)
        {
            insideCount++;
        }
    }

    return insideCount > mNumRays/2;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolyhedron3<Real>::ContainsS0(Vector3<Real> const& p) const
{
    int insideCount = 0;

    TIQuery<Real, Ray3<Real>, Triangle3<Real>> rtQuery;
    Triangle3<Real> triangle;
    Ray3<Real> ray;
    ray.origin = p;

    for (int j = 0; j < mNumRays; ++j)
    {
        ray.direction = mDirections[j];

        // Zero intersections to start with.
        bool odd = false;

        SimpleFace const* face = mSFaces;
        for (int i = 0; i < mNumFaces; ++i, ++face)
        {
            // Attempt to quickly cull the triangle.
            if (FastNoIntersect(ray, face->plane))
            {
                continue;
            }

            // The triangulation must exist to use it.
            size_t numTriangles = face->triangles.size()/3;
            LogAssert(numTriangles > 0, "Triangulation must exist.");

            // Process the triangles in a triangulation of the face.
            int const* currIndex = &face->triangles[0];
            for (size_t t = 0; t < numTriangles; ++t)
            {
                // Get the triangle vertices.
                for (int k = 0; k < 3; ++k)
                {
                    triangle.v[k] = mPoints[*currIndex++];
                }

                // Test for intersection.
                if (rtQuery(ray, triangle).intersect)
                {
                    // The ray intersects the triangle.
                    odd = !odd;
                }
            }
        }

        if (odd)
        {
            insideCount++;
        }
    }

    return insideCount > mNumRays/2;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolyhedron3<Real>::ContainsC1C2(Vector3<Real> const& p,
    unsigned int method) const
{
    int insideCount = 0;

    FIQuery<Real, Ray3<Real>, Plane3<Real>> rpQuery;
    Ray3<Real> ray;
    ray.origin = p;

    for (int j = 0; j < mNumRays; ++j)
    {
        ray.direction = mDirections[j];

        // Zero intersections to start with.
        bool odd = false;

        ConvexFace const* face = mCFaces;
        for (int i = 0; i < mNumFaces; ++i, ++face)
        {
            // Attempt to quickly cull the triangle.
            if (FastNoIntersect(ray, face->plane))
            {
                continue;
            }

            // Compute the ray-plane intersection.
            auto result = rpQuery(ray, face->plane);

            // If you trigger this assertion, numerical round-off errors have
            // led to a discrepancy between FastNoIntersect and the Find()
            // result.
            LogAssert(result.intersect, "Unexpected condition.");

            // Get a coordinate system for the plane.  Use vertex 0 as the
            // origin.
            Vector3<Real> const& V0 = mPoints[face->indices[0]];
            Vector3<Real> basis[3];
            basis[0] = face->plane.normal;
            ComputeOrthogonalComplement(1, basis);

            // Project the intersection onto the plane.
            Vector3<Real> diff = result.point - V0;
            Vector2<Real> projIntersect(
                Dot(basis[1], diff), Dot(basis[2], diff));

            // Project the face vertices onto the plane of the face.
            if (face->indices.size() > mProjVertices.size())
            {
                mProjVertices.resize(face->indices.size());
            }

            // Project the remaining vertices.  Vertex 0 is always the origin.
            size_t numIndices = face->indices.size();
            mProjVertices[0] = Vector2<Real>::Zero();
            for (size_t k = 1; k < numIndices; ++k)
            {
                diff = mPoints[face->indices[k]] - V0;
                mProjVertices[k][0] = Dot(basis[1], diff);
                mProjVertices[k][1] = Dot(basis[2], diff);
            }

            // Test whether the intersection point is in the convex polygon.
            PointInPolygon2<Real> PIP(static_cast<int>(mProjVertices.size()),
                &mProjVertices[0]);

            if (method == 1)
            {
                if (PIP.ContainsConvexOrderN(projIntersect))
                {
                    // The ray intersects the triangle.
                    odd = !odd;
                }
            }
            else
            {
                if (PIP.ContainsConvexOrderLogN(projIntersect))
                {
                    // The ray intersects the triangle.
                    odd = !odd;
                }
            }
        }

        if (odd)
        {
            insideCount++;
        }
    }

    return insideCount > mNumRays/2;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolyhedron3<Real>::ContainsS1(Vector3<Real> const& p) const
{
    int insideCount = 0;

    FIQuery<Real, Ray3<Real>, Plane3<Real>> rpQuery;
    Ray3<Real> ray;
    ray.origin = p;

    for (int j = 0; j < mNumRays; ++j)
    {
        ray.direction = mDirections[j];

        // Zero intersections to start with.
        bool odd = false;

        SimpleFace const* face = mSFaces;
        for (int i = 0; i < mNumFaces; ++i, ++face)
        {
            // Attempt to quickly cull the triangle.
            if (FastNoIntersect(ray, face->plane))
            {
                continue;
            }

            // Compute the ray-plane intersection.
            auto result = rpQuery(ray, face->plane);

            // If you trigger this assertion, numerical round-off errors have
            // led to a discrepancy between FastNoIntersect and the Find()
            // result.
            LogAssert(result.intersect, "Unexpected condition.");

            // Get a coordinate system for the plane.  Use vertex 0 as the
            // origin.
            Vector3<Real> const& V0 = mPoints[face->indices[0]];
            Vector3<Real> basis[3];
            basis[0] = face->plane.normal;
            ComputeOrthogonalComplement(1, basis);

            // Project the intersection onto the plane.
            Vector3<Real> diff = result.point - V0;
            Vector2<Real> projIntersect(
                Dot(basis[1], diff), Dot(basis[2], diff));

            // Project the face vertices onto the plane of the face.
            if (face->indices.size() > mProjVertices.size())
            {
                mProjVertices.resize(face->indices.size());
            }

            // Project the remaining vertices.  Vertex 0 is always the origin.
            size_t numIndices = face->indices.size();
            mProjVertices[0] = Vector2<Real>::Zero();
            for (size_t k = 1; k < numIndices; ++k)
            {
                diff = mPoints[face->indices[k]] - V0;
                mProjVertices[k][0] = Dot(basis[1], diff);
                mProjVertices[k][1] = Dot(basis[2], diff);
            }

            // Test whether the intersection point is in the convex polygon.
            PointInPolygon2<Real> PIP(static_cast<int>(mProjVertices.size()),
                &mProjVertices[0]);

            if (PIP.Contains(projIntersect))
            {
                // The ray intersects the triangle.
                odd = !odd;
            }
        }

        if (odd)
        {
            insideCount++;
        }
    }

    return insideCount > mNumRays/2;
}
//----------------------------------------------------------------------------
