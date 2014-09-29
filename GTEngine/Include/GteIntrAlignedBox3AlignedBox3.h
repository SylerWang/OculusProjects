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

// The queries consider the box to be a solid.
//
// The aligned-aligned queries use simple min-max comparisions.  The
// interesection of aligned boxes is an aligned box, possibly degenerate,
// where min[d] == max[d] for at least one dimension d.

namespace gte
{

template <typename Real>
class TIQuery<Real, AlignedBox3<Real>, AlignedBox3<Real>>
{
public:
    struct Result
    {
        bool intersect;
    };

    Result operator()(AlignedBox3<Real> const& box0,
        AlignedBox3<Real> const& box1);
};

template <typename Real>
class FIQuery<Real, AlignedBox3<Real>, AlignedBox3<Real>>
{
public:
    struct Result
    {
        bool intersect;
        AlignedBox3<Real> box;
    };

    Result operator()(AlignedBox3<Real> const& box0,
        AlignedBox3<Real> const& box1);
};


#include "GteIntrAlignedBox3AlignedBox3.inl"

}
