// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

// Linear interpolation of a network of triangles whose vertices are of the
// form (x,y,z,f(x,y,z)).  The function samples are F[i] and represent
// f(x[i],y[i],z[i]), where i is the index of the input vertex
// (x[i],y[i],z[i]) to Delaunay3.
//
// The TetrahedronMesh interface must support the following:
//   int GetContainingTetrahedron(Vector3<Real> const&) const;
//   bool GetIndices(int, std::array<int, 4>&) const;
//   bool GetBarycentrics(int, Vector3<Real> const&, Real[4]) const;

#include "GteVector3.h"
#include "GteLogger.h"

namespace gte
{

template <typename Real, typename TetrahedronMesh>
class IntpLinearNonuniform3
{
public:
    // Construction.
    IntpLinearNonuniform3(TetrahedronMesh const& mesh, Real const* F);

    // Linear interpolation.  The return value is 'true' if and only if the
    // input point is in the convex hull of the input vertices, in which case
    // the interpolation is valid.
    bool operator()(Vector3<Real> const& P, Real& F) const;

private:
    TetrahedronMesh const* mMesh;
    Real const* mF;
};

#include "GteIntpLinearNonuniform3.inl"

}
