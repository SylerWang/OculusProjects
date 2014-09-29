// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
ConvexHull3<InputType, ComputeType>::ConvexHull3()
    :
    mEpsilon((InputType)0),
    mDimension(0),
    mLine(Vector3<InputType>::Zero(), Vector3<InputType>::Zero()),
    mPlane(Vector3<InputType>::Zero(), (InputType)0),
    mNumPoints(0),
    mNumUniquePoints(0),
    mPoints(nullptr)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool ConvexHull3<InputType, ComputeType>::operator()(int numPoints,
    Vector3<InputType> const* points, InputType epsilon)
{
    mEpsilon = std::max(epsilon, (InputType)0);
    mDimension = 0;
    mLine.origin = Vector3<InputType>::Zero();
    mLine.direction = Vector3<InputType>::Zero();
    mPlane.normal = Vector3<InputType>::Zero();
    mPlane.constant = (InputType)0;
    mNumPoints = numPoints;
    mNumUniquePoints = 0;
    mPoints = points;
    mHullUnordered.clear();
    mHullMesh = ETManifoldMesh();

    int i, j;
    if (mNumPoints < 4)
    {
        // ConvexHull3 should be called with at least four points.
        return false;
    }

    IntrinsicsVector3<InputType> info(mNumPoints, mPoints, mEpsilon);
    if (info.dimension == 0)
    {
        // The set is (nearly) a point.
        return false;
    }

    if (info.dimension == 1)
    {
        // The set is (nearly) collinear.
        mDimension = 1;
        mLine = Line3<InputType>(info.origin, info.direction[0]);
        return false;
    }

    if (info.dimension == 2)
    {
        // The set is (nearly) coplanar.
        mDimension = 2;
        mPlane = Plane3<InputType>(UnitCross(info.direction[0],
            info.direction[1]), info.origin);
        return false;
    }

    mDimension = 3;

    // Compute the vertices for the queries.
    mComputePoints.resize(mNumPoints);
    mQuery.Set(mNumPoints, &mComputePoints[0]);
    for (i = 0; i < mNumPoints; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            mComputePoints[i][j] = points[i][j];
        }
    }

    // Insert the faces of the (nondegenerate) tetrahedron constructed by the
    // call to GetInformation.
    if (!info.extremeCCW)
    {
        std::swap(info.extreme[2], info.extreme[3]);
    }

    mHullUnordered.push_back(TriangleKey<true>(info.extreme[1],
        info.extreme[2], info.extreme[3]));
    mHullUnordered.push_back(TriangleKey<true>(info.extreme[0],
        info.extreme[3], info.extreme[2]));
    mHullUnordered.push_back(TriangleKey<true>(info.extreme[0],
        info.extreme[1], info.extreme[3]));
    mHullUnordered.push_back(TriangleKey<true>(info.extreme[0],
        info.extreme[2], info.extreme[1]));

    // Incrementally update the hull.  The set of processed points is
    // maintained to eliminate duplicates, either in the original input
    // points or in the points obtained by snap rounding.
    std::set<Vector3<InputType>> processed;
    for (i = 0; i < 4; ++i)
    {
        processed.insert(points[info.extreme[i]]);
    }
    for (i = 0; i < mNumPoints; ++i)
    {
        if (processed.find(points[i]) == processed.end())
        {
            Update(i);
            processed.insert(points[i]);
        }
    }
    mNumUniquePoints = static_cast<int>(processed.size());
    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
InputType ConvexHull3<InputType, ComputeType>::GetEpsilon() const
{
    return mEpsilon;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int ConvexHull3<InputType, ComputeType>::GetDimension() const
{
    return mDimension;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Line3<InputType> const& ConvexHull3<InputType, ComputeType>::GetLine() const
{
    return mLine;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Plane3<InputType> const& ConvexHull3<InputType, ComputeType>::GetPlane() const
{
    return mPlane;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int ConvexHull3<InputType, ComputeType>::GetNumPoints() const
{
    return mNumPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int ConvexHull3<InputType, ComputeType>::GetNumUniquePoints() const
{
    return mNumUniquePoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector3<InputType> const* ConvexHull3<InputType, ComputeType>::GetPoints()
    const
{
    return mPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
PrimalQuery3<ComputeType> const&
ConvexHull3<InputType, ComputeType>::GetQuery() const
{
    return mQuery;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<TriangleKey<true>> const&
ConvexHull3<InputType, ComputeType>::GetHullUnordered() const
{
    return mHullUnordered;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
ETManifoldMesh const& ConvexHull3<InputType, ComputeType>::GetHullMesh()
    const
{
    // Create the mesh only on demand.
    if (mHullMesh.GetTriangles().size() == 0)
    {
        for (auto const& tri : mHullUnordered)
        {
            mHullMesh.Insert(tri.V[0], tri.V[1], tri.V[2]);
        }
    }

    return mHullMesh;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void ConvexHull3<InputType, ComputeType>::Update(int i)
{
    // The terminator that separates visible faces from nonvisible faces is
    // constructed by this code.  Visible faces for the incoming hull are
    // removed, and the boundary of that set of triangles is the terminator.
    // New visible faces are added using the incoming point and the edges of
    // the terminator.
    //
    // A simple algorithm for computing terminator edges is the following.
    // Back-facing triangles are located and the three edges are processed.
    // The first time an edge is visited, insert it into the terminator.  If
    // it is visited a second time, the edge is removed because it is shared
    // by another back-facing triangle and, therefore, cannot be a terminator
    // edge.  After visiting all back-facing triangles, the only remaining
    // edges in the map are the terminator edges.
    //
    // The order of vertices of an edge is important for adding new faces with
    // the correct vertex winding.  However, the edge "toggle" (insert edge,
    // remove edge) should use edges with unordered vertices, because the
    // edge shared by one triangle has opposite ordering relative to that of
    // the other triangle.  The map uses unordered edges as the keys but
    // stores the ordered edge as the value.  This avoids having to look up
    // an edge twice in a map with ordered edge keys.
    std::map<EdgeKey<false>, std::pair<int, int>> terminator;

    std::vector<TriangleKey<true>> backFaces;
    bool existsFrontFacingTriangle = false;
    for (auto const& tri : mHullUnordered)
    {
        if (mQuery.ToPlane(i, tri.V[0], tri.V[1], tri.V[2]) <= 0)
        {
            // The triangle is back facing.  These include triangles that
            // are coplanar with the incoming point.
            backFaces.push_back(tri);

            // The current hull is a 2-manifold watertight mesh.  The
            // terminator edges are those shared with a front-facing triangle.
            // The first time an edge of a back-facing triangle is visited,
            // insert it into the terminator.  If it is visited a second time,
            // the edge is removed because it is shared by another back-facing
            // triangle.  After all back-facing triangles are visited, the
            // only remaining edges are shared by a single back-facing
            // triangle, which makes them terminator edges.
            for (int j0 = 2, j1 = 0; j1 < 3; j0 = j1++)
            {
                int v0 = tri.V[j0], v1 = tri.V[j1];
                EdgeKey<false> edge(v0, v1);
                auto iter = terminator.find(edge);
                if (iter == terminator.end())
                {
                    // The edge is visited for the first time.
                    terminator.insert(std::make_pair(edge,
                        std::make_pair(v0, v1)));
                }
                else
                {
                    // The edge is visited for the second time.
                    terminator.erase(edge);
                }
            }
        }
        else
        {
            // If there are no strictly front-facing triangles, then the
            // incoming point is inside or on the convex hull.  If we get
            // to this code, then the point is truly outside and we can
            // update the hull.
            existsFrontFacingTriangle = true;
        }
    }

    if (!existsFrontFacingTriangle)
    {
        // The incoming point is inside or on the current hull, so no
        // update of the hull is necessary.
        return;
    }

    // The updated hull contains the triangles not visible to the incoming
    // point.
    mHullUnordered = backFaces;

    // Insert the triangles formed by the incoming point and the terminator
    // edges.
    for (auto const& edge : terminator)
    {
        mHullUnordered.push_back(TriangleKey<true>(i, edge.second.second,
            edge.second.first));
    }
}
//----------------------------------------------------------------------------
