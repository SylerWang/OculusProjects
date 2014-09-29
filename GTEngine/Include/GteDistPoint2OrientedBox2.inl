// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector2<Real>, OrientedBox2<Real>>::Result
DCPQuery<Real, Vector2<Real>, OrientedBox2<Real>>::operator()(
    Vector2<Real> const& point, OrientedBox2<Real> const& box)
{
    // Translate the point to the coordinate system of the box.  In this
    // system, the box is axis-aligned with center at the origin.
    Vector2<Real> diff = point - box.center;
    Vector2<Real> closest;
    for (int i = 0; i < 2; ++i)
    {
        closest[i] = Dot(diff, box.axis[i]);
    }

    Result result;
    this->DoQuery(closest, box.extent, result);

    // Compute the closest point on the box.
    result.boxClosestPoint = box.center;
    for (int i = 0; i < 2; ++i)
    {
        result.boxClosestPoint += closest[i] * box.axis[i];
    }
    return result;
}
//----------------------------------------------------------------------------
