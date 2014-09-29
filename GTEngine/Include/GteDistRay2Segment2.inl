// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Ray2<Real>, Segment2<Real>>::Result
DCPQuery<Real, Ray2<Real>, Segment2<Real>>::operator()(
    Ray2<Real> const& ray, Segment2<Real> const& segment)
{
    Result result;

    Vector2<Real> segCenter, segDirection;
    Real segExtent;
    segment.GetCenteredForm(segCenter, segDirection, segExtent);

    Vector2<Real> diff = ray.origin - segCenter;
    Real a01 = -Dot(ray.direction, segDirection);
    Real b0 = Dot(diff, ray.direction);
    Real b1 = -Dot(diff, segDirection);
    Real c = Dot(diff, diff);
    Real det = std::abs((Real)1 - a01*a01);
    Real s0, s1, extDet;

    if (det > (Real)0)
    {
        // The ray and segment are not parallel.
        s0 = a01*b1 - b0;
        s1 = a01*b0 - b1;
        extDet = segExtent*det;

        if (s0 >= (Real)0)
        {
            if (s1 >= -extDet)
            {
                if (s1 <= extDet)  // region 0
                {
                    // Minimum at interior points of ray and segment.
                    Real invDet = ((Real)1) / det;
                    s0 *= invDet;
                    s1 *= invDet;
                    result.sqrDistance = (Real)0;
                }
                else  // region 1
                {
                    s1 = segExtent;
                    s0 = -(a01*s1 + b0);
                    if (s0 > (Real)0)
                    {
                        result.sqrDistance =
                            -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                    }
                    else
                    {
                        s0 = (Real)0;
                        result.sqrDistance = s1*(s1 + ((Real)2)*b1) + c;
                    }
                }
            }
            else  // region 5
            {
                s1 = -segExtent;
                s0 = -(a01*s1 + b0);
                if (s0 > (Real)0)
                {
                    result.sqrDistance =
                        -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                }
                else
                {
                    s0 = (Real)0;
                    result.sqrDistance = s1*(s1 + ((Real)2)*b1) + c;
                }
            }
        }
        else
        {
            if (s1 <= -extDet)  // region 4
            {
                s0 = -(-a01*segExtent + b0);
                if (s0 > (Real)0)
                {
                    s1 = -segExtent;
                    result.sqrDistance =
                        -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                }
                else
                {
                    s0 = (Real)0;
                    s1 = -b1;
                    if (s1 < -segExtent)
                    {
                        s1 = -segExtent;
                    }
                    else if (s1 > segExtent)
                    {
                        s1 = segExtent;
                    }
                    result.sqrDistance = s1*(s1 + ((Real)2)*b1) + c;
                }
            }
            else if (s1 <= extDet)  // region 3
            {
                s0 = (Real)0;
                s1 = -b1;
                if (s1 < -segExtent)
                {
                    s1 = -segExtent;
                }
                else if (s1 > segExtent)
                {
                    s1 = segExtent;
                }
                result.sqrDistance = s1*(s1 + ((Real)2)*b1) + c;
            }
            else  // region 2
            {
                s0 = -(a01*segExtent + b0);
                if (s0 > (Real)0)
                {
                    s1 = segExtent;
                    result.sqrDistance = -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                }
                else
                {
                    s0 = (Real)0;
                    s1 = -b1;
                    if (s1 < -segExtent)
                    {
                        s1 = -segExtent;
                    }
                    else if (s1 > segExtent)
                    {
                        s1 = segExtent;
                    }
                    result.sqrDistance = s1*(s1 + ((Real)2)*b1) + c;
                }
            }
        }
    }
    else
    {
        // Ray and segment are parallel.
        if (a01 > (Real)0)
        {
            // Opposite direction vectors.
            s1 = -segExtent;
        }
        else
        {
            // Same direction vectors.
            s1 = segExtent;
        }

        s0 = -(a01*s1 + b0);
        if (s0 > (Real)0)
        {
            result.sqrDistance = -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
        }
        else
        {
            s0 = (Real)0;
            result.sqrDistance = s1*(s1 + ((Real)2)*b1) + c;
        }
    }

    // Account for numerical round-off errors.
    if (result.sqrDistance < (Real)0)
    {
        result.sqrDistance = (Real)0;
    }

    result.distance = sqrt(result.sqrDistance);
    result.closestPoint[0] = ray.origin + s0*ray.direction;
    result.closestPoint[1] = segCenter + s1*segDirection;
    return result;
}
//----------------------------------------------------------------------------
