// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteCapsule3.h"
#include "GteSphere3.h"
#include "GteApprOrthogonalLine3.h"
#include "GteDistPoint3Line3.h"
#include "GteDistPoint3Segment3.h"

namespace gte
{

// Compute the axis of the capsule segment using least-squares fitting.  The
// radius is the maximum distance from the points to the axis.  Hemispherical
// caps are chosen as close together as possible.
template <typename Real>
bool GetContainer(int numPoints, Vector3<Real> const* points,
    Capsule3<Real>& capsule);

// Test for containment of a point by a capsule.
template <typename Real>
bool InContainer(Vector3<Real> const& point, Capsule3<Real> const& capsule);

// Test for containment of a sphere by a capsule.
template <typename Real>
bool InContainer(Sphere3<Real> const& sphere, Capsule3<Real> const& capsule);

// Test for containment of a capsule by a capsule.
template <typename Real>
bool InContainer(Capsule3<Real> const& testCapsule,
    Capsule3<Real> const& capsule);

// Compute a capsule that contains the input capsules.  The returned capsule
// is not necessarily the one of smallest volume that contains the inputs.
template <typename Real>
bool MergeContainers(Capsule3<Real> const& capsule0,
     Capsule3<Real> const& capsule1, Capsule3<Real>& merge);

#include "GteContCapsule3.inl"

}
