// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteSphere3.h"

namespace gte
{

// Compute the smallest sphere whose center is the average of the input
// points.
template <typename Real>
bool GetContainer(int numPoints, Vector3<Real> const* points,
    Sphere3<Real>& sphere);

// Test for containment of a point inside a sphere.
template <typename Real>
bool InContainer(Vector3<Real> const& point, Sphere3<Real> const& sphere);

// Compute the smallest sphere that contains the input spheres.
template <typename Real>
bool MergeContainers(Sphere3<Real> const& sphere0,
    Sphere3<Real> const& sphere1, Sphere3<Real>& merge);

#include "GteContSphere3.inl"

}
