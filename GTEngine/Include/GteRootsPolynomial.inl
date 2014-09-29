// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
int RootsPolynomial<Real>::Find(Real c0, Real c1, Real* roots)
{
    Real const zero = (Real)0;
    if (c1 != zero)
    {
        roots[0] = -c0 / c1;
        return 1;
    }
    else if (c0 == zero)
    {
        roots[0] = zero;
        return 1;
    }
    else
    {
        return 0;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
int RootsPolynomial<Real>::Find(Real c0, Real c1, Real c2, Real* roots)
{
    Real const zero = (Real)0;
    if (c2 != zero)
    {
        Real discr = c1*c1 - ((Real)4)*c0*c2;
        if (discr > zero)
        {
            Real tmp = ((Real)0.5) / c2;
            discr = sqrt(discr);
            roots[0] = tmp*(-c1 - discr);
            roots[1] = tmp*(-c1 + discr);
            return 2;
        }
        else if (discr < zero)
        {
            return 0;
        }
        else
        {
            roots[0] = ((Real)-0.5) * c1 / c2;
            return 1;
        }
    }
    else
    {
        // The polynomial is at most linear.
        return Find(c0, c1, roots);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
int RootsPolynomial<Real>::Find(Real c0, Real c1, Real c2, Real c3,
    Real* roots)
{
    Real const zero = (Real)0;
    if (c3 != zero)
    {
        // Make the polynomial monic, k0 + k1*x + k2*x^2 + x^3.
        Real const one = (Real)1;
        Real invC3 = one / c3;
        Real k0 = c0 * invC3;
        Real k1 = c1 * invC3;
        Real k2 = c2 * invC3;

        // Convert to y^3 + a*y + b = 0 using x = y - c2/3.
        Real const third = one / (Real)3;
        Real const twentySeventh = one / (Real)27;
        Real const two = (Real)2;
        Real const nine = (Real)9;
        Real const half = (Real)0.5;
        Real offset = third * k2;
        Real a = k1 - k2 * offset;
        Real b = k0 + k2 * (two * k2 * k2 - nine * k1)*twentySeventh;
        Real halfB = half * b;

        Real discr = halfB * halfB + a * a * a * twentySeventh;
        if (discr > zero)  // 1 real, 2 complex roots
        {
            discr = sqrt(discr);
            Real temp = -halfB + discr;
            if (temp >= zero)
            {
                roots[0] = pow(temp, third);
            }
            else
            {
                roots[0] = -pow(-temp, third);
            }
            temp = -halfB - discr;
            if (temp >= zero)
            {
                roots[0] += pow(temp, third);
            }
            else
            {
                roots[0] -= pow(-temp, third);
            }
            roots[0] -= offset;
            return 1;
        }
        else if (discr < zero)
        {
            Real const sqrt3 = sqrt((Real)3);
            Real dist = sqrt(-third * a);
            Real angle = third * atan2(sqrt(-discr), -halfB);
            Real cs = cos(angle);
            Real sn = sin(angle);
            roots[0] = two * dist * cs - offset;
            roots[1] = -dist * (cs + sqrt3 * sn) - offset;
            roots[2] = -dist * (cs - sqrt3 * sn) - offset;
            return 3;
        }
        else
        {
            Real temp;
            if (halfB >= zero)
            {
                temp = -pow(halfB, third);
            }
            else
            {
                temp = pow(-halfB, third);
            }
            roots[0] = two * temp - offset;
            roots[1] = -temp - offset;
            roots[2] = roots[1];
            return 3;
        }

    }
    else
    {
        // The polynomial is at most quadratic.
        return Find(c0, c1, c2, roots);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
int RootsPolynomial<Real>::Find(Real c0, Real c1, Real c2, Real c3,
    Real c4, Real* roots)
{
    Real const zero = (Real)0;
    if (c4 != zero)
    {
        // Make the polynomial monic, k0 + k1*x + k2*x^2 + k3*x^3 + x^4
        Real const one = (Real)1;
        Real invC4 = one / c4;
        Real k0 = c0 * invC4;
        Real k1 = c1 * invC4;
        Real k2 = c2 * invC4;
        Real k3 = c3 * invC4;

        // Reduction to resolvent cubic polynomial y^3 + r2*y^2 + r1*y + r0.
        Real const four = (Real)4;
        Real r0 = k0 * (four * k2 - k3 * k3) - k1 * k1;
        Real r1 = k3 * k1 - four * k0;
        Real r2 = -k2;
        Find(r0, r1, r2, one, roots);  // Produces at least one root.
        Real y = roots[0];

        Real const oneFourth = (Real)0.25;
        Real const threeFourths = (Real)0.75;
        Real const two = (Real)2;
        Real const half = (Real)0.5;
        int numRoots = 0;
        Real discr = oneFourth*k3*k3 - k2 + y;
        if (discr > zero)
        {
            Real r = sqrt(discr);
            Real t1 = threeFourths*k3*k3 - r*r - two*k2;
            Real t2 = (k3 * k2 - two * k1 - oneFourth * k3 * k3 * k3) / r;

            Real tPlus = t1 + t2;
            Real tMinus = t1 - t2;
            if (tPlus >= zero)
            {
                Real d = sqrt(tPlus);
                roots[0] = -oneFourth*k3 + half*(r + d);
                roots[1] = -oneFourth*k3 + half*(r - d);
                numRoots += 2;
            }
            if (tMinus >= zero)
            {
                Real e = sqrt(tMinus);
                roots[numRoots++] = -oneFourth*k3 + half*(e - r);
                roots[numRoots++] = -oneFourth*k3 - half*(e + r);
            }
        }
        else if (discr < zero)
        {
            numRoots = 0;
        }
        else
        {
            Real t2 = y*y - four*k0;
            if (t2 >= zero)
            {
                t2 = two * sqrt(t2);
                Real t1 = threeFourths * k3 * k3 - two * k2;
                Real tPlus = t1 + t2;
                if (tPlus >= zero)
                {
                    Real d = sqrt(tPlus);
                    roots[0] = -oneFourth * k3 + half * d;
                    roots[1] = -oneFourth * k3 - half * d;
                    numRoots += 2;
                }
                Real tMinus = t1 - t2;
                if (tMinus >= zero)
                {
                    Real e = sqrt(tMinus);
                    roots[numRoots++] = -oneFourth*k3 + half * e;
                    roots[numRoots++] = -oneFourth*k3 - half * e;
                }
            }
        }

        return numRoots;
    }
    else
    {
        // The polynomial is at most cubic.
        return Find(c0, c1, c2, c3, roots);
    }
}
//----------------------------------------------------------------------------
template <typename Real>
int RootsPolynomial<Real>::Find(int degree, Real const* c,
    unsigned int maxIterations, Real* roots)
{
    if (degree >= 0 && c)
    {
        Real const zero = (Real)0;
        while (degree >= 0 && c[degree] == zero)
        {
            --degree;
        }

        if (degree > 0)
        {
            // Compute the Cauchy bound.
            Real const one = (Real)1;
            Real invLeading = one / c[degree];
            Real maxValue = zero;
            for (int i = 0; i < degree; ++i)
            {
                Real value = std::abs(c[i] * invLeading);
                if (value > maxValue)
                {
                    maxValue = value;
                }
            }
            Real bound = one + maxValue;

            return FindRecursive(degree, c, -bound, bound, maxIterations,
                roots);
        }
        else if (degree == 0)
        {
            // The polynomial is a nonzero constant.
            return 0;
        }
        else
        {
            // The polynomial is identically zero.
            roots[0] = zero;
            return 1;
        }
    }
    else
    {
        // Invalid degree or c.
        return 0;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
bool RootsPolynomial<Real>::Find(int degree, Real const* c, Real tmin,
    Real tmax, unsigned int maxIterations, Real& root)
{
    Real const zero = (Real)0;
    Real pmin = Evaluate(degree, c, tmin);
    if (pmin == zero)
    {
        root = tmin;
        return true;
    }
    Real pmax = Evaluate(degree, c, tmax);
    if (pmax == zero)
    {
        root = tmax;
        return true;
    }

    if (pmin*pmax > zero)
    {
        // It is not known whether the interval bounds a root.
        return false;
    }

    if (tmin >= tmax)
    {
        // Invalid ordering of interval endpoitns. 
        return false;
    }

    for (unsigned int i = 1; i <= maxIterations; ++i)
    {
        root = ((Real)0.5) * (tmin + tmax);

        // This test is designed for 'float' or 'double' when tmin and tmax
        // are consecutive floating-point numbers.
        if (root == tmin || root == tmax)
        {
            break;
        }

        Real p = Evaluate(degree, c, root);
        Real product = p * pmin;
        if (product < zero)
        {
            tmax = root;
            pmax = p;
        }
        else if (product > zero)
        {
            tmin = root;
            pmin = p;
        }
        else
        {
            break;
        }
    }

    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
int RootsPolynomial<Real>::FindRecursive(int degree, Real const* c,
    Real tmin, Real tmax, unsigned int maxIterations, Real* roots)
{
    // The base of the recursion.
    Real root;
    if (degree == 1)
    {
        int numRoots = Find(c[0], c[1], &root);
        if (numRoots > 0 && tmin <= root && root <= tmax)
        {
            roots[0] = root;
            return 1;
        }
        return 0;
    }

    // Find the roots of the derivative polynomial scaled by 1/degree.  The
    // scaling avoids the factorial growth in the coefficients; for example,
    // without the scaling, the high-order term x^d becomes (d!)*x through
    // multiple differentiations.  With the scaling we instead get x.  This
    // leads to better numerical behavior of the root finder.
    int derivDegree = degree - 1;
    std::vector<Real> derivCoeff(derivDegree + 1);
    std::vector<Real> derivRoots(derivDegree);
    for (int i = 0; i <= derivDegree; ++i)
    {
        derivCoeff[i] = c[i + 1] * (Real)(i + 1) / (Real)degree;
    }
    int numDerivRoots = FindRecursive(degree - 1, &derivCoeff[0], tmin, tmax,
        maxIterations, &derivRoots[0]);

    int numRoots = 0;
    if (numDerivRoots > 0)
    {
        // Find root on [tmin,derivRoots[0]].
        if (Find(degree, c, tmin, derivRoots[0], maxIterations, root))
        {
            roots[numRoots++] = root;
        }

        // Find root on [derivRoots[i],derivRoots[i+1]].
        for (int i = 0; i <= numDerivRoots - 2; ++i)
        {
            if (Find(degree, c, derivRoots[i], derivRoots[i + 1],
                maxIterations, root))
            {
                roots[numRoots++] = root;
            }
        }

        // Find root on [derivRoots[numDerivRoots-1],tmax].
        if (Find(degree, c, derivRoots[numDerivRoots - 1], tmax,
            maxIterations, root))
        {
            roots[numRoots++] = root;
        }
    }
    else
    {
        // The polynomial is monotone on [tmin,tmax], so has at most one root.
        if (Find(degree, c, tmin, tmax, maxIterations, root))
        {
            roots[numRoots++] = root;
        }
    }
    return numRoots;
}
//----------------------------------------------------------------------------
template <typename Real>
Real RootsPolynomial<Real>::Evaluate(int degree, Real const* c, Real t)
{
    int i = degree;
    Real result = c[i];
    while (--i >= 0)
    {
        result = t * result + c[i];
    }
    return result;
}
//----------------------------------------------------------------------------
