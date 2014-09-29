// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/16)

#pragma once

#include "GteConstants.h"
#include "GteFrenetFrame.h"
#include <functional>
#include <memory>

namespace gte
{

template <typename Real>
class TubeSurface
{
public:
    // Construction.
    TubeSurface(std::shared_ptr<ParametricCurve<3, Real>> const& medial,
        std::function<Real(Real)> const& radial);

    // Support for generating triangle meshes that approximate the tube
    // surface.  Use Set(...) first.  The information is persistent for calls
    // to the Get* functions.  Use the GetNumVertices() and GetNumTriangles()
    // functions second so you can allocate the correct number of elements in
    // the arrays passed to the Get* functions.
    void Set(int numMedialSamples, int numRadialSamples, bool closed,
        bool sampleByArcLength, bool outsideView);

    // The return values of these functions should be used to allocate the
    // array inputs to the other Get* functions.
    inline int GetNumVertices() const;
    inline int GetNumTriangles() const;

    // The positions must be 3-tuples separated by 'stride' bytes.  The
    // normals must be 3-tuples separated by 'stride' bytes.  The tcoords
    // must be 2-tuples separated by 'stride' bytes.
    void GetPositions(void* positions, size_t stride) const;
    void GetNormals(void* normals, size_t stride) const;
    void GetTCoords(void* tcoords, size_t stride) const;
    void GetIndices(int* indices) const;

private:
    inline int Index(int medialIndex, int radialIndex) const;
    inline Vector3<Real>& Position(int i) const;
    inline Vector3<Real>& Normal(int i) const;
    inline Vector2<Real>& TCoord(int i) const;

    std::shared_ptr<ParametricCurve<3, Real>> mMedial;
    std::function<Real(Real)> mRadial;
    int mNumMedialSamples;
    int mNumRadialSamples;
    bool mClosed, mSampleByArcLength, mOutsideView;
    int mNumVertices;
    int mNumTriangles;
    std::vector<Real> mCosAngle, mSinAngle;
    mutable char* mPositions;
    mutable char* mNormals;
    mutable char* mTCoords;
    mutable size_t mStride;
};

#include "GteTubeSurface.inl"

}
