// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteApprQuadratic3.h"

// Least-squares fit of a sphere to a set of points.  A successful fit is
// indicated by the return value of 'true'.  The return value is the number
// of iterations used.  If the number is the maximum, you can either accept
// the result or try increasing the maximum number and calling the function
// again.  TODO: Currently, the test for terminating the algorithm is exact
// (diff == (0,0,0)).  Expose an epsilon for this?
//
// If initialCenterIsAverage is set to 'true', the initial guess for the
// sphere center is the average of the data points.  If the data points are
// clustered along a solid angle, ApprSphere32 is very slow to converge.  If
// initialCenterIsAverage is set to 'false', the initial guess for the
// sphere center is computed using a least-squares estimate of the
// coefficients for a quadratic equation that represents a sphere.  This
// approach tends to converge rapidly.

namespace gte
{

template <typename Real>
class ApprSphere3
{
public:
    unsigned int operator()(int numPoints, Vector3<Real> const* points,
        unsigned int maxIterations, bool initialCenterIsAverage,
        Sphere3<Real>& sphere);
};

#include "GteApprSphere3.inl"

}
