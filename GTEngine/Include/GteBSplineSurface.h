// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/18)

#pragma once

#include "GteParametricSurface.h"
#include "GteBasisFunction.h"
#include "GteVector.h"

namespace gte
{

template <int N, typename Real>
class BSplineSurface : public ParametricSurface<N, Real>
{
public:
    // Construction and destruction.  This object makes copies of the input
    // arrays.  The input 'controls' must be stored in row-major order,
    // control[i0 + numControls0*i1].  As a 2D array, this corresponds to
    // control2D[i1][i0].  To validate construction, create an object as
    // shown:
    //     BSplineSurface<N,Real> surface(parameters);
    //     if (!surface) { <constructor failed, handle accordingly>; }
    virtual ~BSplineSurface();
    BSplineSurface(BasisFunctionInput<Real> const input[2],
        Vector<N, Real> const* controls);

    // Member access.  The index 'dim' must be in {0,1}.
    inline int GetNumControls(int dim) const;
    inline Vector<N, Real> const* GetControls() const;
    inline BasisFunction<Real> const& GetBasisFunction(int dim) const;
    void SetControl(int i0, int i1, Vector<N, Real> const& control);
    Vector<N, Real> const& GetControl(int i0, int i1) const;

    // Evaluation of the surface.  The function supports derivative
    // calculation through order 2; that is, maxOrder <= 2 is required.  If
    // you want only the position, pass in maxOrder of 0.  If you want the
    // position and first-order derivatives, pass in maxOrder of 1, and so on.
    // The output 'values' are ordered as: position X; first-order derivatives
    // dX/du, dX/dv; second-order derivatives d2X/du2, d2X/dudv, d2X/dv2.
    virtual void Evaluate(Real u, Real v, unsigned int maxOrder,
        Vector<N, Real> values[6]) const;

private:
    // Support for Evaluate(...).
    Vector<N, Real> Compute(unsigned int uOrder, unsigned int vOrder,
        int iumin, int iumax, int ivmin, int ivmax) const;

    std::array<BasisFunction<Real>, 2> mBasisFunction;
    std::array<int, 2> mNumControls;
    std::vector<Vector<N, Real>> mControls;
};

#include "GteBSplineSurface.inl"

}
