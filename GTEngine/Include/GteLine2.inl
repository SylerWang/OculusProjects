// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Line2<Real>::Line2()
    :
    origin(Vector2<Real>::Origin()),
    direction(Vector2<Real>::Basis0())
{
}
//----------------------------------------------------------------------------
template <typename Real>
Line2<Real>::Line2 (Vector2<Real> const& inOrigin,
    Vector2<Real> const& inDirection)
    :
    origin(inOrigin),
    direction(inDirection)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Line2<Real>::IsEqualTo(Line2 const& line) const
{
    return origin == line.origin && direction == line.direction;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Line2<Real>::IsLessThan(Line2 const& line) const
{
    if (origin < line.origin)
    {
        return true;
    }

    if (origin > line.origin)
    {
        return false;
    }

    return direction < line.direction;
}
//----------------------------------------------------------------------------
