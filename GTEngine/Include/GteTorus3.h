// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteGeometricPrimitive.h"
#include "GteVector3.h"

namespace gte
{

// The torus has center C with plane of symmetry containing C and having
// directions D0 and D1.  The axis of symmetry is the line containing C
// and having direction N (the plane normal).  The radius from the center
// of the torus is r0 (outer radius) and the radius of the tube of the
// torus is r1 (inner radius).  It must be that r0 >= r1.  A point X may
// be written as X = C + y0*D0 + y1*D1 + y2*N, where matrix [U V N] is
// orthonormal and has determinant 1.  Thus, y0 = Dot(D0,X-C),
// y1 = Dot(D1,X-C), and y2 = Dot(N,X-C).  The implicit form is
//      [|X-C|^2 - (r0^2 + r1^2)]^2 + 4*r0^2*((Dot(N,X-C))^2 - r1^2) = 0
// Note that D0 and D1 are not present in the equation, which is to be
// expected by the symmetry.  The parametric form is
//      X(u,v) = (r0 + r1*cos(v))*(cos(u)*D0 + sin(u)*D1) + r1*sin(v)*N
// for -pi <= u < pi, -pi <= v < pi.  The member 'center' is C, 'direction0'
// is D0, 'direction1' is D1, 'normal' is N, 'radius0' is r0, and 'radius1'
// is r1.

template <typename Real>
class Torus3 : public GeometricPrimitive<Torus3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets center to
    // (0,0,0), direction0 to (1,0,0), direction1 to (0,1,0), normal to
    // (0,0,1), radius0 to 2, and radius1 to 1.
    Torus3();
    Torus3(Vector3<Real> const& inCenter, Vector3<Real> const& inDirection0,
        Vector3<Real> const& inDirection1, Vector3<Real> const& inNormal,
        Real inRadius0, Real inRadius1);

    // Evaluation of the surface.  The function supports derivative
    // calculation through order 2; that is, maxOrder <= 2 is required.  If
    // you want only the position, pass in maxOrder of 0.  If you want the
    // position and first-order derivatives, pass in maxOrder of 1, and so on.
    // The output 'values' are ordered as: position X; first-order derivatives
    // dX/du, dX/dv; second-order derivatives d2X/du2, d2X/dudv, d2X/dv2.
    void Evaluate(Real u, Real v, unsigned int maxOrder,
        Vector3<Real> values[6]) const;

    // Reverse lookup of parameters from position.
    void GetParameters(Vector3<Real> const& X, Real& u, Real& v) const;

    Vector3<float> center, direction0, direction1, normal;
    Real radius0, radius1;

public:
    // Support for comparisons in GeometricPrimitive<T>.
    bool IsEqualTo(Torus3 const& torus) const;
    bool IsLessThan(Torus3 const& torus) const;
};

#include "GteTorus3.inl"

}
