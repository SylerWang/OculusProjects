// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/17)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
Delaunay3<InputType, ComputeType>::Delaunay3()
    :
    mEpsilon((InputType)0),
    mDimension(0),
    mLine(Vector3<InputType>::Zero(), Vector3<InputType>::Zero()),
    mPlane(Vector3<InputType>::Zero(), (InputType)0),
    mNumVertices(0),
    mNumUniqueVertices(0),
    mNumTetrahedra(0),
    mVertices(nullptr)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay3<InputType, ComputeType>::operator()(int numVertices,
    Vector3<InputType> const* vertices, InputType epsilon)
{
    mEpsilon = std::max(epsilon, (InputType)0);
    mDimension = 0;
    mLine.origin = Vector3<InputType>::Zero();
    mLine.direction = Vector3<InputType>::Zero();
    mPlane.normal = Vector3<InputType>::Zero();
    mPlane.constant = (InputType)0;
    mNumVertices = numVertices;
    mNumUniqueVertices = 0;
    mNumTetrahedra = 0;
    mVertices = vertices;
    mGraph = TSManifoldMesh();
    mIndices.clear();
    mAdjacencies.clear();

    int i, j;
    if (mNumVertices < 4)
    {
        // Delaunay3 should be called with at least four points.
        return false;
    }

    IntrinsicsVector3<InputType> info(mNumVertices, vertices, mEpsilon);
    if (info.dimension == 0)
    {
        // mDimension is 0; mGraph, mIndices, and mAdjacencies are empty
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
    mComputeVertices.resize(mNumVertices);
    mQuery.Set(mNumVertices, &mComputeVertices[0]);
    for (i = 0; i < mNumVertices; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            mComputeVertices[i][j] = vertices[i][j];
        }
    }

    // Insert the (nondegenerate) tetrahedron constructed by the call to
    // GetInformation. This is necessary for the circumsphere-visibility
    // algorithm to work correctly.
    if (!info.extremeCCW)
    {
        std::swap(info.extreme[2], info.extreme[3]);
    }
    mGraph.Insert(info.extreme[0], info.extreme[1], info.extreme[2],
        info.extreme[3]);

    // Incrementally update the tetrahedralization.  The set of processed
    // points is maintained to eliminate duplicates, either in the original
    // input points or in the points obtained by snap rounding.
    std::set<Vector3<InputType>> processed;
    for (i = 0; i < 4; ++i)
    {
        processed.insert(vertices[info.extreme[i]]);
    }
    for (i = 0; i < mNumVertices; ++i)
    {
        if (processed.find(vertices[i]) == processed.end())
        {
            Update(i);
            processed.insert(vertices[i]);
        }
    }
    mNumUniqueVertices = static_cast<int>(processed.size());

    // Assign integer values to the tetrahedra for use by the caller.
    std::map<Tetrahedron*, int> permute;
    i = -1;
    permute[nullptr] = i++;
    for (auto const& element : mGraph.GetTetrahedra())
    {
        permute[element.second] = i++;
    }

    // Put Delaunay tetrahedra into an array (vertices and adjacency info).
    mNumTetrahedra = static_cast<int>(mGraph.GetTetrahedra().size());
    int numIndices = 4 * mNumTetrahedra;
    if (mNumTetrahedra > 0)
    {
        mIndices.resize(numIndices);
        mAdjacencies.resize(numIndices);
        i = 0;
        for (auto const& element : mGraph.GetTetrahedra())
        {
            Tetrahedron const* tetra = element.second;
            for (j = 0; j < 4; ++j, ++i)
            {
                mIndices[i] = tetra->V[j];
                mAdjacencies[i] = permute[tetra->S[j]];
            }
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
InputType Delaunay3<InputType, ComputeType>::GetEpsilon() const
{
    return mEpsilon;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay3<InputType, ComputeType>::GetDimension() const
{
    return mDimension;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Line3<InputType> const& Delaunay3<InputType, ComputeType>::GetLine() const
{
    return mLine;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Plane3<InputType> const& Delaunay3<InputType, ComputeType>::GetPlane() const
{
    return mPlane;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay3<InputType, ComputeType>::GetNumVertices() const
{
    return mNumVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay3<InputType, ComputeType>::GetNumUniqueVertices() const
{
    return mNumUniqueVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int Delaunay3<InputType, ComputeType>::GetNumTetrahedra() const
{
    return mNumTetrahedra;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector3<InputType> const* Delaunay3<InputType, ComputeType>::GetVertices()
    const
{
    return mVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
PrimalQuery3<ComputeType> const&
Delaunay3<InputType, ComputeType>::GetQuery() const
{
    return mQuery;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
TSManifoldMesh const& Delaunay3<InputType, ComputeType>::GetGraph() const
{
    return mGraph;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& Delaunay3<InputType, ComputeType>::GetIndices() const
{
    return mIndices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& Delaunay3<InputType, ComputeType>::GetAdjacencies()
    const
{
    return mAdjacencies;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay3<InputType, ComputeType>::GetHull(std::vector<int>& hull) const
{
    if (mDimension == 3)
    {
        // Count the number of triangles that are not shared by two
        // tetrahedra.
        int numTriangles = 0;
        for (auto adj : mAdjacencies)
        {
            if (adj == -1)
            {
                ++numTriangles;
            }
        }

        if (numTriangles > 0)
        {
            // Enumerate the triangles.  The prototypical case is the single
            // tetrahedron V[0] = (0,0,0), V[1] = (1,0,0), V[2] = (0,1,0), and
            // V[3] = (0,0,1) with no adjacent tetrahedra.  The mIndices[]
            // array is <0,1,2,3>.
            //   i = 0, face = 0:
            //     skip index 0, <x,1,2,3>, no swap, triangle = <1,2,3>
            //   i = 1, face = 1:
            //     skip index 1, <0,x,2,3>, swap,    triangle = <0,3,2>
            //   i = 2, face = 2:
            //     skip index 2, <0,1,x,3>, no swap, triangle = <0,1,3>
            //   i = 3, face = 3:
            //     skip index 3, <0,1,2,x>, swap,    triangle = <0,2,1>
            // To guarantee counterclockwise order of triangles when viewed
            // outside the tetrahedron, the swap of the last two indices
            // occurs when face is an odd number; (face % 2) != 0.
            hull.resize(3 * numTriangles);
            int current = 0, i = 0;
            for (auto adj : mAdjacencies)
            {
                if (adj == -1)
                {
                    int tetra = i / 4, face = i % 4;
                    for (int j = 0; j < 4; ++j)
                    {
                        if (j != face)
                        {
                            hull[current++] = mIndices[4 * tetra + j];
                        }
                    }
                    if ((face % 2) != 0)
                    {
                        std::swap(hull[current - 1], hull[current - 2]);
                    }
                }
                ++i;
            }
            return true;
        }
        else
        {
            LogError("Unexpected.  There must be at least one tetrahedron.");
        }
    }
    else
    {
        LogError("The dimension must be 3.");
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay3<InputType, ComputeType>::GetIndices(int i,
    std::array<int, 4>& indices) const
{
    if (mDimension == 3)
    {
        int numTetrahedra = static_cast<int>(mIndices.size() / 4);
        if (0 <= i && i < numTetrahedra)
        {
            indices[0] = mIndices[4 * i];
            indices[1] = mIndices[4 * i + 1];
            indices[2] = mIndices[4 * i + 2];
            indices[3] = mIndices[4 * i + 3];
            return true;
        }
    }
    else
    {
        LogError("The dimension must be 3.");
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay3<InputType, ComputeType>::GetAdjacencies(int i,
    std::array<int, 4>& adjacencies) const
{
    if (mDimension == 3)
    {
        int numTetrahedra = static_cast<int>(mIndices.size() / 4);
        if (0 <= i && i < numTetrahedra)
        {
            adjacencies[0] = mAdjacencies[4 * i];
            adjacencies[1] = mAdjacencies[4 * i + 1];
            adjacencies[2] = mAdjacencies[4 * i + 2];
            adjacencies[3] = mAdjacencies[4 * i + 3];
            return true;
        }
    }
    else
    {
        LogError("The dimension must be 3.");
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
int Delaunay3<InputType, ComputeType>::GetContainingTetrahedron(
    Vector3<InputType> const& p, SearchInfo& info) const
{
    if (mDimension == 3)
    {
        Vector3<ComputeType> test(p[0], p[1], p[2]);

        int numTetrahedra = static_cast<int>(mIndices.size() / 4);
        info.path.resize(numTetrahedra);
        info.numPath = 0;
        int tetrahedron;
        if (0 <= info.initialTetrahedron
            && info.initialTetrahedron < numTetrahedra)
        {
            tetrahedron = info.initialTetrahedron;
        }
        else
        {
            info.initialTetrahedron = 0;
            tetrahedron = 0;
        }

        // Use tetrahedron faces as binary separating planes.
        for (int i = 0; i < numTetrahedra; ++i)
        {
            int ibase = 4 * tetrahedron;
            int const* v = &mIndices[ibase];

            info.path[info.numPath++] = tetrahedron;
            info.finalTetrahedron = tetrahedron;
            info.finalV[0] = v[0];
            info.finalV[1] = v[1];
            info.finalV[2] = v[2];
            info.finalV[3] = v[3];

            // <V1,V2,V3> counterclockwise when viewed outside tetrahedron.
            if (mQuery.ToPlane(test, v[1], v[2], v[3]) > 0)
            {
                tetrahedron = mAdjacencies[ibase];
                if (tetrahedron == -1)
                {
                    info.finalV[0] = v[1];
                    info.finalV[1] = v[2];
                    info.finalV[2] = v[3];
                    info.finalV[3] = v[0];
                    return -1;
                }
                continue;
            }

            // <V0,V3,V2> counterclockwise when viewed outside tetrahedron.
            if (mQuery.ToPlane(test, v[0], v[2], v[3]) < 0)
            {
                tetrahedron = mAdjacencies[ibase + 1];
                if (tetrahedron == -1)
                {
                    info.finalV[0] = v[0];
                    info.finalV[1] = v[2];
                    info.finalV[2] = v[3];
                    info.finalV[3] = v[1];
                    return -1;
                }
                continue;
            }

            // <V0,V1,V3> counterclockwise when viewed outside tetrahedron.
            if (mQuery.ToPlane(test, v[0], v[1], v[3]) > 0)
            {
                tetrahedron = mAdjacencies[ibase + 2];
                if (tetrahedron == -1)
                {
                    info.finalV[0] = v[0];
                    info.finalV[1] = v[1];
                    info.finalV[2] = v[3];
                    info.finalV[3] = v[2];
                    return -1;
                }
                continue;
            }

            // <V0,V2,V1> counterclockwise when viewed outside tetrahedron.
            if (mQuery.ToPlane(test, v[0], v[1], v[2]) < 0)
            {
                tetrahedron = mAdjacencies[ibase + 3];
                if (tetrahedron == -1)
                {
                    info.finalV[0] = v[0];
                    info.finalV[1] = v[1];
                    info.finalV[2] = v[2];
                    info.finalV[3] = v[3];
                    return -1;
                }
                continue;
            }

            return tetrahedron;
        }
    }
    else
    {
        LogError("The dimension must be 3.");
    }
    return -1;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool Delaunay3<InputType, ComputeType>::GetContainingTetrahedron(int i,
    Tetrahedron*& tetra) const
{
    int numTetrahedra = static_cast<int>(mGraph.GetTetrahedra().size());
    for (int t = 0; t < numTetrahedra; ++t)
    {
        int j;
        for (j = 0; j < 4; ++j)
        {
            auto const& opposite = TetrahedronKey<true>::oppositeFace;
            int v0 = tetra->V[opposite[j][0]];
            int v1 = tetra->V[opposite[j][1]];
            int v2 = tetra->V[opposite[j][2]];
            if (mQuery.ToPlane(i, v0, v1, v2) > 0)
            {
                // Point i sees face <v0,v1,v2> from outside the tetrahedron.
                if (tetra->S[j])
                {
                    // Traverse to the tetrahedron sharing the face.
                    tetra = tetra->S[j];
                    break;
                }
                else
                {
                    // We reached a hull face, so the point is outside the
                    // hull.  TODO:  Once a hull data structure is in place,
                    // return tetra->S[j] as the candidate for starting a
                    // search for visible hull faces.
                    return false;
                }
            }

        }

        if (j == 4)
        {
            // The point is inside all four faces, so the point is inside
            // a tetrahedron.
            return true;
        }
    }

    LogError("Unexpected termination of GetContainingTetrahedron.");
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void Delaunay3<InputType, ComputeType>::GetAndRemoveInsertionPolyhedron(int i,
    std::set<Tetrahedron*>& candidates, std::set<TriangleKey<true>>& boundary)
{
    // Locate the tetrahedra that make up the insertion polyhedron.
    TSManifoldMesh polyhedron;
    while (candidates.size() > 0)
    {
        Tetrahedron* tetra = *candidates.begin();
        candidates.erase(candidates.begin());

        for (int j = 0; j < 4; ++j)
        {
            Tetrahedron* adj = tetra->S[j];
            if (adj && candidates.find(adj) == candidates.end())
            {
                int a0 = adj->V[0];
                int a1 = adj->V[1];
                int a2 = adj->V[2];
                int a3 = adj->V[3];
                if (mQuery.ToCircumsphere(i, a0, a1, a2, a3) <= 0)
                {
                    // Point i is in the circumsphere.
                    candidates.insert(adj);
                }
            }
        }

        int v0 = tetra->V[0];
        int v1 = tetra->V[1];
        int v2 = tetra->V[2];
        int v3 = tetra->V[3];
        polyhedron.Insert(v0, v1, v2, v3);
        mGraph.Remove(v0, v1, v2, v3);
    }

    // Get the boundary triangles of the insertion polyhedron.
	for (auto const& element : polyhedron.GetTetrahedra())
    {
        Tetrahedron const* tetra = element.second;
        for (int j = 0; j < 4; ++j)
        {
            if (!tetra->S[j])
            {
                auto const& opposite = TetrahedronKey<true>::oppositeFace;
                int v0 = tetra->V[opposite[j][0]];
                int v1 = tetra->V[opposite[j][1]];
                int v2 = tetra->V[opposite[j][2]];
                boundary.insert(TriangleKey<true>(v0, v1, v2));
            }
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void Delaunay3<InputType, ComputeType>::Update(int i)
{
    auto const& smap = mGraph.GetTetrahedra();
    Tetrahedron* tetra = smap.begin()->second;
    if (GetContainingTetrahedron(i, tetra))
    {
        // The point is inside the convex hull.  The insertion polyhedron
        // contains only tetrahedra in the current tetrahedralization; the
        // hull does not change.

        // Use a depth-first search for those tetrahedra whose circumspheres
        // contain point i.
        std::set<Tetrahedron*> candidates;
        candidates.insert(tetra);

        // Get the boundary of the insertion polyhedron C that contains the
        // tetrahedra whose circumspheres contain point i.  C contains the
        // point i.
        std::set<TriangleKey<true>> boundary;
        GetAndRemoveInsertionPolyhedron(i, candidates, boundary);

        // The insertion polyhedron consists of the tetrahedra formed by
        // point i and the faces of C.
        for (auto const& key : boundary)
        {
            int v0 = key.V[0];
            int v1 = key.V[1];
            int v2 = key.V[2];
            if (mQuery.ToPlane(i, v0, v1, v2) < 0)
            {
                mGraph.Insert(i, v0, v1, v2);
            }
            // else:  Point i is on an edge or face of 'tetra', so the
            // subdivision has degenerate tetrahedra.  Ignore these.
        }
    }
    else
    {
        // The point is outside the convex hull.  The insertion polyhedron
        // is formed by point i and any tetrahedra in the current
        // tetrahedralization whose circumspheres contain point i.

        // Locate the convex hull of the tetrahedra.  TODO:  Maintain a hull
        // data structure that is updated incrementally.
        std::set<TriangleKey<true>> hull;
        for (auto const& element : smap)
        {
            Tetrahedron const* tetra = element.second;
            for (int j = 0; j < 4; ++j)
            {
                if (!tetra->S[j])
                {
                    auto const& opposite = TetrahedronKey<true>::oppositeFace;
                    int v0 = tetra->V[opposite[j][0]];
                    int v1 = tetra->V[opposite[j][1]];
                    int v2 = tetra->V[opposite[j][2]];
                    hull.insert(TriangleKey<true>(v0, v1, v2));
                }
            }
        }

        // TODO:  Until the hull change, for now just iterate over all the
        // hull faces and use the ones visible to point i to locate the
        // insertion polyhedron.
        auto const& tmap = mGraph.GetTriangles();
        std::set<Tetrahedron*> candidates;
        std::set<TriangleKey<true>> visible;
        for (auto const& key : hull)
        {
            int v0 = key.V[0];
            int v1 = key.V[1];
            int v2 = key.V[2];
            if (mQuery.ToPlane(i, v0, v1, v2) > 0)
            {
                auto iter = tmap.find(TriangleKey<false>(v0, v1, v2));
                LogAssert(iter != tmap.end(),
                    "Unexpected condition.");
                LogAssert(iter->second->T[1] == nullptr,
                    "Unexpected condition.");
                Tetrahedron* adj = iter->second->T[0];
                if (adj && candidates.find(adj) == candidates.end())
                {
                    int a0 = adj->V[0];
                    int a1 = adj->V[1];
                    int a2 = adj->V[2];
                    int a3 = adj->V[3];
                    if (mQuery.ToCircumsphere(i, a0, a1, a2, a3) <= 0)
                    {
                        // Point i is in the circumsphere.
                        candidates.insert(adj);
                    }
                    else
                    {
                        // Point i is not in the circumsphere but the hull
                        // face is visible.
                        visible.insert(key);
                    }
                }
            }
        }

        // Get the boundary of the insertion subpolyhedron C that contains the
        // tetrahedra whose circumspheres contain point i.
        std::set<TriangleKey<true>> boundary;
        GetAndRemoveInsertionPolyhedron(i, candidates, boundary);

        // The insertion polyhedron P consists of the tetrahedra formed by
        // point i and the back faces of C *and* the visible faces of
        // mGraph-C.
        for (auto const& key : boundary)
        {
            int v0 = key.V[0];
            int v1 = key.V[1];
            int v2 = key.V[2];
            if (mQuery.ToPlane(i, v0, v1, v2) < 0)
            {
                // This is a back face of the boundary.
                mGraph.Insert(i, v0, v1, v2);
            }
        }
        for (auto const& key : visible)
        {
            mGraph.Insert(i, key.V[0], key.V[2], key.V[1]);
        }
    }
}
//----------------------------------------------------------------------------
