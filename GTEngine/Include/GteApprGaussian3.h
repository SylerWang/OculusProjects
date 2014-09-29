// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteOrientedBox3.h"
#include "GteSymmetricEigensolver.h"

// Fit points with a Gaussian distribution.  The center is the mean of the
// points, the axes are the eigenvectors of the covariance matrix, and the
// extents are the eigenvalues of the covariance matrix and are returned in
// increasing order.  An oriented box is used to store the mean, axes, and
// extents.

namespace gte
{

template <typename Real>
class ApprGaussian3
    :
    public ApprQuery<Real, ApprGaussian3<Real>, Vector3<Real>>
{
public:
    // Initialize the model parameters to zero.
    ApprGaussian3();

    // Basic fitting algorithm.
    bool Fit(int numPoints, Vector3<Real> const* points);
    OrientedBox3<Real> const& GetParameters() const;

    // Functions called by ApprQuery::RANSAC.  See GteApprQuery.h for a
    // detailed description.
    int GetMinimumRequired() const;
    Real Error(Vector3<Real> const& observation) const;
    bool Fit(std::vector<Vector3<Real>> const& observations,
        std::vector<int> const& indices);

private:
    OrientedBox3<Real> mParameters;
};

#include "GteApprGaussian3.inl"

}
