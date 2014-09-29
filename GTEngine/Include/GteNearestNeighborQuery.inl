// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <int N, typename Real, typename Site, int MaxNeighbors>
NearestNeighborQuery<N, Real, Site, MaxNeighbors>::NearestNeighborQuery(
    std::vector<Site> const& sites, int maxLeafSize, int maxLevel)
    :
    mMaxLeafSize(maxLeafSize),
    mMaxLevel(maxLevel),
    mSortedPoints(sites.size())
{
    int const numSites = static_cast<int>(sites.size());
    for (int i = 0; i < numSites; ++i)
    {
        mSortedPoints[i] = std::make_pair(sites[i].GetPosition(), i);
    }

    mNodes.push_back(Node());
    Build(numSites, 0, 0, 0);
}
//----------------------------------------------------------------------------
template <int N, typename Real, typename Site, int MaxNeighbors> inline
int NearestNeighborQuery<N, Real, Site, MaxNeighbors>::GetMaxLeafSize() const
{
    return mMaxLeafSize;
}
//----------------------------------------------------------------------------
template <int N, typename Real, typename Site, int MaxNeighbors> inline
int NearestNeighborQuery<N, Real, Site, MaxNeighbors>::GetMaxLevel() const
{
    return mMaxLevel;
}
//----------------------------------------------------------------------------
template <int N, typename Real, typename Site, int MaxNeighbors>
int NearestNeighborQuery<N, Real, Site, MaxNeighbors>::FindNeighbors(
    Vector<N, Real> const& point, Real radius,
    std::array<int, MaxNeighbors>& neighbors) const
{
    Real sqrRadius = radius * radius;
    int numNeighbors = 0;
    std::array<int, MaxNeighbors + 1> localNeighbors;
    std::array<Real, MaxNeighbors + 1> neighborSqrLength;
    for (int i = 0; i <= MaxNeighbors; ++i)
    {
        localNeighbors[i] = -1;
        neighborSqrLength[i] = std::numeric_limits<Real>::max();
    }

    // The kd-tree construction is recursive, simulated here by using a stack.
    // The maximum depth is limited to 32, because the number of sites is
    // limited to 2^{32} (the number of 32-bit integer indices).
    std::array<int, 32> stack;
    int top = 0;
    stack[0] = 0;

    while (top >= 0)
    {
        Node node = mNodes[stack[top--]];

        if (node.siteOffset != -1)
        {
            for (int i = 0, j = node.siteOffset; i < node.numSites; ++i, ++j)
            {
                Vector<N, Real> diff = mSortedPoints[j].first - point;
                Real sqrLength = Dot(diff, diff);
                if (sqrLength <= sqrRadius)
                {
                    // Maintain the nearest neighbors.
                    int k;
                    for (k = 0; k < numNeighbors; ++k)
                    {
                        if (sqrLength <= neighborSqrLength[k])
                        {
                            for (int n = numNeighbors; n > k; --n)
                            {
                                localNeighbors[n] = localNeighbors[n-1];
                                neighborSqrLength[n] = neighborSqrLength[n-1];
                            }
                            break;
                        }
                    }
                    if (k < MaxNeighbors)
                    {
                        localNeighbors[k] = mSortedPoints[j].second;
                        neighborSqrLength[k] = sqrLength;
                    }
                    if (numNeighbors < MaxNeighbors)
                    {
                        ++numNeighbors;
                    }
                }
            }
        }

        if (node.left != -1 && point[node.axis] - radius <= node.split)
        {
            stack[++top] = node.left;
        }

        if (node.right != -1 && point[node.axis] + radius >= node.split)
        {
            stack[++top] = node.right;
        }
    }

    for (int i = 0; i < numNeighbors; ++i)
    {
        neighbors[i] = localNeighbors[i];
    }

    return numNeighbors;
}
//----------------------------------------------------------------------------
template <int N, typename Real, typename Site, int MaxNeighbors>
void NearestNeighborQuery<N, Real, Site, MaxNeighbors>::Build(int numSites,
    int siteOffset, int nodeIndex, int level)
{
    LogAssert(siteOffset != -1, "Invalid site offset.");
    LogAssert(nodeIndex != -1, "Invalid node index.");
    LogAssert(numSites > 0, "Empty point list.");

    Node& node = mNodes[nodeIndex];
    node.numSites = numSites;

    if (numSites > mMaxLeafSize && level <= mMaxLevel)
    {
        int halfNumSites = numSites/2;

        // The point set is too large for a leaf node, so split it at the
        // median.  The O(m log m) sort is not needed; rather, we locate the
        // median using an order statistic construction that is expected
        // time O(m).
        int const axis = level % N;
        SortFunctor sorter(axis);
        auto begin = mSortedPoints.begin() + siteOffset;
        auto mid = mSortedPoints.begin() + siteOffset + halfNumSites;
        auto end = mSortedPoints.begin() + siteOffset + numSites;
        std::nth_element(begin, mid, end, sorter);

        // Get the median position.
        node.split = mSortedPoints[siteOffset + halfNumSites].first[axis];
        node.axis = axis;
        node.siteOffset = -1;
        
        // Apply a divide-and-conquer step.
        int left = (int)mNodes.size(), right = left + 1;
        node.left = left;
        node.right = right;
        mNodes.push_back(Node());
        mNodes.push_back(Node());

        int nextLevel = level + 1;
        Build(halfNumSites, siteOffset, left, nextLevel);
        Build(numSites - halfNumSites, siteOffset + halfNumSites, right,
            nextLevel);
    }
    else
    {
        // The number of points is small enough, so make this node a leaf.
        node.split = std::numeric_limits<Real>::max();
        node.axis = -1;
        node.siteOffset = siteOffset;
        node.left = -1;
        node.right = -1;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real, typename Site, int MaxNeighbors> inline
NearestNeighborQuery<N, Real, Site, MaxNeighbors>::SortFunctor::SortFunctor(
    int axis)
    :
    mAxis(axis)
{ 
}
//----------------------------------------------------------------------------
template <int N, typename Real, typename Site, int MaxNeighbors> inline
bool NearestNeighborQuery<N, Real, Site, MaxNeighbors>::SortFunctor::
operator()(SortedPoint const& sorted0, SortedPoint const& sorted1) const
{
    return sorted0.first[mAxis] < sorted1.first[mAxis];
}
//----------------------------------------------------------------------------
