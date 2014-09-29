// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Ray2<Real>, Ray2<Real>>::Result
DCPQuery<Real, Ray2<Real>, Ray2<Real>>::operator()(
    Ray2<Real> const& ray0, Ray2<Real> const& ray1)
{
    Result result;

    Vector2<Real> diff = ray0.origin - ray1.origin;
    Real a01 = -Dot(ray0.direction, ray1.direction);
    Real b0 = Dot(diff, ray0.direction);
    Real c = Dot(diff, diff);
    Real det = std::abs((Real)1 - a01*a01);
    Real b1, s0, s1;

    if (det > (Real)0)
    {
        // Rays are not parallel.
        b1 = -Dot(diff, ray1.direction);
        s0 = a01*b1 - b0;
        s1 = a01*b0 - b1;

        if (s0 >= (Real)0)
        {
            if (s1 >= (Real)0)  // region 0 (interior)
            {
                // Minimum at two interior points of rays.
                Real invDet = ((Real)1) / det;
                s0 *= invDet;
                s1 *= invDet;
                result.sqrDistance = (Real)0;
            }
            else  // region 3 (side)
            {
                s1 = (Real)0;
                if (b0 >= (Real)0)
                {
                    s0 = (Real)0;
                    result.sqrDistance = c;
                }
                else
                {
                    s0 = -b0;
                    result.sqrDistance = b0*s0 + c;
                }
            }
        }
        else
        {
            if (s1 >= (Real)0)  // region 1 (side)
            {
                s0 = (Real)0;
                if (b1 >= (Real)0)
                {
                    s1 = (Real)0;
                    result.sqrDistance = c;
                }
                else
                {
                    s1 = -b1;
                    result.sqrDistance = b1*s1 + c;
                }
            }
            else  // region 2 (corner)
            {
                if (b0 < (Real)0)
                {
                    s0 = -b0;
                    s1 = (Real)0;
                    result.sqrDistance = b0*s0 + c;
                }
                else
                {
                    s0 = (Real)0;
                    if (b1 >= (Real)0)
                    {
                        s1 = (Real)0;
                        result.sqrDistance = c;
                    }
                    else
                    {
                        s1 = -b1;
                        result.sqrDistance = b1*s1 + c;
                    }
                }
            }
        }
    }
    else
    {
        // Rays are parallel.
        if (a01 > (Real)0.0)
        {
            // Opposite direction vectors.
            s1 = (Real)0;
            if (b0 >= (Real)0)
            {
                s0 = (Real)0;
                result.sqrDistance = c;
            }
            else
            {
                s0 = -b0;
                result.sqrDistance = b0*s0 + c;
            }
        }
        else
        {
            // Same direction vectors.
            if (b0 >= (Real)0)
            {
                b1 = -Dot(diff, ray1.direction);
                s0 = (Real)0;
                s1 = -b1;
                result.sqrDistance = b1*s1 + c;
            }
            else
            {
                s0 = -b0;
                s1 = (Real)0;
                result.sqrDistance = b0*s0 + c;
            }
        }
    }

    // Account for numerical round-off errors.
    if (result.sqrDistance < (Real)0)
    {
        result.sqrDistance = (Real)0;
    }

    result.distance = sqrt(result.sqrDistance);
    result.closestPoint[0] = ray0.origin + s0*ray0.direction;
    result.closestPoint[1] = ray1.origin + s1*ray1.direction;
    return result;
}
//----------------------------------------------------------------------------
