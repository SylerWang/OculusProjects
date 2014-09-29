// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
bool GetContainer(int numPoints, Vector3<Real> const* points,
    Cylinder3<Real>& cylinder)
{
    ApprOrthogonalLine3<Real> fitter;
    fitter.Fit(numPoints, points);
    Line3<Real> line = fitter.GetParameters();

    DCPQuery<Real, Vector3<Real>, Line3<Real>> plQuery;
    Real maxRadiusSqr = (Real)0;
    for (int i = 0; i < numPoints; ++i)
    {
        auto result = plQuery(points[i], line);
        if (result.sqrDistance > maxRadiusSqr)
        {
            maxRadiusSqr = result.sqrDistance;
        }
    }

    Vector3<Real> diff = points[0] - line.origin;
    Real wMin = Dot(line.direction, diff);
    Real wMax = wMin;
    for (int i = 1; i < numPoints; ++i)
    {
        diff = points[i] - line.origin;
        Real w = Dot(line.direction, diff);
        if (w < wMin)
        {
            wMin = w;
        }
        else if (w > wMax)
        {
            wMax = w;
        }
    }

    cylinder.axis.origin = line.origin +
        (((Real)0.5)*(wMax + wMin))*line.direction;
    cylinder.axis.direction = line.direction;
    cylinder.radius = sqrt(maxRadiusSqr);
    cylinder.height = wMax - wMin;
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool InContainer(Vector3<Real> const& point, Cylinder3<Real> const& cylinder)
{
    Vector3<Real> diff = point - cylinder.axis.origin;
    Real zProj = Dot(diff, cylinder.axis.direction);
    if (std::abs(zProj)*(Real)2 > cylinder.height)
    {
        return false;
    }

    Vector3<Real> xyProj = diff - zProj*cylinder.axis.direction;
    return Length(xyProj) <= cylinder.radius;
}
//----------------------------------------------------------------------------
