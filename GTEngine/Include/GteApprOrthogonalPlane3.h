// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteVector3.h"
#include "GteSymmetricEigensolver.h"

// Least-squares fit of a plane to (x,y,z) data by using distance measurements
// orthogonal to the proposed plane.  The return value is 'true' iff the fit
// is unique (always successful, 'true' when a minimum eigenvalue is unique).
// The mParameters value is (P,N) = (origin,normal).  The error for
// S = (x0,y0,z0) is (S-P)^T*(I - N*N^T)*(S-P).

namespace gte
{

template <typename Real>
class ApprOrthogonalPlane3
    :
    public ApprQuery<Real, ApprOrthogonalPlane3<Real>, Vector3<Real>>
{
public:
    // Initialize the model parameters to zero.
    ApprOrthogonalPlane3();

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

#include "GteApprOrthogonalPlane3.inl"

}
