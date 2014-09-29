// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Line2<Real>, Ray2<Real>>::Result
TIQuery<Real, Line2<Real>, Ray2<Real>>::operator()(
    Line2<Real> const& line, Ray2<Real> const& ray)
{
    Result result;
    FIQuery<Real, Line2<Real>, Line2<Real>> llQuery;
    auto llResult = llQuery(line, Line2<Real>(ray.origin, ray.direction));
    if (llResult.numIntersections == 1)
    {
        // Test whether the line-line intersection is on the ray.
        if (llResult.line1Parameter[0] >= (Real)0)
        {
            result.intersect = true;
            result.numIntersections = 1;
        }
        else
        {
            result.intersect = false;
            result.numIntersections = 0;
        }
    }
    else
    {
        result.intersect = llResult.intersect;
        result.numIntersections = llResult.numIntersections;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line2<Real>, Ray2<Real>>::Result
FIQuery<Real, Line2<Real>, Ray2<Real>>::operator()(
    Line2<Real> const& line, Ray2<Real> const& ray)
{
    Result result;
    FIQuery<Real, Line2<Real>, Line2<Real>> llQuery;
    auto llResult = llQuery(line, Line2<Real>(ray.origin, ray.direction));
    if (llResult.numIntersections == 1)
    {
        // Test whether the line-line intersection is on the ray.
        if (llResult.line1Parameter[0] >= (Real)0)
        {
            result.intersect = true;
            result.numIntersections = 1;
            result.lineParameter[0] = llResult.line0Parameter[0];
            result.rayParameter[0] = llResult.line1Parameter[0];
            result.point = llResult.point;
        }
        else
        {
            result.intersect = false;
            result.numIntersections = 0;
        }
    }
    else if (llResult.numIntersections == std::numeric_limits<int>::max())
    {
        result.intersect = true;
        result.numIntersections = std::numeric_limits<int>::max();
        Real maxReal = std::numeric_limits<Real>::max();
        result.lineParameter[0] = -maxReal;
        result.lineParameter[1] = +maxReal;
        result.rayParameter[0] = (Real)0;
        result.rayParameter[1] = +maxReal;
    }
    else
    {
        result.intersect = false;
        result.numIntersections = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
