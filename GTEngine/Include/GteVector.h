// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/08/30)

#pragma once

#include <array>
#include <cmath>

namespace gte
{

template <int N, typename Real>
class Vector
{
public:
    // The dimension of the vector.
    enum { DIMENSION = N };

    // The default constructor, copy constructor, destructor, and assignment
    // operator are generated by the compiler.  The default constructor does
    // not initialize its data.  The default destructor is not virtual.  This
    // avoids the extra storage needed for the virtual function table, and it
    // allows for derived classes with specific dimensions.  The derived
    // classes add constructors for N elements.  The base class destruction
    // has no side effects, so polymorphic destruction of an object behaves
    // correctly.

    // Create special vectors.
    void MakeZero();  // All components are 0.
    void MakeUnit(int d);  // Component d is 1, all others are zero.

    // Member access.  The first operator[] returns a const reference rather
    // than a Real value.  This supports writing via standard file operations
    // that require a const pointer to data.
    inline int GetSize() const;  // returns N
    inline Real const& operator[](int i) const;
    inline Real& operator[](int i);

    // Comparisons for sorted containers and geometric ordering.
    bool operator==(Vector const& vec) const;
    bool operator!=(Vector const& vec) const;
    bool operator< (Vector const& vec) const;
    bool operator<=(Vector const& vec) const;
    bool operator> (Vector const& vec) const;
    bool operator>=(Vector const& vec) const;

    // Special vectors.
    static Vector Zero();
    static Vector Unit(int d);

protected:
    // This data structure takes advantage of the built-in operator[],
    // range checking, and visualizers in MSVS.
    std::array<Real,N> mTuple;
};

// Unary operations.
template <int N, typename Real>
Vector<N,Real> operator+(Vector<N,Real> const& v);

template <int N, typename Real>
Vector<N,Real> operator-(Vector<N,Real> const& v);

// Linear-algebraic operations.
template <int N, typename Real>
Vector<N,Real> operator+(Vector<N,Real> const& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Vector<N,Real> operator-(Vector<N,Real> const& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Vector<N,Real> operator*(Vector<N,Real> const& v, Real scalar);

template <int N, typename Real>
Vector<N,Real> operator*(Real scalar, Vector<N,Real> const& v);

template <int N, typename Real>
Vector<N,Real> operator/(Vector<N,Real> const& v, Real scalar);

template <int N, typename Real>
Vector<N,Real>& operator+=(Vector<N,Real>& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Vector<N,Real>& operator-=(Vector<N,Real>& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Vector<N,Real>& operator*=(Vector<N,Real>& v, Real scalar);

template <int N, typename Real>
Vector<N,Real>& operator/=(Vector<N,Real>& v, Real scalar);

// Componentwise algebraic operations.
template <int N, typename Real>
Vector<N,Real> operator*(Vector<N,Real> const& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Vector<N,Real> operator/(Vector<N,Real> const& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Vector<N,Real>& operator*=(Vector<N,Real>& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Vector<N,Real>& operator/=(Vector<N,Real>& v0, Vector<N,Real> const& v1);

// Geometric operations.
template <int N, typename Real>
Real Dot(Vector<N,Real> const& v0, Vector<N,Real> const& v1);

template <int N, typename Real>
Real Length(Vector<N,Real> const& v);

template <int N, typename Real>
Real LengthRobust(Vector<N,Real> const& v);

template <int N, typename Real>
Real Normalize(Vector<N,Real>& v);

template <int N, typename Real>
Real NormalizeRobust(Vector<N,Real>& v);

// Gram-Schmidt orthonormalization to generate orthonormal vectors from the
// linearly independent inputs.  The function returns the smallest length of
// the unnormalized vectors computed during the process.  If this value is
// nearly zero, it is possible that the inputs are linearly dependent (within
// numerical round-off errors).  On input, 1 <= numElements <= N and v[0]
// through v[numElements-1] must be initialized.  On output, the vectors
// v[0] through v[numElements-1] form an orthonormal set.
template <int N, typename Real>
Real Orthonormalize(int numElements, Vector<N,Real>* v);

// Compute the axis-aligned bounding box of the vectors.  The return value is
// 'true' iff the inputs are valid, in which case vmin and vmax have valid
// values.
template <int N, typename Real>
bool ComputeExtremes(int numVectors, Vector<N,Real> const* v,
    Vector<N,Real>& vmin, Vector<N,Real>& vmax);

// Lift n-tuple v to homogeneous (n+1)-tuple (v,last).
template <int N, typename Real>
Vector<N + 1, Real> HLift(Vector<N, Real> const& v, Real last);

// Project homogeneous n-tuple v = (u,v[n-1]) to (n-1)-tuple u.
template <int N, typename Real>
Vector<N - 1, Real> HProject(Vector<N, Real> const& v);

// Lift n-tuple v = (w0,w1) to (n+1)-tuple u = (w0,u[inject],w1).  By
// inference, w0 is a (inject)-tuple [nonexistent when inject=0] and w1 is a
// (n-inject)-tuple [nonexistent when inject=n].
template <int N, typename Real>
Vector<N + 1, Real> Lift(Vector<N, Real> const& v, int inject, Real value);

// Project n-tuple v = (w0,v[reject],w1) to (n-1)-tuple u = (w0,w1).  By
// inference, w0 is a (reject)-tuple [nonexistent when reject=0] and w1 is a
// (n-1-reject)-tuple [nonexistent when reject=n-1].
template <int N, typename Real>
Vector<N - 1, Real> Project(Vector<N, Real> const& v, int reject);

#include "GteVector.inl"

}
