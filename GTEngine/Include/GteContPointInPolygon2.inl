// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
PointInPolygon2<Real>::PointInPolygon2(int numPoints,
    Vector2<Real> const* points)
    :
    mNumPoints(numPoints),
    mPoints(points)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolygon2<Real>::Contains(Vector2<Real> const& p) const
{
    bool inside = false;
    for (int i = 0, j = mNumPoints-1; i < mNumPoints; j = i++)
    {
        Vector2<Real> const& U0 = mPoints[i];
        Vector2<Real> const& U1 = mPoints[j];
        Real rhs, lhs;

        if (p[1] < U1[1])  // U1 above ray
        {
            if (U0[1] <= p[1])  // U0 on or below ray
            {
                lhs = (p[1] - U0[1])*(U1[0] - U0[0]);
                rhs = (p[0] - U0[0])*(U1[1] - U0[1]);
                if (lhs > rhs)
                {
                    inside = !inside;
                }
            }
        }
        else if (p[1] < U0[1])  // U1 on or below ray, U0 above ray
        {
            lhs = (p[1] - U0[1])*(U1[0] - U0[0]);
            rhs = (p[0] - U0[0])*(U1[1] - U0[1]);
            if (lhs < rhs)
            {
                inside = !inside;
            }
        }
    }
    return inside;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolygon2<Real>::ContainsConvexOrderN(Vector2<Real> const& p) const
{
    for (int i1 = 0, i0 = mNumPoints-1; i1 < mNumPoints; i0 = i1++)
    {
        Real nx = mPoints[i1][1] - mPoints[i0][1];
        Real ny = mPoints[i0][0] - mPoints[i1][0];
        Real dx = p[0] - mPoints[i0][0];
        Real dy = p[1] - mPoints[i0][1];
        if (nx*dx + ny*dy > (Real)0)
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolygon2<Real>::ContainsConvexOrderLogN(Vector2<Real> const& p)
    const
{
    return SubContainsPoint(p, 0, 0);
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolygon2<Real>::ContainsQuadrilateral(Vector2<Real> const& p)
    const
{
    if (mNumPoints != 4)
    {
        return false;
    }

    Real nx = mPoints[2][1] - mPoints[0][1];
    Real ny = mPoints[0][0] - mPoints[2][0];
    Real dx = p[0] - mPoints[0][0];
    Real dy = p[1] - mPoints[0][1];

    if (nx*dx + ny*dy > (Real)0)
    {
        // P potentially in <V0,V1,V2>
        nx = mPoints[1][1] - mPoints[0][1];
        ny = mPoints[0][0] - mPoints[1][0];
        if (nx*dx + ny*dy > (Real)0.0)
        {
            return false;
        }

        nx = mPoints[2][1] - mPoints[1][1];
        ny = mPoints[1][0] - mPoints[2][0];
        dx = p[0] - mPoints[1][0];
        dy = p[1] - mPoints[1][1];
        if (nx*dx + ny*dy > (Real)0)
        {
            return false;
        }
    }
    else
    {
        // P potentially in <V0,V2,V3>
        nx = mPoints[0][1] - mPoints[3][1];
        ny = mPoints[3][0] - mPoints[0][0];
        if (nx*dx + ny*dy > (Real)0)
        {
            return false;
        }

        nx = mPoints[3][1] - mPoints[2][1];
        ny = mPoints[2][0] - mPoints[3][0];
        dx = p[0] - mPoints[3][0];
        dy = p[1] - mPoints[3][1];
        if (nx*dx + ny*dy > (Real)0)
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool PointInPolygon2<Real>::SubContainsPoint(Vector2<Real> const& p, int i0,
    int i1) const
{
    Real nx, ny, dx, dy;

    int diff = i1 - i0;
    if (diff == 1 || (diff < 0 && diff + mNumPoints == 1))
    {
        nx = mPoints[i1][1] - mPoints[i0][1];
        ny = mPoints[i0][0] - mPoints[i1][0];
        dx = p[0] - mPoints[i0][0];
        dy = p[1] - mPoints[i0][1];
        return nx*dx + ny*dy <= (Real)0;
    }

    // Bisect the index range.
    int mid;
    if (i0 < i1)
    {
        mid = (i0 + i1) >> 1;
    }
    else
    {
        mid = ((i0 + i1 + mNumPoints) >> 1);
        if (mid >= mNumPoints)
        {
            mid -= mNumPoints;
        }
    }

    // Determine which side of the splitting line contains the point.
    nx = mPoints[mid][1] - mPoints[i0][1];
    ny = mPoints[i0][0] - mPoints[mid][0];
    dx = p[0] - mPoints[i0][0];
    dy = p[1] - mPoints[i0][1];
    if (nx*dx + ny*dy > (Real)0)
    {
        // P potentially in <V(i0),V(i0+1),...,V(mid-1),V(mid)>
        return SubContainsPoint(p, i0, mid);
    }
    else
    {
        // P potentially in <V(mid),V(mid+1),...,V(i1-1),V(i1)>
        return SubContainsPoint(p, mid, i1);
    }
}
//----------------------------------------------------------------------------
