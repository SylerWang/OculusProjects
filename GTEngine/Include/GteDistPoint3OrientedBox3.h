// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteDistPoint3AlignedBox3.h"
#include "GteOrientedBox3.h"

namespace gte
{

template <typename Real>
class DCPQuery<Real, Vector3<Real>, OrientedBox3<Real>>
    :
    public DCPQuery<Real, Vector3<Real>, AlignedBox3<Real>>
{
public:
    struct Result
        :
        public DCPQuery<Real, Vector3<Real>, AlignedBox3<Real>>::Result
    {
        // No additional information to compute.
    };

    Result operator()(Vector3<Real> const& point,
        OrientedBox3<Real> const& box);
};

#include "GteDistPoint3OrientedBox3.inl"

}
