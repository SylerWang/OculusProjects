// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

#pragma once

// Compute the convex hull of 3D points using incremental insertion.  The only
// way to ensure a correct result for the input vertices (assumed to be exact)
// is to choose ComputeType for exact rational arithmetic.  You may use
// BSNumber.  No divisions are performed in this computation, so you do not
// have to use BSRational.

#include "GteLine3.h"
#include "GtePlane3.h"
#include "GtePrimalQuery3.h"
#include "GteETManifoldMesh.h"
#include <set>
#include <vector>

namespace gte
{

template <typename InputType, typename ComputeType>
class ConvexHull3
{
public:
    // The class is a functor to support computing the convex hull of multiple
    // data sets using the same class object.
    ConvexHull3();

    // The input is the array of points whose convex hull is required.  The
    // epsilon value is used to determine the intrinsic dimensionality of the
    // vertices (d = 0, 1, 2, or 3).  When epsilon is positive, the
    // determination is fuzzy--points approximately the same point,
    // approximately on a line, approximately planar, or volumetric.
    bool operator()(int numPoints, Vector3<InputType> const* points,
        InputType epsilon);

    // Dimensional information.  If GetDimension() returns 1, the points lie
    // on a line P+t*D (fuzzy comparison when epsilon > 0).  You can sort
    // these if you need a polyline output by projecting onto the line each
    // vertex X = P+t*D, where t = Dot(D,X-P).  If GetDimension() returns 2,
    // the points line on a plane P+s*U+t*V (fuzzy comparison when
    // epsilon > 0).  You can project each point X = P+s*U+t*V, where
    // s = Dot(U,X-P) and t = Dot(V,X-P), then apply ConvexHull2 to the (s,t)
    // tuples.
    inline InputType GetEpsilon() const;
    inline int GetDimension() const;
    inline Line3<InputType> const& GetLine() const;
    inline Plane3<InputType> const& GetPlane() const;

    // Member access.
    inline int GetNumPoints() const;
    inline int GetNumUniquePoints() const;
    inline Vector3<InputType> const* GetPoints() const;
    inline PrimalQuery3<ComputeType> const& GetQuery() const;

    // The convex hull is a convex polyhedron with triangular faces.
    inline std::vector<TriangleKey<true>> const& GetHullUnordered() const;
    ETManifoldMesh const& GetHullMesh() const;

private:
    // Support for incremental insertion.
    void Update(int i);

    // The epsilon value is used for fuzzy determination of intrinsic
    // dimensionality.  If the dimension is 0, 1, or 2, the constructor
    // returns early.  The caller is responsible for retrieving the dimension
    // and taking an alternate path should the dimension be smaller than 3.
    // If the dimension is 0, the caller may as well treat all points[] as a
    // single point, say, points[0].  If the dimension is 1, the caller can
    // query for the approximating line and project points[] onto it for
    // further processing.  If the dimension is 2, the caller can query for
    // the approximating plane and project points[] onto it for further
    // processing.
    InputType mEpsilon;
    int mDimension;
    Line3<InputType> mLine;
    Plane3<InputType> mPlane;

    // The array of points used for geometric queries.  If you want to be
    // certain of a correct result, choose ComputeType to be BSNumber.
    std::vector<Vector3<ComputeType>> mComputePoints;
    PrimalQuery3<ComputeType> mQuery;

    int mNumPoints;
    int mNumUniquePoints;
    Vector3<InputType> const* mPoints;
    std::vector<TriangleKey<true>> mHullUnordered;
    mutable ETManifoldMesh mHullMesh;
};

#include "GteConvexHull3.inl"

}
