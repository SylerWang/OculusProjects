// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDistPoint2AlignedBox2.h"
#include "GteOrientedBox2.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector2<Real>, OrientedBox2<Real>>
    :
    public DCPQuery<Real, Vector2<Real>, AlignedBox2<Real>>
{
public:
    struct Result
        :
        public DCPQuery<Real, Vector2<Real>, AlignedBox2<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Vector2<Real> const& point,
        OrientedBox2<Real> const& box);
};

#include "GteDistPoint2OrientedBox2.inl"

}
