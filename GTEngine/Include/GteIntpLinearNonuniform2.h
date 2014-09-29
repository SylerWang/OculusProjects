// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

// Linear interpolation of a network of triangles whose vertices are of the
// form (x,y,f(x,y)).  The function samples are F[i] and represent
// f(x[i],y[i]), where i is the index of the input vertex (x[i],y[i]) to
// Delaunay2.
//
// The TriangleMesh interface must support the following:
//   bool GetIndices(int, std::array<int, 3>&) const;
//   bool GetBarycentrics(int, Vector2<Real> const&,
//       std::array<Real, 3>&) const;
//   int GetContainingTriangle(Vector2<Real> const&) const;

#include "GteVector2.h"
#include "GteLogger.h"

namespace gte
{

template <typename Real, typename TriangleMesh>
class IntpLinearNonuniform2
{
public:
    // Construction.
    IntpLinearNonuniform2(TriangleMesh const& mesh, Real const* F);

    // Linear interpolation.  The return value is 'true' if and only if the
    // input point P is in the convex hull of the input vertices, in which
    // case the interpolation is valid.
    bool operator()(Vector2<Real> const& P, Real& F) const;

private:
    TriangleMesh const* mMesh;
    Real const* mF;
};

#include "GteIntpLinearNonuniform2.inl"

}
