// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/08/19)

#pragma once

#include <cstddef>

// The allocation and deallocation functions minimize the number of new and
// delete calls to represent an N-dimensional array.  If 'data' is the
// returned pointer, the actual T objects are stored in contiguous arrays
// pointed to by data[0] for Allocate2, data[0][0] for Allocate3, and
// data[0][0][0] for Allocate4.  The contiguous arrays are dynamically
// allocated, thus owned in a sense by 'data'.  The DeallocateN functions
// will delete all memory allocate in the AllocateN functions.
//
// Sometimes it is convenient to take an already existing contiguous array
// of T objects and wrap it for multidimensional access.  In this case, you
// must provide the contiguous array as input to AllocateMapN and pair that
// call with a DeallocateMapN (if you want to retain ownership of the T
// objects) or DeallocateN (if you want to transfer ownership of the T
// objects).  It is your responsibility to ensure that the 'objects' arrays
// have the correct number of elements.

namespace gte
{

// For 2D arrays:  data[bound1][bound0]
template <typename T>
T** Allocate2(size_t const bound0, size_t const bound1);

template <typename T>
T** AllocateMap2(size_t const bound0, size_t const bound1, T* objects);

// For 3D arrays:  data[bound2][bound1][bound0]
template <typename T>
T*** Allocate3(size_t const bound0, size_t const bound1, size_t const bound2);

template <typename T>
T*** AllocateMap3(size_t const bound0, size_t const bound1,
    size_t const bound2, T* objects);

// For 4D arrays:  data[bound3][bound2][bound1][bound0]
template <typename T>
T**** Allocate4(size_t const bound0, size_t const bound1, size_t const bound2,
    size_t const bound3);

template <typename T>
T**** AllocateMap4(size_t const bound0, size_t const bound1,
    size_t const bound2, size_t const bound3, T* objects);

// For 2D arrays:  data[bound1][bound0]
template <typename T>
void Deallocate2(T**& data);

template <typename T>
void DeallocateMap2(T**& data);

// For 3D arrays:  data[bound2][bound1][bound0]
template <typename T>
void Deallocate3(T***& data);

template <typename T>
void DeallocateMap3(T***& data);

// For 4D arrays:  data[bound3][bound2][bound1][bound0]
template <typename T>
void Deallocate4(T****& data);

template <typename T>
void DeallocateMap4(T****& data);

#include "GteMemory.inl"

}
