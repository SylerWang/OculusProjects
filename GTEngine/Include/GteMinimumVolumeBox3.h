// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteOrientedBox3.h"
#include "GteConvexHull3.h"
#include "GteMinimumAreaBox2.h"
#include "GteEdgeKey.h"

// Compute a minimum-volume oriented box containing the specified points.  The
// algorithm is really about computing the minimum-volume box containing the
// convex hull of the points, so we must compute the convex hull or you must
// pass an already built hull to the code.
//
// The minimum-volume oriented box has a face coincident with a hull face
// or has three mutually orthogonal edges coincident with three hull edges
// that (of course) are mutually orthogonal.
//    J.O'Rourke, "Finding minimal enclosing boxes",
//    Internat. J. Comput. Inform. Sci., 14:183-199, 1985.
//
// The minimum-area oriented box algorithm, MinimumAreaBox2, is used for the
// hull face processing.  Although one would hope that it is possible to do
// so using exact arithmetic, this appears to be intractable.  Given a
// triangular face whose vertices have rational components, you can construct
// a rational normal N (usually not unit length).  The projection of the hull
// onto the plane containing the triangular face requires computing rational
// vectors U and V for which {N,U,V} is an orthonormal set.  This appears to
// be a quite difficult problem.  The MinimumVolumeBox3 code allows exact
// arithmetic (via ComputeType) for all but the box construction, which uses
// floating-point arithmetic (via InputType).

namespace gte
{

template <typename InputType, typename ComputeType>
class MinimumVolumeBox3
{
public:
    // The class is a functor to support computing the minimum-volume box of
    // multiple data sets using the same class object.
    MinimumVolumeBox3();

    // The points are arbitrary, so we must compute the convex hull from
    // them in order to compute the minimum-area box.  The input parameters
    // are necessary for using ConvexHull3.
    bool operator()(int numPoints, Vector3<InputType> const* points,
        InputType epsilon, OrientedBox3<InputType>& minBox);

    // The points form a nondegenerate convex polyhedron.  The indices input
    // must be nonnull and specify the triangle faces.
    bool operator()(int numPoints, Vector3<InputType> const* points,
        int numIndices, int const* indices, OrientedBox3<InputType>& minBox);

    // Member access.
    inline int GetNumPoints() const;
    inline Vector3<InputType> const* GetPoints() const;
    inline std::vector<int> const& GetHull() const;

private:
    struct Box
    {
        Vector3<InputType> U[3];
        std::array<int, 6> index;
        InputType volume;
    };

    void ComputeBox(ETManifoldMesh const& mesh,
        Vector3<ComputeType> const* computePoints,
        OrientedBox3<InputType>& itMinBox);

    void ProcessFaces(ETManifoldMesh const& mesh,
        Vector3<ComputeType> const* computePoints, Box& minBox);

    void ProcessEdges(ETManifoldMesh const& mesh,
        Vector3<ComputeType> const* computePoints, Box& minBox);

    void Convert(Box const& minBox, OrientedBox3<InputType>& itMinBox);

    int mNumPoints;
    Vector3<InputType> const* mPoints;
    std::vector<int> mHull;
    std::set<int> mUniqueIndices;
};

#include "GteMinimumVolumeBox3.inl"

}
