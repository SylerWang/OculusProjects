// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprGaussian3.h"
#include "GteMatrix3x3.h"
#include "GteRotation.h"

namespace gte
{

// Compute an oriented bounding box of the points.  The box center is the
// average of the points.  The box axes are the eigenvectors of the covariance
// matrix.
template <typename Real>
bool GetContainer(int numPoints, Vector3<Real> const* points,
    OrientedBox3<Real>& box);

// Test for containment.  Let X = C + y0*U0 + y1*U1 + y2*U2 where C is the
// box center and U0, U1, U2 are the orthonormal axes of the box.  X is in
// the box if |y_i| <= E_i for all i where E_i are the extents of the box.
template <typename Real>
bool InContainer(Vector3<Real> const& point, OrientedBox3<Real> const& box);

// Construct an oriented box that contains two other oriented boxes.  The
// result is not guaranteed to be the minimum volume box containing the
// input boxes.
template <typename Real>
bool MergeContainers(OrientedBox3<Real> const& box0,
    OrientedBox3<Real> const& box1, OrientedBox3<Real>& merge);

#include "GteContOrientedBox3.inl"

}
