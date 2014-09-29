// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteVector3.h"

// Queries about the relation of a point to various geometric objects.

namespace gte
{

template <typename Real>
class PrimalQuery3
{
public:
    // The caller is responsible for ensuring that the array is not empty
    // before calling queries and that the indices passed to the queries are
    // valid.  The class does no range checking.
    PrimalQuery3();
    PrimalQuery3(int numVertices, Vector3<Real> const* vertices);

    // Member access.
    inline void Set(int numVertices, Vector3<Real> const* vertices);
    inline int GetNumVertices() const;
    inline Vector3<Real> const* GetVertices() const;

    // In the following, point P refers to vertices[i] or 'test' and Vi refers
    // to vertices[vi].

    // For a plane with origin V0 and normal N = Cross(V1-V0,V2-V0), ToPlane
    // returns
    //   +1, P on positive side of plane (side to which N points)
    //   -1, P on negative side of plane (side to which -N points)
    //    0, P on the plane
    int ToPlane(int i, int v0, int v1, int v2) const;
    int ToPlane(Vector3<Real> const& test, int v0, int v1, int v2) const;

    // For a tetrahedron with vertices ordered as described in the file
    // GteTetrahedronKey.h, the function returns
    //   +1, P outside tetrahedron
    //   -1, P inside tetrahedron
    //    0, P on tetrahedron
    int ToTetrahedron(int i, int v0, int v1, int v2, int v3) const;
    int ToTetrahedron(Vector3<Real> const& test, int v0, int v1, int v2,
        int v3) const;

    // For a tetrahedron with vertices ordered as described in the file
    // GteTetrahedronKey.h, the function returns
    //   +1, P outside circumsphere of tetrahedron
    //   -1, P inside circumsphere of tetrahedron
    //    0, P on circumsphere of tetrahedron
    int ToCircumsphere(int i, int v0, int v1, int v2, int v3) const;
    int ToCircumsphere(Vector3<Real> const& test, int v0, int v1, int v2,
        int v3) const;

private:
    int mNumVertices;
    Vector3<Real> const* mVertices;
};

#include "GtePrimalQuery3.inl"

}
