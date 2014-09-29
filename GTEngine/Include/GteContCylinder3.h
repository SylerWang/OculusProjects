// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteCylinder3.h"
#include "GteApprOrthogonalLine3.h"
#include "GteDistPoint3Line3.h"

namespace gte
{

// Compute the cylinder axis segment using least-squares fit.  The radius is
// the maximum distance from points to the axis.  The height is determined by
// projection of points onto the axis and determining the containing interval.
template <typename Real>
bool GetContainer(int numPoints, Vector3<Real> const* points,
     Cylinder3<Real>& cylinder);

// Test for containment of a point by a cylinder.
template <typename Real>
bool InContainer(Vector3<Real> const& point, Cylinder3<Real> const& cylinder);

#include "GteContCylinder3.inl"

}
