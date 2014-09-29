// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Circle2<Real>, Arc2<Real>>::Result
FIQuery<Real, Circle2<Real>, Arc2<Real>>::operator()(
    Circle2<Real> const& circle, Arc2<Real> const& arc)
{
    Result result;

    Circle2<Real> circleOfArc(arc.center, arc.radius);
    FIQuery<Real, Circle2<Real>, Circle2<Real>> ccQuery;
    auto ccResult = ccQuery(circle, circleOfArc);
    if (!ccResult.intersect)
    {
        result.intersect = false;
        result.numIntersections = 0;
        return result;
    }

    if (ccResult.numIntersections == std::numeric_limits<int>::max())
    {
        // The arc is on the circle.
        result.intersect = true;
        result.numIntersections = std::numeric_limits<int>::max();
        result.arc = arc;
        return result;
    }

    // Test whether circle-circle intersection points are on the arc.
    for (int i = 0; i < ccResult.numIntersections; ++i)
    {
        result.numIntersections = 0;
        if (arc.Contains(ccResult.point[i]))
        {
            result.point[result.numIntersections++] = ccResult.point[i];
            result.intersect = true;
        }
    }
    return result;
}
//----------------------------------------------------------------------------
