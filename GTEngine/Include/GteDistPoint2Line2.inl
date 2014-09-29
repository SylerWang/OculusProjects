// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector2<Real>, Line2<Real>>::Result
DCPQuery<Real, Vector2<Real>, Line2<Real>>::operator()(
    Vector2<Real> const& point, Line2<Real> const& line)
{
    Result result;

    Vector2<Real> diff = point - line.origin;
    result.lineParameter = Dot(line.direction, diff);
    result.lineClosestPoint =
        line.origin + result.lineParameter*line.direction;

    diff = point - result.lineClosestPoint;
    result.sqrDistance = Dot(diff, diff);
    result.distance = sqrt(result.sqrDistance);

    return result;
}
//----------------------------------------------------------------------------
