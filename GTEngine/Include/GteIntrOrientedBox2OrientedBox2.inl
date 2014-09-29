// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, OrientedBox2<Real>, OrientedBox2<Real>>::Result
TIQuery<Real, OrientedBox2<Real>, OrientedBox2<Real>>::operator()(
    OrientedBox2<Real> const& box0, OrientedBox2<Real> const& box1)
{
    Result result;

    // Convenience variables.
    Vector2<Real> const* A0 = box0.axis;
    Vector2<Real> const* A1 = box1.axis;
    Vector2<Real> const& E0 = box0.extent;
    Vector2<Real> const& E1 = box1.extent;

    // Compute difference of box centers, D = C1-C0.
    Vector2<Real> D = box1.center - box0.center;

    Real absA0dA1[2][2], rSum;

    // Test box0.axis[0].
    absA0dA1[0][0] = std::abs(Dot(A0[0], A1[0]));
    absA0dA1[0][1] = std::abs(Dot(A0[0], A1[1]));
    rSum = E0[0] + E1[0] * absA0dA1[0][0] + E1[1] * absA0dA1[0][1];
    if (std::abs(Dot(A0[0], D)) > rSum)
    {
        result.intersect = false;
        result.separating = 0;
        return result;
    }

    // Test axis box0.axis[1].
    absA0dA1[1][0] = std::abs(Dot(A0[1], A1[0]));
    absA0dA1[1][1] = std::abs(Dot(A0[1], A1[1]));
    rSum = E0[1] + E1[0] * absA0dA1[1][0] + E1[1] * absA0dA1[1][1];
    if (std::abs(Dot(A0[1], D)) > rSum)
    {
        result.intersect = false;
        result.separating = 1;
        return result;
    }

    // Test axis box1.axis[0].
    rSum = E1[0] + E0[0] * absA0dA1[0][0] + E0[1] * absA0dA1[1][0];
    if (std::abs(Dot(A1[0], D)) > rSum)
    {
        result.intersect = false;
        result.separating = 2;
        return result;
    }

    // Test axis box1.axis[1].
    rSum = E1[1] + E0[0] * absA0dA1[0][1] + E0[1] * absA0dA1[1][1];
    if (std::abs(Dot(A1[1], D)) > rSum)
    {
        result.intersect = false;
        result.separating = 3;
        return result;
    }

    result.intersect = true;
    return result;
}
//----------------------------------------------------------------------------
