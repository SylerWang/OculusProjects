// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Halfspace3<Real>::Halfspace3()
    :
    normal((Real)0, (Real)0, (Real)1),
    constant((Real)0)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Halfspace3<Real>::Halfspace3(Vector3<Real> const& inNormal, Real inConstant)
    :
    normal(inNormal),
    constant(inConstant)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Halfspace3<Real>::IsEqualTo(Halfspace3 const& halfspace) const
{
    return normal == halfspace.normal && constant == halfspace.constant;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Halfspace3<Real>::IsLessThan(Halfspace3 const& halfspace) const
{
    if (normal < halfspace.normal)
    {
        return true;
    }

    if (normal > halfspace.normal)
    {
        return false;
    }

    return constant < halfspace.constant;
}
//----------------------------------------------------------------------------
