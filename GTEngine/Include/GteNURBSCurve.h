// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/15)

#pragma once

#include "GteParametricCurve.h"
#include "GteBasisFunction.h"

namespace gte
{

template <int N, typename Real>
class NURBSCurve : public ParametricCurve<N, Real>
{
public:
    // Construction and destruction.  This object makes copies of the input
    // arrays.  The domain is t in [t[d],t[n]], where t[d] and t[n] are knots
    // with d the degree and n the number of control points.  To validate
    // construction, create an object as shown:
    //     NURBSCurve<N, Real> curve(parameters);
    //     if (!curve) { <constructor failed, handle accordingly>; }
    virtual ~NURBSCurve();
    NURBSCurve(BasisFunctionInput<Real> const& input,
        Vector<N, Real> const* controls, Real const* weights);

    // Member access.
    inline int GetNumControls() const;
    inline Vector<N, Real> const* GetControls() const;
    inline Real const* GetWeights() const;
    inline BasisFunction<Real> const& GetBasisFunction() const;
    void SetControl(int i, Vector<N, Real> const& control);
    Vector<N, Real> const& GetControl(int i) const;
    void SetWeight(int i, Real weight);
    Real const& GetWeight(int i) const;

    // Evaluation of the curve.  The function supports derivative calculation
    // through order 3; that is, maxOrder <= 3 is required.  If you want
    // only the position, pass in maxOrder of 0.  If you want the position and
    // first derivative, pass in maxOrder of 1, and so on.  The output
    // 'values' are ordered as: position, first derivative, second derivative,
    // third derivative.
    virtual void Evaluate(Real t, unsigned int maxOrder,
        Vector<N, Real> values[4]) const;

private:
    // Support for Evaluate(...).
    void Compute(unsigned int order, int imin, int imax, Vector<N, Real>& X,
        Real& w) const;

    BasisFunction<Real> mBasisFunction;
    std::vector<Vector<N, Real>> mControls;
    std::vector<Real> mWeights;
};

#include "GteNURBSCurve.inl"

}
