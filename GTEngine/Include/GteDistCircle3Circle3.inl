// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Circle3<Real>, Circle3<Real>>::Result
DCPQuery<Real, Circle3<Real>, Circle3<Real>>::operator()(
    Circle3<Real> const& circle0, Circle3<Real> const& circle1)
{
    Result result;
    result.distance = std::numeric_limits<Real>::max();
    result.sqrDistance = result.distance;

    Real const zero = (Real)0;
    Real const one = (Real)1;
    Real const two = (Real)2;

    // Compute coordinate systems for the planes of the circles.
    Vector3<Real> basis0[3], basis1[3];
    basis0[0] = circle0.normal;
    ComputeOrthogonalComplement(1, basis0);
    basis1[0] = circle1.normal;
    ComputeOrthogonalComplement(1, basis1);

    Vector3<Real> diff = circle1.center - circle0.center;
    Real u0u1 = Dot(basis0[1], basis1[1]);
    Real u0v1 = Dot(basis0[1], basis1[2]);
    Real v0u1 = Dot(basis0[2], basis1[1]);
    Real v0v1 = Dot(basis0[2], basis1[2]);

    Real a0 = -Dot(diff, basis0[1]);
    Real a1 = -circle1.radius*u0u1;
    Real a2 = -circle1.radius*u0v1;
    Real a3 = Dot(diff, basis0[2]);
    Real a4 = circle1.radius*v0u1;
    Real a5 = circle1.radius*v0v1;

    Real b0 = -Dot(diff, basis1[1]);
    Real b1 = circle0.radius * u0u1;
    Real b2 = circle0.radius * v0u1;
    Real b3 = Dot(diff, basis1[2]);
    Real b4 = -circle0.radius * u0v1;
    Real b5 = -circle0.radius * v0v1;

    // Compute polynomial p0 = p00+p01*z+p02*z^2.
    std::array<Real, 3> p0;
    p0[0] = a2*b1 - a5*b2;
    p0[1] = a0*b4 - a3*b5;
    p0[2] = a5*b2 - a2*b1 + a1*b4 - a4*b5;

    // Compute polynomial p1 = p10+p11*z.
    std::array<Real, 2> p1;
    p1[0] = a0*b1 - a3*b2;
    p1[1] = a1*b1 - a5*b5 + a2*b4 - a4*b2;

    // Compute polynomial q0 = q00+q01*z+q02*z^2.
    std::array<Real, 3> q0;
    q0[0] = a0*a0 + a2*a2 + a3*a3 + a5*a5;
    q0[1] = two*(a0*a1 + a3*a4);
    q0[2] = a1*a1 - a2*a2 + a4*a4 - a5*a5;

    // Compute polynomial q1 = q10+q11*z.
    std::array<Real, 2> q1;
    q1[0] = two*(a0*a2 + a3*a5);
    q1[1] = two*(a1*a2 + a4*a5);

    // Compute coefficients of r0 = r00+r02*z^2.
    std::array<Real, 3> r0;
    r0[0] = b0*b0;
    r0[1] = zero;
    r0[2] = b3*b3 - b0*b0;

    // Compute polynomial r1 = r11*z.
    std::array<Real, 2> r1;
    r1[0] = zero;
    r1[1] = two*b0*b3;

    // Compute polynomial g0 = g00+g01*z+g02*z^2+g03*z^3+g04*z^4.
    std::array<Real, 5> g0;
    g0[0] = p0[0]*p0[0] + p1[0]*p1[0] - q0[0]*r0[0];
    g0[1] = two*(p0[0]*p0[1] + p1[0]*p1[1]) - q0[1]*r0[0] - q1[0]*r1[1];
    g0[2] = p0[1]*p0[1] + two*p0[0]*p0[2] - p1[0]*p1[0] +
        p1[1]*p1[1] - q0[2]*r0[0] - q0[0]*r0[2] - q1[1]*r1[1];
    g0[3] = two*(p0[1]*p0[2] - p1[0]*p1[1]) - q0[1]*r0[2] + q1[0]*r1[1];
    g0[4] = p0[2]*p0[2] - p1[1]*p1[1] - q0[2]*r0[2] + q1[1]*r1[1];
    std::function<Real(Real)> evaluateG0 = [&g0](Real z)
    {
        return g0[0] + z*(g0[1] + z*(g0[2] + z*(g0[3] + z*g0[4])));
    };

    // Compute polynomial g1 = g10+g11*z+g12*z^2+g13*z^3.
    std::array<Real, 4> g1;
    g1[0] = two*p0[0]*p1[0] - q1[0]*r0[0];
    g1[1] = two*(p0[1]*p1[0] + p0[0]*p1[1]) - q1[1]*r0[0] - q0[0]*r1[1];
    g1[2] = two*(p0[2]*p1[0] + p0[1]*p1[1]) - q1[0]*r0[2] - q0[1]*r1[1];
    g1[3] = two*p0[2]*p1[1] - q1[1]*r0[2] - q0[2]*r1[1];
    std::function<Real(Real)> evaluateG1 = [&g1](Real z)
    {
        return g1[0] + z*(g1[1] + z*(g1[2] + z*g1[3]));
    };

    // Compute polynomial h = sum_{i=0}^8 h_i z^i.
    std::array<Real, 9> h;
    h[0] = g0[0]*g0[0] - g1[0]*g1[0];
    h[1] = two*(g0[0]*g0[1] - g1[0]*g1[1]);
    h[2] = g0[1]*g0[1] + g1[0]*g1[0] - g1[1]*g1[1] +
        two*(g0[0]*g0[2] - g1[0]*g1[2]);
    h[3] = two*(g0[1]*g0[2] + g0[0]*g0[3] + g1[0]*g1[1] -
        g1[1]*g1[2] - g1[0]*g1[3]);
    h[4] = g0[2]*g0[2] + g1[1]*g1[1] - g1[2]*g1[2] +
        two*(g0[1]*g0[3] + g0[0]*g0[4] + g1[0]*g1[2] -
        g1[1]*g1[3]);
    h[5] = two*(g0[2]*g0[3] + g0[1]*g0[4] + g1[1]*g1[2] +
        g1[0]*g1[3] - g1[2]*g1[3]);
    h[6] = g0[3]*g0[3] + g1[2]*g1[2] - g1[3]*g1[3] +
        two*(g0[2]*g0[4] + g1[1]*g1[3]);
    h[7] = two*(g0[3]*g0[4] + g1[2]*g1[3]);
    h[8] = g0[4]*g0[4] + g1[3]*g1[3];

    unsigned int const imax = 1024;
    Real roots[8];
    int numRoots = RootsPolynomial<Real>::Find(8, &h[0], imax, roots);
    for (int i = 0; i < numRoots; ++i)
    {
        // You can also try sn1 = -g0(cs1)/g1(cs1) to avoid the sqrt call,
        // but beware when g1 is nearly zero.  For now use g0 and g1 to
        // determine the sign of sn1.
        Real cs1 = std::min(std::max(roots[i], -one), one);
        Real sn1 = sqrt(std::max(one - cs1*cs1, zero));

        Real g0cs1 = evaluateG0(cs1);
        Real g1cs1 = evaluateG1(cs1);
        Real product = g0cs1*g1cs1;
        if (product > zero)
        {
            sn1 = -sn1;
        }
        else if (product < zero)
        {
            // sn1 already has correct sign
        }
        else if (g1cs1 != zero)
        {
            // g0 == 0.0
            // assert( sn1 == 0.0 );
        }
        else // g1 == 0.0
        {
            // TO DO:  When g1 = 0, there is no constraint on sn1.
            // What should be done here?  In this case, cs1 is a root
            // to the quartic equation g0(cs1) = 0.  Is there some
            // geometric significance?
            LogError("Unexpected case.");
        }

        Real m00 = a0 + a1*cs1 + a2*sn1;
        Real m01 = a3 + a4*cs1 + a5*sn1;
        Real m10 = b2*sn1 + b5*cs1;
        Real m11 = b1*sn1 + b4*cs1;
        Real det = m00*m11 - m01*m10;
        if (det != zero)
        {
            Real invDet = one / det;
            Real lambda = -(b0*sn1 + b3*cs1);
            Real cs0 = lambda*m00*invDet;
            Real sn0 = -lambda*m01*invDet;

            // Unitize in case of numerical error.  Remove if you feel
            // confident of the accuracy for cs0 and sn0.
            Real tmp = one / sqrt(cs0*cs0 + sn0*sn0);
            cs0 *= tmp;
            sn0 *= tmp;

            Vector3<Real> closest0 = circle0.center +
                circle0.radius*(cs0*basis0[1] + sn0*basis0[2]);

            Vector3<Real> closest1 = circle1.center +
                circle1.radius*(cs1*basis1[1] + sn1*basis1[2]);

            diff = closest1 - closest0;

            Real sqrDistance = Dot(diff, diff);
            if (sqrDistance < result.sqrDistance)
            {
                result.sqrDistance = sqrDistance;
                result.closestPoint[0] = closest0;
                result.closestPoint[1] = closest1;
            }
        }
        else
        {
            // TO DO:  Handle this case.  Is there some geometric
            // significance?
            LogError("Unexpected case.");
        }
    }

    return result;
}
//----------------------------------------------------------------------------
