// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

#pragma once

#include "GteMatrix3x3.h"

namespace gte
{

// The input triangle mesh must represent a polyhedron.  The triangles are
// represented as triples of indices <V0,V1,V2> into the vertex array.
// The index array has numTriangles such triples.  The Boolean value
// 'bodyCoords is' 'true' if you want the inertia tensor to be relative to
// body coordinates but 'false' if you want it to be relative to world
// coordinates.
//
// The code assumes the rigid body has a constant density of 1.  If your
// application assigns a constant density of 'd', then you must multiply
// the output 'mass' by 'd' and the output 'inertia' by 'd'.

template <typename Real>
void ComputeMassProperties(Vector3<Real> const* vertices, int numTriangles,
    int const* indices, bool bodyCoords, Real& mass, Vector3<Real>& center,
    Matrix3x3<Real>& inertia);

#include "GtePolyhedralMassProperties.inl"

}
