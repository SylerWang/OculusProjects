// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteMatrix3x3.h"

// Least-squares fit of a plane to height data (x,y,f(x,y)).  The plane is of
// the form (z - zAvr) = a*(x - xAvr) + b*(y - yAvr), where (xAvr,yAvr,zAvr)
// is the average of the sample points.  The return value is 'true' iff the
// fit is successful (the input points are noncollinear).  The mParameters
// values are ((xAvr,yAvr,zAvr),(a,b,-1)) on success and ((0,0,0),(0,0,0)) on
// failure.  The error for (x0,y0,z0) is [a*(x0-xAvr)+b*(y0-yAvr)-(z0-zAvr)]^2.

namespace gte
{

template <typename Real>
class ApprHeightPlane3
    :
    public ApprQuery<Real, ApprHeightPlane3<Real>, Vector3<Real>>
{
public:
    // Initialize the model parameters to zero.
    ApprHeightPlane3();

    // Basic fitting algorithm.
    bool Fit(int numPoints, Vector3<Real> const* points);
    std::pair<Vector3<Real>, Vector3<Real>> const& GetParameters() const;

    // Functions called by ApprQuery::RANSAC.  See GteApprQuery.h for a
    // detailed description.
    int GetMinimumRequired() const;
    Real Error(Vector3<Real> const& observation) const;
    bool Fit(std::vector<Vector3<Real>> const& observations,
        std::vector<int> const& indices);

private:
    std::pair<Vector3<Real>, Vector3<Real>> mParameters;
};

#include "GteApprHeightPlane3.inl"

}
