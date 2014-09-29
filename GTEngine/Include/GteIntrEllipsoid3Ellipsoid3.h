// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteTIQuery.h"
#include "GteFIQuery.h"
#include "GteEllipsoid3.h"
#include "GteRootsBisection.h"
#include "GteRootsPolynomial.h"
#include "GteLogger.h"

namespace gte
{

template <typename Real>
class TIQuery<Real, Ellipsoid3<Real>, Ellipsoid3<Real>>
{
public:
    enum
    {
        ELLIPSOIDS_SEPARATED,
        ELLIPSOIDS_INTERSECTING,
        ELLIPSOID0_CONTAINS_ELLIPSOID1,
        ELLIPSOID1_CONTAINS_ELLIPSOID0
    };

    struct Result
    {
        // As solids, the ellipsoids intersect as long as they are not
        // separated.
        bool intersect;

        // This is one of the four enumerations listed above.
        int relationship;
    };

    Result operator()(Ellipsoid3<Real> const& ellipsoid0,
        Ellipsoid3<Real> const& ellipsoid1);

private:
    void GetRoots(Real d0, Real c0, int& numRoots, Real* roots);
    void GetRoots(Real d0, Real d1, Real c0, Real c1, int& numRoots,
        Real* roots);
    void GetRoots(Real d0, Real d1, Real d2, Real c0, Real c1, Real c2,
        int& numRoots, Real* roots);
};

#include "GteIntrEllipsoid3Ellipsoid3.inl"

}
