// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteCircle3.h"
#include "GteSphere3.h"
#include "GteLinearSystem.h"

namespace gte
{

// All functions return 'true' if circle/sphere has been constructed,
// 'false' otherwise (input points are linearly dependent).

// Circle circumscribing a triangle in 3D.
template <typename Real>
bool Circumscribe(Vector3<Real> const& v0, Vector3<Real> const& v1,
    Vector3<Real> const& v2, Circle3<Real>& circle);

// Sphere circumscribing a tetrahedron.
template <typename Real>
bool Circumscribe(Vector3<Real> const& v0, Vector3<Real> const& v1,
    Vector3<Real> const& v2, Vector3<Real> const& v3, Sphere3<Real>& sphere);

// Circle inscribing a triangle in 3D.
template <typename Real>
bool Inscribe(Vector3<Real> const& v0, Vector3<Real> const& v1,
    Vector3<Real> const& v2, Circle3<Real>& circle);

// Sphere inscribing tetrahedron.
template <typename Real>
bool Inscribe(Vector3<Real> const& v0, Vector3<Real> const& v1,
    Vector3<Real> const& v2, Vector3<Real> const& v3, Sphere3<Real>& sphere);

#include "GteContScribeCircle3Sphere3.inl"

}
