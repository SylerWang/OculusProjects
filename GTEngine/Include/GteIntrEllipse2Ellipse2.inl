// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/22)

//----------------------------------------------------------------------------
template <typename Real>
typename TIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>::Result
TIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>::operator()(
    Ellipse2<Real> const& ellipse0, Ellipse2<Real> const& ellipse1)
{
    Result result;

    Real const zero = (Real)0;
    Real const one = (Real)1;

    // Get the parameters of ellipe0.
    Vector2<Real> K0 = ellipse0.center;
    Matrix2x2<Real> R0(ellipse0.axis, true);
    Matrix2x2<Real> D0(
        one / (ellipse0.extent[0] * ellipse0.extent[0]),
        one / (ellipse0.extent[1] * ellipse0.extent[1]));

    // Get the parameters of ellipse1.
    Vector2<Real> K1 = ellipse1.center;
    Matrix2x2<Real> R1(ellipse1.axis, true);
    Matrix2x2<Real> D1(
        one / (ellipse1.extent[0] * ellipse1.extent[0]),
        one / (ellipse1.extent[1] * ellipse1.extent[1]));

    // Compute K2.
    Matrix2x2<Real> D0NegHalf(
        ellipse0.extent[0],
        ellipse0.extent[1]);
    Matrix2x2<Real> D0Half(
        one/ellipse0.extent[0],
        one/ellipse0.extent[1]);
    Vector2<Real> K2 = D0Half*((K1 - K0)*R0);

    // Compute M2.
    Matrix2x2<Real> R1TR0D0NegHalf = MultiplyATB(R1, R0*D0NegHalf);
    Matrix2x2<Real> M2 = MultiplyATB(R1TR0D0NegHalf, D1)*R1TR0D0NegHalf;

    // Factor M2 = R*D*R^T.
    SymmetricEigensolver<Real> es(2, 4);
    es.Solve(&M2[0], +1);
    Matrix2x2<Real> R;
    es.GetEigenvectors(&R[0]);
    Real D[2];
    es.GetEigenvalues(D);

    // Compute K = R^T*K2.
    Vector2<Real> K = K2*R;

    // Transformed ellipse0 is Z^T*Z = 1 and transformed ellipse1 is
    // (Z-K)^T*D*(Z-K) = 0.

    // The minimum and maximum squared distances from the origin of points on
    // transformed ellipse1 are used to determine whether the ellipses
    // intersect, are separated, or one contains the other.
    Real minSqrDistance = std::numeric_limits<Real>::max();
    Real maxSqrDistance = zero;
    int i;

    if (K == Vector2<Real>::Zero())
    {
        // The special case of common centers must be handled separately.  It
        // is not possible for the ellipsoids to be separated.
        for (i = 0; i < 2; ++i)
        {
            Real invD = one / D[i];
            if (invD < minSqrDistance)
            {
                minSqrDistance = invD;
            }
            if (invD > maxSqrDistance)
            {
                maxSqrDistance = invD;
            }
        }

        if (maxSqrDistance < one)
        {
            result.relationship = ELLIPSE0_CONTAINS_ELLIPSE1;
        }
        else if (minSqrDistance > one)
        {
            result.relationship = ELLIPSE1_CONTAINS_ELLIPSE0;
        }
        else
        {
            result.relationship = ELLIPSES_INTERSECTING;
        }
        result.intersect = true;
        return result;
    }

    // The closest point P0 and farthest point P1 are solutions to
    // s0*D*(P0 - K) = P0 and s1*D1*(P1 - K) = P1 for some scalars s0 and s1
    // that are roots to the function
    //   f(s) = d0*k0^2/(d0*s-1)^2 + d1*k1^2/(d1*s-1)^2 - 1
    // where D = diagonal(d0,d1) and K = (k0,k1).
    Real d0 = D[0], d1 = D[1];
    Real c0 = K[0]*K[0], c1 = K[1]*K[1];

    // Sort the values so that d0 >= d1.  This allows us to bound the roots of
    // f(s), of which there are at most 4.
    std::vector<std::pair<Real,Real>> param(2);
    if (d0 >= d1)
    {
        param[0] = std::make_pair(d0, c0);
        param[1] = std::make_pair(d1, c1);
    }
    else
    {
        param[0] = std::make_pair(d1, c1);
        param[1] = std::make_pair(d0, c0);
    }

    std::vector<std::pair<Real,Real>> valid;
    valid.reserve(2);
    if (param[0].first > param[1].first)
    {
        // d0 > d1
        for (i = 0; i < 2; ++i)
        {
            if (param[i].second > zero)
            {
                valid.push_back(param[i]);
            }
        }
    }
    else
    {
        // d0 = d1
        param[0].second += param[1].second;
        if (param[0].second > zero)
        {
            valid.push_back(param[0]);
        }
    }

    size_t numValid = valid.size();
    int numRoots;
    Real roots[4];
    if (numValid == 2)
    {
        GetRoots(valid[0].first, valid[1].first, valid[0].second,
            valid[1].second, numRoots, roots);
    }
    else if (numValid == 1)
    {
        GetRoots(valid[0].first, valid[0].second, numRoots, roots);
    }
    else
    {
        // numValid cannot be zero because we already handled case K = 0
        LogError("Unexpected condition.");
        result.intersect = true;
        result.relationship = ELLIPSES_INTERSECTING;
        return result;
    }

    for (int i = 0; i < numRoots; ++i)
    {
        Real s = roots[i];
        Real p0 = d0*K[0] * s / (d0 * s - (Real)1);
        Real p1 = d1*K[1] * s / (d1 * s - (Real)1);
        Real sqrDistance = p0 * p0 + p1 * p1;
        if (sqrDistance < minSqrDistance)
        {
            minSqrDistance = sqrDistance;
        }
        if (sqrDistance > maxSqrDistance)
        {
            maxSqrDistance = sqrDistance;
        }
    }

    if (maxSqrDistance < one)
    {
        result.intersect = true;
        result.relationship = ELLIPSE0_CONTAINS_ELLIPSE1;
    }
    else if (minSqrDistance > one)
    {
        if (d0 * c0 + d1 * c1 > one)
        {
            result.intersect = false;
            result.relationship = ELLIPSES_SEPARATED;
            return result;
        }
        else
        {
            result.intersect = true;
            result.relationship = ELLIPSE1_CONTAINS_ELLIPSE0;
        }
    }
    else
    {
        result.intersect = true;
        result.relationship = ELLIPSES_INTERSECTING;
    }

    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
void TIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>::GetRoots(Real d0, Real c0,
    int& numRoots, Real* roots)
{
    // f(s) = d0*c0/(d0*s-1)^2 - 1
    Real const one = (Real)1;
    Real temp = sqrt(d0*c0);
    Real inv = one / d0;
    numRoots = 2;
    roots[0] = (one - temp) * inv;
    roots[1] = (one + temp) * inv;
}
//----------------------------------------------------------------------------
template <typename Real>
void TIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>::GetRoots(Real d0, Real d1,
    Real c0, Real c1, int& numRoots, Real* roots)
{
    // f(s) = d0*c0/(d0*s-1)^2 + d1*c1/(d1*s-1)^2 - 1
    // with d0 > d1

    Real const zero = (Real)0;
    Real const one = (Real)1;
    Real const two = (Real)2;
    Real d0c0 = d0 * c0;
    Real d1c1 = d1 * c1;

    std::function<Real(Real)> F = [d0, d1, d0c0, d1c1](Real s)
    {
        Real const one = (Real)1;
        Real invN0 = one / (d0*s - one);
        Real invN1 = one / (d1*s - one);
        Real term0 = d0c0 * invN0 * invN0;
        Real term1 = d1c1 * invN1 * invN1;
        Real f = term0 + term1 - one;
        return f;
    };

    std::function<Real(Real)> DF = [d0, d1, d0c0, d1c1](Real s)
    {
        Real const one = (Real)1;
        Real const two = (Real)2;
        Real invN0 = one / (d0*s - one);
        Real invN1 = one / (d1*s - one);
        Real term0 = d0 * d0c0 * invN0 * invN0 * invN0;
        Real term1 = d1 * d1c1 * invN1 * invN1 * invN1;
        Real df = -two * (term0 + term1);
        return df;
    };

    unsigned int const maxIterations = 1024;
    unsigned int iterations;
    numRoots = 0;

    // TODO: What role does epsilon play?
    Real const epsilon = (Real)0.001;
    Real multiplier0 = sqrt(two / (one - epsilon));
    Real multiplier1 = sqrt(one / (one + epsilon));
    Real sqrtd0c0 = sqrt(d0c0);
    Real sqrtd1c1 = sqrt(d1c1);
    Real invD0 = one / d0;
    Real invD1 = one / d1;
    Real temp0, temp1, smin, smax, s;

    // Compute root in (-infinity,1/d0).
    temp0 = (one - multiplier0 * sqrtd0c0) * invD0;
    temp1 = (one - multiplier0 * sqrtd1c1) * invD1;
    smin = std::min(temp0, temp1);
    LogAssert(F(smin) < zero, "Unexpected condition.");
    smax = (one - multiplier1*sqrtd0c0)*invD0;
    LogAssert(F(smax) > zero, "Unexpected condition.");
    iterations = RootsBisection<Real>::Find(F, smin, smax, maxIterations, s);
    LogAssert(iterations > 0, "Unexpected condition.");
    roots[numRoots++] = s;

    // Compute roots (if any) in (1/d0,1/d1).  It is the case that
    //   F(1/d0) = +infinity, F'(1/d0) = -infinity
    //   F(1/d1) = +infinity, F'(1/d1) = +infinity
    //   F"(s) > 0 for all s in the domain of F
    // Compute the unique root r of F'(s) on (1/d0,1/d1).  The bisector needs
    // only the signs at the endpoints, so we pass -1 and +1 instead of the
    // infinite values.  If F(r) < 0, F(s) has two roots in the interval.
    // If F(r) = 0, F(s) has only one root in the interval.
    Real smid;
    iterations = RootsBisection<Real>::Find(DF, invD0, invD1, -one, one,
        maxIterations, smid);
    LogAssert(iterations > 0, "Unexpected condition.");
    if (F(smid) < zero)
    {
        // Pass in signs rather than infinities, because the bisector cares
        // only about the signs.
        iterations = RootsBisection<Real>::Find(F, invD0, smid, one, -one,
            maxIterations, s);
        LogAssert(iterations > 0, "Unexpected condition.");
        roots[numRoots++] = s;
        iterations = RootsBisection<Real>::Find(F, smid, invD1, -one, one,
            maxIterations, s);
        LogAssert(iterations > 0, "Unexpected condition.");
        roots[numRoots++] = s;
    }

    // Compute root in (1/d1,+infinity).
    temp0 = (one + multiplier0 * sqrtd0c0) * invD0;
    temp1 = (one + multiplier0 * sqrtd1c1) * invD1;
    smax = std::max(temp0, temp1);
    LogAssert(F(smax) < zero, "Unexpected condition.");
    smin = (one + multiplier1 * sqrtd1c1) * invD1;
    LogAssert(F(smin) > zero, "Unexpected condition.");
    iterations = RootsBisection<Real>::Find(F, smin, smax, maxIterations, s);
    LogAssert(iterations > 0, "Unexpected condition.");
    roots[numRoots++] = s;
}
//----------------------------------------------------------------------------
template <typename Real>
typename FIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>::Result
FIQuery<Real, Ellipse2<Real>, Ellipse2<Real>>::operator()(
    Ellipse2<Real> const& ellipse0, Ellipse2<Real> const& ellipse1)
{
    Result result;
    result.intersect = false;
    result.numPoints = 0;

    // Compute the 4th-degree polynomial whose roots lead to intersections of
    // the ellipses, and then compute its roots.  The polynomials are
    //   P0 = a0 + a1*x + a2*y + a3*x^2 + a4*x*y + a5*y^2
    //      = (a0 + a2*y + a5*y^2) + (a1 + a4*y)*x + (a3)*x^2
    //      = u0(y) + u1(y)*x + u2(y)*x^2
    //   P1 = b0 + b1*x + b2*y + b3*x^2 + b4*x*y + b5*y^2
    //      = (b0 + b2*y + b5*y^2) + (b1 + b4*y)*x + (b3)*x^2
    //      = v0(y) + v1(y)*x + v2(y)*x^2
    // The Bezout determinant eliminates the variable x when solving the
    // equations P0(x,y) = 0 and P1(x,y) = 0.  We have
    //   0 = P0 = u0 + u1*x + u2*x^2
    //   0 = P1 = v0 + v1*x + v2*x^2
    //   0 = v2*P0 - u2*P1 = (u0*v2 - u2*v0) + (u1*v2 - u2*v1)*x
    //   0 = v1*P0 - u1*P1 = (u0*v1 - u1*v0) + (u2*v1 - u1*v2)*x^2
    // Solve the equation 0 = v2*P0-u2*P1 for x and substitute in the other
    // equation and simplify to
    //   Q(y) = (u0*v1-v1*u0)*(u1*v2-u2*v1) - (u0*v2-u2*v0)^2 = 0
    //        = c0 + c1*y + c2*y^2 + c3*y^3 + c4*y^4
    // Define dij = ai*bj - aj*bi for various indices i and j.  For example,
    // d01 = a0*b1-b1*a0.  The coefficients of Q(y) are
    //   c0 = d01*d13 - d30^2
    //   c1 = d01*d43 + (d04+d21)*d13 - 2*d30*d32
    //   c2 = (d04+d21)*d43 + (d24+d51)*d13 - 2*d30*d35 - d32^2
    //   c3 = (d24+d51)*d43 + d54*d13 - 2*d32*d35
    //   c4 = d54*d43 - d35^2
    Real p0[6], p1[6];
    ellipse0.ToCoefficients(p0);
    ellipse1.ToCoefficients(p1);
    Real d01 = p0[0] * p1[1] - p0[1] * p1[0];
    Real d04 = p0[0] * p1[4] - p0[4] * p1[0];
    Real d13 = p0[1] * p1[3] - p0[3] * p1[1];
    Real d21 = p0[2] * p1[1] - p0[1] * p1[2];
    Real d24 = p0[2] * p1[4] - p0[4] * p1[2];
    Real d30 = p0[3] * p1[0] - p0[0] * p1[3];
    Real d32 = p0[3] * p1[2] - p0[2] * p1[3];
    Real d35 = p0[3] * p1[5] - p0[5] * p1[3];
    Real d43 = p0[4] * p1[3] - p0[3] * p1[4];
    Real d51 = p0[5] * p1[1] - p0[1] * p1[5];
    Real d54 = p0[5] * p1[4] - p0[4] * p1[5];
    Real d04p21 = d04 + d21;
    Real d24p51 = d24 + d51;
    std::array<Real, 5> poly;
    poly[0] = d01*d13 - d30*d30;
    poly[1] = d01*d43 + d04p21*d13 - ((Real)2)*d30*d32;
    poly[2] = d04p21*d43 + d24p51*d13 - ((Real)2)*d30*d35 - d32*d32;
    poly[3] = d24p51*d43 + d54*d13 - ((Real)2)*d32*d35;
    poly[4] = d54*d43 - d35*d35;

    unsigned int const imax = 1024;
    Real roots[4];
    int numRoots = RootsPolynomial<Real>::Find(4, &poly[0], imax, roots);
    if (numRoots == 0)
    {
        return result;
    }

    // Evaluate the quadratics to compute points of intersection and to
    // eliminate extraneous roots.  Using the notation from previously in
    // this function, given a y-value you can compute u0, u1, u2, v0, v1, and
    // v2.  Solve for x in 0 = (u0*v2 - u2*v0) + (u1*v2 - u2*v1)*x.  The
    // pair (x,y) is a candidate intersection point.
    Real const epsilon = (Real)1e-06;
    Matrix2x2<Real> M0, M1;
    ellipse0.GetM(M0);
    ellipse1.GetM(M1);
    for (int i = 0; i < numRoots; ++i)
    {
        Vector2<Real> point;
        point[1] = roots[i];
        Real u0 = p0[0] + (p0[2] + point[1] * p0[5]) * point[1];
        Real u1 = p0[1] + p0[4] * point[1];
        Real u2 = p0[2];
        Real v0 = p1[0] + (p1[2] + point[1] * p1[5]) * point[1];
        Real v1 = p1[1] + p1[4] * point[1];
        Real v2 = p1[2];
        Real denom = u1 * v2 - u2 * v1;
        if (std::abs(denom) != (Real)0)
        {
            Real numer = u2 * v0 - u0 * v2;
            point[0] = numer / denom;

            Vector2<Real> diff = point - ellipse0.center;
            Real quad0 = Dot(diff, M0*diff) - (Real)1;
            diff = point - ellipse1.center;
            Real quad1 = Dot(diff, M1*diff) - (Real)1;
            if (std::abs(quad0) <= epsilon && std::abs(quad1) <= epsilon)
            {
                result.intersect = true;
                result.points[result.numPoints++] = point;
            }
        }
    }

    return result;
}
//----------------------------------------------------------------------------
