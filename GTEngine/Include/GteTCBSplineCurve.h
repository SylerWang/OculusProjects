// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/15)

#pragma once

#include "GteParametricCurve.h"
#include "GteLogger.h"

namespace gte
{

template <int N, typename Real>
class TCBSplineCurve : public ParametricCurve<N, Real>
{
public:
    // Construction and destruction.  The object copies the input arrays.
    // The number of points must be at least 2.  To validate construction,
    // create an object as shown:
    //     TCBSplineCurve<N, Real> curve(parameters);
    //     if (!curve) { <constructor failed, handle accordingly>; }
    virtual ~TCBSplineCurve();
    TCBSplineCurve(int numPoints, Vector<N, Real> const* points,
        Real const* times, Real const* tension, Real const* continuity,
        Real const* bias);

    // Member access.
    inline int GetNumPoints() const;
    inline Vector<N, Real> const* GetPoints() const;
    inline Real const* GetTensions() const;
    inline Real const* GetContinuities() const;
    inline Real const* GetBiases() const;

    // Evaluation of the curve.  The function supports derivative calculation
    // through order 3; that is, maxOrder <= 3 is required.  If you want
    // only the position, pass in maxOrder of 0.  If you want the position and
    // first derivative, pass in maxOrder of 1, and so on.  The output
    // 'values' are ordered as: position, first derivative, second derivative,
    // third derivative.
    virtual void Evaluate(Real t, unsigned int maxOrder,
        Vector<N, Real> values[4]) const;

protected:
    // Support for construction.
    void ComputePoly(int i0, int i1, int i2, int i3);

    // Determine the index i for which times[i] <= t < times[i+1].
    void GetKeyInfo(Real t, int& key, Real& dt) const;

    std::vector<Vector<N, Real>> mPoints;
    std::vector<Real> mTension, mContinuity, mBias;

    // Polynomial coefficients.  mA are the degree 0 coefficients,  mB are
    // the degree 1 coefficients, mC are the degree 2 coefficients, and mD
    // are the degree 3 coefficients.
    std::vector<Vector<N, Real>> mA, mB, mC, mD;
};

#include "GteTCBSplineCurve.inl"

}
