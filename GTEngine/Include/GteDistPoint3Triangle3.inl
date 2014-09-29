// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector3<Real>, Triangle3<Real>>::Result
DCPQuery<Real, Vector3<Real>, Triangle3<Real>>::operator()(
    Vector3<Real> const& point, Triangle3<Real> const& triangle)
{
    Result result;

    Vector3<Real> diff = triangle.v[0] - point;
    Vector3<Real> edge0 = triangle.v[1] - triangle.v[0];
    Vector3<Real> edge1 = triangle.v[2] - triangle.v[0];
    Real a00 = Dot(edge0, edge0);
    Real a01 = Dot(edge0, edge1);
    Real a11 = Dot(edge1, edge1);
    Real b0 = Dot(diff, edge0);
    Real b1 = Dot(diff, edge1);
    Real c = Dot(diff, diff);
    Real det = std::abs(a00*a11 - a01*a01);
    Real s = a01*b1 - a11*b0;
    Real t = a01*b0 - a00*b1;

    if (s + t <= det)
    {
        if (s < (Real)0)
        {
            if (t < (Real)0)  // region 4
            {
                if (b0 < (Real)0)
                {
                    t = (Real)0;
                    if (-b0 >= a00)
                    {
                        s = (Real)1;
                        result.sqrDistance = a00 + ((Real)2)*b0 + c;
                    }
                    else
                    {
                        s = -b0 / a00;
                        result.sqrDistance = b0*s + c;
                    }
                }
                else
                {
                    s = (Real)0;
                    if (b1 >= (Real)0)
                    {
                        t = (Real)0;
                        result.sqrDistance = c;
                    }
                    else if (-b1 >= a11)
                    {
                        t = (Real)1;
                        result.sqrDistance = a11 + ((Real)2)*b1 + c;
                    }
                    else
                    {
                        t = -b1 / a11;
                        result.sqrDistance = b1*t + c;
                    }
                }
            }
            else  // region 3
            {
                s = (Real)0;
                if (b1 >= (Real)0)
                {
                    t = (Real)0;
                    result.sqrDistance = c;
                }
                else if (-b1 >= a11)
                {
                    t = (Real)1;
                    result.sqrDistance = a11 + ((Real)2)*b1 + c;
                }
                else
                {
                    t = -b1 / a11;
                    result.sqrDistance = b1*t + c;
                }
            }
        }
        else if (t < (Real)0)  // region 5
        {
            t = (Real)0;
            if (b0 >= (Real)0)
            {
                s = (Real)0;
                result.sqrDistance = c;
            }
            else if (-b0 >= a00)
            {
                s = (Real)1;
                result.sqrDistance = a00 + ((Real)2)*b0 + c;
            }
            else
            {
                s = -b0 / a00;
                result.sqrDistance = b0*s + c;
            }
        }
        else  // region 0
        {
            // minimum at interior point
            Real invDet = ((Real)1) / det;
            s *= invDet;
            t *= invDet;
            result.sqrDistance = s*(a00*s + a01*t + ((Real)2)*b0) +
                t*(a01*s + a11*t + ((Real)2)*b1) + c;
        }
    }
    else
    {
        Real tmp0, tmp1, numer, denom;

        if (s < (Real)0)  // region 2
        {
            tmp0 = a01 + b0;
            tmp1 = a11 + b1;
            if (tmp1 > tmp0)
            {
                numer = tmp1 - tmp0;
                denom = a00 - ((Real)2)*a01 + a11;
                if (numer >= denom)
                {
                    s = (Real)1;
                    t = (Real)0;
                    result.sqrDistance = a00 + ((Real)2)*b0 + c;
                }
                else
                {
                    s = numer / denom;
                    t = (Real)1 - s;
                    result.sqrDistance = s*(a00*s + a01*t + ((Real)2)*b0) +
                        t*(a01*s + a11*t + ((Real)2)*b1) + c;
                }
            }
            else
            {
                s = (Real)0;
                if (tmp1 <= (Real)0)
                {
                    t = (Real)1;
                    result.sqrDistance = a11 + ((Real)2)*b1 + c;
                }
                else if (b1 >= (Real)0)
                {
                    t = (Real)0;
                    result.sqrDistance = c;
                }
                else
                {
                    t = -b1 / a11;
                    result.sqrDistance = b1*t + c;
                }
            }
        }
        else if (t < (Real)0)  // region 6
        {
            tmp0 = a01 + b1;
            tmp1 = a00 + b0;
            if (tmp1 > tmp0)
            {
                numer = tmp1 - tmp0;
                denom = a00 - ((Real)2)*a01 + a11;
                if (numer >= denom)
                {
                    t = (Real)1;
                    s = (Real)0;
                    result.sqrDistance = a11 + ((Real)2)*b1 + c;
                }
                else
                {
                    t = numer / denom;
                    s = (Real)1 - t;
                    result.sqrDistance = s*(a00*s + a01*t + ((Real)2)*b0) +
                        t*(a01*s + a11*t + ((Real)2)*b1) + c;
                }
            }
            else
            {
                t = (Real)0;
                if (tmp1 <= (Real)0)
                {
                    s = (Real)1;
                    result.sqrDistance = a00 + ((Real)2)*b0 + c;
                }
                else if (b0 >= (Real)0)
                {
                    s = (Real)0;
                    result.sqrDistance = c;
                }
                else
                {
                    s = -b0 / a00;
                    result.sqrDistance = b0*s + c;
                }
            }
        }
        else  // region 1
        {
            numer = a11 + b1 - a01 - b0;
            if (numer <= (Real)0)
            {
                s = (Real)0;
                t = (Real)1;
                result.sqrDistance = a11 + ((Real)2)*b1 + c;
            }
            else
            {
                denom = a00 - ((Real)2)*a01 + a11;
                if (numer >= denom)
                {
                    s = (Real)1;
                    t = (Real)0;
                    result.sqrDistance = a00 + ((Real)2)*b0 + c;
                }
                else
                {
                    s = numer / denom;
                    t = (Real)1 - s;
                    result.sqrDistance = s*(a00*s + a01*t + ((Real)2)*b0) +
                        t*(a01*s + a11*t + ((Real)2)*b1) + c;
                }
            }
        }
    }

    // Account for numerical round-off error.
    if (result.sqrDistance < (Real)0)
    {
        result.sqrDistance = (Real)0;
    }

    result.distance = sqrt(result.sqrDistance);
    result.triangleClosestPoint = triangle.v[0] + s*edge0 + t*edge1;
    result.triangleParameter[1] = s;
    result.triangleParameter[2] = t;
    result.triangleParameter[0] = (Real)1 - s - t;
    return result;
}
//----------------------------------------------------------------------------
