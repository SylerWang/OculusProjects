// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Plane3<Real>, Circle3<Real>>::Result
TIQuery<Real, Plane3<Real>, Circle3<Real>>::operator()(
    Plane3<Real> const& plane, Circle3<Real> const& circle)
{
    Result result;

    // Construct the plane of the circle.
    Plane3<Real> cPlane(circle.normal, circle.center);

    // Compute the intersection of this plane with the input plane.
    FIQuery<Real, Plane3<Real>, Plane3<Real>> ppQuery;
    auto ppResult = ppQuery(plane, cPlane);
    if (!ppResult.intersect)
    {
        // Planes are parallel and nonintersecting.
        result.intersect = false;
        return result;
    }

    if (!ppResult.isLine)
    {
        // Planes are the same, the circle is the common intersection set.
        result.intersect = true;
        return result;
    }

    // The planes intersect in a line.  Locate one or two points that are on
    // the circle and line.  If the line is t*D+P, the circle center is C,
    // and the circle radius is r, then
    //   r^2 = |t*D+P-C|^2 = |D|^2*t^2 + 2*Dot(D,P-C)*t + |P-C|^2
    // This is a quadratic equation of the form a2*t^2 + 2*a1*t + a0 = 0.
    Vector3<Real> diff = ppResult.line.origin - circle.center;
    Real a2 = Dot(ppResult.line.direction, ppResult.line.direction);
    Real a1 = Dot(diff, ppResult.line.direction);
    Real a0 = Dot(diff, diff) - circle.radius*circle.radius;

    // Real-valued roots imply an intersection.
    Real discr = a1*a1 - a0*a2;
    result.intersect = (discr >= (Real)0);
    return result;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Plane3<Real>, Circle3<Real>>::Result
FIQuery<Real, Plane3<Real>, Circle3<Real>>::operator()(
    Plane3<Real> const& plane, Circle3<Real> const& circle)
{
    Result result;

    // Construct the plane of the circle.
    Plane3<Real> cPlane(circle.normal, circle.center);

    // Compute the intersection of this plane with the input plane.
    FIQuery<Real, Plane3<Real>, Plane3<Real>> ppQuery;
    auto ppResult = ppQuery(plane, cPlane);
    if (!ppResult.intersect)
    {
        // Planes are parallel and nonintersecting.
        result.intersect = false;
        return result;
    }

    if (!ppResult.isLine)
    {
        // Planes are the same, the circle is the common intersection set.
        result.intersect = true;
        result.isPoints = false;
        result.circle = circle;
        return result;
    }

    // The planes intersect in a line.  Locate one or two points that are on
    // the circle and line.  If the line is t*D+P, the circle center is C,
    // and the circle radius is r, then
    //   r^2 = |t*D+P-C|^2 = |D|^2*t^2 + 2*Dot(D,P-C)*t + |P-C|^2
    // This is a quadratic equation of the form a2*t^2 + 2*a1*t + a0 = 0.
    Vector3<Real> diff = ppResult.line.origin - circle.center;
    Real a2 = Dot(ppResult.line.direction, ppResult.line.direction);
    Real a1 = Dot(diff, ppResult.line.direction);
    Real a0 = Dot(diff, diff) - circle.radius*circle.radius;

    Real discr = a1*a1 - a0*a2;
    if (discr < (Real)0)
    {
        // No real roots, the circle does not intersect the plane.
        result.intersect = false;
        return result;
    }

    result.isPoints = true;

    Real inv = ((Real)1)/a2;
    if (discr == (Real)0)
    {
        // One repeated root, the circle just touches the plane.
        result.numIntersections = 1;
        result.point[0] =
            ppResult.line.origin - (a1*inv)*ppResult.line.direction;
        return result;
    }

    // Two distinct, real-valued roots, the circle intersects the plane in
    // two points.
    Real root = sqrt(discr);
    result.numIntersections = 2;
    result.point[0] =
        ppResult.line.origin - ((a1 + root)*inv)*ppResult.line.direction;
    result.point[1] =
        ppResult.line.origin - ((a1 - root)*inv)*ppResult.line.direction;
    return result;
}
//----------------------------------------------------------------------------
