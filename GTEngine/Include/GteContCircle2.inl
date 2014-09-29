// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
bool GetContainer(int numPoints, Vector2<Real> const* points,
    Circle2<Real>& circle)
{
    circle.center = points[0];
    for (int i = 1; i < numPoints; ++i)
    {
        circle.center += points[i];
    }
    circle.center /= (Real)numPoints;

    for (int i = 0; i < numPoints; ++i)
    {
        Vector2<Real> diff = points[i] - circle.center;
        Real radiusSqr = Dot(diff, diff);
        if (radiusSqr > circle.radius)
        {
            circle.radius = radiusSqr;
        }
    }

    circle.radius = sqrt(circle.radius);
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool InContainer(Vector2<Real> const& point, Circle2<Real> const& circle)
{
    Vector2<Real> diff = point - circle.center;
    return Length(diff) <= circle.radius;
}
//----------------------------------------------------------------------------
template <typename Real>
bool MergeContainers(Circle2<Real> const& circle0,
    Circle2<Real> const& circle1, Circle2<Real>& merge)
{
    Vector2<Real> cenDiff = circle1.center - circle0.center;
    Real lenSqr = Dot(cenDiff, cenDiff);
    Real rDiff = circle1.radius - circle0.radius;
    Real rDiffSqr = rDiff*rDiff;

    if (rDiffSqr >= lenSqr)
    {
        merge = (rDiff >= (Real)0 ? circle1 : circle0);
    }
    else
    {
        Real length = sqrt(lenSqr);
        if (length > (Real)0)
        {
            Real coeff = (length + rDiff) / (((Real)2)*length);
            merge.center = circle0.center + coeff*cenDiff;
        }
        else
        {
            merge.center = circle0.center;
        }

        merge.radius = ((Real)0.5)*(length + circle0.radius + circle1.radius);
    }

    return true;
}
//----------------------------------------------------------------------------
