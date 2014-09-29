// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
bool GetContainer(int numPoints, Vector3<Real> const* points,
    OrientedBox3<Real>& box)
{
    // Fit the points with a Gaussian distribution.
    ApprGaussian3<Real> fitter;
    if (fitter.Fit(numPoints, points))
    {
        box = fitter.GetParameters();

        // Let C be the box center and let U0, U1, and U2 be the box axes.
        // Each input point is of the form X = C + y0*U0 + y1*U1 + y2*U2.
        // The following code computes min(y0), max(y0), min(y1), max(y1),
        // min(y2), and max(y2).  The box center is then adjusted to be
        //   C' = C + 0.5*(min(y0)+max(y0))*U0 + 0.5*(min(y1)+max(y1))*U1 +
        //        0.5*(min(y2)+max(y2))*U2

        Vector3<Real> diff = points[0] - box.center;
        Vector3<Real> pmin(Dot(diff, box.axis[0]), Dot(diff, box.axis[1]),
            Dot(diff, box.axis[2]));
        Vector3<Real> pmax = pmin;
        for (int i = 1; i < numPoints; ++i)
        {
            diff = points[i] - box.center;
            for (int j = 0; j < 3; ++j)
            {
                Real dot = Dot(diff, box.axis[j]);
                if (dot < pmin[j])
                {
                    pmin[j] = dot;
                }
                else if (dot > pmax[j])
                {
                    pmax[j] = dot;
                }
            }
        }

        for (int j = 0; j < 3; ++j)
        {
            box.center += (((Real)0.5)*(pmin[j] + pmax[j]))*box.axis[j];
            box.extent[j] = ((Real)0.5)*(pmax[j] - pmin[j]);
        }
        return true;
    }

    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool InContainer(Vector3<Real> const& point, OrientedBox3<Real> const& box)
{
    Vector3<Real> diff = point - box.center;
    for (int i = 0; i < 3; ++i)
    {
        Real coeff = Dot(diff, box.axis[i]);
        if (std::abs(coeff) > box.extent[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool MergeContainers(OrientedBox3<Real> const& box0,
    OrientedBox3<Real> const& box1, OrientedBox3<Real>& merge)
{
    // The first guess at the box center.  This value will be updated later
    // after the input box vertices are projected onto axes determined by an
    // average of box axes.
    merge.center = ((Real)0.5)*(box0.center + box1.center);

    // A box's axes, when viewed as the columns of a matrix, form a rotation
    // matrix.  The input box axes are converted to quaternions.  The average
    // quaternion is computed, then normalized to unit length.  The result is
    // the slerp of the two input quaternions with t-value of 1/2.  The result
    // is converted back to a rotation matrix and its columns are selected as
    // the merged box axes.
    Matrix3x3<Real> rot0(box0.axis, true);
    Matrix3x3<Real> rot1(box1.axis, true);
    Quaternion<Real> q0 = Rotation<3, Real>(rot0);
    Quaternion<Real> q1 = Rotation<3, Real>(rot1);
    if (Dot(q0, q1) < (Real)0)
    {
        q1 = -q1;
    }

    Quaternion<Real> q = q0 + q1;
    Real invLength = ((Real)1) / Length(q);
    q = invLength*q;
    Matrix<3, 3, Real> rot = Rotation<3, Real>(q);
    for (int j = 0; j < 3; ++j)
    {
        merge.axis[j] = rot.GetCol(j);
    }

    // Project the input box vertices onto the merged-box axes.  Each axis
    // D[i] containing the current center C has a minimum projected value
    // min[i] and a maximum projected value max[i].  The corresponding end
    // points on the axes are C+min[i]*D[i] and C+max[i]*D[i].  The point C
    // is not necessarily the midpoint for any of the intervals.  The actual
    // box center will be adjusted from C to a point C' that is the midpoint
    // of each interval,
    //   C' = C + sum_{i=0}^2 0.5*(min[i]+max[i])*D[i]
    // The box extents are
    //   e[i] = 0.5*(max[i]-min[i])

    Vector3<Real> vertex[8];
    Vector3<Real> pmin = Vector3<Real>::Zero();
    Vector3<Real> pmax = Vector3<Real>::Zero();

    box0.GetVertices(vertex);
    for (int i = 0; i < 8; ++i)
    {
        Vector3<Real> diff = vertex[i] - merge.center;
        for (int j = 0; j < 3; ++j)
        {
            Real dot = Dot(diff, merge.axis[j]);
            if (dot > pmax[j])
            {
                pmax[j] = dot;
            }
            else if (dot < pmin[j])
            {
                pmin[j] = dot;
            }
        }
    }

    box1.GetVertices(vertex);
    for (int i = 0; i < 8; ++i)
    {
        Vector3<Real> diff = vertex[i] - merge.center;
        for (int j = 0; j < 3; ++j)
        {
            Real dot = Dot(diff, merge.axis[j]);
            if (dot > pmax[j])
            {
                pmax[j] = dot;
            }
            else if (dot < pmin[j])
            {
                pmin[j] = dot;
            }
        }
    }

    // [min,max] is the axis-aligned box in the coordinate system of the
    // merged box axes.  Update the current box center to be the center of
    // the new box.  Compute the extents based on the new center.
    Real const half = (Real)0.5;
    for (int j = 0; j < 3; ++j)
    {
        merge.center += half*(pmax[j] + pmin[j])*merge.axis[j];
        merge.extent[j] = half*(pmax[j] - pmin[j]);
    }

    return true;
}
//----------------------------------------------------------------------------
