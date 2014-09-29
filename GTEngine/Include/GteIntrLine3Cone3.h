// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GteIntrIntervals.h"
#include "GteLine3.h"
#include "GteCone3.h"

// The queries consider the cone to be single sided and solid.

namespace gte
{

template <typename Real>
class FIQuery<Real, Line3<Real>, Cone3<Real>>
{
public:
    struct Result
    {
        bool intersect;

        // Because the intersection of line and cone with infinite height
        // h > 0 can be a ray or a line with t, we use a 'type' value instead
        // that allows you to decide how to interpret the parameter[] and
        // point[] values.
        //   type  intersect  valid data
        //   0     none       none
        //   1     point      parameter[0] = parameter[1], finite
        //                    point[0] = point[1]
        //   2     segment    parameter[0] < parameter[1], finite
        //                    point[0,1] valid
        //   3     ray        parameter[0] finite, parameter[1] maxReal
        //                    point[0] = rayOrigin, point[1] = lineDirection
        //   4     ray        parameter[0] -maxReal, parameter[1] finite
        //                    point[0] = rayOrigin, point[1] = -lineDirection
        //   5     line       parameter[0] -maxReal, parameter[1] maxReal,
        //                    point[0] = lineOrigin, point[1] = lineDirection
        // If the cone height h is finite, only types 0, 1, or 2 can occur.
        int type;
        std::array<Real, 2> parameter;  // Relative to incoming line.
        std::array<Vector3<Real>, 2> point;
    };

    Result operator()(Line3<Real> const& line, Cone3<Real> const& cone);

protected:
    void DoQuery(Vector3<Real> const& lineOrigin,
        Vector3<Real> const& lineDirection, Cone3<Real> const& cone,
        Result& result);
};

#include "GteIntrLine3Cone3.inl"

}
