// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteCircle2.h"

namespace gte
{

// Compute the smallest circle whose center is the average of the input
// points.
template <typename Real>
bool GetContainer(int numPoints, Vector2<Real> const* points,
    Circle2<Real>& circle);

// Test for containment of a point inside a circle.
template <typename Real>
bool InContainer(Vector2<Real> const& point, Circle2<Real> const& circle);

// Compute the smallest circle that contains the input circles.
template <typename Real>
bool MergeContainers(Circle2<Real> const& circle0,
    Circle2<Real> const& circle1, Circle2<Real>& merge);

#include "GteContCircle2.inl"

}
