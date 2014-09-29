// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprGaussian2.h"

namespace gte
{

// Compute an oriented bounding box of the points.  The box center is the
// average of the points.  The box axes are the eigenvectors of the covariance
// matrix.
template <typename Real>
bool GetContainer(int numPoints, Vector2<Real> const* points,
     OrientedBox2<Real>& box);

// Test for containment.  Let X = C + y0*U0 + y1*U1 where C is the box center
// and U0 and U1 are the orthonormal axes of the box.  X is in the box when
// |y_i| <= E_i for all i, where E_i are the extents of the box.
template <typename Real>
bool InContainer(Vector2<Real> const& point, OrientedBox2<Real> const& box);

// Construct an oriented box that contains two other oriented boxes.  The
// result is not guaranteed to be the minimum area box containing the input
// boxes.
template <typename Real>
bool MergeContainers(OrientedBox2<Real> const& box0,
    OrientedBox2<Real> const& box1, OrientedBox2<Real>& merge);

#include "GteContOrientedBox2.inl"

}
