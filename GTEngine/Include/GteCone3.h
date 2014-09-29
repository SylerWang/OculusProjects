// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteConstants.h"
#include "GteVector3.h"

namespace gte
{

// An acute cone is Dot(A,X-V) = |X-V| cos(t) where V is the vertex, A is the
// unit-length direction of the axis of the cone, and T is the cone angle with
// 0 < t < pi/2.  The cone interior is defined by the inequality
// Dot(A,X-V) >= |X-V| cos(t).  Since cos(t) > 0, we can avoid computing
// square roots.  The solid cone is defined by the inequality
// Dot(A,X-V)^2 >= Dot(X-V,X-V) cos(t)^2.  This is an infinite, single-sided
// cone.
//
// The cone may be truncated by a plane perpendicular to its axis at a height
// h from the vertex (distance from the vertex to the intersection of the
// plane and the axis).  The infinite cone has h = infinity.  The finite cone
// has a disk of intersection between the plane and infinite cone.  The radius
// r of the disk is r = h*tan(t).

template <typename Real>
class Cone3 : public GeometricPrimitive<Cone3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets center to
    // (0,0,0), axis to (0,0,1), cosAngle and sinAngle to 1/sqrt(2) [angle is
    // pi/4], and height to 1.
    Cone3();

    // The axis must be unit-length and the angle must be in (0,pi/2).  For
    // an infinite cone, set inHeight to std::numeric_limits<float>::max().
    Cone3(Vector3<Real> const& inVertex, Vector3<Real> const& inAxis,
        Real angle, Real inHeight);

    // The axis must be unit-length.  The pair (cosAngle,sinAngle) must be
    // strictly in the first quadrant of the plane to guarantee that the
    // cone angle is in (0,pi/2).  For an infinite cone, set inHeight to
    // std::numeric_limits<float>::max().
    Cone3(Vector3<Real> const& inVertex, Vector3<Real> const& inAxis,
        Real inCosAngle, Real inSinAngle, Real inHeight);

    Vector3<Real> vertex, axis;
    Real cosAngle, sinAngle, height;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Cone3 const& cone) const;
    bool IsLessThan(Cone3 const& cone) const;
};

#include "GteCone3.inl"

}
