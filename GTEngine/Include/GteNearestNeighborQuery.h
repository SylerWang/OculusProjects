// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

#include "GteVector.h"
#include "GteLogger.h"
#include <algorithm>
#include <limits>
#include <vector>

namespace gte
{

// Use a kd-tree for sorting used in a query for finding nearest neighbors
// of a point in a space of the specified dimension N.  The split order is
// always 0,1,2,...,N-1.  The number of sites at a leaf node is controlled
// by 'maxLeafSize' and the maximum level of the tree is controlled by
// 'maxLevels'.  The points are of type Vector<N,Real>.  The 'Site' is a
// structure of information that minimally implements the function
// 'Vector<N,Real> GetPosition () const'.  The Site template parameter
// allows the query to be applied even when it has more local information
// than just point location.
template <int N, typename Real, typename Site, int MaxNeighbors>
class NearestNeighborQuery
{
public:
    // Construction.
    NearestNeighborQuery(std::vector<Site> const& sites, int maxLeafSize,
        int maxLevel);

    // Member access.
    inline int GetMaxLeafSize () const;
    inline int GetMaxLevel () const;

    // Compute up to MaxNeighbor nearest neighbors within the specified radius
    // of the point.  The returned integer is the number of neighbors found,
    // possibly zero.  The neighbors array stores indices into the array
    // passed to the constructor.
    int FindNeighbors(Vector<N,Real> const& point, Real radius,
        std::array<int, MaxNeighbors>& neighbors) const;

private:
    typedef std::pair<Vector<N, Real>, int> SortedPoint;

    struct Node
    {
        Real split;
        int axis;
        int numSites;
        int siteOffset;
        int left;
        int right;
    };

    // Populate the node so that it contains the points split along the
    // coordinate axes.
    void Build(int numSites, int siteOffset, int nodeIndex, int level);

    // Helper class for sorting along axes.
    class SortFunctor
    {
    public:
        inline SortFunctor(int axis);
        inline bool operator()(SortedPoint const& sorted0,
            SortedPoint const& sorted1) const;
   private:
        int mAxis;
    };

    int mMaxLeafSize;
    int mMaxLevel;
    std::vector<SortedPoint> mSortedPoints;
    std::vector<Node> mNodes;
};

#include "GteNearestNeighborQuery.inl"

}
