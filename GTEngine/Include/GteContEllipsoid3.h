// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprGaussian3.h"
#include "GteEllipsoid3.h"
#include "GteRotation.h"
#include "GteProjection.h"

namespace gte
{

// The input points are fit with a Gaussian distribution.  The center C of the
// ellipsoid is chosen to be the mean of the distribution.  The axes of the
// ellipsoid are chosen to be the eigenvectors of the covariance matrix M.
// The shape of the ellipsoid is determined by the absolute values of the
// eigenvalues.  NOTE: The construction is ill-conditioned if the points are
// (nearly) collinear or (nearly) planar.  In this case M has a (nearly) zero
// eigenvalue, so inverting M is problematic.
template <typename Real>
bool GetContainer(int numPoints, Vector3<Real> const* points,
    Ellipsoid3<Real>& ellipsoid);

// Test for containment of a point inside an ellipsoid.
template <typename Real>
bool InContainer(Vector2<Real> const& point,
    Ellipsoid3<Real> const& ellipsoid);

// Construct a bounding ellipsoid for the two input ellipsoids.  The result is
// not necessarily the minimum-volume ellipsoid containing the two ellipsoids.
template <typename Real>
bool MergeContainers(Ellipsoid3<Real> const& ellipsoid0,
    Ellipsoid3<Real> const& ellipsoid1, Ellipsoid3<Real>& merge);

#include "GteContEllipsoid3.inl"

}
