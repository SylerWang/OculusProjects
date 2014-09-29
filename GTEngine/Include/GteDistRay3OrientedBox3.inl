// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Ray3<Real>, OrientedBox3<Real>>::Result
DCPQuery<Real, Ray3<Real>, OrientedBox3<Real >> ::operator()(
    Ray3<Real> const& ray, OrientedBox3<Real> const& box)
{
    Result result;

    Line3<Real> line(ray.origin, ray.direction);
    DCPQuery<Real, Line3<Real>, OrientedBox3<Real>> lbQuery;
    auto lbResult = lbQuery(line, box);

    if (lbResult.lineParameter >= (Real)0)
    {
        result.sqrDistance = lbResult.sqrDistance;
        result.distance = lbResult.distance;
        result.rayParameter = lbResult.lineParameter;
        result.closestPoint[0] = lbResult.closestPoint[0];
        result.closestPoint[1] = lbResult.closestPoint[1];
    }
    else
    {
        DCPQuery<Real, Vector3<Real>, OrientedBox3<Real>> pbQuery;
        auto pbResult = pbQuery(ray.origin, box);
        result.sqrDistance = pbResult.sqrDistance;
        result.distance = pbResult.distance;
        result.rayParameter = (Real)0;
        result.closestPoint[0] = ray.origin;
        result.closestPoint[1] = pbResult.boxClosestPoint;
    }
    return result;
}
//----------------------------------------------------------------------------
