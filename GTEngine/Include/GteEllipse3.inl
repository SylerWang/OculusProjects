// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Ellipse3<Real>::Ellipse3()
    :
    center(Vector3<Real>::Zero()),
    normal(Vector3<Real>::Basis2()),
    extent((Real)1, (Real)1)
{
    axis[0] = Vector3<Real>::Basis0();
    axis[1] = Vector3<Real>::Basis1();
}
//----------------------------------------------------------------------------
template <typename Real>
Ellipse3<Real>::Ellipse3(Vector3<Real> const& inCenter,
    Vector3<Real> const& inNormal, Vector3<Real> const inAxis[2],
    Vector2<Real> const& inExtent)
    :
    center(inCenter),
    normal(inNormal),
    extent(inExtent)
{
    for (int i = 0; i < 2; ++i)
    {
        axis[i] = inAxis[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipse3<Real>::IsEqualTo(Ellipse3 const& ellipse) const
{
    return center == ellipse.center
        && normal == ellipse.normal
        && axis[0] == ellipse.axis[0]
        && axis[1] == ellipse.axis[1]
        && extent == ellipse.extent;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Ellipse3<Real>::IsLessThan(Ellipse3 const& ellipse) const
{
    if (center < ellipse.center)
    {
        return true;
    }

    if (center > ellipse.center)
    {
        return false;
    }

    if (normal < ellipse.normal)
    {
        return true;
    }

    if (normal > ellipse.normal)
    {
        return false;
    }

    if (axis[0] < ellipse.axis[0])
    {
        return true;
    }

    if (axis[0] > ellipse.axis[0])
    {
        return false;
    }

    if (axis[1] < ellipse.axis[1])
    {
        return true;
    }

    if (axis[1] > ellipse.axis[1])
    {
        return false;
    }

    return extent < ellipse.extent;
}
//----------------------------------------------------------------------------
