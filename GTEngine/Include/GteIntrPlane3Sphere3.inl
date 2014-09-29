// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Plane3<Real>, Sphere3<Real>>::Result
TIQuery<Real, Plane3<Real>, Sphere3<Real>>::operator()(
    Plane3<Real> const& plane, Sphere3<Real> const& sphere)
{
    Result result;
    DCPQuery<Real, Vector3<Real>, Plane3<Real>> ppQuery;
    auto ppResult = ppQuery(sphere.center, plane);
    result.intersect = (ppResult.distance <= sphere.radius);
    return result;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Plane3<Real>, Sphere3<Real>>::Result
FIQuery<Real, Plane3<Real>, Sphere3<Real>>::operator()(
    Plane3<Real> const& plane, Sphere3<Real> const& sphere)
{
    Result result;
    DCPQuery<Real, Vector3<Real>, Plane3<Real>> ppQuery;
    auto ppResult = ppQuery(sphere.center, plane);
    if (ppResult.distance < sphere.radius)
    {
        result.intersect = true;
        result.isCircle = true;
        result.circle.center = sphere.center -
            ppResult.signedDistance*plane.normal;
        return result;
    }
    else if (ppResult.distance == sphere.radius)
    {
        result.intersect = true;
        result.isCircle = false;
        result.point = sphere.center - ppResult.signedDistance*plane.normal;
        return result;
    }
    else
    {
        result.intersect = false;
        return result;
    }
}
//----------------------------------------------------------------------------
