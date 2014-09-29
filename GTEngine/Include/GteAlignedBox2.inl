// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
AlignedBox2<Real>::AlignedBox2()
{
    for (int i = 0; i < 2; ++i)
    {
        min[i] = (Real)-1;
        max[i] = (Real)+1;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
AlignedBox2<Real>::AlignedBox2(Real const inMin[2], Real const inMax[2])
{
    for (int i = 0; i < 2; ++i)
    {
        min[i] = inMin[i];
        max[i] = inMax[i];
    }
}
//----------------------------------------------------------------------------
template <typename Real>
AlignedBox2<Real>::AlignedBox2(Real min0, Real min1, Real max0, Real max1)
{
    min[0] = min0;
    min[1] = min1;
    max[0] = max0;
    max[1] = max1;
}
//----------------------------------------------------------------------------
template <typename Real>
void AlignedBox2<Real>::GetCenteredForm(Vector2<Real>& center,
    Vector2<Real>& extent) const
{
    center[0] = ((Real)0.5)*(max[0] + min[0]);
    center[1] = ((Real)0.5)*(max[1] + min[1]);
    extent[0] = ((Real)0.5)*(max[0] - min[0]);
    extent[1] = ((Real)0.5)*(max[1] - min[1]);
}
//----------------------------------------------------------------------------
template <typename Real>
bool AlignedBox2<Real>::IsEqualTo(AlignedBox2 const& box) const
{
    for (int i = 0; i < 2; ++i)
    {
        if (min[i] != box.min[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        if (max[i] != box.max[i])
        {
            return false;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool AlignedBox2<Real>::IsLessThan(AlignedBox2 const& box) const
{
    for (int i = 0; i < 2; ++i)
    {
        if (min[i] < box.min[i])
        {
            return true;
        }
        if (min[i] > box.min[i])
        {
            return false;
        }
    }

    for (int i = 0; i < 2; ++i)
    {
        if (max[i] < box.max[i])
        {
            return true;
        }
        if (max[i] > box.max[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
