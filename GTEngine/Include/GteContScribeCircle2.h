// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteCircle2.h"
#include "GteLinearSystem.h"

namespace gte
{

// All functions return 'true' if the circle has been constructed, 'false'
// otherwise (input points are linearly dependent).

// Circle circumscribing triangle.
template <typename Real>
bool Circumscribe(Vector2<Real> const& v0, Vector2<Real> const& v1,
    Vector2<Real> const& v2, Circle2<Real>& circle);

// Circle inscribing triangle.
template <typename Real>
bool Inscribe(Vector2<Real> const& v0, Vector2<Real> const& v1,
    Vector2<Real> const& v2, Circle2<Real>& circle);

#include "GteContScribeCircle2.inl"

}
