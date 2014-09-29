// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Arc2<Real>::Arc2()
    :
    center(Vector2<Real>::Zero()),
    radius((Real)1)
{
    end[0] = Vector2<Real>::Basis0();
    end[1] = Vector2<Real>::Basis1();
}
//----------------------------------------------------------------------------
template <typename Real>
Arc2<Real>::Arc2(Vector2<Real> const& inCenter, Real inRadius,
    Vector2<Real>const& inEnd0, Vector2<Real>const & inEnd1)
    :
    center(inCenter),
    radius(inRadius)
{
    end[0] = inEnd0;
    end[1] = inEnd1;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Arc2<Real>::Contains(Vector2<Real> const& p) const
{
    // Assert: |P-C| = R where P is the input point, C is the circle center,
    // and R is the circle radius.  For P to be on the arc from A to B, it
    // must be on the side of the plane containing A with normal N = Perp(B-A)
    // where Perp(u,v) = (v,-u).

    Vector2<Real> diffPE0 = p - end[0];
    Vector2<Real> diffE1E0 = end[1] - end[0];
    Real dotPerp = DotPerp(diffPE0, diffE1E0);
    return dotPerp >= (Real)0;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Arc2<Real>::IsEqualTo(Arc2 const& arc) const
{
    return center == arc.center && radius == arc.radius
        && end[0] == arc.end[0] && end[1] == arc.end[1];
}
//----------------------------------------------------------------------------
template <typename Real>
bool Arc2<Real>::IsLessThan(Arc2 const& arc) const
{
    if (center < arc.center)
    {
        return true;
    }

    if (center > arc.center)
    {
        return false;
    }

    if (radius < arc.radius)
    {
        return true;
    }

    if (radius > arc.radius)
    {
        return false;
    }

    if (end[0] < arc.end[0])
    {
        return true;
    }

    if (end[0] > arc.end[0])
    {
        return false;
    }

    return end[1] < arc.end[1];
}
//----------------------------------------------------------------------------
