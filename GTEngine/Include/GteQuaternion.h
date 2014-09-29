// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteMatrix.h"

namespace gte
{

template <typename Real>
class Quaternion : public Vector<4,Real>
{
public:
    // The quaternions are of the form q = x*i + y*j + z*k + w.  In tuple
    // form, q = (x,y,z,w).

    // Construction and destruction.  The default constructor does not
    // initialize the members.
    ~Quaternion();
    Quaternion();
    Quaternion(Quaternion const& q);
    Quaternion(Vector<4,Real> const& q);
    Quaternion(Real x, Real y, Real z, Real w);

    // Assignment.
    Quaternion& operator=(Quaternion const& q);
    Quaternion& operator=(Vector<4,Real> const& q);

    // Special quaternions.
    static Quaternion Zero();      // z = 0*i + 0*j + 0*k + 0
    static Quaternion I();         // i = 1*i + 0*j + 0*k + 0
    static Quaternion J();         // j = 0*i + 1*j + 0*k + 0
    static Quaternion K();         // k = 0*i + 0*j + 1*k + 0
    static Quaternion Identity();   // 1 = 0*i + 0*j + 0*k + 1
};

// Multiplication of quaternions.  This operation is not generally
// commutative; that is, q0*q1 and q1*q0 are not usually the same value.
// (x0*i + y0*j + z0*k + w0)*(x1*i + y1*j + z1*k + w1)
// =
// i*(+x0*w1 + y0*z1 - z0*y1 + w0*x1) +
// j*(-x0*z1 + y0*w1 + z0*x1 + w0*y1) +
// k*(+x0*y1 - y0*x1 + z0*w1 + w0*z1) +
// 1*(-x0*x1 - y0*y1 - z0*z1 + w0*w1)
template <typename Real>
Quaternion<Real> operator*(Quaternion<Real> const& q0,
    Quaternion<Real> const& q1);

// For a nonzero quaternion q = (x,y,z,w), inv(q) = (-x,-y,-z,w)/|q|^2, where
// |q| is the length of the quaternion.  When q is zero, the function returns
// zero, which is considered to be an improbable case.
template <typename Real>
Quaternion<Real> Inverse(Quaternion<Real> const& q);

// The conjugate of q = (x,y,z,w) is conj(q) = (-x,-y,-z,w).
template <typename Real>
Quaternion<Real> Conjugate(Quaternion<Real> const& q);

// Rotate a vector using quaternion multiplication.  The input quaternion must
// be unit length.
template <typename Real>
Vector<4,Real> Rotate(Quaternion<Real> const& q, Vector<4,Real> const& v);

// The spherical linear interpolation (slerp) of unit-length quaternions
// q0 and q1 for t in [0,1] is
//     slerp(t,q0,q1) = [sin(t*theta)*q0 + sin((1-t)*theta)*q1]/sin(theta)
// where theta is the angle between q0 and q1 [cos(theta) = Dot(q0,q1)].
// This function is a parameterization of the great spherical arc between
// q0 and q1 on the unit hypersphere.  Moreover, the parameterization is
// one of normalized arclength--a particle traveling along the arc through
// time t does so with constant speed.
template <typename Real>
Quaternion<Real> Slerp(Real t, Quaternion<Real> const& q0,
    Quaternion<Real> const& q1);

#include "GteQuaternion.inl"

}
