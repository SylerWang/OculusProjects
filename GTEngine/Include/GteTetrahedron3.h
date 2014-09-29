// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GtePlane3.h"

namespace gte
{

// The tetrahedron is represented as an array of four vertices: V0, V1, V2,
// and V3.  The vertices are ordered so that the triangular faces are
// counterclockwise-ordered triangles when viewed by an observer outside the
// tetrahedron:
//   face 0 = <V[0],V[2],V[1]>
//   face 1 = <V[0],V[1],V[3]>
//   face 2 = <V[0],V[3],V[2]>
//   face 3 = <V[1],V[2],V[3]>

template <typename Real>
class Tetrahedron3 : public GeometricPrimitive<Tetrahedron3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the
    // vertices to (0,0,0), (1,0,0), (0,1,0), and (0,0,1).
    Tetrahedron3();
    Tetrahedron3(Vector3<Real> const& v0, Vector3<Real> const& v1,
        Vector3<Real> const& v2, Vector3<Real> const& v3);
    Tetrahedron3(Vector3<Real> const inV[4]);

    // Get the vertex indices for the specified face.  The input 'face' must
    // be in {0,1,2,3}.
    void GetFaceIndices(int face, int index[3]) const;

    // Construct the planes of the faces.  The planes have outer pointing
    // normal vectors.  The plane indexing is the same as the face indexing
    // mentioned previously.
    void GetPlanes(Plane3<Real> plane[4]) const;

    // Public member access.
    Vector3<Real> v[4];

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Tetrahedron3 const& tetrahedron) const;
    bool IsLessThan(Tetrahedron3 const& tetrahedron) const;
};

#include "GteTetrahedron3.inl"

}
