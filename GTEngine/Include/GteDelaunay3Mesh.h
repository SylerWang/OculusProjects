// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

#pragma once

#include "GteDelaunay3.h"

namespace gte
{

template <typename InputType, typename ComputeType, typename RationalType>
class Delaunay3Mesh
{
public:
    // Construction.
    Delaunay3Mesh(Delaunay3<InputType, ComputeType> const& delaunay);

    // Mesh information.
    inline int GetNumVertices() const;
    inline int GetNumTetrahedra() const;
    inline Vector3<InputType> const* GetVertices() const;
    inline int const* GetIndices() const;
    inline int const* GetAdjacencies() const;

    // Containment queries.
    int GetContainingTetrahedron(Vector3<InputType> const& P) const;
    bool GetVertices(int t, std::array<Vector3<InputType>, 4>& vertices)
        const;
    bool GetIndices(int t, std::array<int, 4>& indices) const;
    bool GetAdjacencies(int t, std::array<int, 4>& adjacencies) const;
    bool GetBarycentrics(int t, Vector3<InputType> const& P,
        std::array<InputType, 4>& bary) const;

private:
    Delaunay3<InputType, ComputeType> const* mDelaunay;
};

#include "GteDelaunay3Mesh.inl"

}
