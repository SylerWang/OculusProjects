// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/08/19)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Line3<Real>, OrientedBox3<Real>>::Result
TIQuery<Real, Line3<Real>, OrientedBox3<Real>>::operator()(
    Line3<Real> const& line, OrientedBox3<Real> const& box)
{
    // Transform the line to the oriented-box coordinate system.
    Vector3<Real> diff = line.origin - box.center;
    Vector3<Real> lineOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1]),
        Dot(diff, box.axis[2])
    );
    Vector3<Real> lineDirection
    (
        Dot(line.direction, box.axis[0]),
        Dot(line.direction, box.axis[1]),
        Dot(line.direction, box.axis[2])
    );

    Result result;
    this->DoQuery(lineOrigin, lineDirection, box.extent, result);
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line3<Real>, OrientedBox3<Real>>::Result
FIQuery<Real, Line3<Real>, OrientedBox3<Real>>::operator()(
    Line3<Real> const& line, OrientedBox3<Real> const& box)
{
    // Transform the line to the oriented-box coordinate system.
    Vector3<Real> diff = line.origin - box.center;
    Vector3<Real> lineOrigin
    (
        Dot(diff, box.axis[0]),
        Dot(diff, box.axis[1]),
        Dot(diff, box.axis[2])
    );
    Vector3<Real> lineDirection
    (
        Dot(line.direction, box.axis[0]),
        Dot(line.direction, box.axis[1]),
        Dot(line.direction, box.axis[2])
    );

    Result result;
    this->DoQuery(lineOrigin, lineDirection, box.extent, result);
    for (int i = 0; i < result.numPoints; ++i)
    {
        result.point[i] =
            line.origin + result.lineParameter[i] * line.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
