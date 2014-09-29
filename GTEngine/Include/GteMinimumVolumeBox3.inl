// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
MinimumVolumeBox3<InputType, ComputeType>::MinimumVolumeBox3()
    :
    mNumPoints(0),
    mPoints(nullptr)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool MinimumVolumeBox3<InputType, ComputeType>::operator()(int numPoints,
    Vector3<InputType> const* points, InputType epsilon,
    OrientedBox3<InputType>& minBox)
{
    mNumPoints = numPoints;
    mPoints = points;
    mHull.clear();
    mUniqueIndices.clear();

    // Get the convex hull of the points.
    ConvexHull3<InputType, ComputeType> ch3;
    ch3(mNumPoints, mPoints, epsilon);
    int dimension = ch3.GetDimension();

    if (dimension == 0)
    {
        // The points are all effectively the same (using fuzzy epsilon).
        minBox.center = mPoints[0];
        minBox.axis[0] = Vector3<InputType>::Basis0();
        minBox.axis[1] = Vector3<InputType>::Basis1();
        minBox.axis[2] = Vector3<InputType>::Basis2();
        minBox.extent[0] = (InputType)0;
        minBox.extent[1] = (InputType)0;
        minBox.extent[2] = (InputType)0;
        mHull.resize(1);
        mHull[0] = 0;
        return true;
    }

    if (dimension == 1)
    {
        // The points effectively lie on a line (using fuzzy epsilon).
        // Determine the extreme t-values for the points represented as
        // P = origin + t*direction.  We know that 'origin' is an input
        // vertex, so we can start both t-extremes at zero.
        Line3<InputType> const& line = ch3.GetLine();
        InputType tmin = (InputType)0, tmax = (InputType)0;
        int imin = 0, imax = 0;
        for (int i = 0; i < mNumPoints; ++i)
        {
            Vector3<InputType> diff = mPoints[i] - line.origin;
            InputType t = Dot(diff, line.direction);
            if (t > tmax)
            {
                tmax = t;
                imax = i;
            }
            else if (t < tmin)
            {
                tmin = t;
                imin = i;
            }
        }

        minBox.center = line.origin +
            ((InputType)0.5)*(tmin + tmax) * line.direction;
        minBox.extent[0] = ((InputType)0.5)*(tmax - tmin);
        minBox.extent[1] = (InputType)0;
        minBox.extent[2] = (InputType)0;
        minBox.axis[0] = line.direction;
        ComputeOrthogonalComplement(1, minBox.axis);
        mHull.resize(2);
        mHull[0] = imin;
        mHull[1] = imax;
        return true;
    }

    if (dimension == 2)
    {
        // The points effectively line on a plane (using fuzzy epsilon).
        // Project the points onto the plane and compute the minimum-area
        // bounding box of them.
        Plane3<InputType> const& plane = ch3.GetPlane();

        // Get a coordinate system relative to the plane of the points.
        // Choose the origin to be any of the input points.
        Vector3<InputType> origin = mPoints[0];
        Vector3<InputType> basis[3];
        basis[0] = plane.normal;
        ComputeOrthogonalComplement(1, basis);

        // Project the input points onto the plane.
        std::vector<Vector2<InputType>> projection(mNumPoints);
        for (int i = 0; i < mNumPoints; ++i)
        {
            Vector3<InputType> diff = mPoints[i] - origin;
            projection[i][0] = Dot(basis[1], diff);
            projection[i][1] = Dot(basis[2], diff);
        }

        // Compute the minimum area box in 2D.
        OrientedBox2<InputType> box2;
        MinimumAreaBox2<InputType, ComputeType> mab2;
        mab2(mNumPoints, &projection[0], epsilon, box2);

        // Lift the values into 3D.
        minBox.center =
            origin + box2.center[0] * basis[1] + box2.center[1] * basis[2];
        minBox.axis[0] =
            box2.axis[0][0] * basis[1] + box2.axis[0][1] * basis[2];
        minBox.axis[1] =
            box2.axis[1][0] * basis[1] + box2.axis[1][1] * basis[2];
        minBox.axis[2] = basis[0];
        minBox.extent[0] = box2.extent[0];
        minBox.extent[1] = box2.extent[1];
        minBox.extent[2] = (InputType)0;
        mHull = mab2.GetHull();
        return true;
    }

    // Get the set of unique indices of the hull.  This is used to project
    // hull vertices onto lines.
    ETManifoldMesh const& mesh = ch3.GetHullMesh();
    mHull.resize(3 * mesh.GetTriangles().size());
    int h = 0;
    for (auto const& element : mesh.GetTriangles())
    {
        for (int i = 0; i < 3; ++i, ++h)
        {
            int index = element.first.V[i];
            mHull[h] = index;
            mUniqueIndices.insert(index);
        }
    }

    ComputeBox(mesh, ch3.GetQuery().GetVertices(), minBox);
    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool MinimumVolumeBox3<InputType, ComputeType>::operator()(int numPoints,
    Vector3<InputType> const* points, int numIndices, int const* indices,
    OrientedBox3<InputType>& minBox)
{
    mNumPoints = numPoints;
    mPoints = points;
    mUniqueIndices.clear();

    // Build the mesh from the indices.  The box construction uses the
    // edge map of the mesh.
    ETManifoldMesh mesh;
    int numTriangles = 3 * numIndices;
    for (int t = 0; t < numTriangles; ++t)
    {
        int v0 = *indices++;
        int v1 = *indices++;
        int v2 = *indices++;
        mesh.Insert(v0, v1, v2);
    }

    // Get the set of unique indices of the hull.  This is used to project
    // hull vertices onto lines.
    mHull.resize(3 * mesh.GetTriangles().size());
    int h = 0;
    for (auto const& element : mesh.GetTriangles())
    {
        for (int i = 0; i < 3; ++i, ++h)
        {
            int index = element.first.V[i];
            mHull[h] = index;
            mUniqueIndices.insert(index);
        }
    }

    // Create the ComputeType points to be used downstream.
    std::vector<Vector3<ComputeType>> computePoints(mNumPoints);
    for (int i = 0; i < mNumPoints; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            computePoints[i][j] = (ComputeType)mPoints[i][j];
        }
    }

    ComputeBox(mesh, &computePoints[0], minBox);
    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int MinimumVolumeBox3<InputType, ComputeType>::GetNumPoints() const
{
    return mNumPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector3<InputType> const*
MinimumVolumeBox3<InputType, ComputeType>::GetPoints() const
{
    return mPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& MinimumVolumeBox3<InputType, ComputeType>::GetHull()
    const
{
    return mHull;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ComputeBox(
    ETManifoldMesh const& mesh, Vector3<ComputeType> const* computePoints,
    OrientedBox3<InputType>& itMinBox)
{
    Box minBox;
    minBox.volume = (InputType)std::numeric_limits<InputType>::max();
    ProcessFaces(mesh, computePoints, minBox);
    ProcessEdges(mesh, computePoints, minBox);
    Convert(minBox, itMinBox);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ProcessFaces(
    ETManifoldMesh const& mesh, Vector3<ComputeType> const* computePoints,
    Box& minBox)
{
    // Compute inner-pointing face normals for searching boxes supported by
    // a face and an extreme vertex.  The indirection in triNormalMap, using
    // an integer index instead of the normal/sqrlength pair itself, avoids
    // expensive copies when using exact arithmetic.
    auto const& tmap = mesh.GetTriangles();
    std::vector<Vector3<ComputeType>> normal(tmap.size());
    std::map<ETManifoldMesh::Triangle const*, int> triNormalMap;
    int index = 0;
    for (auto const& element : tmap)
    {
        auto const* tri = element.second;
        Vector3<ComputeType> const& v0 = computePoints[tri->V[0]];
        Vector3<ComputeType> const& v1 = computePoints[tri->V[1]];
        Vector3<ComputeType> const& v2 = computePoints[tri->V[2]];
        Vector3<ComputeType> edge1 = v1 - v0;
        Vector3<ComputeType> edge2 = v2 - v0;
        normal[index] = Cross(edge2, edge1);  // inner-pointing normal
        triNormalMap[tri] = index++;
    }

    // Process the triangle faces.  For each face, compute the polyline of
    // edges that supports the bounding box with face coincident with the
    // triangle face.  The projection of the polyline onto the plane of the
    // triangle face is a convex polygon, so we can use the method of rotating
    // calipers to compute its minimum-area box efficiently.
    ComputeType const zero = (ComputeType)0;
    std::vector<int> polyline(mNumPoints), closedPolyline(mNumPoints);
    int polylineStart = -1;
    std::vector<Vector2<InputType>> projection;
    projection.reserve(mNumPoints);

    auto const& emap = mesh.GetEdges();
    for (auto const& triElement : tmap)
    {
        // Get the supporting triangle information.
        auto const* supportTri = triElement.second;
        auto const& supportNormal = normal[triNormalMap[supportTri]];

        // Build the polyline of supporting edges.  The pair (v,polyline[v])
        // represents an edge directed appropriately (see next set of
        // comments).
        for (auto const& edgeElement : emap)
        {
            auto const& edge = *edgeElement.second;
            auto const* tri0 = edge.T[0];
            auto const* tri1 = edge.T[1];
            auto const& normal0 = normal[triNormalMap[tri0]];
            auto const& normal1 = normal[triNormalMap[tri1]];
            ComputeType dot0 = Dot(supportNormal, normal0);
            ComputeType dot1 = Dot(supportNormal, normal1);

            ETManifoldMesh::Triangle const* tri = nullptr;
            if (dot0 > zero && dot1 <= zero)
            {
                tri = tri0;
            }
            else if (dot1 > zero && dot0 <= zero)
            {
                tri = tri1;
            }

            if (tri)
            {
                // The edge supports the bounding box.  Insert the edge in the
                // list using clockwise order relative to tri.  This will lead
                // to a polygon of projection onto the plane of supportTri
                // that is counterclockwise oriented.
                for (int j0 = 2, j1 = 0; j1 < 3; j0 = j1++)
                {
                    if (tri->V[j1] == edge.V[0])
                    {
                        if (tri->V[j0] == edge.V[1])
                        {
                            polyline[edge.V[0]] = edge.V[1];
                        }
                        else
                        {
                            polyline[edge.V[1]] = edge.V[0];
                        }
                        polylineStart = edge.V[0];
                        break;
                    }
                }
            }
        }

        // Rearrange the edges to form a closed polyline.
        int numClosedPolyline = 0;
        int v = polylineStart;
        for (auto& cp : closedPolyline)
        {
            cp = v;
            ++numClosedPolyline;
            v = polyline[v];
            if (v == polylineStart)
            {
                break;
            }
        }

        // Project the polyline onto the support plane.  The plane origin is
        // chosen to be a point on the support triangle.
        Vector3<InputType> const& origin = mPoints[supportTri->V[0]];
        Vector3<InputType> basis[3];
        for (int j = 0; j < 3; ++j)
        {
            basis[0][j] = (InputType)supportNormal[j];
        }
        ComputeOrthogonalComplement(1, basis);

        projection.clear();
        for (int i = 0; i < numClosedPolyline; ++i)
        {
            Vector3<InputType> diff = mPoints[closedPolyline[i]] - origin;
            projection.emplace_back(Dot(basis[1], diff), Dot(basis[2], diff));
        }

        //std::ofstream output("projection.raw", std::ios::out | std::ios::binary);
        //output.write((char const*)&projection[0], projection.size()*2*sizeof(ComputeType));
        //output.close();

        // Compute the minimum-area box of the projection.
        auto box2 =
            MinimumAreaBox2<InputType, InputType>::ComputeBox(projection);

        // Compute the maximum height above the supporting plane.
        InputType maxHeight = (InputType)0;
        int maxHeightIndex = supportTri->V[0];
        for (auto i : mUniqueIndices)
        {
            Vector3<InputType> diff = mPoints[i] - origin;
            InputType height = Dot(basis[0], diff);
            if (height > maxHeight)
            {
                maxHeight = height;
                maxHeightIndex = i;
            }
        }

        // Compare squared volumes to support exact arithmetic.
        InputType volume = maxHeight * box2.area;
        if (volume < minBox.volume)
        {
            Normalize(box2.U[0]);
            Normalize(box2.U[1]);
            minBox.U[0] = box2.U[0][0] * basis[1] + box2.U[0][1] * basis[2];
            minBox.U[1] = box2.U[1][0] * basis[1] + box2.U[1][1] * basis[2];
            minBox.U[2] = basis[0];
            minBox.index[0] = closedPolyline[box2.index[3]];    // min U0
            minBox.index[1] = closedPolyline[box2.index[1]];    // max U0
            minBox.index[2] = closedPolyline[box2.index[0]];    // min U1
            minBox.index[3] = closedPolyline[box2.index[2]];    // max U1
            minBox.index[4] = supportTri->V[0]; // min U2
            minBox.index[5] = maxHeightIndex;   // max U2
            minBox.volume = volume;
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::ProcessEdges(
    ETManifoldMesh const& mesh, Vector3<ComputeType> const* computePoints,
    Box& minBox)
{
    // The minimum-volume box can also be supported by three mutually
    // orthogonal edges of the convex hull.  For each triple of orthogonal
    // edges, compute the minimum-volume box for that coordinate frame by
    // projecting the points onto the axes of the frame.  Use a hull vertex
    // as the origin.
    int index = mesh.GetTriangles().begin()->first.V[0];
    Vector3<InputType> origin = mPoints[index];
    Vector3<ComputeType> U[3];
    std::array<ComputeType, 3> sqrLenU;
    ComputeType const zero = (ComputeType)0;

    auto const& emap = mesh.GetEdges();
    auto e2 = emap.begin(), end = emap.end();
    for (/**/; e2 != end; ++e2)
    {
        U[2] =
            computePoints[e2->first.V[1]] -
            computePoints[e2->first.V[0]];
        sqrLenU[2] = Dot(U[2], U[2]);

        auto e1 = e2;
        for (++e1; e1 != end; ++e1)
        {
            U[1] =
                computePoints[e1->first.V[1]] -
                computePoints[e1->first.V[0]];
            sqrLenU[1] = Dot(U[1], U[1]);
            if (Dot(U[1], U[2]) != zero)
            {
                continue;
            }

            auto e0 = e1;
            for (++e0; e0 != end; ++e0)
            {
                U[0] =
                    computePoints[e0->first.V[1]] -
                    computePoints[e0->first.V[0]];
                sqrLenU[0] = Dot(U[0], U[0]);
                if (Dot(U[0], U[1]) != zero || Dot(U[0], U[2]) != zero)
                {
                    continue;
                }

                // The three edges are mutually orthogonal.  Project the
                // vertices onto the lines containing the edges.  Use vertex 0
                // as the origin.
                Vector3<InputType> itU[3];
                for (int j = 0; j < 3; ++j)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        itU[j][k] = (InputType)U[j][k];
                    }
                    Normalize(itU[j]);
                }

                std::array<InputType, 3> umin, umax;
                std::array<int, 3> imin, imax;
                for (int j = 0; j < 3; ++j)
                {
                    umin[j] = (InputType)0;
                    umax[j] = (InputType)0;
                    imin[j] = -1;
                    imax[j] = -1;
                }

                for (auto i : mUniqueIndices)
                {
                    Vector3<InputType> diff = mPoints[i] - origin;
                    for (int j = 0; j < 3; ++j)
                    {
                        InputType dot = Dot(itU[j], diff);
                        if (dot < umin[j])
                        {
                            umin[j] = dot;
                            imin[j] = i;
                        }
                        else if (dot > umax[j])
                        {
                            umax[j] = dot;
                            imax[j] = i;
                        }
                    }
                }

                InputType range[3];
                for (int j = 0; j < 3; ++j)
                {
                    range[j] = umax[j] - umin[j];
                }

                InputType volume = range[0] * range[1] * range[2];

                // Update current minimum-volume box (if necessary).
                if (volume < minBox.volume)
                {
                    minBox.U[0] = itU[0];
                    minBox.U[1] = itU[1];
                    minBox.U[2] = itU[2];
                    minBox.index[0] = imin[0];
                    minBox.index[1] = imax[0];
                    minBox.index[2] = imin[1];
                    minBox.index[3] = imax[1];
                    minBox.index[4] = imin[2];
                    minBox.index[5] = imax[2];
                    minBox.volume = volume;
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
void MinimumVolumeBox3<InputType, ComputeType>::Convert(Box const& minBox,
    OrientedBox3<InputType>& itMinBox)
{
    InputType const half = (InputType)0.5;
    std::array<Vector3<InputType>, 3> tmp;

    tmp[0] = mPoints[minBox.index[1]] + mPoints[minBox.index[0]];
    tmp[1] = mPoints[minBox.index[3]] + mPoints[minBox.index[2]];
    tmp[2] = mPoints[minBox.index[5]] + mPoints[minBox.index[4]];
    itMinBox.center =
        (half * Dot(minBox.U[0], tmp[0])) * minBox.U[0] +
        (half * Dot(minBox.U[1], tmp[1])) * minBox.U[1] +
        (half * Dot(minBox.U[2], tmp[2])) * minBox.U[2];

    tmp[0] = mPoints[minBox.index[1]] - mPoints[minBox.index[0]];
    tmp[1] = mPoints[minBox.index[3]] - mPoints[minBox.index[2]];
    tmp[2] = mPoints[minBox.index[5]] - mPoints[minBox.index[4]];
    for (int i = 0; i < 3; ++i)
    {
        itMinBox.axis[i] = minBox.U[i];
        itMinBox.extent[i] = half * Dot(minBox.U[i], tmp[i]);
    }
}
//----------------------------------------------------------------------------
