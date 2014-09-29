// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line3<Real>, Cylinder3<Real>>::Result
FIQuery<Real, Line3<Real>, Cylinder3<Real>>::operator()(
    Line3<Real> const& line, Cylinder3<Real> const& cylinder)
{
    Result result;
    DoQuery(line.origin, line.direction, cylinder, result);
    for (int i = 0; i < result.numIntersections; ++i)
    {
        result.point[i] = line.origin + result.parameter[i] * line.direction;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void FIQuery<Real, Line3<Real>, Cylinder3<Real>>::DoQuery(
    Vector3<Real> const& lineOrigin, Vector3<Real> const& lineDirection,
    Cylinder3<Real> const& cylinder, Result& result)
{
    // Create a coordinate system for the cylinder.  In this system, the
    // cylinder segment center C is the origin and the cylinder axis direction
    // W is the z-axis.  U and V are the other coordinate axis directions.
    // If P = x*U+y*V+z*W, the cylinder is x^2 + y^2 = r^2, where r is the
    // cylinder radius.  The end caps are |z| = h/2, where h is the cylinder
    // height.
    Vector3<Real> basis[3];  // {W, U, V}
    basis[0] = cylinder.axis.direction;
    ComputeOrthogonalComplement(1, basis);
    Real halfHeight = ((Real)0.5)*cylinder.height;
    Real rSqr = cylinder.radius * cylinder.radius;

    // Convert incoming line origin to capsule coordinates.
    Vector3<Real> diff = lineOrigin - cylinder.axis.origin;
    Vector3<Real> P(Dot(basis[1], diff), Dot(basis[2], diff),
        Dot(basis[0], diff));

    // Get the z-value, in cylinder coordinates, of the incoming line's
    // unit-length direction.
    Real dz = Dot(basis[0], lineDirection);
    if (std::abs(dz) == (Real)1)
    {
        // The line is parallel to the cylinder axis.  Determine whether the
        // line intersects the cylinder end disks.
        Real radialSqrDist = rSqr - P[0]*P[0] - P[1]*P[1];
        if (radialSqrDist < (Real)0)
        {
            // The line is outside the cylinder, so there is no intersection.
            result.intersect = false;
            result.numIntersections = 0;
            return;
        }

        // The line intersects the cylinder end disks.
        result.intersect = true;
        result.numIntersections = 2;
        if (dz > (Real)0)
        {
            result.parameter[0] = -P[2] - halfHeight;
            result.parameter[1] = -P[2] + halfHeight;
        }
        else
        {
            result.parameter[0] = P[2] - halfHeight;
            result.parameter[1] = P[2] + halfHeight;
        }
        return;
    }

    // Convert the incoming line unit-length direction to cylinder
    // coordinates.
    Vector3<Real> D(Dot(basis[1], lineDirection),
        Dot(basis[2], lineDirection), dz);

    Real a0, a1, a2, discr, root, inv, tValue;

    if (D[2] == (Real)0)
    {
        // The line is perpendicular to the cylinder axis.
        if (std::abs(P[2]) > halfHeight)
        {
            // The line is outside the planes of the cylinder end disks.
            result.intersect = false;
            result.numIntersections = 0;
            return;
        }

        // Test intersection of line P+t*D with infinite cylinder
        // x^2+y^2 = r^2.  This reduces to computing the roots of a
        // quadratic equation.  If P = (px,py,pz) and D = (dx,dy,dz),
        // then the quadratic equation is
        //   (dx^2+dy^2)*t^2 + 2*(px*dx+py*dy)*t + (px^2+py^2-r^2) = 0
        a0 = P[0]*P[0] + P[1]*P[1] - rSqr;
        a1 = P[0]*D[0] + P[1]*D[1];
        a2 = D[0]*D[0] + D[1]*D[1];
        discr = a1*a1 - a0*a2;
        if (discr < (Real)0)
        {
            // The line does not intersect the cylinder.
            result.intersect = false;
            result.numIntersections = 0;
            return;
        }
        else if (discr > (Real)0)
        {
            // The line intersects the cylinder in two places.
            result.intersect = true;
            result.numIntersections = 2;
            root = sqrt(discr);
            inv = ((Real)1)/a2;
            result.parameter[0] = (-a1 - root)*inv;
            result.parameter[1] = (-a1 + root)*inv;
            return;
        }
        else
        {
            // The line is tangent to the cylinder.
            result.intersect = true;
            result.numIntersections = 1;
            result.parameter[0] = -a1 / a2;
            // Used by derived classes.
            result.parameter[1] = result.parameter[0];
            return;
        }
    }

    // Test plane intersections first.
    result.numIntersections = 0;
    inv = ((Real)1.0)/D[2];

    Real t0 = (-halfHeight - P[2])*inv;
    Real xTmp = P[0] + t0*D[0];
    Real yTmp = P[1] + t0*D[1];
    if (xTmp*xTmp + yTmp*yTmp <= rSqr)
    {
        // Planar intersection inside the top cylinder end disk.
        result.parameter[result.numIntersections++] = t0;
    }

    Real t1 = (+halfHeight - P[2])*inv;
    xTmp = P[0] + t1*D[0];
    yTmp = P[1] + t1*D[1];
    if (xTmp*xTmp + yTmp*yTmp <= rSqr)
    {
        // Planar intersection inside the bottom cylinder end disk.
        result.parameter[result.numIntersections++] = t1;
    }

    if (result.numIntersections == 2)
    {
        // Line intersects both top and bottom cylinder end disks.
        if (result.parameter[0] > result.parameter[1])
        {
            std::swap(result.parameter[0], result.parameter[1]);
        }
        return;
    }

    // If numIntersections == 1, then the line must intersect cylinder wall
    // in a single point somewhere between the end disks.  This case is
    // detected in the following code that tests for intersection between
    // line and cylinder wall.
    a0 = P[0]*P[0] + P[1]*P[1] - rSqr;
    a1 = P[0]*D[0] + P[1]*D[1];
    a2 = D[0]*D[0] + D[1]*D[1];
    discr = a1*a1 - a0*a2;
    if (discr < (Real)0)
    {
        // Line does not intersect cylinder wall.
        LogError("Unexpected condition.");
        result.intersect = false;
        result.numIntersections = 0;
        return;
    }
    else if (discr > (Real)0)
    {
        root = sqrt(discr);
        inv = ((Real)1)/a2;
        tValue = (-a1 - root)*inv;
        if (t0 <= t1)
        {
            if (t0 <= tValue && tValue <= t1)
            {
                result.intersect = true;
                result.parameter[result.numIntersections++] = tValue;
            }
        }
        else
        {
            if (t1 <= tValue && tValue <= t0)
            {
                result.intersect = true;
                result.parameter[result.numIntersections++] = tValue;
            }
        }

        if (result.numIntersections == 2)
        {
            // Line intersects one of the cylinder end disks and once on the
            // cylinder wall.
            if (result.parameter[0] > result.parameter[1])
            {
                std::swap(result.parameter[0], result.parameter[1]);
            }
            return;
        }

        tValue = (-a1 + root)*inv;
        if (t0 <= t1)
        {
            if (t0 <= tValue && tValue <= t1)
            {
                result.intersect = true;
                result.parameter[result.numIntersections++] = tValue;
            }
        }
        else
        {
            if (t1 <= tValue && tValue <= t0)
            {
                result.intersect = true;
                result.parameter[result.numIntersections++] = tValue;
            }
        }
    }
    else
    {
        tValue = -a1/a2;
        if (t0 <= t1)
        {
            if (t0 <= tValue && tValue <= t1)
            {
                result.intersect = true;
                result.parameter[result.numIntersections++] = tValue;
            }
        }
        else
        {
            if (t1 <= tValue && tValue <= t0)
            {
                result.intersect = true;
                result.parameter[result.numIntersections++] = tValue;
            }
        }
    }

    if (result.numIntersections == 2)
    {
        if (result.parameter[0] > result.parameter[1])
        {
            std::swap(result.parameter[0], result.parameter[1]);
        }
        return;
    }

    if (result.numIntersections == 1)
    {
        // Used by derived classes.
        result.parameter[1] = result.parameter[0];
    }
}
//----------------------------------------------------------------------------
