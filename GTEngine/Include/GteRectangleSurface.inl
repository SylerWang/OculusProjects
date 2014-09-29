// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/19)

//----------------------------------------------------------------------------
template <typename Real>
RectangleSurface<Real>::RectangleSurface(
    std::shared_ptr<ParametricSurface<3, Real>> const& surface)
    :
    mSurface(surface),
    mNumUSamples(0),
    mNumVSamples(0),
    mNumVertices(0),
    mNumTriangles(0),
    mPositions(nullptr),
    mNormals(nullptr),
    mTCoords(nullptr),
    mStride(0)
{
}
//----------------------------------------------------------------------------
template <typename Real>
void RectangleSurface<Real>::Set(int numUSamples, int numVSamples)
{
    mNumUSamples = numUSamples;
    mNumVSamples = numVSamples;

    mNumVertices = numUSamples * numVSamples;
    mNumTriangles = 2 * (numUSamples - 1) * (numVSamples - 1);
}
//----------------------------------------------------------------------------
template <typename Real> inline
int RectangleSurface<Real>::GetNumVertices() const
{
    return mNumVertices;
}
//----------------------------------------------------------------------------
template <typename Real> inline
int RectangleSurface<Real>::GetNumTriangles() const
{
    return mNumTriangles;
}
//----------------------------------------------------------------------------
template <typename Real>
void RectangleSurface<Real>::GetPositions(void* positions, size_t stride)
    const
{
    mPositions = static_cast<char*>(positions);
    mStride = stride;

    Real uMin = mSurface->GetUMin();
    Real uDelta = (mSurface->GetUMax() - uMin) / (Real)(mNumUSamples - 1);
    Real vMin = mSurface->GetVMin();
    Real vDelta = (mSurface->GetVMax() - vMin) / (Real)(mNumVSamples - 1);
    for (int vIndex = 0, i = 0; vIndex < mNumVSamples; ++vIndex)
    {
        Real v = vMin + vDelta * vIndex;
        for (int uIndex = 0; uIndex < mNumUSamples; ++uIndex, ++i)
        {
            Real u = uMin + uDelta * uIndex;
            Position(i) = mSurface->GetPosition(u, v);
        }
    }

    mPositions = nullptr;
    mStride = 0;
}
//----------------------------------------------------------------------------
template <typename Real>
void RectangleSurface<Real>::GetNormals(void* normals, size_t stride) const
{
    mNormals = static_cast<char*>(normals);
    mStride = stride;

    Real uMin = mSurface->GetUMin();
    Real uDelta = (mSurface->GetUMax() - uMin) / (Real)(mNumUSamples - 1);
    Real vMin = mSurface->GetVMin();
    Real vDelta = (mSurface->GetVMax() - vMin) / (Real)(mNumVSamples - 1);
    DarbouxFrame3<Real> darboux(*mSurface.get());
    for (int vIndex = 0, i = 0; vIndex < mNumVSamples; ++vIndex)
    {
        Real v = vMin + vDelta * vIndex;
        for (int uIndex = 0; uIndex < mNumUSamples; ++uIndex, ++i)
        {
            Real u = uMin + uDelta * uIndex;
            Vector3<Real> position, tangent0, tangent1, normal;
            darboux(u, v, position, tangent0, tangent1, normal);
            Normal(i) = normal;
        }
    }

    mNormals = nullptr;
    mStride = 0;
}
//----------------------------------------------------------------------------
template <typename Real>
void RectangleSurface<Real>::GetTCoords(void* tcoords, size_t stride) const
{
    mTCoords = static_cast<char*>(tcoords);
    mStride = stride;

    Real uMin = mSurface->GetUMin();
    Real uDelta = (mSurface->GetUMax() - uMin) / (Real)(mNumUSamples - 1);
    Real vMin = mSurface->GetVMin();
    Real vDelta = (mSurface->GetVMax() - vMin) / (Real)(mNumVSamples - 1);
    Vector2<Real> tcoord;
    for (int vIndex = 0, i = 0; vIndex < mNumVSamples; ++vIndex)
    {
        tcoord[1] = vMin + vDelta * vIndex;
        for (int uIndex = 0; uIndex < mNumUSamples; ++uIndex, ++i)
        {
            tcoord[0] = uMin + uDelta * uIndex;
            TCoord(i) = tcoord;
        }
    }

    mTCoords = nullptr;
    mStride = 0;
}
//----------------------------------------------------------------------------
template <typename Real>
void RectangleSurface<Real>::GetIndices(int* indices) const
{
    for (int v = 0, i = 0; v < mNumVSamples - 1; ++v)
    {
        int i0 = i;
        int i1 = i0 + 1;
        i += mNumUSamples;
        int i2 = i;
        int i3 = i2 + 1;
        for (int u = 0; u < mNumUSamples - 1; ++u, indices += 6)
        {
            indices[0] = i0;
            indices[1] = i2;
            indices[2] = i1;
            indices[3] = i1;
            indices[4] = i2;
            indices[5] = i3;
            i0++;
            i1++;
            i2++;
            i3++;
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real>& RectangleSurface<Real>::Position(int i) const
{
    return *reinterpret_cast<Vector3<Real>*>(mPositions + i * mStride);
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real>& RectangleSurface<Real>::Normal(int i) const
{
    return *reinterpret_cast<Vector3<Real>*>(mNormals + i * mStride);
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector2<Real>& RectangleSurface<Real>::TCoord(int i) const
{
    return *reinterpret_cast<Vector2<Real>*>(mTCoords + i * mStride);
}
//----------------------------------------------------------------------------
