// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteAlignedBox3.h"
#include "GteOrientedBox3.h"

// The queries consider the box to be a solid.
//
// The test-intersection query uses the method of separating axes.  The set of
// potential separating directions includes the 3 face normals of box0, the 3
// face normals of box1, and 9 directions, each of which is the cross product
// of an edge of box0 and and an edge of box1.
//
// The separating axes involving cross products of edges has numerical
// robustness problems when the two edges are nearly parallel.  The cross
// product of the edges is nearly the zero vector, so normalization of the
// cross product may produce unit-length directions that are not close to the
// true direction.  Such a pair of edges occurs when a box0 face normal N0 and
// a box1 face normal N1 are nearly parallel.  In this case, you may skip the
// edge-edge directions, which is equivalent to projecting the boxes onto the
// plane with normal N0 and applying a 2D separating axis test.  The ability
// to do so involves choosing a small nonnegative epsilon .  It is used to
// determine whether two face normals, one from each box, are nearly parallel:
// |Dot(N0,N1)| >= 1 - epsilon.  If the input is negative, it is clamped to
// zero.
//
// The pair of integers 'separating', say, (i0,i1), identify the axis that
// reported separation; there may be more than one but only one is
// reported.  If the separating axis is a face normal N[i0] of the aligned
// box0 in dimension i0, then (i0,-1) is returned.  If the axis is a face
// normal box1.Axis[i1], then (-1,i1) is returned.  If the axis is a cross
// product of edges, Cross(N[i0],box1.Axis[i1]), then (i0,i1) is returned.

namespace gte
{

template <typename Real>
class TIQuery<Real, AlignedBox3<Real>, OrientedBox3<Real>>
{
public:
    struct Result
    {
        // The 'epsilon' value must be nonnegative.
        Result(Real inEpsilon = (Real)0);

        bool intersect;
        Real epsilon;
        int separating[2];
    };

    Result operator()(AlignedBox3<Real> const& box0,
        OrientedBox3<Real> const& box1);
};

#include "GteIntrAlignedBox3OrientedBox3.inl"

}
