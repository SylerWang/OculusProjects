// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/18)

#pragma once

#include "GteParametricSurface.h"
#include "GteVector3.h"
#include "GteMatrix2x2.h"

namespace gte
{
template <typename Real>
class DarbouxFrame3
{
public:
    // Construction.  The curve must persist as long as the DarbouxFrame3
    // object does.
    DarbouxFrame3(ParametricSurface<3, Real> const& surface);

    // Get a coordinate frame, {T0, T1, N}.  At a nondegenerate surface
    // points, dX/du and dX/dv are linearly independent tangent vectors.
    // The frame is constructed as
    //   T0 = (dX/du)/|dX/du|
    //   N  = Cross(dX/du,dX/dv)/|Cross(dX/du,dX/dv)|
    //   T1 = Cross(N, T0)
    // so that {T0, T1, N} is a right-handed orthonormal set.
    void operator()(Real u, Real v, Vector3<Real>& position,
        Vector3<Real>& tangent0, Vector3<Real>& tangent1,
        Vector3<Real>& normal) const;

    // Compute the principal curvatures and principal directions.
    void GetPrincipalInformation(Real u, Real v,
        Real& curvature0, Real& curvature1,
        Vector3<Real>& direction0, Vector3<Real>& direction1) const;

private:
    ParametricSurface<3, Real> const* mSurface;
};

#include "GteDarbouxFrame.inl"

}
