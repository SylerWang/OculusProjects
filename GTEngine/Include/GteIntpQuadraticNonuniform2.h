// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

// Quadratic interpolation of a network of triangles whose vertices are of
// the form (x,y,f(x,y)).  This code is an implementation of the algorithm
// found in
//
//   Zoltan J. Cendes and Steven H. Wong,
//   C1 quadratic interpolation over arbitrary point sets,
//   IEEE Computer Graphics & Applications,
//   pp. 8-16, 1987
//
// The TriangleMesh interface must support the following:
//   int GetNumVertices() const;
//   int GetNumTriangles() const;
//   Vector2<Real> const* GetVertices() const;
//   int const* GetIndices() const;
//   bool GetVertices(int, std::array<Vector2<Real>, 3>&) const;
//   bool GetIndices(int, std::array<int, 3>&) const;
//   bool GetAdjacencies(int, std::array<int, 3>&) const;
//   bool GetBarycentrics(int, Vector2<Real> const&,
//      std::array<Real, 3>&) const;
//   int GetContainingTriangle(Vector2<Real> const&) const;

#include "GteDelaunay2.h"
#include "GteContScribeCircle2.h"
#include "GteDistPoint3AlignedBox3.h"

namespace gte
{

template <typename Real, typename TriangleMesh>
class IntpQuadraticNonuniform2
{
public:
    // Construction.
    //
    // The first constructor requires only F and a measure of the rate of
    // change of the function values relative to changes in the spatial
    // variables.  The df/dx and df/dy values are estimated at the sample
    // points using mesh normals and spatialDelta.
    //
    // The second constructor requires you to specify function values F and
    // first-order partial derivative values df/dx and df/dy.

    IntpQuadraticNonuniform2(TriangleMesh const& mesh, Real const* F,
        Real spatialDelta);

    IntpQuadraticNonuniform2(TriangleMesh const& mesh, Real const* F,
        Real const* FX, Real const* FY);

    // Quadratic interpolation.  The return value is 'true' if and only if the
    // input point is in the convex hull of the input vertices, in which case
    // the interpolation is valid.
    bool operator()(Vector2<Real> const & P, Real& F, Real& FX, Real& FY)
        const;

private:
    void EstimateDerivatives(Real spatialDelta);
    void ProcessTriangles();
    void ComputeCrossEdgeIntersections(int t);
    void ComputeCoefficients(int t);

    class TriangleData
    {
    public:
        Vector2<Real> center;
        Vector2<Real> intersect[3];
        Real coeff[19];
    };

    class Jet
    {
    public:
        Real F, FX, FY;
    };

    TriangleMesh const* mMesh;
    Real const* mF;
    Real const* mFX;
    Real const* mFY;
    std::vector<Real> mFXStorage;
    std::vector<Real> mFYStorage;
    std::vector<TriangleData> mTData;
};

#include "GteIntpQuadraticNonuniform2.inl"

}
