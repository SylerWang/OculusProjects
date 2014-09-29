// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename T>
T AtomicMin(std::atomic<T>& v0, T const& v1)
{
    T vInitial, vMin;
    do
    {
        vInitial = v0;
        vMin = std::min(vInitial, v1);
    }
    while (!std::atomic_compare_exchange_strong(&v0, &vInitial, vMin));
    return vInitial;
}
//----------------------------------------------------------------------------
template <typename T>
T AtomicMax(std::atomic<T>& v0, T const& v1)
{
    T vInitial, vMax;
    do
    {
        vInitial = v0;
        vMax = std::max(vInitial, v1);
    }
    while (!std::atomic_compare_exchange_strong(&v0, &vInitial, vMax));
    return vInitial;
}
//----------------------------------------------------------------------------
