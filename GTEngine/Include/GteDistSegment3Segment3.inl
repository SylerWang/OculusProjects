// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Segment3<Real>, Segment3<Real>>::Result
DCPQuery<Real, Segment3<Real>, Segment3<Real>>::operator()(
    Segment3<Real> const& segment0, Segment3<Real> const& segment1)
{
    Result result;

    Vector3<Real> seg0Center, seg0Direction, seg1Center, seg1Direction;
    Real seg0Extent, seg1Extent;
    segment0.GetCenteredForm(seg0Center, seg0Direction, seg0Extent);
    segment1.GetCenteredForm(seg1Center, seg1Direction, seg1Extent);

    Vector3<Real> diff = seg0Center - seg1Center;
    Real a01 = -Dot(seg0Direction, seg1Direction);
    Real b0 = Dot(diff, seg0Direction);
    Real b1 = -Dot(diff, seg1Direction);
    Real c = Dot(diff, diff);
    Real det = std::abs((Real)1 - a01*a01);
    Real s0, s1, extDet0, extDet1, tmpS0, tmpS1;

    if (det > (Real)0)
    {
        // Segments are not parallel.
        s0 = a01*b1 - b0;
        s1 = a01*b0 - b1;
        extDet0 = seg0Extent*det;
        extDet1 = seg1Extent*det;

        if (s0 >= -extDet0)
        {
            if (s0 <= extDet0)
            {
                if (s1 >= -extDet1)
                {
                    if (s1 <= extDet1)  // region 0 (interior)
                    {
                        // Minimum at interior points of segments.
                        Real invDet = ((Real)1) / det;
                        s0 *= invDet;
                        s1 *= invDet;
                        result.sqrDistance = s0*(s0 + a01*s1 + ((Real)2)*b0) +
                            s1*(a01*s0 + s1 + ((Real)2)*b1) + c;
                    }
                    else  // region 3 (side)
                    {
                        s1 = seg1Extent;
                        tmpS0 = -(a01*s1 + b0);
                        if (tmpS0 < -seg0Extent)
                        {
                            s0 = -seg0Extent;
                            result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                                s1*(s1 + ((Real)2)*b1) + c;
                        }
                        else if (tmpS0 <= seg0Extent)
                        {
                            s0 = tmpS0;
                            result.sqrDistance =
                                -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                        }
                        else
                        {
                            s0 = seg0Extent;
                            result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                                s1*(s1 + ((Real)2)*b1) + c;
                        }
                    }
                }
                else  // region 7 (side)
                {
                    s1 = -seg1Extent;
                    tmpS0 = -(a01*s1 + b0);
                    if (tmpS0 < -seg0Extent)
                    {
                        s0 = -seg0Extent;
                        result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                            s1*(s1 + ((Real)2)*b1) + c;
                    }
                    else if (tmpS0 <= seg0Extent)
                    {
                        s0 = tmpS0;
                        result.sqrDistance =
                            -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                    }
                    else
                    {
                        s0 = seg0Extent;
                        result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                            s1*(s1 + ((Real)2)*b1) + c;
                    }
                }
            }
            else
            {
                if (s1 >= -extDet1)
                {
                    if (s1 <= extDet1)  // region 1 (side)
                    {
                        s0 = seg0Extent;
                        tmpS1 = -(a01*s0 + b1);
                        if (tmpS1 < -seg1Extent)
                        {
                            s1 = -seg1Extent;
                            result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                                s0*(s0 + ((Real)2)*b0) + c;
                        }
                        else if (tmpS1 <= seg1Extent)
                        {
                            s1 = tmpS1;
                            result.sqrDistance =
                                -s1*s1 + s0*(s0 + ((Real)2)*b0) + c;
                        }
                        else
                        {
                            s1 = seg1Extent;
                            result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                                s0*(s0 + ((Real)2)*b0) + c;
                        }
                    }
                    else  // region 2 (corner)
                    {
                        s1 = seg1Extent;
                        tmpS0 = -(a01*s1 + b0);
                        if (tmpS0 < -seg0Extent)
                        {
                            s0 = -seg0Extent;
                            result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                                s1*(s1 + ((Real)2)*b1) + c;
                        }
                        else if (tmpS0 <= seg0Extent)
                        {
                            s0 = tmpS0;
                            result.sqrDistance =
                                -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                        }
                        else
                        {
                            s0 = seg0Extent;
                            tmpS1 = -(a01*s0 + b1);
                            if (tmpS1 < -seg1Extent)
                            {
                                s1 = -seg1Extent;
                                result.sqrDistance =
                                    s1*(s1 - ((Real)2)*tmpS1) +
                                    s0*(s0 + ((Real)2)*b0) + c;
                            }
                            else if (tmpS1 <= seg1Extent)
                            {
                                s1 = tmpS1;
                                result.sqrDistance =
                                    -s1*s1 + s0*(s0 + ((Real)2)*b0) + c;
                            }
                            else
                            {
                                s1 = seg1Extent;
                                result.sqrDistance =
                                    s1*(s1 - ((Real)2)*tmpS1) +
                                    s0*(s0 + ((Real)2)*b0) + c;
                            }
                        }
                    }
                }
                else  // region 8 (corner)
                {
                    s1 = -seg1Extent;
                    tmpS0 = -(a01*s1 + b0);
                    if (tmpS0 < -seg0Extent)
                    {
                        s0 = -seg0Extent;
                        result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                            s1*(s1 + ((Real)2)*b1) + c;
                    }
                    else if (tmpS0 <= seg0Extent)
                    {
                        s0 = tmpS0;
                        result.sqrDistance =
                            -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                    }
                    else
                    {
                        s0 = seg0Extent;
                        tmpS1 = -(a01*s0 + b1);
                        if (tmpS1 > seg1Extent)
                        {
                            s1 = seg1Extent;
                            result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                                s0*(s0 + ((Real)2)*b0) + c;
                        }
                        else if (tmpS1 >= -seg1Extent)
                        {
                            s1 = tmpS1;
                            result.sqrDistance =
                                -s1*s1 + s0*(s0 + ((Real)2)*b0) + c;
                        }
                        else
                        {
                            s1 = -seg1Extent;
                            result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                                s0*(s0 + ((Real)2)*b0) + c;
                        }
                    }
                }
            }
        }
        else
        {
            if (s1 >= -extDet1)
            {
                if (s1 <= extDet1)  // region 5 (side)
                {
                    s0 = -seg0Extent;
                    tmpS1 = -(a01*s0 + b1);
                    if (tmpS1 < -seg1Extent)
                    {
                        s1 = -seg1Extent;
                        result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                            s0*(s0 + ((Real)2)*b0) + c;
                    }
                    else if (tmpS1 <= seg1Extent)
                    {
                        s1 = tmpS1;
                        result.sqrDistance =
                            -s1*s1 + s0*(s0 + ((Real)2)*b0) + c;
                    }
                    else
                    {
                        s1 = seg1Extent;
                        result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                            s0*(s0 + ((Real)2)*b0) + c;
                    }
                }
                else  // region 4 (corner)
                {
                    s1 = seg1Extent;
                    tmpS0 = -(a01*s1 + b0);
                    if (tmpS0 > seg0Extent)
                    {
                        s0 = seg0Extent;
                        result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                            s1*(s1 + ((Real)2)*b1) + c;
                    }
                    else if (tmpS0 >= -seg0Extent)
                    {
                        s0 = tmpS0;
                        result.sqrDistance =
                            -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                    }
                    else
                    {
                        s0 = -seg0Extent;
                        tmpS1 = -(a01*s0 + b1);
                        if (tmpS1 < -seg1Extent)
                        {
                            s1 = -seg1Extent;
                            result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                                s0*(s0 + ((Real)2)*b0) + c;
                        }
                        else if (tmpS1 <= seg1Extent)
                        {
                            s1 = tmpS1;
                            result.sqrDistance =
                                -s1*s1 + s0*(s0 + ((Real)2)*b0) + c;
                        }
                        else
                        {
                            s1 = seg1Extent;
                            result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                                s0*(s0 + ((Real)2)*b0) + c;
                        }
                    }
                }
            }
            else   // region 6 (corner)
            {
                s1 = -seg1Extent;
                tmpS0 = -(a01*s1 + b0);
                if (tmpS0 > seg0Extent)
                {
                    s0 = seg0Extent;
                    result.sqrDistance = s0*(s0 - ((Real)2)*tmpS0) +
                        s1*(s1 + ((Real)2)*b1) + c;
                }
                else if (tmpS0 >= -seg0Extent)
                {
                    s0 = tmpS0;
                    result.sqrDistance =
                        -s0*s0 + s1*(s1 + ((Real)2)*b1) + c;
                }
                else
                {
                    s0 = -seg0Extent;
                    tmpS1 = -(a01*s0 + b1);
                    if (tmpS1 < -seg1Extent)
                    {
                        s1 = -seg1Extent;
                        result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                            s0*(s0 + ((Real)2)*b0) + c;
                    }
                    else if (tmpS1 <= seg1Extent)
                    {
                        s1 = tmpS1;
                        result.sqrDistance =
                            -s1*s1 + s0*(s0 + ((Real)2)*b0) + c;
                    }
                    else
                    {
                        s1 = seg1Extent;
                        result.sqrDistance = s1*(s1 - ((Real)2)*tmpS1) +
                            s0*(s0 + ((Real)2)*b0) + c;
                    }
                }
            }
        }
    }
    else
    {
        // The segments are parallel.  The average b0 term is designed to
        // ensure symmetry of the function.  That is, dist(seg0,seg1) and
        // dist(seg1,seg0) should produce the same number.
        Real e0pe1 = seg0Extent + seg1Extent;
        Real sign = (a01 > (Real)0 ? (Real)-1 : (Real)1);
        Real b0Avr = ((Real)0.5)*(b0 - sign*b1);
        Real lambda = -b0Avr;
        if (lambda < -e0pe1)
        {
            lambda = -e0pe1;
        }
        else if (lambda > e0pe1)
        {
            lambda = e0pe1;
        }

        s1 = -sign*lambda*seg1Extent / e0pe1;
        s0 = lambda + sign*s1;
        result.sqrDistance = lambda*(lambda + ((Real)2)*b0Avr) + c;
    }

    // Account for numerical round-off errors.
    if (result.sqrDistance < (Real)0)
    {
        result.sqrDistance = (Real)0;
    }
    result.distance = sqrt(result.sqrDistance);
    result.parameter[0] = s0;
    result.parameter[1] = s1;
    result.closestPoint[0] = seg0Center + s0*seg0Direction;
    result.closestPoint[1] = seg1Center + s1*seg1Direction;
    return result;
}
//----------------------------------------------------------------------------
