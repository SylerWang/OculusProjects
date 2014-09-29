// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, AlignedBox3<Real>, AlignedBox3<Real>>::Result
TIQuery<Real, AlignedBox3<Real>, AlignedBox3<Real>>::operator()(
    AlignedBox3<Real> const& box0, AlignedBox3<Real> const& box1)
{
    Result result;
    for (int i = 0; i < 3; i++)
    {
        if (box0.max[i] < box1.min[i] || box0.min[i] > box1.max[i])
        {
            result.intersect = false;
            return result;
        }
    }
    result.intersect = true;
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, AlignedBox3<Real>, AlignedBox3<Real>>::Result
FIQuery<Real, AlignedBox3<Real>, AlignedBox3<Real>>::operator()(
    AlignedBox3<Real> const& box0, AlignedBox3<Real> const& box1)
{
    Result result;
    for (int i = 0; i < 3; i++)
    {
        if (box0.max[i] < box1.min[i] || box0.min[i] > box1.max[i])
        {
            result.intersect = false;
            return result;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (box0.max[i] <= box1.max[i])
        {
            result.box.max[i] = box0.max[i];
        }
        else
        {
            result.box.max[i] = box1.max[i];
        }

        if (box0.min[i] <= box1.min[i])
        {
            result.box.min[i] = box1.min[i];
        }
        else
        {
            result.box.min[i] = box0.min[i];
        }
    }
    result.intersect = true;
    return result;
}
//----------------------------------------------------------------------------
