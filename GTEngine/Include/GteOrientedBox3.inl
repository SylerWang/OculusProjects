// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
OrientedBox3<Real>::OrientedBox3()
    :
    center(Vector3<Real>::Origin())
{
    for (int i = 0; i < 3; ++i)
    {
        axis[i] = Vector3<Real>::Unit(i);
        extent[i] = (Real)1;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
OrientedBox3<Real>::OrientedBox3(Vector3<Real> const& inCenter,
    Vector3<Real> const inAxis[3],
    Vector3<Real> const& inExtent)
    :
    center(inCenter),
    extent(inExtent)
{
    for (int i = 0; i < 3; ++i)
    {
        axis[i] = inAxis[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
OrientedBox3<Real>::OrientedBox3(Vector3<Real> const& inCenter,
    Vector3<Real> const& axis0, Vector3<Real> const& axis1,
    Vector3<Real> const& axis2, Real extent0, Real extent1, Real extent2)
    :
    center(inCenter)
{
    axis[0] = axis0;
    axis[1] = axis1;
    axis[2] = axis2;
    extent[0] = extent0;
    extent[1] = extent1;
    extent[2] = extent2;
}
//----------------------------------------------------------------------------
template <typename Real>
void OrientedBox3<Real>::GetVertices(Vector3<Real> vertex[8])
    const
{
    Vector3<Real> extAxis0 = extent[0] * axis[0];
    Vector3<Real> extAxis1 = extent[1] * axis[1];
    Vector3<Real> extAxis2 = extent[2] * axis[2];

    vertex[0] = center - extAxis0 - extAxis1 - extAxis2;
    vertex[1] = center + extAxis0 - extAxis1 - extAxis2;
    vertex[2] = center + extAxis0 + extAxis1 - extAxis2;
    vertex[3] = center - extAxis0 + extAxis1 - extAxis2;
    vertex[4] = center - extAxis0 - extAxis1 + extAxis2;
    vertex[5] = center + extAxis0 - extAxis1 + extAxis2;
    vertex[6] = center + extAxis0 + extAxis1 + extAxis2;
    vertex[7] = center - extAxis0 + extAxis1 + extAxis2;
}
//----------------------------------------------------------------------------
template <typename Real>
bool OrientedBox3<Real>::IsEqualTo(OrientedBox3 const& box) const
{
    if (center != box.center)
    {
        return false;
    }

    for (int i = 0; i < 3; ++i)
    {
        if (axis[i] != box.axis[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 3; ++i)
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
bool OrientedBox3<Real>::IsLessThan(OrientedBox3 const& box) const
{
    if (center < box.center)
    {
        return true;
    }

    if (center > box.center)
    {
        return false;
    }

    for (int i = 0; i < 3; ++i)
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

    for (int i = 0; i < 3; ++i)
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
