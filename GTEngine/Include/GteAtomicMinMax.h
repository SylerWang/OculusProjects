// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <algorithm>
#include <atomic>

// Implementations of atomic minimum and atomic maximum computations.  These
// are based on std::atomic_compare_exchange_strong.

namespace gte
{

template <typename T>
T AtomicMin(std::atomic<T>& v0, T const& v1);

template <typename T>
T AtomicMax(std::atomic<T>& v0, T const& v1);

#include "GteAtomicMinMax.inl"

}