// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteCircle2.h"
#include "GteLinearSystem.h"
#include "GteGMatrix.h"
#include "GteLogger.h"
#include <algorithm>
#include <random>

// Compute the minimum area circle containing the input set of points.  The
// algorithm randomly permutes the input points so that the construction
// occurs in 'expected' O(N) time.  All internal minimal circle calculations
// store the squared radius in the radius member of Circle2.  Only at the
// end is a sqrt computed.

namespace gte
{

template <typename InputType, typename ComputeType>
class MinimumAreaCircle2
{
public:
    bool operator()(int numPoints, Vector2<InputType> const* points,
        Circle2<InputType>& minimal);

    // Member access.
    inline int GetNumSupport() const;
    inline std::array<int, 3> const& GetSupport() const;

private:
    // Test whether point P is inside circle C using squared distance and
    // squared radius.
    bool Contains(int i, Circle2<ComputeType> const& circle) const;

    Circle2<ComputeType> ExactCircle1(int i0) const;
    Circle2<ComputeType> ExactCircle2(int i0, int i1) const;
    Circle2<ComputeType> ExactCircle3(int i0, int i1, int i2) const;

    Circle2<ComputeType> UpdateSupport1(int i);
    Circle2<ComputeType> UpdateSupport2(int i);
    Circle2<ComputeType> UpdateSupport3(int i);

    // Indices of points that support current minimum area circle.
    bool SupportContains(int j) const;

    int mNumSupport;
    std::array<int, 3> mSupport;

    // Random permutation of the unique input points to produce expected
    // linear time for the algorithm.
    std::vector<Vector2<ComputeType>> mComputePoints;
};

#include "GteMinimumAreaCircle2.inl"

}
