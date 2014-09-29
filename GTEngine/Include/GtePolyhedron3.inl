// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Polyhedron3<Real>::~Polyhedron3()
{

}
//----------------------------------------------------------------------------
template <typename Real>
Polyhedron3<Real>::Polyhedron3(Vector3<Real> const* vertexPool,
    int numIndices, int const* indices, bool counterClockwise)
    :
    mVertexPool(vertexPool),
    mCounterClockwise(counterClockwise)
{
    if (numIndices >= 4 && vertexPool && indices)
    {
        for (int i = 0; i < numIndices; ++i)
        {
            mVertices.insert(indices[i]);
        }

        if (numIndices == static_cast<int>(mVertices.size()))
        {
            mIndices.resize(numIndices);
            std::copy(indices, indices + numIndices, mIndices.begin());
            return;
        }

        mVertices.clear();
    }

    // Invalid input to the Polyhedron3 constructor.
    mVertexPool = nullptr;
    mCounterClockwise = false;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Polyhedron3<Real>::operator bool() const
{
    return mVertexPool != nullptr;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real> const* Polyhedron3<Real>::GetVertexPool() const
{
    return mVertexPool;
}
//----------------------------------------------------------------------------
template <typename Real> inline
std::set<int> const& Polyhedron3<Real>::GetVertices() const
{
    return mVertices;
}
//----------------------------------------------------------------------------
template <typename Real> inline
std::vector<int> const& Polyhedron3<Real>::GetIndices() const
{
    return mIndices;
}
//----------------------------------------------------------------------------
template <typename Real> inline
bool Polyhedron3<Real>::CounterClockwise() const
{
    return mCounterClockwise;
}
//----------------------------------------------------------------------------
template <typename Real>
Vector3<Real> Polyhedron3<Real>::ComputeVertexAverage() const
{
    Vector3<Real> average((Real)0, (Real)0, (Real)0);
    if (mVertexPool)
    {
        for (int index : mVertices)
        {
            average += mVertexPool[index];
        }
        average /= static_cast<Real>(mVertices.size());
    }
    return average;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Polyhedron3<Real>::ComputeSurfaceArea() const
{
    Real surfaceArea = (Real)0;
    if (mVertexPool)
    {
        int const numTriangles = static_cast<int>(mIndices.size()) / 3;
        int const* indices = &mIndices[0];
        for (int t = 0; t < numTriangles; ++t)
        {
            int v0 = *indices++;
            int v1 = *indices++;
            int v2 = *indices++;
            Vector3<Real> edge0 = mVertexPool[v1] - mVertexPool[v0];
            Vector3<Real> edge1 = mVertexPool[v2] - mVertexPool[v0];
            Vector3<Real> cross = Cross(edge0, edge1);
            surfaceArea += Length(cross);
        }
        surfaceArea *= (Real)0.5;
    }
    return surfaceArea;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Polyhedron3<Real>::ComputeVolume() const
{
    Real volume = (Real)0;
    if (mVertexPool)
    {
        int const numTriangles = static_cast<int>(mIndices.size()) / 3;
        int const* indices = &mIndices[0];
        for (int t = 0; t < numTriangles; ++t)
        {
            int v0 = *indices++;
            int v1 = *indices++;
            int v2 = *indices++;
            volume +=
                DotCross(mVertexPool[v0], mVertexPool[v1], mVertexPool[v2]);
        }
        volume /= (Real)6;
    }
    return std::abs(volume);
}
//----------------------------------------------------------------------------
