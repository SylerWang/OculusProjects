// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Polygon2<Real>::~Polygon2()
{

}
//----------------------------------------------------------------------------
template <typename Real>
Polygon2<Real>::Polygon2(Vector2<Real> const* vertexPool, int numIndices,
    int const* indices, bool counterClockwise)
    :
    mVertexPool(vertexPool),
    mCounterClockwise(counterClockwise)
{
    if (numIndices >= 3 && vertexPool && indices)
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

    // Invalid input to the Polygon2 constructor.
    mVertexPool = nullptr;
    mCounterClockwise = false;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Polygon2<Real>::operator bool() const
{
    return mVertexPool != nullptr;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector2<Real> const* Polygon2<Real>::GetVertexPool() const
{
    return mVertexPool;
}
//----------------------------------------------------------------------------
template <typename Real> inline
std::set<int> const& Polygon2<Real>::GetVertices() const
{
    return mVertices;
}
//----------------------------------------------------------------------------
template <typename Real> inline
std::vector<int> const& Polygon2<Real>::GetIndices() const
{
    return mIndices;
}
//----------------------------------------------------------------------------
template <typename Real> inline
bool Polygon2<Real>::CounterClockwise() const
{
    return mCounterClockwise;
}
//----------------------------------------------------------------------------
template <typename Real>
Vector2<Real> Polygon2<Real>::ComputeVertexAverage() const
{
    Vector2<Real> average((Real)0, (Real)0);
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
Real Polygon2<Real>::ComputePerimeterLength() const
{
    Real length = (Real)0;
    if (mVertexPool)
    {
        Vector2<Real> v0 = mVertexPool[mIndices.back()];
        for (int index : mIndices)
        {
            Vector2<Real> v1 = mVertexPool[index];
            length += Length(v1 - v0);
            v0 = v1;
        }
    }
    return length;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Polygon2<Real>::ComputeArea() const
{
    Real area = (Real)0;
    if (mVertexPool)
    {
        int const numIndices = static_cast<int>(mIndices.size());
        Vector2<Real> v0 = mVertexPool[mIndices[numIndices - 2]];
        Vector2<Real> v1 = mVertexPool[mIndices[numIndices - 1]];
        for (int index : mIndices)
        {
            Vector2<Real> v2 = mVertexPool[index];
            area += v1[0] * (v2[1] - v0[1]);
            v0 = v1;
            v1 = v2;
        }
        area *= (Real)0.5;
    }
    return std::abs(area);
}
//----------------------------------------------------------------------------
