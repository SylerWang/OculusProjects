// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuery.h"
#include "GteMatrix2x2.h"

// Least-squares fit of a line to height data (x,f(x)).  The line is of the
// form: (y - yAvr) = a*(x - xAvr), where (xAvr,yAvr) is the average of the
// sample points.  The return value of Fit is 'true' iff the fit is successful
// (the input points are not degenerate to a single point).  The mParameters
// values are ((xAvr,yAvr),(a,-1)) on success and ((0,0),(0,0)) on failure.
// The error for (x0,y0) is [a*(x0-xAvr)-(y0-yAvr)]^2.

namespace gte
{

template <typename Real>
class ApprHeightLine2
    :
    public ApprQuery<Real, ApprHeightLine2<Real>, Vector2<Real>>
{
public:
    // Initialize the model parameters to zero.
    ApprHeightLine2();

    // Basic fitting algorithm.
    bool Fit(int numPoints, Vector2<Real> const* points);
    std::pair<Vector2<Real>, Vector2<Real>> const& GetParameters() const;

    // Functions called by ApprQuery::RANSAC.  See GteApprQuery.h for a
    // detailed description.
    int GetMinimumRequired() const;
    Real Error(Vector2<Real> const& observation) const;
    bool Fit(std::vector<Vector2<Real>> const& observations,
        std::vector<int> const& indices);

private:
    std::pair<Vector2<Real>, Vector2<Real>> mParameters;
};

#include "GteApprHeightLine2.inl"

}
