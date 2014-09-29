// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteOdeSolver.h"
#include "GteGMatrix.h"

// The TVector template parameter allows you to create solvers with
// Vector<N,Real> when the dimension N is known at compile time or
// GVector<Real> when the dimension N is known at run time.  Both classes
// have 'int GetSize() const' that allow OdeSolver-derived classes to query
// for the dimension.  The TMatrix parameter must be either Matrix<N,N,Real>
// or GMatrix<Real> accordingly.
//
// The function F(t,x) has input t, a scalar, and input x, an N-vector.
// The first derivative matrix with respect to x is DF(t,x), an
// N-by-N matrix.  Entry DF(r,c) is the derivative of F[r] with
// respect to x[c].

namespace gte
{

template <typename Real, typename TVector, typename TMatrix>
class OdeImplicitEuler : public OdeSolver<Real,TVector>
{
public:
    // Construction and destruction.
    virtual ~OdeImplicitEuler();
    OdeImplicitEuler(Real tDelta,
        std::function<TVector(Real, TVector const&)> const& F,
        std::function<TMatrix(Real, TVector const&)> const& DF);

    // Estimate x(t + tDelta) from x(t) using dx/dt = F(t,x).  You may allow
    // xIn and xOut to be the same object.
    virtual void Update(Real tIn, TVector const& xIn, Real& tOut,
        TVector& xOut);

private:
    std::function<TMatrix(Real, TVector const&)> mDerivativeFunction;
};

#include "GteOdeImplicitEuler.inl"

}
