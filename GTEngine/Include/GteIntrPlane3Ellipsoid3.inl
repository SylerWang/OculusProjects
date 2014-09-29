// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Plane3<Real>, Ellipsoid3<Real>>::Result
TIQuery<Real, Plane3<Real>, Ellipsoid3<Real>>::operator()(
    Plane3<Real> const& plane, Ellipsoid3<Real> const& ellipsoid)
{
    Result result;
    Matrix3x3<Real> MInverse;
    ellipsoid.GetMInverse(MInverse);
    Real discr = Dot(plane.normal, MInverse * plane.normal);
    Real root = sqrt(std::max(discr, (Real)0));
    DCPQuery<Real, Vector3<Real>, Plane3<Real>> vpQuery;
    Real distance = vpQuery(ellipsoid.center, plane).distance;
    result.intersect = (distance <= root);
    return result;
}
//----------------------------------------------------------------------------
