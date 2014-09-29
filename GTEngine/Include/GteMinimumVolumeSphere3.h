// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteSphere3.h"
#include "GteLinearSystem.h"
#include "GteLogger.h"
#include <algorithm>
#include <random>

// Compute the minimum volume sphere containing the input set of points.  The
// algorithm randomly permutes the input points so that the construction
// occurs in 'expected' O(N) time.  All internal minimal sphere calculations
// store the squared radius in the radius member of Sphere3.  Only at
// the end is a sqrt computed.

namespace gte
{

template <typename InputType, typename ComputeType>
class MinimumVolumeSphere3
{
public:
    bool operator()(int numPoints, Vector3<InputType> const* points,
        Sphere3<InputType>& minimal);

    // Member access.
    inline int GetNumSupport() const;
    inline std::array<int, 4> const& GetSupport() const;

private:
    // Test whether point P is inside sphere S using squared distance and
    // squared radius.
    bool Contains(int i, Sphere3<ComputeType> const& sphere) const;

    Sphere3<ComputeType> ExactSphere1(int i0) const;
    Sphere3<ComputeType> ExactSphere2(int i0, int i1) const;
    Sphere3<ComputeType> ExactSphere3(int i0, int i1, int i2) const;
    Sphere3<ComputeType> ExactSphere4(int i0, int i1, int i2, int i3) const;

    Sphere3<ComputeType> UpdateSupport1(int i);
    Sphere3<ComputeType> UpdateSupport2(int i);
    Sphere3<ComputeType> UpdateSupport3(int i);
    Sphere3<ComputeType> UpdateSupport4(int i);

    // Indices of points that support current minimum volume sphere.
    bool SupportContains(int j) const;

    int mNumSupport;
    std::array<int, 4> mSupport;

    // Random permutation of the unique input points to produce expected
    // linear time for the algorithm.
    std::vector<Vector3<ComputeType>> mComputePoints;
};

#include "GteMinimumVolumeSphere3.inl"

}
