// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
OrientedBox2<Real>::OrientedBox2()
    :
    center(Vector2<Real>::Origin())
{
    for (int i = 0; i < 2; ++i)
    {
        axis[i] = Vector2<Real>::Unit(i);
        extent[i] = (Real)1;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
OrientedBox2<Real>::OrientedBox2(Vector2<Real> const& inCenter,
    Vector2<Real> const inAxis[2], Vector2<Real> const& inExtent)
    :
    center(inCenter)
{
    for (int i = 0; i < 2; ++i)
    {
        axis[i] = inAxis[i];
        extent[i] = inExtent[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
OrientedBox2<Real>::OrientedBox2(Vector2<Real> const& inCenter,
    Vector2<Real> const& axis0, Vector2<Real> const& axis1, Real extent0,
    Real extent1)
    :
    center(inCenter)
{
    axis[0] = axis0;
    axis[1] = axis1;
    extent[0] = extent0;
    extent[1] = extent1;
}
//----------------------------------------------------------------------------
template <typename Real>
void OrientedBox2<Real>::GetVertices(Vector2<Real> vertex[4])
    const
{
    Vector2<Real> extAxis0 = extent[0] * axis[0];
    Vector2<Real> extAxis1 = extent[1] * axis[1];

    vertex[0] = center - extAxis0 - extAxis1;
    vertex[1] = center + extAxis0 - extAxis1;
    vertex[2] = center + extAxis0 + extAxis1;
    vertex[3] = center - extAxis0 + extAxis1;
}
//----------------------------------------------------------------------------
template <typename Real>
bool OrientedBox2<Real>::IsEqualTo(OrientedBox2 const& box) const
{
    if (center != box.center)
    {
        return false;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (axis[i] != box.axis[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        if (extent[i] != box.extent[i])
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool OrientedBox2<Real>::IsLessThan(OrientedBox2 const& box) const
{
    if (center < box.center)
    {
        return true;
    }

    if (center > box.center)
    {
        return false;
    }

    for (int i = 0; i < 2; ++i)
    {
        if (axis[i] < box.axis[i])
        {
            return true;
        }
        if (axis[i] > box.axis[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        if (extent[i] < box.extent[i])
        {
            return true;
        }
        if (extent[i] > box.extent[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
