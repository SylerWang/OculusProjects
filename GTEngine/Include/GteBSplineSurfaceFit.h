// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.3.0 (2014/09/11)

#pragma once

#include "GteBasisFunction.h"
#include "GteBandedMatrix.h"
#include "GteVector3.h"

namespace gte
{

template <typename Real>
class BSplineSurfaceFit
{
public:
    // Construction.  The preconditions for calling the constructor are
    //   1 <= degree0 && degree0 + 1 < numControls0 <= numSamples0
    //   1 <= degree1 && degree1 + 1 < numControls1 <= numSamples1
    // The sample data must be in row-major order.  The control data is
    // also stored in row-major order.
    BSplineSurfaceFit(int degree0, int numControls0, int numSamples0,
        int degree1, int numControls1, int numSamples1,
        Vector3<Real> const* sampleData);

    // Access to input sample information.
    inline int GetNumSamples(int dimension) const;
    inline Vector3<Real> const* GetSampleData() const;

    // Access to output control point and surface information.
    inline int GetDegree(int dimension) const;
    inline int GetNumControls(int dimension) const;
    inline Vector3<Real> const* GetControlData() const;
    inline BasisFunction<Real> const& GetBasis(int dimension) const;

    // Evaluation of the B-spline surface.  It is defined for 0 <= u <= 1
    // and 0 <= v <= 1.  If a parameter value is outside [0,1], it is clamped
    // to [0,1].
    Vector3<Real> GetPosition(Real u, Real v) const;

private:
    // Input sample information.
    int mNumSamples[2];
    Vector3<Real> const* mSampleData;

    // The fitted B-spline surface, open and with uniform knots.
    int mDegree[2];
    int mNumControls[2];
    std::vector<Vector3<Real>> mControlData;
    BasisFunction<Real> mBasis[2];
};

#include "GteBSplineSurfaceFit.inl"

}
