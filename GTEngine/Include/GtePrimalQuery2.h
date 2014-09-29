// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteVector2.h"

// Queries about the relation of a point to various geometric objects.

namespace gte
{

template <typename Real>
class PrimalQuery2
{
public:
    // The caller is responsible for ensuring that the array is not empty
    // before calling queries and that the indices passed to the queries are
    // valid.  The class does no range checking.
    PrimalQuery2();
    PrimalQuery2(int numVertices, Vector2<Real> const* vertices);

    // Member access.
    inline void Set(int numVertices, Vector2<Real> const* vertices);
    inline int GetNumVertices() const;
    inline Vector2<Real> const* GetVertices() const;

    // In the following, point P refers to vertices[i] or 'test' and Vi refers
    // to vertices[vi].

    // For a line with origin V0 and direction <V0,V1>, ToLine returns
    //   +1, P on right of line
    //   -1, P on left of line
    //    0, P on the line
    // The last two versions return the same information.  The 'order'
    // parameter is
    //   -3, points not collinear, P on left of line
    //   -2, P strictly left of V0 on the line
    //   -1, P = V0
    //    0, P interior to line segment [V0,V1]
    //   +1, P = V1
    //   +2, P strictly right of V0 on the line
    int ToLine(int i, int v0, int v1) const;
    int ToLine(Vector2<Real> const& test, int v0, int v1) const;
    int ToLine(int i, int v0, int v1, int& order) const;
    int ToLine(Vector2<Real> const& test, int v0, int v1, int& order) const;

    // For a triangle with counterclockwise vertices V0, V1, and V2,
    // ToTriangle returns
    //   +1, P outside triangle
    //   -1, P inside triangle
    //    0, P on triangle
    int ToTriangle(int i, int v0, int v1, int v2) const;
    int ToTriangle(Vector2<Real> const& test, int v0, int v1, int v2) const;

    // For a triangle with counterclockwise vertices V0, V1, and V2,
    // ToCircumcircle returns
    //   +1, P outside circumcircle of triangle
    //   -1, P inside circumcircle of triangle
    //    0, P on circumcircle of triangle
    int ToCircumcircle(int i, int v0, int v1, int v2) const;
    int ToCircumcircle(Vector2<Real> const& test, int v0, int v1, int v2)
        const;

    // An extended classification of the relationship of a point to a line
    // segment.  For noncollinear points, the return value is
    //   ORDER_POSITIVE when <P,Q0,Q1> is a counterclockwise triangle
    //   ORDER_NEGATIVE when <P,Q0,Q1> is a clockwise triangle
    // For collinear points, the line direction is Q1-Q0.  The return value is
    //   ORDER_COLLINEAR_LEFT when the line ordering is <P,Q0,Q1>
    //   ORDER_COLLINEAR_RIGHT when the line ordering is <Q0,Q1,P>
    //   ORDER_COLLINEAR_CONTAIN when the line ordering is <Q0,P,Q1>
    enum OrderType
    {
        ORDER_Q0_EQUALS_Q1,
        ORDER_P_EQUALS_Q0,
        ORDER_P_EQUALS_Q1,
        ORDER_POSITIVE,
        ORDER_NEGATIVE,
        ORDER_COLLINEAR_LEFT,
        ORDER_COLLINEAR_RIGHT,
        ORDER_COLLINEAR_CONTAIN
    };

    OrderType ToLineExtended(Vector2<Real> const& P, Vector2<Real> const& Q0,
        Vector2<Real> const& Q1) const;

private:
    int mNumVertices;
    Vector2<Real> const* mVertices;
};

#include "GtePrimalQuery2.inl"

}
