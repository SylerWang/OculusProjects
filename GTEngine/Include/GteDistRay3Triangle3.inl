// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Ray3<Real>, Triangle3<Real>>::Result
DCPQuery<Real, Ray3<Real>, Triangle3<Real>>::operator()(
    Ray3<Real> const& ray, Triangle3<Real> const& triangle)
{
    Result result;

    Line3<Real> line(ray.origin, ray.direction);
    DCPQuery<Real, Line3<Real>, Triangle3<Real>> ltQuery;
    auto ltResult = ltQuery(line, triangle);

    if (ltResult.lineParameter >= (Real)0)
    {
        result.distance = ltResult.distance;
        result.sqrDistance = ltResult.sqrDistance;
        result.rayParameter = ltResult.lineParameter;
        result.triangleParameter[0] = ltResult.triangleParameter[0];
        result.triangleParameter[1] = ltResult.triangleParameter[1];
        result.triangleParameter[2] = ltResult.triangleParameter[2];
        result.closestPoint[0] = ltResult.closestPoint[0];
        result.closestPoint[1] = ltResult.closestPoint[1];
    }
    else
    {
        DCPQuery<Real, Vector3<Real>, Triangle3<Real>> ptQuery;
        auto ptResult = ptQuery(ray.origin, triangle);
        result.distance = ptResult.distance;
        result.sqrDistance = ptResult.sqrDistance;
        result.rayParameter = (Real)0;
        result.triangleParameter[0] = ptResult.triangleParameter[0];
        result.triangleParameter[1] = ptResult.triangleParameter[1];
        result.triangleParameter[2] = ptResult.triangleParameter[2];
        result.closestPoint[0] = ray.origin;
        result.closestPoint[1] = ptResult.triangleClosestPoint;
    }
    return result;
}
//----------------------------------------------------------------------------
