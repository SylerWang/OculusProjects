// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteEllipse2.h"
#include "GteRootsBisection.h"
#include "GteRootsPolynomial.h"
#include "GteLogger.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>
{
public:
    enum
    {
        ELLIPSES_SEPARATED,
        ELLIPSES_INTERSECTING,
        ELLIPSE0_CONTAINS_ELLIPSE1,
        ELLIPSE1_CONTAINS_ELLIPSE0
    };

    struct Result
    {
        // As solids, the ellipses intersect as long as they are not
        // separated.
        bool intersect;

        // This is one of the four enumerations listed above.
        int relationship;
    };

    Result operator()(Ellipse2<Real> const& ellipse0,
        Ellipse2<Real> const& ellipse1);

private:
    void GetRoots(Real d0, Real c0, int& numRoots, Real* roots);
    void GetRoots(Real d0, Real d1, Real c0, Real c1, int& numRoots,
        Real* roots);
};

template <typename Real>
class FIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>
{
public:
    struct Result
    {
        // This value is true when the ellipse boundaries intersect in at
        // least one point; that is, the ellipses are treated as hollow
        // objects.
        bool intersect;

        // If the ellipses are not the same, numPoints is 0 through 4 and
        // that number of elements of 'points' are valid.  If the ellipses
        // are the same, numPoints is set to maxInt and 'points' is invalid.
        int numPoints;
        std::array<Vector2<Real>, 4> points;
    };

    Result operator()(Ellipse2<Real> const& ellipse0,
        Ellipse2<Real> const& ellipse1);
};

#include "GteIntrEllipse2Ellipse2.inl"

}
