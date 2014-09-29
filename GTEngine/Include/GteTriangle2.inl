// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Triangle2<Real>::Triangle2()
{
    v[0] = Vector2<Real>::Origin();
    v[1] = Vector2<Real>::Basis0();
    v[2] = Vector2<Real>::Basis1();
}
//----------------------------------------------------------------------------
template <typename Real>
Triangle2<Real>::Triangle2(Vector2<Real> const& v0, Vector2<Real> const& v1,
    Vector2<Real> const& v2)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
}
//----------------------------------------------------------------------------
template <typename Real>
Triangle2<Real>::Triangle2(Vector2<Real> const inV[3])
{
    for (int i = 0; i < 3; ++i)
    {
        v[i] = inV[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
bool Triangle2<Real>::IsEqualTo(Triangle2 const& triangle) const
{
    return v[0] == triangle.v[0]
        && v[1] == triangle.v[1]
        && v[2] == triangle.v[2];
}
//----------------------------------------------------------------------------
template <typename Real>
bool Triangle2<Real>::IsLessThan(Triangle2 const& triangle) const
{
    for (int i = 0; i < 3; ++i)
    {
        if (v[i] < triangle.v[i])
        {
            return true;
        }

        if (v[i] > triangle.v[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
