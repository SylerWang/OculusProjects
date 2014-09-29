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

// Orthogonal frustum.  Let E be the origin, D be the direction vector, U be
// the up vector, and R be the right vector.  Let u > 0 and r > 0 be the
// extents in the U and R directions, respectively.  Let n and f be the
// extents in the D direction with 0 < n < f.  The four corners of the frustum
// in the near plane are E + n*D + s0*u*U + s1*r*R where |s0| = |s1| = 1 (four
// choices).  The four corners of the frustum in the far plane are
// E + f*D + (f/n)*(s0*u*U + s1*r*R) where |s0| = |s1| = 1 (four choices).

template <typename Real>
class Frustum3 : public GeometricPrimitive<Frustum3<Real>>
{
public:
    // Construction and destruction.  The default constructor sets the
    // following values:  origin (E) to (0,0,0), dVector (D) to (0,0,1),
    // uVector (U) to (0,1,0), rVector (R) to (1,0,0), dMin (n) to 1,
    // dMax (f) to 2, uBound (u) to 1, and rBound (r) to 1.
    Frustum3();
    Frustum3(Vector3<Real> const& inOrigin, Vector3<Real> const& inDVector,
        Vector3<Real> const& inUVector, Vector3<Real> const& inRVector,
        Real inDMin, Real inDMax, Real inUBound, Real inRBound);

    // The Update() function must be called whenever changes are made to DMIN,
    // DMax, UBound, or RBound.  The values mDRatio, mMTwoUF, and mMTwoRF are
    // dependent on the changes, so call the Get*() accessors only after the
    // Update() call.
    void Update();
    inline Real GetDRatio() const;
    inline Real GetMTwoUF() const;
    inline Real GetMTwoRF() const;

    void ComputeVertices(Vector3<Real> vertex[8]) const;

    Vector3<Real> origin, dVector, uVector, rVector;
    Real dMin, dMax, uBound, rBound;

protected:
    // Quantities derived from the constructor inputs.
    Real mDRatio, mMTwoUF, mMTwoRF;
};

#include "GteFrustum3.inl"

}
