// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Line3<Real>, Cone3<Real>>::Result
FIQuery<Real, Line3<Real>, Cone3<Real>>::operator()(
    Line3<Real> const& line, Cone3<Real> const& cone)
{
    Result result;
    DoQuery(line.origin, line.direction, cone, result);
    switch (result.type)
    {
    case 1:  // point
        result.point[0] = line.origin + result.parameter[0] * line.direction;
        result.point[1] = result.point[0];
        break;
    case 2:  // segment
        result.point[0] = line.origin + result.parameter[0] * line.direction;
        result.point[1] = line.origin + result.parameter[1] * line.direction;
        break;
    case 3:  // ray
        result.point[0] = line.origin + result.parameter[0] * line.direction;
        result.point[1] = line.direction;
        break;
    case 4:  // ray
        result.point[0] = line.origin + result.parameter[1] * line.direction;
        result.point[1] = -line.direction;
        break;
    case 5:  // line
        result.point[0] = line.origin;
        result.point[1] = line.direction;
        break;
    default:  // no intersection
        break;
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void FIQuery<Real, Line3<Real>, Cone3<Real>>::DoQuery(
    Vector3<Real> const& lineOrigin, Vector3<Real> const& lineDirection,
    Cone3<Real> const& cone, Result& result)
{
    // The cone has vertex V, unit-length axis direction A, angle theta in
    // [0,pi/2), and height h in (0,+infinity).  The line is P + t*D, where D
    // is a unit-length direction vector.  Define g = cos(theta).  The cone
    // is represented by
    //   (X-V)^T * (A*A^T - g^2*I) * (X-V) = 0,  0 <= Dot(A, X-V) <= h
    // The first equation defines a double-sided cone.  The first inequality
    // in the second equation limits this to a single-sided cone containing
    // the ray V+s*A.  The second inequality in the second equation limits
    // the single-sided cone to the region bounded by the height.  Setting
    // X(t) = P + t*D, the equations are
    //   c2*t^2 + 2*c1*t + c0 = 0,  0 <= Dot(A,D)*t + Dot(A,P-V) <= h
    // where
    //   c2 = Dot(A,D)^2 - g^2
    //   c1 = Dot(A,D)*Dot(A,P-V) - g^2*Dot(D,P-V)
    //   c0 = Dot(A,P-V)^2 - g^2*Dot(P-V,P-V)
    // The following code computes the t-interval that satisfies the quadratic
    // equation subject to the linear inequality constraints.

    Vector3<Real> PmV = lineOrigin - cone.vertex;
    Real AdD = Dot(cone.axis, lineDirection);
    Real AdPmV = Dot(cone.axis, PmV);
    Real DdPmV = Dot(lineDirection, PmV);
    Real PmVdPmV = Dot(PmV, PmV);
    Real cosSqr = cone.cosAngle * cone.cosAngle;
    Real c2 = AdD*AdD - cosSqr;
    Real c1 = AdD*AdPmV - cosSqr*DdPmV;
    Real c0 = AdPmV*AdPmV - cosSqr*PmVdPmV;
    Real t;

    if (c2 != (Real)0)
    {
        // c2 != 0
        Real discr = c1*c1 - c0*c2;
        if (discr < (Real)0)
        {
            // The quadratic has no real-valued roots.  The line does not
            // intersect the double-sided cone.
            result.intersect = false;
            result.type = 0;
        }
        else if (discr >(Real)0)
        {
            // The quadratic has two distinct real-valued roots.  However,
            // one or both of them might intersect the single-sided cone
            // containing ray V-s*A.  We are interested only in those
            // intersections of the single-sided code containing ray V+s*A.
            Real root = sqrt(discr);
            Real invC2 = ((Real)1) / c2;
            int numParameters = 0;

            t = (-c1 - root)*invC2;
            if (AdD*t + AdPmV >= (Real)0)
            {
                result.parameter[numParameters++] = t;
            }

            t = (-c1 + root)*invC2;
            if (AdD*t + AdPmV >= (Real)0)
            {
                result.parameter[numParameters++] = t;
            }

            if (numParameters == 2)
            {
                // The line intersects twice the single-sided cone containing
                // ray V+s*A.
                result.intersect = true;
                result.type = 2;
                if (result.parameter[0] > result.parameter[1])
                {
                    std::swap(result.parameter[0], result.parameter[1]);
                }
            }
            else if (numParameters == 1)
            {
                // The line intersects once the single-sided cone containing
                // ray V+s*A.  The other intersection is with the other
                // single-sided cone and is not relevant.
                result.intersect = true;
                if (AdD > (Real)0)
                {
                    result.type = 3;
                    result.parameter[1] = std::numeric_limits<Real>::max();
                }
                else
                {
                    result.type = 4;
                    result.parameter[1] = result.parameter[0];
                    result.parameter[0] = -std::numeric_limits<Real>::max();

                }
            }
            else
            {
                // The line intersects the single-sided cone behind the vertex
                // twice.
                result.intersect = false;
                result.type = 0;
            }
        }
        else
        {
            // One repeated real root; the line is tangent to the cone.
            t = -c1 / c2;
            if (AdD*t + AdPmV >= (Real)0)
            {
                result.intersect = true;
                result.type = 1;
                result.parameter[0] = t;
                result.parameter[1] = t;
            }
            else
            {
                result.intersect = false;
                result.type = 0;
            }
        }
    }
    else if (c1 != (Real)0)
    {
        // c2 = 0, c1 != 0; D is a direction vector on the cone boundary
        t = -((Real)0.5)*c0 / c1;
        if (AdD*t + AdPmV >= (Real)0)
        {
            result.intersect = true;
            if (AdD > (Real)0)
            {
                result.type = 3;
                result.parameter[0] = t;
                result.parameter[1] = std::numeric_limits<Real>::max();
            }
            else
            {
                result.type = 4;
                result.parameter[0] = -std::numeric_limits<Real>::max();
                result.parameter[1] = t;
            }
        }
        else
        {
            result.intersect = false;
            result.type = 0;
        }
    }
    else if (c0 != (Real)0)
    {
        // c2 = c1 = 0, c0 != 0
        result.intersect = false;
        result.type = 0;
    }
    else
    {
        // c2 = c1 = c0 = 0; the line is on the cone boundary.
        result.intersect = true;
        result.type = 5;
        result.parameter[0] = -std::numeric_limits<Real>::max();
        result.parameter[1] = +std::numeric_limits<Real>::max();
    }

    if (cone.height < std::numeric_limits<Real>::max() && AdD != (Real)0)
    {
        // Clamp the intersection to the height of the cone.
        Real invAdD = ((Real)1) / AdD;
        std::array<Real, 2> hInterval;
        if (AdD > (Real)0)
        {
            hInterval[0] = -AdPmV * invAdD;
            hInterval[1] = (cone.height - AdPmV) * invAdD;
        }
        else // (AdD < (Real)0)
        {
            hInterval[0] = (cone.height - AdPmV) * invAdD;
            hInterval[1] = -AdPmV * invAdD;
        }

        FIQuery<Real, std::array<Real, 2>, std::array<Real, 2>> iiQuery;
        auto iiResult = iiQuery(result.parameter, hInterval);
        result.parameter = iiResult.overlap;
        result.type = iiResult.numIntersections;
    }
}
//----------------------------------------------------------------------------
