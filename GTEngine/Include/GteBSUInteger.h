// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteLogger.h"
#include <array>

// Uncomment this to allow testing for out-of-range indices to the
// operator[] functions.  Also test for 'size' in the default
// constructor to be no larger than N.
//#define GTE_ASSERT_ON_BSUINTEGER_OUT_OF_RANGE

namespace gte
{

template <size_t N>
class BSUInteger
{
public:
    // Construction.  The input 'size' must be no larger than N.
    BSUInteger(size_t size = 0);
    BSUInteger(BSUInteger const& number);
    BSUInteger(BSUInteger&& number);

    // Assignment.
    BSUInteger& operator=(BSUInteger const& number);
    BSUInteger& operator=(BSUInteger&& number);

    // Member access.
    inline size_t size() const;
    inline uint32_t& operator[](int32_t i);
    inline uint32_t const& operator[](int32_t i) const;
    inline uint32_t& back();
    inline uint32_t const& back() const;

private:
    size_t mSize;
    std::array<uint32_t, N> mElements;
};

#include "GteBSUInteger.inl"

}
