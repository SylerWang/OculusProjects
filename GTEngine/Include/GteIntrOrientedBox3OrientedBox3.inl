// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
TIQuery<Real, OrientedBox3<Real>, OrientedBox3<Real>>::Result::
Result(Real inEpsilon)
{
    if (inEpsilon >= (Real)0)
    {
        epsilon = inEpsilon;
    }
    else
    {
        epsilon = (Real)0;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, OrientedBox3<Real>, OrientedBox3<Real>>::Result
TIQuery<Real, OrientedBox3<Real>, OrientedBox3<Real>>::operator()(
    OrientedBox3<Real> const& box0, OrientedBox3<Real> const& box1)
{
    Result result;

    // Convenience variables.
    Vector3<Real> const& C0 = box0.center;
    Vector3<Real> const* A0 = box0.axis;
    Vector3<Real> const& E0 = box0.extent;
    Vector3<Real> const& C1 = box1.center;
    Vector3<Real> const* A1 = box1.axis;
    Vector3<Real> const& E1 = box1.extent;

    const Real cutoff = (Real)1 - result.epsilon;
    bool existsParallelPair = false;

    // Compute difference of box centers.
    Vector3<Real> D = C1 - C0;

    Real dot01[3][3];       // dot01[i][j] = Dot(A0[i],A1[j]) = A1[j][i]
    Real absDot01[3][3];    // |dot01[i][j]|
    Real dotDA0[3];         // Dot(D, A0[i])
    Real r0, r1, r;         // interval radii and distance between centers
    Real r01;               // r0 + r1

    // Test for separation on the axis C0 + t*A0[0].
    for (int i = 0; i < 3; ++i)
    {
        dot01[0][i] = Dot(A0[0], A1[i]);
        absDot01[0][i] = std::abs(dot01[0][i]);
        if (absDot01[0][i] > cutoff)
        {
            existsParallelPair = true;
        }
    }
    dotDA0[0] = Dot(D, A0[0]);
    r = std::abs(dotDA0[0]);
    r1 = E1[0] * absDot01[0][0] + E1[1] * absDot01[0][1] + E1[2] * absDot01[0][2];
    r01 = E0[0] + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 0;
        result.separating[1] = -1;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[1].
    for (int i = 0; i < 3; ++i)
    {
        dot01[1][i] = Dot(A0[1], A1[i]);
        absDot01[1][i] = std::abs(dot01[1][i]);
        if (absDot01[1][i] > cutoff)
        {
            existsParallelPair = true;
        }
    }
    dotDA0[1] = Dot(D, A0[1]);
    r = std::abs(dotDA0[1]);
    r1 = E1[0] * absDot01[1][0] + E1[1] * absDot01[1][1] + E1[2] * absDot01[1][2];
    r01 = E0[1] + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 1;
        result.separating[1] = -1;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[2].
    for (int i = 0; i < 3; ++i)
    {
        dot01[2][i] = Dot(A0[2], A1[i]);
        absDot01[2][i] = std::abs(dot01[2][i]);
        if (absDot01[2][i] > cutoff)
        {
            existsParallelPair = true;
        }
    }
    dotDA0[2] = Dot(D, A0[2]);
    r = std::abs(dotDA0[2]);
    r1 = E1[0] * absDot01[2][0] + E1[1] * absDot01[2][1] + E1[2] * absDot01[2][2];
    r01 = E0[2] + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 2;
        result.separating[1] = -1;
        return result;
    }

    // Test for separation on the axis C0 + t*A1[0].
    r = std::abs(Dot(D, A1[0]));
    r0 = E0[0] * absDot01[0][0] + E0[1] * absDot01[1][0] + E0[2] * absDot01[2][0];
    r01 = r0 + E1[0];
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = -1;
        result.separating[1] = 0;
        return result;
    }

    // Test for separation on the axis C0 + t*A1[1].
    r = std::abs(Dot(D, A1[1]));
    r0 = E0[0] * absDot01[0][1] + E0[1] * absDot01[1][1] + E0[2] * absDot01[2][1];
    r01 = r0 + E1[1];
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = -1;
        result.separating[1] = 1;
        return result;
    }

    // Test for separation on the axis C0 + t*A1[2].
    r = std::abs(Dot(D, A1[2]));
    r0 = E0[0] * absDot01[0][2] + E0[1] * absDot01[1][2] + E0[2] * absDot01[2][2];
    r01 = r0 + E1[2];
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = -1;
        result.separating[1] = 2;
        return result;
    }

    // At least one pair of box axes was parallel, so the separation is
    // effectively in 2D.  The edge-edge axes do not need to be tested.
    if (existsParallelPair)
    {
        return true;
    }

    // Test for separation on the axis C0 + t*A0[0]xA1[0].
    r = std::abs(dotDA0[2] * dot01[1][0] - dotDA0[1] * dot01[2][0]);
    r0 = E0[1] * absDot01[2][0] + E0[2] * absDot01[1][0];
    r1 = E1[1] * absDot01[0][2] + E1[2] * absDot01[0][1];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 0;
        result.separating[1] = 0;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[0]xA1[1].
    r = std::abs(dotDA0[2] * dot01[1][1] - dotDA0[1] * dot01[2][1]);
    r0 = E0[1] * absDot01[2][1] + E0[2] * absDot01[1][1];
    r1 = E1[0] * absDot01[0][2] + E1[2] * absDot01[0][0];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 0;
        result.separating[1] = 1;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[0]xA1[2].
    r = std::abs(dotDA0[2] * dot01[1][2] - dotDA0[1] * dot01[2][2]);
    r0 = E0[1] * absDot01[2][2] + E0[2] * absDot01[1][2];
    r1 = E1[0] * absDot01[0][1] + E1[1] * absDot01[0][0];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 0;
        result.separating[1] = 2;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[1]xA1[0].
    r = std::abs(dotDA0[0] * dot01[2][0] - dotDA0[2] * dot01[0][0]);
    r0 = E0[0] * absDot01[2][0] + E0[2] * absDot01[0][0];
    r1 = E1[1] * absDot01[1][2] + E1[2] * absDot01[1][1];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 1;
        result.separating[1] = 0;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[1]xA1[1].
    r = std::abs(dotDA0[0] * dot01[2][1] - dotDA0[2] * dot01[0][1]);
    r0 = E0[0] * absDot01[2][1] + E0[2] * absDot01[0][1];
    r1 = E1[0] * absDot01[1][2] + E1[2] * absDot01[1][0];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 1;
        result.separating[1] = 1;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[1]xA1[2].
    r = std::abs(dotDA0[0] * dot01[2][2] - dotDA0[2] * dot01[0][2]);
    r0 = E0[0] * absDot01[2][2] + E0[2] * absDot01[0][2];
    r1 = E1[0] * absDot01[1][1] + E1[1] * absDot01[1][0];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 1;
        result.separating[1] = 2;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[2]xA1[0].
    r = std::abs(dotDA0[1] * dot01[0][0] - dotDA0[0] * dot01[1][0]);
    r0 = E0[0] * absDot01[1][0] + E0[1] * absDot01[0][0];
    r1 = E1[1] * absDot01[2][2] + E1[2] * absDot01[2][1];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 2;
        result.separating[1] = 0;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[2]xA1[1].
    r = std::abs(dotDA0[1] * dot01[0][1] - dotDA0[0] * dot01[1][1]);
    r0 = E0[0] * absDot01[1][1] + E0[1] * absDot01[0][1];
    r1 = E1[0] * absDot01[2][2] + E1[2] * absDot01[2][0];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 2;
        result.separating[1] = 1;
        return result;
    }

    // Test for separation on the axis C0 + t*A0[2]xA1[2].
    r = std::abs(dotDA0[1] * dot01[0][2] - dotDA0[0] * dot01[1][2]);
    r0 = E0[0] * absDot01[1][2] + E0[1] * absDot01[0][2];
    r1 = E1[0] * absDot01[2][1] + E1[1] * absDot01[2][0];
    r01 = r0 + r1;
    if (r > r01)
    {
        result.intersect = false;
        result.separating[0] = 2;
        result.separating[1] = 2;
        return result;
    }

    result.intersect = true;
    return result;
}
//----------------------------------------------------------------------------
