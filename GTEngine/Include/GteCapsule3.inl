// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Capsule3<Real>::Capsule3 ()
{
}
//----------------------------------------------------------------------------
template <typename Real>
Capsule3<Real>::Capsule3(Segment3<Real> const& inSegment, Real inRadius)
    :
    segment(inSegment),
    radius(inRadius)
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool Capsule3<Real>::IsEqualTo(Capsule3 const& capsule) const
{
    return segment == capsule.segment && radius == capsule.radius;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Capsule3<Real>::IsLessThan(Capsule3 const& capsule) const
{
    if (segment < capsule.segment)
    {
        return true;
    }

    if (segment < capsule.segment)
    {
        return false;
    }

    return radius < capsule.radius;
}
//----------------------------------------------------------------------------
