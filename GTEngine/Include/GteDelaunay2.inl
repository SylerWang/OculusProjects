// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/17)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
Delaunay2<InputType, ComputeType>::~Delaunay2()
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
Delaunay2<InputType, ComputeType>::Delaunay2()
    :
    mEpsilon((InputType)0),
    mDimension(0),
    mLine(Vector2<InputType>::Zero(), Vector2<InputType>::Zero()),
    mNumVertices(0),
    mNumUniqueVertices(0),
    mNumTriangles(0),
    mVertices(nullptr)
{
    // INVESTIGATE.  If the initialization of mIndex is placed in the
    // constructor initializer list, MSVS 2012 generates an internal
    // compiler error.
    mIndex = {{ { 0, 1 }, { 1, 2 }, { 2, 0 } }};
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay2<InputType, ComputeType>::operator()(int numVertices,
    Vector2<InputType> const* vertices, InputType epsilon)
{
    mEpsilon = std::max(epsilon, (InputType)0);
    mDimension = 0;
    mLine.origin = Vector2<InputType>::Zero();
    mLine.direction = Vector2<InputType>::Zero();
    mNumVertices = numVertices;
    mNumUniqueVertices = 0;
    mNumTriangles = 0;
    mVertices = vertices;
    mGraph = ETManifoldMesh();
    mIndices.clear();
    mAdjacencies.clear();
    mDuplicates.resize(std::max(numVertices, 3));

    int i, j;
    if (mNumVertices < 3)
    {
        // Delaunay2 should be called with at least three points.
        return false;
    }

    IntrinsicsVector2<InputType> info(mNumVertices, vertices, mEpsilon);
    if (info.dimension == 0)
    {
        // mDimension is 0; mGraph, mIndices, and mAdjacencies are empty
        return false;
    }

    if (info.dimension == 1)
    {
        // The set is (nearly) collinear.
        mDimension = 1;
        mLine = Line2<InputType>(info.origin, info.direction[0]);
        return false;
    }

    mDimension = 2;

    // Compute the vertices for the queries.
    mComputeVertices.resize(mNumVertices);
    mQuery.Set(mNumVertices, &mComputeVertices[0]);
    for (i = 0; i < mNumVertices; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            mComputeVertices[i][j] = vertices[i][j];
        }
    }

    // Insert the (nondegenerate) triangle constructed by the call to
    // GetInformation.  This is necessary for the circumcircle-visibility
    // algorithm to work correctly.
    if (!info.extremeCCW)
    {
        std::swap(info.extreme[1], info.extreme[2]);
    }
    mGraph.Insert(info.extreme[0], info.extreme[1], info.extreme[2]);

    // Incrementally update the triangulation.  The set of processed points
    // is maintained to eliminate duplicates, either in the original input
    // points or in the points obtained by snap rounding.
    std::set<ProcessedVertex> processed;
    for (i = 0; i < 3; ++i)
    {
        int j = info.extreme[i];
        processed.insert(ProcessedVertex(vertices[j], j));
        mDuplicates[j] = j;
    }
    for (i = 0; i < mNumVertices; ++i)
    {
        ProcessedVertex v(vertices[i], i);
        auto iter = processed.find(v);
        if (iter == processed.end())
        {
            Update(i);
            processed.insert(v);
            mDuplicates[i] = i;
        }
        else
        {
            mDuplicates[i] = iter->location;
        }
    }
    mNumUniqueVertices = static_cast<int>(processed.size());

    // Assign integer values to the triangles for use by the caller.
    std::map<Triangle*, int> permute;
    i = -1;
    permute[nullptr] = i++;
    for (auto const& element : mGraph.GetTriangles())
    {
        permute[element.second] = i++;
    }

    // Put Delaunay triangles into an array (vertices and adjacency info).
    mNumTriangles = static_cast<int>(mGraph.GetTriangles().size());
    int numindices = 3 * mNumTriangles;
    if (numindices > 0)
    {
        mIndices.resize(numindices);
        mAdjacencies.resize(numindices);
        i = 0;
        for (auto const& element : mGraph.GetTriangles())
        {
            Triangle const* tri = element.second;
            for (j = 0; j < 3; ++j, ++i)
            {
                mIndices[i] = tri->V[j];
                mAdjacencies[i] = permute[tri->T[j]];
            }
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
InputType Delaunay2<InputType, ComputeType>::GetEpsilon() const
{
    return mEpsilon;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay2<InputType, ComputeType>::GetDimension() const
{
    return mDimension;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Line2<InputType> const& Delaunay2<InputType, ComputeType>::GetLine() const
{
    return mLine;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay2<InputType, ComputeType>::GetNumVertices() const
{
    return mNumVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay2<InputType, ComputeType>::GetNumUniqueVertices() const
{
    return mNumUniqueVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay2<InputType, ComputeType>::GetNumTriangles() const
{
    return mNumTriangles;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector2<InputType> const* Delaunay2<InputType, ComputeType>::GetVertices()
    const
{
    return mVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
PrimalQuery2<ComputeType> const&
Delaunay2<InputType, ComputeType>::GetQuery() const
{
    return mQuery;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
ETManifoldMesh const& Delaunay2<InputType, ComputeType>::GetGraph() const
{
    return mGraph;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& Delaunay2<InputType, ComputeType>::GetIndices() const
{
    return mIndices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& Delaunay2<InputType, ComputeType>::GetAdjacencies()
    const
{
    return mAdjacencies;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& Delaunay2<InputType, ComputeType>::GetDuplicates()
    const
{
    return mDuplicates;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay2<InputType, ComputeType>::GetHull(std::vector<int>& hull) const
{
    if (mDimension == 2)
    {
        // Count the number of edges that are not shared by two triangles.
        int numEdges = 0;
        for (auto adj : mAdjacencies)
        {
            if (adj == -1)
            {
                ++numEdges;
            }
        }

        if (numEdges > 0)
        {
            // Enumerate the edges.
            hull.resize(2 * numEdges);
            int current = 0, i = 0;
            for (auto adj : mAdjacencies)
            {
                if (adj == -1)
                {
                    int tri = i / 3, j = i % 3;
                    hull[current++] = mIndices[3 * tri + j];
                    hull[current++] = mIndices[3 * tri + ((j + 1) % 3)];
                }
                ++i;
            }
            return true;
        }
        else
        {
            LogError("Unexpected.  There must be at least one triangle.");
        }
    }
    else
    {
        LogError("The dimension must be 2.");
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay2<InputType, ComputeType>::GetIndices(int i,
    std::array<int, 3>& indices) const
{
    if (mDimension == 2)
    {
        int numTriangles = static_cast<int>(mIndices.size() / 3);
        if (0 <= i && i < numTriangles)
        {
            indices[0] = mIndices[3 * i];
            indices[1] = mIndices[3 * i + 1];
            indices[2] = mIndices[3 * i + 2];
            return true;
        }
    }
    else
    {
        LogError("The dimension must be 2.");
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay2<InputType, ComputeType>::GetAdjacencies(int i,
    std::array<int, 3>& adjacencies) const
{
    if (mDimension == 2)
    {
        int numTriangles = static_cast<int>(mIndices.size() / 3);
        if (0 <= i && i < numTriangles)
        {
            adjacencies[0] = mAdjacencies[3 * i];
            adjacencies[1] = mAdjacencies[3 * i + 1];
            adjacencies[2] = mAdjacencies[3 * i + 2];
            return true;
        }
    }
    else
    {
        LogError("The dimension must be 2.");
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
int Delaunay2<InputType, ComputeType>::GetContainingTriangle(
    Vector2<InputType> const& p, SearchInfo& info) const
{
    if (mDimension == 2)
    {
        Vector2<ComputeType> test(p[0], p[1]);

        int numTriangles = static_cast<int>(mIndices.size() / 3);
        info.path.resize(numTriangles);
        info.numPath = 0;
        int triangle;
        if (0 <= info.initialTriangle && info.initialTriangle < numTriangles)
        {
            triangle = info.initialTriangle;
        }
        else
        {
            info.initialTriangle = 0;
            triangle = 0;
        }

        // Use triangle edges as binary separating lines.
        for (int i = 0; i < numTriangles; ++i)
        {
            int ibase = 3 * triangle;
            int const* v = &mIndices[ibase];

            info.path[info.numPath++] = triangle;
            info.finalTriangle = triangle;
            info.finalV[0] = v[0];
            info.finalV[1] = v[1];
            info.finalV[2] = v[2];

            if (mQuery.ToLine(test, v[0], v[1]) > 0)
            {
                triangle = mAdjacencies[ibase];
                if (triangle == -1)
                {
                    info.finalV[0] = v[0];
                    info.finalV[1] = v[1];
                    info.finalV[2] = v[2];
                    return -1;
                }
                continue;
            }

            if (mQuery.ToLine(test, v[1], v[2]) > 0)
            {
                triangle = mAdjacencies[ibase + 1];
                if (triangle == -1)
                {
                    info.finalV[0] = v[1];
                    info.finalV[1] = v[2];
                    info.finalV[2] = v[0];
                    return -1;
                }
                continue;
            }

            if (mQuery.ToLine(test, v[2], v[0]) > 0)
            {
                triangle = mAdjacencies[ibase + 2];
                if (triangle == -1)
                {
                    info.finalV[0] = v[2];
                    info.finalV[1] = v[0];
                    info.finalV[2] = v[1];
                    return -1;
                }
                continue;
            }

            return triangle;
        }
    }
    else
    {
        LogError("The dimension must be 2.");
    }
    return -1;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay2<InputType, ComputeType>::GetContainingTriangle(int i,
    Triangle*& tri) const
{
    int numTriangles = static_cast<int>(mGraph.GetTriangles().size());
    for (int t = 0; t < numTriangles; ++t)
    {
        int j;
        for (j = 0; j < 3; ++j)
        {
            int v0 = tri->V[mIndex[j][0]];
            int v1 = tri->V[mIndex[j][1]];
            if (mQuery.ToLine(i, v0, v1) > 0)
            {
                // Point i sees edge <v0,v1> from outside the triangle.
                if (tri->T[j])
                {
                    // Traverse to the triangle sharing the face.
                    tri = tri->T[j];
                    break;
                }
                else
                {
                    // We reached a hull edge, so the point is outside the
                    // hull.  TODO:  Once a hull data structure is in place,
                    // return tri->T[j] as the candidate for starting a search
                    // for visible hull edges.
                    return false;
                }
            }

        }

        if (j == 3)
        {
            // The point is inside all four edges, so the point is inside
            // a triangle.
            return true;
        }
    }

    LogError("Unexpected termination of GetContainingTriangle.");
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void Delaunay2<InputType, ComputeType>::GetAndRemoveInsertionPolygon(int i,
    std::set<Triangle*>& candidates, std::set<EdgeKey<true>>& boundary)
{
    // Locate the triangles that make up the insertion polygon.
    ETManifoldMesh polygon;
    while (candidates.size() > 0)
    {
        Triangle* tri = *candidates.begin();
        candidates.erase(candidates.begin());

        for (int j = 0; j < 3; ++j)
        {
            Triangle* adj = tri->T[j];
            if (adj && candidates.find(adj) == candidates.end())
            {
                int a0 = adj->V[0];
                int a1 = adj->V[1];
                int a2 = adj->V[2];
                if (mQuery.ToCircumcircle(i, a0, a1, a2) <= 0)
                {
                    // Point i is in the circumcircle.
                    candidates.insert(adj);
                }
            }
        }

        polygon.Insert(tri->V[0], tri->V[1], tri->V[2]);
        mGraph.Remove(tri->V[0], tri->V[1], tri->V[2]);
    }

    // Get the boundary edges of the insertion polygon.
    for (auto const& element : polygon.GetTriangles())
    {
        Triangle const* tri = element.second;
        for (int j = 0; j < 3; ++j)
        {
            if (!tri->T[j])
            {
                boundary.insert(EdgeKey<true>(
                    tri->V[mIndex[j][0]],
                    tri->V[mIndex[j][1]]));
            }
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void Delaunay2<InputType, ComputeType>::Update(int i)
{
    auto const& tmap = mGraph.GetTriangles();
    Triangle* tri = tmap.begin()->second;
    if (GetContainingTriangle(i, tri))
    {
        // The point is inside the convex hull.  The insertion polygon
        // contains only triangles in the current triangulation; the
        // hull does not change.

        // Use a depth-first search for those triangles whose circumcircles
        // contain point i.
        std::set<Triangle*> candidates;
        candidates.insert(tri);

        // Get the boundary of the insertion polygon C that contains the
        // triangles whose circumcircles contain point i.  C contains the
        // point i.
        std::set<EdgeKey<true>> boundary;
        GetAndRemoveInsertionPolygon(i, candidates, boundary);

        // The insertion polygon consists of the triangles formed by
        // point i and the faces of C.
        for (auto const& key : boundary)
        {
            int v0 = key.V[0];
            int v1 = key.V[1];
            if (mQuery.ToLine(i, v0, v1) < 0)
            {
                mGraph.Insert(i, v0, v1);
            }
            // else:  Point i is on an edge of 'tri', so the
            // subdivision has degenerate triangles.  Ignore these.
        }
    }
    else
    {
        // The point is outside the convex hull.  The insertion polygon
        // is formed by point i and any triangles in the current
        // triangulation whose circumcircles contain point i.

        // Locate the convex hull of the triangles.  TODO:  Maintain a hull
        // data structure that is updated incrementally.
        std::set<EdgeKey<true>> hull;
        for (auto const& element : tmap)
        {
            Triangle const* tri = element.second;
            for (int j = 0; j < 3; ++j)
            {
                if (!tri->T[j])
                {
                    hull.insert(EdgeKey<true>(
                        tri->V[mIndex[j][0]],
                        tri->V[mIndex[j][1]]));
                }
            }
        }

        // TODO:  Until the hull change, for now just iterate over all the
        // hull edges and use the ones visible to point i to locate the
        // insertion polygon.
        auto const& emap = mGraph.GetEdges();
        std::set<Triangle*> candidates;
        std::set<EdgeKey<true>> visible;
        for (auto const& key : hull)
        {
            int v0 = key.V[0];
            int v1 = key.V[1];
            if (mQuery.ToLine(i, v0, v1) > 0)
            {
                auto iter = emap.find(EdgeKey<false>(v0, v1));
                LogAssert(iter != emap.end(),
                    "Unexpected condition.");
                LogAssert(iter->second->T[1] == nullptr,
                    "Unexpected condition.");
                Triangle* adj = iter->second->T[0];
                if (adj && candidates.find(adj) == candidates.end())
                {
                    int a0 = adj->V[0];
                    int a1 = adj->V[1];
                    int a2 = adj->V[2];
                    if (mQuery.ToCircumcircle(i, a0, a1, a2) <= 0)
                    {
                        // Point i is in the circumcircle.
                        candidates.insert(adj);
                    }
                    else
                    {
                        // Point i is not in the circumcircle but the hull
                        // edge is visible.
                        visible.insert(key);
                    }
                }
            }
        }

        // Get the boundary of the insertion subpolygon C that contains the
        // triangles whose circumcircles contain point i.
        std::set<EdgeKey<true>> boundary;
        GetAndRemoveInsertionPolygon(i, candidates, boundary);

        // The insertion polygon P consists of the triangles formed by point i
        // and the back edges of C *and* the visible edges of mGraph-C.
        for (auto const& key : boundary)
        {
            int v0 = key.V[0];
            int v1 = key.V[1];
            if (mQuery.ToLine(i, v0, v1) < 0)
            {
                // This is a back edge of the boundary.
                mGraph.Insert(i, v0, v1);
            }
        }
        for (auto const& key : visible)
        {
            mGraph.Insert(i, key.V[1], key.V[0]);
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
Delaunay2<InputType, ComputeType>::ProcessedVertex::ProcessedVertex()
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
Delaunay2<InputType, ComputeType>::ProcessedVertex::ProcessedVertex(
    Vector2<InputType> const& inVertex, int inLocation)
    :
    vertex(inVertex),
    location(inLocation)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay2<InputType, ComputeType>::ProcessedVertex::operator<(
    ProcessedVertex const& v) const
{
    return vertex < v.vertex;
}
//----------------------------------------------------------------------------
