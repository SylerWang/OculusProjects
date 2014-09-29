// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/16)

#pragma once

#include "GteParametricCurve.h"
#include "GteVector2.h"
#include "GteVector3.h"

namespace gte
{

template <typename Real>
class FrenetFrame2
{
public:
    // Construction.  The curve must persist as long as the FrenetFrame2
    // object does.
    FrenetFrame2(ParametricCurve<2, Real> const& curve);

    // The normal is perpendicular to the tangent, rotated clockwise by
    // pi/2 radians.
    void operator()(Real t, Vector2<Real>& position, Vector2<Real>& tangent,
        Vector2<Real>& normal) const;

    Real GetCurvature(Real t) const;

private:
    ParametricCurve<2, Real> const* mCurve;
};


template <typename Real>
class FrenetFrame3
{
public:
    // Construction.  The curve must persist as long as the FrenetFrame3
    // object does.
    FrenetFrame3(ParametricCurve<3, Real> const& curve);

    // The binormal is Cross(tangent, normal).
    void operator()(Real t, Vector3<Real>& position, Vector3<Real>& tangent,
        Vector3<Real>& normal, Vector3<Real>& binormal) const;

    Real GetCurvature(Real t) const;
    Real GetTorsion(Real t) const;

private:
    ParametricCurve<3, Real> const* mCurve;
};

#include "GteFrenetFrame.inl"

}
