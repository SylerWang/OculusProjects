// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

// Compute the convex hull of 2D points using a divide-and-conquer algorithm.
// This is an O(N log N) algorithm for N input points.  The only way to ensure
// a correct result for the input vertices (assumed to be exact) is to choose
// ComputeType for exact rational arithmetic.  You may use BSNumber.  No
// divisions are performed in this computation, so you do not have to use
// BSRational.

#include "GteLine2.h"
#include "GtePrimalQuery2.h"
#include "GteLogger.h"
#include <algorithm>
#include <vector>

namespace gte
{

template <typename InputType, typename ComputeType>
class ConvexHull2
{
public:
    // The class is a functor to support computing the convex hull of multiple
    // data sets using the same class object.
    ConvexHull2();

    // The input is the array of points whose convex hull is required.  The
    // epsilon value is used to determine the intrinsic dimensionality of the
    // vertices (d = 0, 1, or 2).  When epsilon is positive, the determination
    // is fuzzy--points approximately the same point, approximately on a
    // line, or planar.  The return value is 'true' if and only if the hull
    // construction is successful.
    bool operator()(int numPoints, Vector2<InputType> const* points,
        InputType epsilon);

    // Dimensional information.  If GetDimension() returns 1, the points lie
    // on a line P+t*D (fuzzy comparison when epsilon > 0).  You can sort
    // these if you need a polyline output by projecting onto the line each
    // vertex X = P+t*D, where t = Dot(D,X-P).
    inline InputType GetEpsilon() const;
    inline int GetDimension() const;
    inline Line2<InputType> const& GetLine() const;

    // Member access.
    inline int GetNumPoints() const;
    inline int GetNumUniquePoints() const;
    inline Vector2<InputType> const* GetPoints() const;
    inline PrimalQuery2<ComputeType> const& GetQuery() const;

    // The convex hull is a convex polygon whose vertices are listed in
    // counterclockwise order.
    inline std::vector<int> const& GetHull() const;

private:
    // Support for divide-and-conquer.
    void GetHull(int& i0, int& i1);
    void Merge(int j0, int j1, int j2, int j3, int& i0, int& i1);
    void GetTangent(int j0, int j1, int j2, int j3, int& i0, int& i1);

    // The epsilon value is used for fuzzy determination of intrinsic
    // dimensionality.  If the dimension is 0 or 1, the constructor returns
    // early.  The caller is responsible for retrieving the dimension and
    // taking an alternate path should the dimension be smaller than 2.  If
    // the dimension is 0, the caller may as well treat all points[] as a
    // single point, say, points[0].  If the dimension is 1, the caller can
    // query for the approximating line and project points[] onto it for
    // further processing.
    InputType mEpsilon;
    int mDimension;
    Line2<InputType> mLine;

    // The array of points used for geometric queries.  If you want to be
    // certain of a correct result, choose ComputeType to be BSNumber.
    std::vector<Vector2<ComputeType>> mComputePoints;
    PrimalQuery2<ComputeType> mQuery;

    int mNumPoints;
    int mNumUniquePoints;
    Vector2<InputType> const* mPoints;
    std::vector<int> mMerged, mHull;
};

#include "GteConvexHull2.inl"

}
