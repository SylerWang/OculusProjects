// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector3<Real>, AlignedBox3<Real>>::Result
DCPQuery<Real, Vector3<Real>, AlignedBox3<Real>>::operator()(
    Vector3<Real> const& point, AlignedBox3<Real> const& box)
{
    // Translate the point and box so that the box has center at the origin.
    Vector3<Real> boxCenter, boxExtent;
    box.GetCenteredForm(boxCenter, boxExtent);
    Vector3<Real> closest = point - boxCenter;

    Result result;
    DoQuery(closest, boxExtent, result);

    // Compute the closest point on the box.
    result.boxClosestPoint = boxCenter + closest;
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void DCPQuery<Real, Vector3<Real>, AlignedBox3<Real>>::DoQuery(
    Vector3<Real>& point, Vector3<Real> const& boxExtent, Result& result)
{
    result.sqrDistance = (Real)0;
    for (int i = 0; i < 3; ++i)
    {
        if (point[i] < -boxExtent[i])
        {
            Real delta = point[i] + boxExtent[i];
            result.sqrDistance += delta*delta;
            point[i] = -boxExtent[i];
        }
        else if (point[i] > boxExtent[i])
        {
            Real delta = point[i] - boxExtent[i];
            result.sqrDistance += delta*delta;
            point[i] = boxExtent[i];
        }
    }
    result.distance = sqrt(result.sqrDistance);
}
//----------------------------------------------------------------------------
