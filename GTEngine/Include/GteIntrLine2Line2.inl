// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Line2<Real>, Line2<Real>>::Result
TIQuery<Real, Line2<Real>, Line2<Real>>::operator()(
    Line2<Real> const& line0, Line2<Real> const& line1)
{
    Result result;

    // The intersection of two lines is a solution to P0 + s0*D0 = P1 + s1*D1.
    // Rewrite this as s0*D0 - s1*D1 = P1 - P0 = Q.  If DotPerp(D0, D1)) = 0,
    // the lines are parallel.  Additionally, if DotPerp(Q, D1)) = 0, the
    // lines are the same.  If Dotperp(D0, D1)) is not zero, then
    //   s0 = DotPerp(Q, D1))/DotPerp(D0, D1))
    // produces the point of intersection.  Also,
    //   s1 = DotPerp(Q, D0))/DotPerp(D0, D1))

    Vector2<Real> diff = line1.origin - line0.origin;
    Real D0DotPerpD1 = DotPerp(line0.direction, line1.direction);
    if (std::abs(D0DotPerpD1) > (Real)0)
    {
        // The lines are not parallel.
        result.intersect = true;
        result.numIntersections = 1;
    }
    else
    {
        // The lines are parallel.
        Normalize(diff);
        Real diffNDotPerpD1 = DotPerp(diff, line1.direction);
        if (std::abs(diffNDotPerpD1) > (Real)0)
        {
            // The lines are the same.
            result.intersect = true;
            result.numIntersections = std::numeric_limits<int>::max();
        }
        else
        {
            // The pines are parallel but distinct.
            result.intersect = false;
            result.numIntersections = 0;
        }
    }

    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line2<Real>, Line2<Real>>::Result
FIQuery<Real, Line2<Real>, Line2<Real>>::operator()(
    Line2<Real> const& line0, Line2<Real> const& line1)
{
    Result result;

    // The intersection of two lines is a solution to P0 + s0*D0 = P1 + s1*D1.
    // Rewrite this as s0*D0 - s1*D1 = P1 - P0 = Q.  If DotPerp(D0, D1)) = 0,
    // the lines are parallel.  Additionally, if DotPerp(Q, D1)) = 0, the
    // lines are the same.  If Dotperp(D0, D1)) is not zero, then
    //   s0 = DotPerp(Q, D1))/DotPerp(D0, D1))
    // produces the point of intersection.  Also,
    //   s1 = DotPerp(Q, D0))/DotPerp(D0, D1))

    Vector2<Real> diff = line1.origin - line0.origin;
    Real D0DotPerpD1 = DotPerp(line0.direction, line1.direction);
    if (std::abs(D0DotPerpD1) > (Real)0)
    {
        // The lines are not parallel.
        result.intersect = true;
        result.numIntersections = 1;
        Real invD0DotPerpD1 = ((Real)1) / D0DotPerpD1;
        Real diffDotPerpD0 = DotPerp(diff, line0.direction);
        Real diffDotPerpD1 = DotPerp(diff, line1.direction);
        Real s0 = diffDotPerpD1*invD0DotPerpD1;
        Real s1 = diffDotPerpD0*invD0DotPerpD1;
        result.line0Parameter[0] = s0;
        result.line1Parameter[0] = s1;
        result.point = line0.origin + s0 * line0.direction;
    }
    else
    {
        // The lines are parallel.
        Normalize(diff);
        Real diffNDotPerpD1 = DotPerp(diff, line1.direction);
        if (std::abs(diffNDotPerpD1) > (Real)0)
        {
            // The lines are the same.
            result.intersect = true;
            result.numIntersections = std::numeric_limits<int>::max();
            Real maxReal = std::numeric_limits<Real>::max();
            result.line0Parameter[0] = -maxReal;
            result.line0Parameter[1] = +maxReal;
            result.line1Parameter[0] = -maxReal;
            result.line1Parameter[1] = +maxReal;
        }
        else
        {
            // The pines are parallel but distinct.
            result.intersect = false;
            result.numIntersections = 0;
        }
    }

    return result;
}
//----------------------------------------------------------------------------
