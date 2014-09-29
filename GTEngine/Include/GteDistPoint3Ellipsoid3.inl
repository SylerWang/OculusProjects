// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector3<Real>, Ellipsoid3<Real>>::Result
DCPQuery<Real, Vector3<Real>, Ellipsoid3<Real>>::operator()(
    Vector3<Real> const& point, Ellipsoid3<Real> const& ellipsoid)
{
    Result result;

    // Compute coordinates of point in ellipsoid coordinate system.
    Vector3<Real> diff = point - ellipsoid.center;
    Real y[3], e[3];
    for (int i = 0; i < 2; ++i)
    {
        y[i] = Dot(diff, ellipsoid.axis[i]);
        e[i] = ellipsoid.extent[i];
    }

    // Compute the closest ellipsoid point.
    Real x[3];
    result.sqrDistance = SqrDistance(e, y, x);
    result.distance = sqrt(result.sqrDistance);
    result.ellipsoidClosestPoint = ellipsoid.center;
    for (int i = 0; i < 2; ++i)
    {
        result.ellipsoidClosestPoint += x[i] * ellipsoid.axis[i];
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
Real DCPQuery<Real, Vector3<Real>, Ellipsoid3<Real>>::SqrDistanceSpecial(
    Real const e[3], Real const y[3], Real x[3])
{
    Real sqrDistance, ePos[3], yPos[3], xPos[3];
    int i, numPos = 0;
    for (i = 0; i < 3; ++i)
    {
        if (y[i] > (Real)0)
        {
            ePos[numPos] = e[i];
            yPos[numPos] = y[i];
            ++numPos;
        }
        else
        {
            x[i] = (Real)0;
        }
    }

    if (y[2] > (Real)0)
    {
        sqrDistance = Bisector(numPos, ePos, yPos, xPos);
    }
    else  // y[2] = 0
    {
        Real e2Sqr = e[2]*e[2];
        Real denom[2], ey[2];
        for (i = 0; i < numPos; ++i)
        {
            denom[i] = ePos[i]*ePos[i] - e2Sqr;
            ey[i] = ePos[i]*yPos[i];
        }

        bool inAABBSubEllipse = true;
        for (i = 0; i < numPos; ++i)
        {
            if (ey[i] >= denom[i])
            {
                inAABBSubEllipse = false;
                break;
            }
        }

        bool inSubEllipse = false;
        sqrDistance = (Real)0;
        if (inAABBSubEllipse)
        {
            // yPos[] is inside the axis-aligned bounding box of the
            // subellipse.  This intermediate test is designed to guard
            // against the division by zero when ePos[i] == e[N-1] for some i.
            Real xde[2], discr = (Real)1;
            for (i = 0; i < numPos; ++i)
            {
                xde[i] = ey[i]/denom[i];
                discr -= xde[i]*xde[i];
            }
            if (discr > (Real)0)
            {
                // yPos[] is inside the subellipse.  The closest ellipsoid
                // point has x[2] > 0.
                sqrDistance = (Real)0;
                for (i = 0; i < numPos; ++i)
                {
                    xPos[i] = ePos[i]*xde[i];
                    Real diff = xPos[i] - yPos[i];
                    sqrDistance += diff*diff;
                }
                x[2] = e[2]*sqrt(discr);
                sqrDistance += x[2]*x[2];
                inSubEllipse = true;
            }
        }

        if (!inSubEllipse)
        {
            // yPos[] is outside the subellipse.  The closest ellipsoid
            // point has x[2] == 0 and is on the domain-boundary ellipse.
            x[2] = (Real)0;
            sqrDistance = Bisector(numPos, ePos, yPos, xPos);
        }
    }

    // Fill in those x[] values that were not zeroed out initially.
    for (i = 0, numPos = 0; i < 3; ++i)
    {
        if (y[i] > (Real)0)
        {
            x[i] = xPos[numPos];
            ++numPos;
        }
    }

    return sqrDistance;
}
//----------------------------------------------------------------------------
template <typename Real>
Real DCPQuery<Real, Vector3<Real>, Ellipsoid3<Real>>::SqrDistance(
    Real const e[3], Real const y[3], Real x[3])
{
    // Determine reflections for y to the first octant.
    bool reflect[3];
    int i, j;
    for (i = 0; i < 3; ++i)
    {
        reflect[i] = (y[i] < (Real)0);
    }

    // Determine the axis order for decreasing extents.
    int permute[3];
    if (e[0] < e[1])
    {
        if (e[2] < e[0])
        {
            permute[0] = 1;  permute[1] = 0;  permute[2] = 2;
        }
        else if (e[2] < e[1])
        {
            permute[0] = 1;  permute[1] = 2;  permute[2] = 0;
        }
        else
        {
            permute[0] = 2;  permute[1] = 1;  permute[2] = 0;
        }
    }
    else
    {
        if (e[2] < e[1])
        {
            permute[0] = 0;  permute[1] = 1;  permute[2] = 2;
        }
        else if (e[2] < e[0])
        {
            permute[0] = 0;  permute[1] = 2;  permute[2] = 1;
        }
        else
        {
            permute[0] = 2;  permute[1] = 0;  permute[2] = 1;
        }
    }

    int invpermute[3];
    for (i = 0; i < 3; ++i)
    {
        invpermute[permute[i]] = i;
    }

    Real locE[3], locY[3];
    for (i = 0; i < 3; ++i)
    {
        j = permute[i];
        locE[i] = e[j];
        locY[i] = y[j];
        if (reflect[j])
        {
            locY[i] = -locY[i];
        }
    }

    Real locX[3];
    Real sqrDistance = SqrDistanceSpecial(locE, locY, locX);

    // Restore the axis order and reflections.
    for (i = 0; i < 3; ++i)
    {
        j = invpermute[i];
        if (reflect[i])
        {
            locX[j] = -locX[j];
        }
        x[i] = locX[j];
    }

    return sqrDistance;
}
//----------------------------------------------------------------------------
template <typename Real>
Real DCPQuery<Real, Vector3<Real>, Ellipsoid3<Real>>::Bisector(
    int numComponents, Real const* e, Real const* y, Real* x)
{
    Real esqr[3], ey[3], argument = (Real)0;
    int i;
    for (i = 0; i < numComponents; ++i)
    {
        esqr[i] = e[i]*e[i];
        ey[i] = e[i]*y[i];
        argument += ey[i]*ey[i];
    }

    Real t0 = -esqr[numComponents-1] + ey[numComponents-1];
    Real t1 = -esqr[numComponents-1] + sqrt(argument);
    Real t = t0;
    int const jmax = 2*std::numeric_limits<Real>::max_exponent;
    for (int j = 0; j < jmax; ++j)
    {
        t = ((Real)0.5)*(t0 + t1);
        if (t == t0 || t == t1)
        {
            break;
        }

        Real f = (Real)-1;
        for (i = 0; i < numComponents; ++i)
        {
            Real r = ey[i]/(t + esqr[i]);
            f += r*r;
        }
        if (f > (Real)0)
        {
            t0 = t;
        }
        else if (f < (Real)0)
        {
            t1 = t;
        }
        else
        {
            break;
        }
    }

    Real sqrDistance = (Real)0;
    for (i = 0; i < numComponents; ++i)
    {
        x[i] = esqr[i]*y[i]/(t + esqr[i]);
        Real diff = x[i] - y[i];
        sqrDistance += diff*diff;
    }
    return sqrDistance;
}
//----------------------------------------------------------------------------
