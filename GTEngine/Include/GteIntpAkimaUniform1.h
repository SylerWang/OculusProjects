// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

#include "GteIntpAkima1.h"

namespace gte
{

template <typename Real>
class IntpAkimaUniform1 : public IntpAkima1<Real>
{
public:
    // Construction and destruction.  The interpolator is for uniformly
    // spaced x-values.
    virtual ~IntpAkimaUniform1();
    IntpAkimaUniform1(int quantity, Real xMin, Real xSpacing, Real const* F);

    // Member access.
    inline virtual Real GetXMin() const;
    inline virtual Real GetXMax() const;
    inline Real GetXSpacing() const;

protected:
    virtual void Lookup(Real x, int& index, Real& dx) const;

    Real mXMin, mXMax, mXSpacing;
};

#include "GteIntpAkimaUniform1.inl"

}
