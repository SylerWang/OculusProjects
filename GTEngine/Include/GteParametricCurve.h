// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/15)

#pragma once

#include "GteVector.h"
#include "GteIntegration.h"
#include "GteRootsBisection.h"
#include <algorithm>
#include <vector>

namespace gte
{

template <int N, typename Real>
class ParametricCurve
{
protected:
    // Abstract base class for a parameterized curve X(t), where t is the
    // parameter in [tmin,tmax] and X is an N-tuple position.  The first
    // constructor is for single-segment curves.  The second constructor is
    // for multiple-segment curves. The times must be strictly increasing.
    ParametricCurve(Real tmin, Real tmax);
    ParametricCurve(int numSegments, Real const* times);
public:
    virtual ~ParametricCurve();

    // To validate construction, create an object as shown:
    //     DerivedClassCurve<N, Real> curve(parameters);
    //     if (!curve) { <constructor failed, handle accordingly>; }
    inline operator bool() const;

    // Member access.
    inline Real GetTMin() const;
    inline Real GetTMax() const;
    inline int GetNumSegments() const;
    Real const* GetTimes() const;

    // Parameters used in GetLength(...), GetTotalLength(), and GetTime(...).
    void SetRombergOrder(int order);  // default = 8
    void SetMaxBisections(unsigned int maxBisections);  // default = 1024

    // Evaluation of the curve.  The function supports derivative calculation
    // through order 3; that is, maxOrder <= 3 is required.  If you want
    // only the position, pass in maxOrder of 0.  If you want the position and
    // first derivative, pass in maxOrder of 1, and so on.  The output
    // 'values' are ordered as: position, first derivative, second derivative,
    // third derivative.
    virtual void Evaluate(Real t, unsigned int maxOrder,
        Vector<N, Real> values[4]) const = 0;

    // Differential geometric quantities.
    Vector<N, Real> GetPosition(Real t) const;
    Vector<N, Real> GetTangent(Real t) const;
    Real GetSpeed(Real t) const;
    Real GetLength(Real t0, Real t1) const;
    Real GetTotalLength() const;

    // Inverse mapping of s = Length(t) given by t = Length^{-1}(s).  The
    // inverse length function is generally a function that cannot be written
    // in closed form, in which case it is not directly computable.  Instead,
    // we can specify s and estimate the root t for F(t) = Length(t) - s.  The
    // derivative is F'(t) = Speed(t) >= 0, so F(t) is nondecreasing.  To be
    // robust, we use bisection to locate the root, although it is possible to
    // use a hybrid of Newton's method and bisection.
    Real GetTime(Real length) const;

    // Compute a subset of curve points according to the specified attribute.
    // The input 'numPoints' must be two or larger.
    void SubdivideByTime(int numPoints, Vector<N, Real>* points) const;
    void SubdivideByLength(int numPoints, Vector<N, Real>* points) const;

protected:
    enum
    {
        DEFAULT_ROMBERG_ORDER = 8,
        DEFAULT_MAX_BISECTIONS = 1024
    };

    std::vector<Real> mTime;
    mutable std::vector<Real> mSegmentLength;
    mutable std::vector<Real> mAccumulatedLength;
    int mRombergOrder;
    unsigned int mMaxBisections;

    bool mConstructed;
};

#include "GteParametricCurve.inl"

}
