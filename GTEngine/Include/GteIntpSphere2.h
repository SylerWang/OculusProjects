// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

// Interpolation of a scalar-valued function defined on a sphere.  Although
// the sphere lives in 3D, the interpolation is a 2D method whose input
// points are angles (theta,phi) from spherical coordinates.  The domains of
// the angles are -pi <= theta <= pi and 0 <= phi <= pi.

#include "GteIntpQuadraticNonuniform2.h"
#include "GteDelaunay2Mesh.h"
#include "GteConstants.h"

namespace gte
{

template <typename InputType, typename ComputeType, typename RationalType>
class IntpSphere2
{
public:
    // Construction and destruction.  For complete spherical coverage, include
    // the two antipodal (theta,phi) points (-pi,0,F(-pi,0)) and
    // (-pi,pi,F(-pi,pi)) in the input data.  These correspond to the sphere
    // poles x = 0, y = 0, and |z| = 1.
    ~IntpSphere2();
    IntpSphere2(int numPoints, InputType const* theta, InputType const* phi,
        InputType const* F);

    // Spherical coordinates are
    //   x = cos(theta)*sin(phi)
    //   y = sin(theta)*sin(phi)
    //   z = cos(phi)
    // for -pi <= theta <= pi, 0 <= phi <= pi.  The application can use this
    // function to convert unit length vectors (x,y,z) to (theta,phi).
    static void GetSphericalCoordinates(InputType x, InputType y, InputType z,
        InputType& theta, InputType& phi);

    // The return value is 'true' if and only if the input point is in the
    // convex hull of the input (theta,pi) array, in which case the
    // interpolation is valid.
    bool operator()(InputType theta, InputType phi, InputType& F) const;

private:
    typedef Delaunay2Mesh<InputType, ComputeType, RationalType> TriangleMesh;

    std::vector<Vector2<InputType>> mWrapAngles;
    Delaunay2<InputType, ComputeType> mDelaunay;
    TriangleMesh mMesh;
    std::vector<InputType> mWrapF;
    IntpQuadraticNonuniform2<InputType, TriangleMesh>* mInterp;
};

#include "GteIntpSphere2.inl"

}
