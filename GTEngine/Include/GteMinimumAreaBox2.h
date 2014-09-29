// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteOrientedBox2.h"
#include "GteConvexHull2.h"

// Compute a minimum-area oriented box containing the specified points.  The
// algorithm uses the rotating calipers method.
//   http://www-cgrl.cs.mcgill.ca/~godfried/research/calipers.html
//   http://cgm.cs.mcgill.ca/~orm/rotcal.html
// The box is supported by the convex hull of the points, so the algorithm
// is really about computing the minimum-area box containing a convex polygon.
// The rotating calipers approach is O(n) in time for n polygon edges.
//
// The naive algorithm is to process an edge as follows.  Let U0 be a
// unit-length direction for the edge.  Let U1 be a unit-length vector that
// is perpendicular to U0.  For each vertex P[i] of the polygon, compute its
// projection (x0[i],x1[i]), where P[i] = x0[i]*U0 + x1[i]*U1.  Compute
// x0min = min(x0[i]), x0max = max(x0[i]), x1min = min(x1[i]), and
// x1max = max(x1[i]).  The bounding box has axes U0 and U1, extents
// e0 = (x0max - x0min)/2 and e1 = (x1max - x1min)/2, and center C =
// ((x0max + x0min)/2)*U0 + ((x1max + x1min)/2)*U1.  Compute the bounding
// box for each of n edges, each edge requiring n projections, thus leading
// to an O(n^2) algorithm.

namespace gte
{

template <typename InputType, typename ComputeType>
class MinimumAreaBox2
{
public:
    // The class is a functor to support computing the minimum-area box of
    // multiple data sets using the same class object.
    MinimumAreaBox2();

    // The points are arbitrary, so we must compute the convex hull from
    // them in order to compute the minimum-area box.  The input parameters
    // are necessary for using ConvexHull2.  NOTE:  ConvexHull2 guarantees
    // that the hull does not have three consecutive collinear points.
    bool operator()(int numPoints, Vector2<InputType> const* points,
        InputType epsilon, OrientedBox2<InputType>& minBox);

    // The points already form a counterclockwise, nondegenerate convex
    // polygon.  If the points directly are the convex polygon, set
    // numIndices to 0 and indices to nullptr.  If the polygon vertices
    // are a subset of the incoming points, that subset is identified by
    // numIndices >= 3 and indices having numIndices elements.  NOTE:  It
    // is necessary that no three consecutive vertices are collinear.
    bool operator()(int numPoints, Vector2<InputType> const* points,
        int numIndices, int const* indices, OrientedBox2<InputType>& minBox);

    // This function is the straightforward O(n^2) algorithm for polygons
    // with n vertices.  This function does not convert the InputType inputs
    // to ComputeType.  We use this for testing and debugging the operator()
    // functinos.
    bool DoOrderNSqr(int numPoints, Vector2<InputType> const* points,
        int numIndices, int const* indices, OrientedBox2<InputType>& minBox);

    // Member access.
    inline int GetNumPoints() const;
    inline Vector2<InputType> const* GetPoints() const;
    inline std::vector<int> const& GetHull() const;

public:
    // This code is used by MinimumVolumeBox3, because that class needs the
    // ComputeType-valued bounding box whose axes are not unit length, not the
    // InputType-valued bounding box.  This avoids conversions back to
    // InputType during intermediate steps of the 3D box computations.

    // Flags for the rotating calipers algorithm.  EXT_B is bottom, EXT_R is
    // right, EXT_T is top, and EXT_L is left.
    enum { EXT_B, EXT_R, EXT_T, EXT_L };

    // The box axes are U[i] and are usually not unit-length in order to allow
    // exact arithmetic.  The box is supported by mPoints[index[i]], where i
    // is one of the enumerations above.  The box axes are not necessarily unit
    // length, but they have the same length.  They need to be normalized for
    // conversion back to InputType.
    struct Box
    {
        Vector2<ComputeType> U[2];
        std::array<int, 4> index;
        ComputeType area;
    };

    // The input must be a nondegenerate convex polygon in counterclockwise
    // order.
    static Box ComputeBox(std::vector<Vector2<ComputeType>> const& vertices);

private:
    // Compare Dot(D0/|D0|,E0/|E0|) > Dot(D1/|D1|,E1/|E1|) using exact
    // arithmetic.  It is known that |D0| = |D1|, but generally |E0| and
    // |E1| are different.  An equivalent comparison is
    // Dot(D0,E0)/|E0| > Dot(D1,E1)/|E1|.  We may square each side and
    // compare, but the signs of the dot products must be taken into account.
    static bool IsLarger(
        Vector2<ComputeType> const& D0,
        Vector2<ComputeType> const& E0,
        Vector2<ComputeType> const& D1,
        Vector2<ComputeType> const& E1);

    void Convert(Box const& minBox,
        std::vector<Vector2<ComputeType>> const& computePoints,
        OrientedBox2<InputType>& itMinBox);

    int mNumPoints;
    Vector2<InputType> const* mPoints;
    std::vector<int> mHull;
};

#include "GteMinimumAreaBox2.inl"

}
