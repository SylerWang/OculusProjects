// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.3.0 (2014/09/11)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
PlanarMesh<InputType, ComputeType, RationalType>::PlanarMesh(int numVertices,
    Vector2<InputType> const* vertices, int numTriangles, int const* indices)
    :
    mNumVertices(0),
    mVertices(nullptr),
    mNumTriangles(0)
{
    if (numVertices < 3 || !vertices || numTriangles < 1 || !indices)
    {
        LogError("Invalid input.");
        return;
    }

    // Create a mesh in order to get adjacency information.
    ETManifoldMesh mesh;
    int const* current = indices;
    for (int t = 0; t < numTriangles; ++t)
    {
        int v0 = *current++;
        int v1 = *current++;
        int v2 = *current++;
        if (!mesh.Insert(v0, v1, v2))
        {
            // The 'mesh' object will assert on nonmanifold inputs.
            return;
        }
    }

    // We have a valid mesh.
    CreateVertices(numVertices, vertices);

    // Build the adjacency graph using the triangle ordering implied by the
    // indices, not the mesh triangle map, to preserve the triangle ordering
    // of the input indices.
    mNumTriangles = numTriangles;
    int const numIndices = 3 * numTriangles;
    mIndices.resize(numIndices);

    std::copy(indices, indices + numIndices, mIndices.begin());
    std::map<TriangleKey<true>, int> triIndexMap;
    for (int t = 0, vIndex = 0; t < numTriangles; ++t)
    {
        int v0 = indices[vIndex++];
        int v1 = indices[vIndex++];
        int v2 = indices[vIndex++];
        TriangleKey<true> key(v0, v1, v2);
        triIndexMap.insert(std::make_pair(key, t));
    }

    mAdjacencies.resize(numIndices);
    auto const& tmap = mesh.GetTriangles();
    for (int t = 0, base = 0; t < numTriangles; ++t, base += 3)
    {
        int v0 = indices[base];
        int v1 = indices[base + 1];
        int v2 = indices[base + 2];
        TriangleKey<true> key(v0, v1, v2);
        auto element = tmap.find(key);
        for (int i = 0; i < 3; ++i)
        {
            auto adj = element->second->T[i];
            if (adj)
            {
                key = TriangleKey<true>(adj->V[0], adj->V[1], adj->V[2]);
                mAdjacencies[base + i] = triIndexMap.find(key)->second;
            }
            else
            {
                mAdjacencies[base + i] = -1;
            }
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
PlanarMesh<InputType, ComputeType, RationalType>::PlanarMesh(int numVertices,
    Vector2<InputType> const* vertices, ETManifoldMesh const& mesh)
    :
    mNumVertices(0),
    mVertices(nullptr),
    mNumTriangles(0)
{
    if (numVertices < 3 || !vertices || mesh.GetTriangles().size() < 1)
    {
        LogError("Invalid input.");
        return;
    }

    // We have a valid mesh.
    CreateVertices(numVertices, vertices);

    // Build the adjacency graph using the triangle ordering implied by the
    // mesh triangle map.
    auto const& tmap = mesh.GetTriangles();
    mNumTriangles = static_cast<int>(tmap.size());
    mIndices.resize(3 * mNumTriangles);

    std::map<TriangleKey<true>, int> triIndexMap;
    int tIndex = 0, vIndex = 0;
    for (auto const& element : tmap)
    {
        triIndexMap.insert(std::make_pair(element.first, tIndex++));
        for (int i = 0; i < 3; ++i, ++vIndex)
        {
            mIndices[vIndex] = element.second->V[i];
        }
    }

    mAdjacencies.resize(3 * mNumTriangles);
    vIndex = 0;
    for (auto const& element : tmap)
    {
        for (int i = 0; i < 3; ++i, ++vIndex)
        {
            auto const* adj = element.second->T[i];
            if (adj)
            {
                TriangleKey<true> key(adj->V[0], adj->V[1], adj->V[2]);
                mAdjacencies[vIndex] = triIndexMap.find(key)->second;
            }
            else
            {
                mAdjacencies[vIndex] = -1;
            }
        }
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
inline int PlanarMesh<InputType, ComputeType, RationalType>::
GetNumVertices() const
{
    return mNumVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
inline int PlanarMesh<InputType, ComputeType, RationalType>::
GetNumTriangles() const
{
    return mNumTriangles;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
inline Vector2<InputType> const*
PlanarMesh<InputType, ComputeType, RationalType>::
GetVertices() const
{
    return mVertices;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
inline int const* PlanarMesh<InputType, ComputeType, RationalType>::
GetIndices() const
{
    return &mIndices[0];
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
inline int const* PlanarMesh<InputType, ComputeType, RationalType>::
GetAdjacencies() const
{
    return &mAdjacencies[0];
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
int PlanarMesh<InputType, ComputeType, RationalType>::
GetContainingTriangle(Vector2<InputType> const& P, int startTriangle) const
{
    Vector2<ComputeType> test(P[0], P[1]);

    // Use triangle edges as binary separating lines.
    int triangle = startTriangle;
    for (int i = 0; i < mNumTriangles; ++i)
    {
        int ibase = 3 * triangle;
        int const* v = &mIndices[ibase];

        if (mQuery.ToLine(test, v[0], v[1]) > 0)
        {
            triangle = mAdjacencies[ibase];
            if (triangle == -1)
            {
                return -1;
            }
            continue;
        }

        if (mQuery.ToLine(test, v[1], v[2]) > 0)
        {
            triangle = mAdjacencies[ibase + 1];
            if (triangle == -1)
            {
                return -1;
            }
            continue;
        }

        if (mQuery.ToLine(test, v[2], v[0]) > 0)
        {
            triangle = mAdjacencies[ibase + 2];
            if (triangle == -1)
            {
                return -1;
            }
            continue;
        }

        return triangle;
    }
    return -1;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
bool PlanarMesh<InputType, ComputeType, RationalType>::
GetVertices(int t, std::array<Vector2<InputType>, 3>& vertices) const
{
    if (0 <= t && t < mNumTriangles)
    {
        for (int i = 0, vIndex = 3 * t; i < 3; ++i, ++vIndex)
        {
            vertices[i] = mVertices[mIndices[vIndex]];
        }
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
bool PlanarMesh<InputType, ComputeType, RationalType>::
GetIndices(int t, std::array<int, 3>& indices) const
{
    if (0 <= t && t < mNumTriangles)
    {
        for (int i = 0, vIndex = 3 * t; i < 3; ++i, ++vIndex)
        {
            indices[i] = mIndices[vIndex];
        }
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
bool PlanarMesh<InputType, ComputeType, RationalType>::
GetAdjacencies(int t, std::array<int, 3>& adjacencies) const
{
    if (0 <= t && t < mNumTriangles)
    {
        for (int i = 0, vIndex = 3 * t; i < 3; ++i, ++vIndex)
        {
            adjacencies[i] = mAdjacencies[vIndex];
        }
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
bool PlanarMesh<InputType, ComputeType, RationalType>::
GetBarycentrics(int t, Vector2<InputType> const& P,
    std::array<InputType, 3>& bary) const
{
    std::array<int, 3> indices;
    if (GetIndices(t, indices))
    {
        Vector2<RationalType> rtP(P[0], P[1]);
        std::array<Vector2<RationalType>, 3> rtV;
        for (int i = 0; i < 3; ++i)
        {
            Vector2<ComputeType> const& V = mComputeVertices[indices[i]];
            for (int j = 0; j < 2; ++j)
            {
                rtV[i][j] = (RationalType)V[j];
            }
        };

        RationalType rtBary[3];
        if (ComputeBarycentrics(rtP, rtV[0], rtV[1], rtV[2], rtBary))
        {
            for (int i = 0; i < 3; ++i)
            {
                bary[i] = (InputType)rtBary[i];
            }
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
void PlanarMesh<InputType, ComputeType, RationalType>::CreateVertices(
    int numVertices, Vector2<InputType> const* vertices)
{
    mNumVertices = numVertices;
    mVertices = vertices;
    mComputeVertices.resize(mNumVertices);
    for (int i = 0; i < mNumVertices; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            mComputeVertices[i][j] = (ComputeType)mVertices[i][j];
        }
    }
    mQuery.Set(mNumVertices, &mComputeVertices[0]);
}
//----------------------------------------------------------------------------
