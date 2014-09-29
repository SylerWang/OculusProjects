// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include <map>
#include <mutex>
#include <vector>

namespace gte
{

template <typename Key, typename Value>
class ThreadSafeMap
{
public:
    // Construction and destruction.
    virtual ~ThreadSafeMap();
    ThreadSafeMap();

    // All the operations are thread-safe.
    bool HasElements() const;
    bool Exists(Key key) const;
    void Insert(Key key, Value value);
    bool Remove(Key key, Value& value);
    void RemoveAll();
    bool Get(Key key, Value& value) const;
    void GatherAll(std::vector<Value>& values) const;

protected:
    std::map<Key,Value> mMap;
    mutable std::mutex mMutex;
};

#include "GteThreadSafeMap.inl"

}
