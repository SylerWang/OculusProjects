// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteOrientedBox2.h"
#include "GteSymmetricEigensolver.h"

// Fit points with a Gaussian distribution.  The center is the mean of the
// points, the axes are the eigenvectors of the covariance matrix, and the
// extents are the eigenvalues of the covariance matrix and are returned in
// increasing order.  An oriented box is used to store the mean, axes, and
// extents.

namespace gte
{

template <typename Real>
class ApprGaussian2
    :
    public ApprQuery<Real, ApprGaussian2<Real>, Vector2<Real>>
{
public:
    // Initialize the model parameters to zero.
    ApprGaussian2();

    // Basic fitting algorithm.
    bool Fit(int numPoints, Vector2<Real> const* points);
    OrientedBox2<Real> const& GetParameters() const;

    // Functions called by ApprQuery::RANSAC.  See GteApprQuery.h for a
    // detailed description.
    int GetMinimumRequired() const;
    Real Error(Vector2<Real> const& observation) const;
    bool Fit(std::vector<Vector2<Real>> const& observations,
        std::vector<int> const& indices);

private:
    OrientedBox2<Real> mParameters;
};

#include "GteApprGaussian2.inl"

}
