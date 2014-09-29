// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprGaussian2.h"
#include "GteEllipse2.h"
#include "GteProjection.h"

namespace gte
{

// The input points are fit with a Gaussian distribution.  The center C of the
// ellipsoid is chosen to be the mean of the distribution.  The axes of the
// ellipsoid are chosen to be the eigenvectors of the covariance matrix M.
// The shape of the ellipsoid is determined by the absolute values of the
// eigenvalues.  NOTE: The construction is ill-conditioned if the points are
// (nearly) collinear.  In this case M has a (nearly) zero eigenvalue, so
// inverting M can be a problem numerically.
template <typename Real>
bool GetContainer(int numPoints, Vector2<Real> const* points,
    Ellipse2<Real>& ellipse);

// Test for containment of a point inside an ellipse.
template <typename Real>
bool InContainer(Vector2<Real> const& point, Ellipse2<Real> const& ellipse);

// Construct a bounding ellipse for the two input ellipses.  The result is
// not necessarily the minimum-area ellipse containing the two ellipses.
template <typename Real>
bool MergeContainers(Ellipse2<Real> const& ellipse0,
    Ellipse2<Real> const& ellipse1, Ellipse2<Real>& merge);

#include "GteContEllipse2.inl"

}
