// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.3.0 (2014/09/11)

#pragma once

#include "GteBasisFunction.h"
#include "GteBandedMatrix.h"

namespace gte
{

template <typename Real>
class BSplineCurveFit
{
public:
    // Construction.  The preconditions for calling the constructor are
    //   1 <= degree && degree < numControls <= numSamples
    // The samples points are contiguous blocks of 'dimension' real values
    // stored in sampleData.
    BSplineCurveFit(int dimension, int numSamples, Real const* sampleData,
        int degree, int numControls);

    // Access to input sample information.
    inline int GetDimension() const;
    inline int GetNumSamples() const;
    inline Real const* GetSampleData() const;

    // Access to output control point and curve information.
    inline int GetDegree() const;
    inline int GetNumControls() const;
    inline Real const* GetControlData() const;
    inline BasisFunction<Real> const& GetBasis() const;

    // Evaluation of the B-spline curve.  It is defined for 0 <= t <= 1.  If a
    // t-value is outside [0,1], an open spline clamps it to [0,1].  The
    // caller must ensure that position[] has at least 'dimension' elements.
    void GetPosition(Real t, Real* position) const;

private:
    // Input sample information.
    int mDimension;
    int mNumSamples;
    Real const* mSampleData;

    // The fitted B-spline curve, open and with uniform knots.
    int mDegree;
    int mNumControls;
    std::vector<Real> mControlData;
    BasisFunction<Real> mBasis;
};

#include "GteBSplineCurveFit.inl"

}
