// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrSegment3AlignedBox3.h"
#include "GteOrientedBox3.h"

// The queries consider the box to be a solid.
//
// The test-intersection queries use the method of separating axes.  The
// find-intersection queries use parametric clipping against the six faces of
// the box.

namespace gte
{

template <typename Real>
class TIQuery<Real, Segment3<Real>, OrientedBox3<Real>>
    :
    public TIQuery<Real, Segment3<Real>, AlignedBox3<Real>>
{
public:
    struct Result
        :
        public TIQuery<Real, Segment3<Real>, AlignedBox3<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Segment3<Real> const& segment,
        OrientedBox3<Real> const& box);
};

template <typename Real>
class FIQuery<Real, Segment3<Real>, OrientedBox3<Real>>
    :
    public FIQuery<Real, Segment3<Real>, AlignedBox3<Real>>
{
public:
    struct Result
        :
        public FIQuery<Real, Segment3<Real>, AlignedBox3<Real>>::Result
    {
        // No additional relevant information to compute.
    };

    Result operator()(Segment3<Real> const& segment,
        OrientedBox3<Real> const& box);
};

#include "GteIntrSegment3OrientedBox3.inl"

}
