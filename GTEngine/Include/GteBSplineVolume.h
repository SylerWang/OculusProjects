// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteBasisFunction.h"
#include "GteVector.h"

namespace gte
{

template <int N, typename Real>
class BSplineVolume
{
public:
    // Construction and destruction.  This object makes copies of the input
    // arrays.  The input 'controls' must be stored in lexicographical order,
    // control[i0 + numControls0*(i1 + numControls1*i2)].  As a 3D array,
    // this corresponds to control3D[i2][i1][i0].
    ~BSplineVolume();
    BSplineVolume(BasisFunctionInput<Real> const input[3],
        Vector<N, Real> const* controls);

    // To validate construction, create an object as shown:
    //     BSplineVolume<N, Real> volume(parameters);
    //     if (!volume) { <constructor failed, handle accordingly>; }
    inline operator bool() const;

    // Member access.  The index 'dim' must be in {0,1,2}.
    inline int GetNumControls(int dim) const;
    inline Vector<N, Real> const* GetControls() const;
    inline BasisFunction<Real> const& GetBasisFunction(int dim) const;
    inline Real GetMinDomain(int dim) const;
    inline Real GetMaxDomain(int dim) const;

    // Evaluation of the volume.  The function supports derivative
    // calculation through order 2; that is, maxOrder <= 2 is required.  If
    // you want only the position, pass in maxOrder of 0.  If you want the
    // position and first-order derivatives, pass in maxOrder of 1, and so on.
    // The output 'values' are ordered as: position X; first-order derivatives
    // dX/du, dX/dv, dX/dw; second-order derivatives d2X/du2, d2X/dv2,
    // d2X/dw2, d2X/dudv, d2X/dudw, d2X/dvdw.
    void Evaluate(Real u, Real v, Real w, unsigned int maxOrder,
        Vector<N, Real> values[10]) const;

private:
    // Support for Evaluate(...).
    Vector<N, Real> Compute(unsigned int uOrder, unsigned int vOrder,
        unsigned int wOrder, int iumin, int iumax, int ivmin, int ivmax,
        int iwmin, int iwmax) const;

    std::array<BasisFunction<Real>, 3> mBasisFunction;
    std::array<int, 3> mNumControls;
    std::vector<Vector<N, Real>> mControls;
    bool mConstructed;
};

#include "GteBSplineVolume.inl"

}
