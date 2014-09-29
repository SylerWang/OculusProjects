// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/15)

#pragma once

#include "GteParametricCurve.h"
#include "GteLogger.h"
#include "GteMemory.h"

namespace gte
{

template <int N, typename Real>
class BezierCurve : public ParametricCurve<N, Real>
{
public:
    // Construction and destruction.  The number of control points must be
    // degree + 1.  This object copies the input array.  The domain is t
    // in [0,1].  To validate construction, create an object as shown:
    //     BezierCurve<N, Real> curve(parameters);
    //     if (!curve) { <constructor failed, handle accordingly>; }
    virtual ~BezierCurve();
    BezierCurve(int degree, Vector<N, Real> const* controls);

    // Member access.
    inline int GetDegree() const;
    inline int GetNumControls() const;
    inline Vector<N, Real> const* GetControls() const;

    // Evaluation of the curve.  The function supports derivative calculation
    // through order 3; that is, maxOrder <= 3 is required.  If you want
    // only the position, pass in maxOrder of 0.  If you want the position and
    // first derivative, pass in maxOrder of 1, and so on.  The output
    // 'values' are ordered as: position, first derivative, second derivative,
    // third derivative.
    virtual void Evaluate(Real t, unsigned int maxOrder,
        Vector<N, Real> values[4]) const;

protected:
    // Support for Evaluate(...).
    Vector<N, Real> Compute(Real t, Real omt, int order) const;

    int mDegree, mNumControls;
    std::vector<Vector<N, Real>> mControls[4];
    Real** mChoose;
};

#include "GteBezierCurve.inl"

}
