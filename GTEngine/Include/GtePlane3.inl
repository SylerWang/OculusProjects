// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Plane3<Real>::Plane3()
    :
    normal((Real)0, (Real)0, (Real)1),
    constant((Real)0)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Plane3<Real>::Plane3(Vector3<Real> const& inNormal, Real inConstant)
    :
    normal(inNormal),
    constant(inConstant)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Plane3<Real>::Plane3(Vector3<Real> const& inNormal, Vector3<Real> const& p)
    :
    normal(inNormal)
{
    constant = Dot(normal, p);
}
//----------------------------------------------------------------------------
template <typename Real>
Plane3<Real>::Plane3(Vector3<Real> const p[3])
{
    Vector3<Real> edge1 = p[1] - p[0];
    Vector3<Real> edge2 = p[2] - p[0];
    normal = UnitCross(edge1, edge2);
    constant = Dot(normal, p[0]);
}
//----------------------------------------------------------------------------
template <typename Real>
Plane3<Real>::Plane3(Vector3<Real> const& p0, Vector3<Real> const& p1,
    Vector3<Real> const& p2)
{
    Vector3<Real> edge1 = p1 - p0;
    Vector3<Real> edge2 = p2 - p0;
    normal = UnitCross(edge1, edge2);
    constant = Dot(normal, p0);
}
//----------------------------------------------------------------------------
template <typename Real>
bool Plane3<Real>::IsEqualTo(Plane3 const& plane) const
{
    return normal == plane.normal && constant == plane.constant;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Plane3<Real>::IsLessThan(Plane3 const& plane) const
{
    if (normal < plane.normal)
    {
        return true;
    }

    if (normal > plane.normal)
    {
        return false;
    }

    return constant < plane.constant;
}
//----------------------------------------------------------------------------
