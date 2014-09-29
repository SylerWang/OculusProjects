// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Ray2<Real>, Arc2<Real>>::Result
TIQuery<Real, Ray2<Real>, Arc2<Real>>::operator()(
    Ray2<Real> const& ray, Arc2<Real> const& arc)
{
    Result result;
    FIQuery<Real, Ray2<Real>, Arc2<Real>> raQuery;
    auto raResult = raQuery(ray, arc);
    result.intersect = raResult.intersect;
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Ray2<Real>, Arc2<Real>>::Result
FIQuery<Real, Ray2<Real>, Arc2<Real>>::operator()(
    Ray2<Real> const& ray, Arc2<Real> const& arc)
{
    Result result;

    FIQuery<Real, Ray2<Real>, Circle2<Real>> rcQuery;
    Circle2<Real> circle(arc.center, arc.radius);
    auto rcResult = rcQuery(ray, circle);
    if (rcResult.intersect)
    {
        // Test whether ray-circle intersections are on the arc.
        result.numIntersections = 0;
        for (int i = 0; i < rcResult.numIntersections; ++i)
        {
            if (arc.Contains(rcResult.point[i]))
            {
                result.intersect = true;
                result.parameter[result.numIntersections]
                    = rcResult.parameter[i];
                result.point[result.numIntersections++]
                    = rcResult.point[i];
            }
        }
    }
    else
    {
        result.intersect = false;
        result.numIntersections = 0;
    }

    return result;
}
//----------------------------------------------------------------------------
