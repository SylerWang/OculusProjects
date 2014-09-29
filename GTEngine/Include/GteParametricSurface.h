// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/18)

#pragma once

#include "GteVector.h"

namespace gte
{

template <int N, typename Real>
class ParametricSurface
{
protected:
    // Abstract base class for a parameterized surface X(u,v).  The parametric
    // domain is either rectangular or triangular.  Valid (u,v) values for a
    // rectangular domain satisfy
    //   umin <= u <= umax,  vmin <= v <= vmax
    // and valid (u,v) values for a triangular domain satisfy
    //   umin <= u <= umax,  vmin <= v <= vmax,
    //   (vmax-vmin)*(u-umin)+(umax-umin)*(v-vmax) <= 0
    ParametricSurface(Real umin, Real umax, Real vmin, Real vmax,
        bool rectangular);
public:
    virtual ~ParametricSurface();

    // To validate construction, create an object as shown:
    //     DerivedClassSurface<Real> surface(parameters);
    //     if (!surface) { <constructor failed, handle accordingly>; }
    inline operator bool() const;

    // Member access.
    inline Real GetUMin() const;
    inline Real GetUMax() const;
    inline Real GetVMin() const;
    inline Real GetVMax() const;
    inline bool IsRectangular() const;

    // Evaluation of the surface.  The function supports derivative
    // calculation through order 2; that is, maxOrder <= 2 is required.  If
    // you want only the position, pass in maxOrder of 0.  If you want the
    // position and first-order derivatives, pass in maxOrder of 1, and so on.
    // The output 'values' are ordered as: position X; first-order derivatives
    // dX/du, dX/dv; second-order derivatives d2X/du2, d2X/dudv, d2X/dv2.
    virtual void Evaluate(Real u, Real v, unsigned int maxOrder,
        Vector<N, Real> values[6]) const = 0;

    // Differential geometric quantities.
    Vector<N, Real> GetPosition(Real u, Real v) const;
    Vector<N, Real> GetUTangent(Real u, Real v) const;
    Vector<N, Real> GetVTangent(Real u, Real v) const;

protected:
    Real mUMin, mUMax, mVMin, mVMax;
    bool mRectangular;
    bool mConstructed;
};

#include "GteParametricSurface.inl"

}
