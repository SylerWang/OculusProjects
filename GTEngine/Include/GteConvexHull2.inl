// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
ConvexHull2<InputType, ComputeType>::ConvexHull2()
    :
    mEpsilon((InputType)0),
    mDimension(0),
    mLine(Vector2<InputType>::Zero(), Vector2<InputType>::Zero()),
    mNumPoints(0),
    mNumUniquePoints(0),
    mPoints(nullptr)
{
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType>
bool ConvexHull2<InputType, ComputeType>::operator()(int numPoints,
    Vector2<InputType> const* points, InputType epsilon)
{
    mEpsilon = std::max(epsilon, (InputType)0);
    mDimension = 0;
    mLine.origin = Vector2<InputType>::Zero();
    mLine.direction = Vector2<InputType>::Zero();
    mNumPoints = numPoints;
    mNumUniquePoints = 0;
    mPoints = points;
    mMerged.clear();
    mHull.clear();

    int i, j;
    if (mNumPoints < 3)
    {
        // ConvexHull2 should be called with at least three points.
        return false;
    }

    IntrinsicsVector2<InputType> info(mNumPoints, mPoints, mEpsilon);
    if (info.dimension == 0)
    {
        // mDimension is 0
        return false;
    }

    if (info.dimension == 1)
    {
        // The set is (nearly) collinear.
        mDimension = 1;
        mLine = Line2<InputType>(info.origin, info.direction[0]);
        return false;
    }

    mDimension = 2;

    // Compute the points for the queries.
    mComputePoints.resize(mNumPoints);
    mQuery.Set(mNumPoints, &mComputePoints[0]);
    for (i = 0; i < mNumPoints; ++i)
    {
        for (j = 0; j < 2; ++j)
        {
            mComputePoints[i][j] = points[i][j];
        }
    }

    // Sort the points.
    mHull.resize(mNumPoints);
    for (int i = 0; i < mNumPoints; ++i)
    {
        mHull[i] = i;
    }
    std::sort(mHull.begin(), mHull.end(),
        [points](int i0, int i1)
        {
            if (points[i0][0] < points[i1][0]) { return true; }
            if (points[i0][0] > points[i1][0]) { return false; }
            return points[i0][1] < points[i1][1];
        }
    );

    // Remove duplicates.
    auto newEnd = std::unique(mHull.begin(), mHull.end(),
        [points](int i0, int i1)
        {
            return points[i0] == points[i1];
        }
    );
    mHull.erase(newEnd, mHull.end());
    mNumUniquePoints = static_cast<int>(mHull.size());

    // Use a divide-and-conquer algorithm.  The merge step computes the
    // convex hull of two convex polygons.
    mMerged.resize(mNumUniquePoints);
    int i0 = 0, i1 = mNumUniquePoints - 1;
    GetHull(i0, i1);
    mHull.resize(i1 - i0 + 1);
    return true;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
InputType ConvexHull2<InputType, ComputeType>::GetEpsilon() const
{
    return mEpsilon;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int ConvexHull2<InputType, ComputeType>::GetDimension() const
{
    return mDimension;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Line2<InputType> const& ConvexHull2<InputType, ComputeType>::GetLine() const
{
    return mLine;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int ConvexHull2<InputType, ComputeType>::GetNumPoints() const
{
    return mNumPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
int ConvexHull2<InputType, ComputeType>::GetNumUniquePoints() const
{
    return mNumUniquePoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
Vector2<InputType> const* ConvexHull2<InputType, ComputeType>::GetPoints()
    const
{
    return mPoints;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
PrimalQuery2<ComputeType> const&
ConvexHull2<InputType, ComputeType>::GetQuery() const
{
    return mQuery;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
std::vector<int> const& ConvexHull2<InputType, ComputeType>::GetHull() const
{
    return mHull;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
void ConvexHull2<InputType, ComputeType>::GetHull(int& i0, int& i1)
{
    int numVertices = i1 - i0 + 1;
    if (numVertices > 1)
    {
        // Compute the middle index of input range.
        int mid = (i0 + i1)/2;

        // Compute the hull of subsets (mid-i0+1 >= i1-mid).
        int j0 = i0, j1 = mid, j2 = mid + 1, j3 = i1;
        GetHull(j0, j1);
        GetHull(j2, j3);

        // Merge the convex hulls into a single convex hull.
        Merge(j0, j1, j2, j3, i0, i1);
    }
    // else: The convex hull is a single point.
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
void ConvexHull2<InputType, ComputeType>::Merge(int j0, int j1, int j2,
    int j3, int& i0, int& i1)
{
    // Subhull0 is to the left of subhull1 because of the initial sorting of
    // the points by x-components.  We need to find two mutually visible
    // points, one on the left subhull and one on the right subhull.
    int size0 = j1 - j0 + 1;
    int size1 = j3 - j2 + 1;

    int i;
    Vector2<ComputeType> p;

    // Find the right-most point of the left subhull.
    Vector2<ComputeType> pmax0 = mComputePoints[mHull[j0]];
    int imax0 = j0;
    for (i = j0 + 1; i <= j1; ++i)
    {
        p = mComputePoints[mHull[i]];
        if (pmax0 < p)
        {
            pmax0 = p;
            imax0 = i;
        }
    }

    // Find the left-most point of the right subhull.
    Vector2<ComputeType> pmin1 = mComputePoints[mHull[j2]];
    int imin1 = j2;
    for (i = j2 + 1; i <= j3; ++i)
    {
        p = mComputePoints[mHull[i]];
        if (p < pmin1)
        {
            pmin1 = p;
            imin1 = i;
        }
    }

    // Get the lower tangent to hulls (LL = lower-left, LR = lower-right).
    int iLL = imax0, iLR = imin1;
    GetTangent(j0, j1, j2, j3, iLL, iLR);

    // Get the upper tangent to hulls (UL = upper-left, UR = upper-right).
    int iUL = imax0, iUR = imin1;
    GetTangent(j2, j3, j0, j1, iUR, iUL);

    // Construct the counterclockwise-ordered merged-hull vertices.
    int k;
    int numMerged = 0;

    i = iUL;
    for (k = 0; k < size0; ++k)
    {
        mMerged[numMerged++] = mHull[i];
        if (i == iLL)
        {
            break;
        }
        i = (i < j1 ? i + 1 : j0);
    }
    LogAssert(k < size0, "Unexpected condition.");

    i = iLR;
    for (k = 0; k < size1; ++k)
    {
        mMerged[numMerged++] = mHull[i];
        if (i == iUR)
        {
            break;
        }
        i = (i < j3 ? i + 1 : j2);
    }
    LogAssert(k < size1, "Unexpected condition.");

    int next = j0;
    for (k = 0; k < numMerged; ++k)
    {
        mHull[next] = mMerged[k];
        ++next;
    }

    i0 = j0;
    i1 = next - 1;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType> inline
void ConvexHull2<InputType, ComputeType>::GetTangent(int j0, int j1, int j2,
    int j3, int& i0, int& i1)
{
    // In theory the loop terminates in a finite number of steps, but the
    // upper bound for the loop variable is used to trap problems caused by
    // floating point roundoff errors that might lead to an infinite loop.

    int size0 = j1 - j0 + 1;
    int size1 = j3 - j2 + 1;
    int const imax = size0 + size1;
    int i, iLm1, iRp1;
    Vector2<ComputeType> L0, L1, R0, R1;

    for (i = 0; i < imax; i++)
    {
        // Get the endpoints of the potential tangent.
        L1 = mComputePoints[mHull[i0]];
        R0 = mComputePoints[mHull[i1]];

        // Walk along the left hull to find the point of tangency.
        if (size0 > 1)
        {
            iLm1 = (i0 > j0 ? i0 - 1 : j1);
            L0 = mComputePoints[mHull[iLm1]];
            auto order = mQuery.ToLineExtended(R0, L0, L1);
            if (order == PrimalQuery2<ComputeType>::ORDER_NEGATIVE
                || order == PrimalQuery2<ComputeType>::ORDER_COLLINEAR_RIGHT)
            {
                i0 = iLm1;
                continue;
            }
        }

        // Walk along right hull to find the point of tangency.
        if (size1 > 1)
        {
            iRp1 = (i1 < j3 ? i1 + 1 : j2);
            R1 = mComputePoints[mHull[iRp1]];
            auto order = mQuery.ToLineExtended(L1, R0, R1);
            if (order == PrimalQuery2<ComputeType>::ORDER_NEGATIVE
                || order == PrimalQuery2<ComputeType>::ORDER_COLLINEAR_LEFT)
            {
                i1 = iRp1;
                continue;
            }
        }

        // The tangent segment has been found.
        break;
    }

    // Detect an "infinite loop" caused by floating point round-off errors.
    LogAssert(i < imax, "Unexpected condition.");
}
//----------------------------------------------------------------------------
