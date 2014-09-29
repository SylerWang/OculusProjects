// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteConstants.h"
#include "GteSymmetricEigensolver.h"
#include "GteMatrix3x3.h"

namespace gte
{

// Least-squares fit of a great circle to unit-length vectors (x,y,z) by
// using distance measurements orthogonal (and measured along great circles)
// to the proposed great circle.  The inputs akPoint[] are unit length.  The
// returned value is unit length, call it N.  The fitted great circle is
// defined by Dot(N,X) = 0, where X is a unit-length vector on the great
// circle.
template <typename Real>
class ApprGreatCircle3
{
public:
    void operator()(int numPoints, Vector3<Real> const* points,
        Vector3<Real>& normal);
};


// In addition to the least-squares fit of a great circle, the input vectors
// are projected onto that circle.  The sector of smallest angle (possibly
// obtuse) that contains the points is computed.  The endpoints of the arc
// of the sector are returned.  The returned endpoints A0 and A1 are
// perpendicular to the returned normal N.  Moreover, when you view the
// arc by looking at the plane of the great circle with a view direction
// of -N, the arc is traversed counterclockwise starting at A0 and ending
// at A1.
template <typename Real>
class ApprGreatArc3
{
public:
    void operator()(int numPoints, Vector3<Real> const* points,
        Vector3<Real>& normal, Vector3<Real>& arcEnd0,
        Vector3<Real>& arcEnd1);
};

#include "GteApprGreatCircle3.inl"

}
