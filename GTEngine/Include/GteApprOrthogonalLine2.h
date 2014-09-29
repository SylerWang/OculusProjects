// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteLine2.h"
#include "GteSymmetricEigensolver.h"

// Least-squares fit of a line to (x,y) data by using distance measurements
// orthogonal to the proposed line.  The return value is 'true' iff the fit
// is unique (always successful, 'true' when a minimum eigenvalue is unique).
// The mParameters value is a line with (P,D) = (origin,direction).  The
// error for S = (x0,y0) is (S-P)^T*(I - D*D^T)*(S-P).

namespace gte
{

template <typename Real>
class ApprOrthogonalLine2
    :
    public ApprQuery<Real, ApprOrthogonalLine2<Real>, Vector2<Real>>
{
public:
    // Initialize the model parameters to zero.
    ApprOrthogonalLine2();

    // Basic fitting algorithm.
    bool Fit(int numPoints, Vector2<Real> const* points);
    Line2<Real> const& GetParameters() const;

    // Functions called by ApprQuery::RANSAC.  See GteApprQuery.h for a
    // detailed description.
    int GetMinimumRequired() const;
    Real Error(Vector2<Real> const& observation) const;
    bool Fit(std::vector<Vector2<Real>> const& observations,
        std::vector<int> const& indices);

private:
    Line2<Real> mParameters;
};

#include "GteApprOrthogonalLine2.inl"

}
