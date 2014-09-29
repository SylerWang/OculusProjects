// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteLogger.h"
#include <cassert>
#include <cmath>
#include <vector>

// Uncomment this to test for size mismatches that are wrapped by
// GVector::ValidateSize.  If the test is not enabled, the compiler should
// not generate any code for ValidateSize in a release build.
//#define GTE_ASSERT_ON_GVECTOR_SIZE_MISMATCH

namespace gte
{

template <typename Real>
class GVector
{
public:
    // Construction and destruction.  The components of the vector are
    // undefined for GVector(int).
    ~GVector();
    GVector(int size = 0);
    GVector(GVector const& vec);

    // Create special vectors.
    void MakeZero();  // All components are 0.
    void MakeUnit(int d);  // Component d is 1, all others are zero.

    // Assignment.
    GVector& operator=(GVector const& vec);

    // Coordinate access.  SetSize(int) initializes the vector to zero.
    void SetSize(int size);
    inline int GetSize() const;
    inline Real const& operator[](int i) const;
    inline Real& operator[](int i);

    // Comparison (for use by STL containers).
    bool operator==(GVector const& vec) const;
    bool operator!=(GVector const& vec) const;
    bool operator< (GVector const& vec) const;
    bool operator<=(GVector const& vec) const;
    bool operator> (GVector const& vec) const;
    bool operator>=(GVector const& vec) const;

    // Special vectors.
    static GVector Zero(int size);
    static GVector Unit(int size, int d);

protected:
    // This data structure takes advantage of the built-in operator[],
    // range checking, and visualizers in MSVS.
    std::vector<Real> mTuple;

public:
    // Test for equal sizes.  When the conditional define used in this
    // function is not active, the compiler should optimize this to a
    // no-operation.
    inline void ValidateSize(GVector const& vec) const;
};

// Unary operations.
template <typename Real>
GVector<Real> operator+(GVector<Real> const& v);

template <typename Real>
GVector<Real> operator-(GVector<Real> const& v);

// Linear-algebraic operations.
template <typename Real>
GVector<Real> operator+(GVector<Real> const& v0, GVector<Real> const& v1);

template <typename Real>
GVector<Real> operator-(GVector<Real> const& v0, GVector<Real> const& v1);

template <typename Real>
GVector<Real> operator*(GVector<Real> const& v, Real scalar);

template <typename Real>
GVector<Real> operator*(Real scalar, GVector<Real> const& v);

template <typename Real>
GVector<Real> operator/(GVector<Real> const& v, Real scalar);

template <typename Real>
GVector<Real>& operator+=(GVector<Real>& v0, GVector<Real> const& v1);

template <typename Real>
GVector<Real>& operator-=(GVector<Real>& v0, GVector<Real> const& v1);

template <typename Real>
GVector<Real>& operator*=(GVector<Real>& v, Real scalar);

template <typename Real>
GVector<Real>& operator/=(GVector<Real>& v, Real scalar);

// Geometric operations.
template <typename Real>
Real Dot(GVector<Real> const& v0, GVector<Real> const& v1);

template <typename Real>
Real Length(GVector<Real> const& v);

template <typename Real>
Real LengthRobust(GVector<Real> const& v);

template <typename Real>
Real Normalize(GVector<Real>& v);

template <typename Real>
Real NormalizeRobust(GVector<Real>& v);

// Gram-Schmidt orthonormalization to generate orthonormal vectors from the
// linearly independent inputs.  The function returns the smallest length of
// the unnormalized vectors computed during the process.  If this value is
// nearly zero, it is possible that the inputs are linearly dependent (within
// numerical round-off errors).  On input, 1 <= numElements <= N and v[0]
// through v[numElements-1] must be initialized.  On output, the vectors
// v[0] through v[numElements-1] form an orthonormal set.
template <typename Real>
Real Orthonormalize(int numElements, GVector<Real>* v);

// Compute the axis-aligned bounding box of the vectors.  The return value is
// 'true' iff the inputs are valid, in which case vmin and vmax have valid
// values.
template <typename Real>
bool ComputeExtremes(int numVectors, GVector<Real> const* v,
    GVector<Real>& vmin, GVector<Real>& vmax);

#include "GteGVector.inl"

}
