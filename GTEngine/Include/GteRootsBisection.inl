// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/22)

//----------------------------------------------------------------------------
template <typename Real>
unsigned int RootsBisection<Real>::Find(std::function<Real(Real)> const& F,
    Real t0, Real t1, unsigned int maxIterations, Real& root)
{
    if (t0 < t1)
    {
        // Test the endpoints to see whether F(t) is zero.
        Real f0 = F(t0);
        if (f0 == (Real)0)
        {
            root = t0;
            return 1;
        }

        Real f1 = F(t1);
        if (f1 == (Real)0)
        {
            root = t1;
            return 1;
        }

        if (f0*f1 > (Real)0)
        {
            // It is not known whether the interval bounds a root.
            return 0;
        }

        for (unsigned int i = 2; i <= maxIterations; ++i)
        {
            root = ((Real)0.5) * (t0 + t1);
            if (root == t0 || root == t1)
            {
                // The numbers t0 and t1 are consecutive floating-point
                // numbers.
                return true;
            }

            Real fm = F(root);
            Real product = fm * f0;
            if (product < (Real)0)
            {
                t1 = root;
                f1 = fm;
            }
            else if (product >(Real)0)
            {
                t0 = root;
                f0 = fm;
            }
            else
            {
                return i;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
template <typename Real>
unsigned int RootsBisection<Real>::Find(std::function<Real(Real)> const& F,
    Real t0, Real t1, Real f0, Real f1, unsigned int maxIterations,
    Real& root)
{
    if (t0 < t1)
    {
        // Test the endpoints to see whether F(t) is zero.
        if (f0 == (Real)0)
        {
            root = t0;
            return 1;
        }

        if (f1 == (Real)0)
        {
            root = t1;
            return 1;
        }

        if (f0*f1 > (Real)0)
        {
            // It is not known whether the interval bounds a root.
            return 0;
        }

        for (unsigned int i = 1; i <= maxIterations; ++i)
        {
            root = ((Real)0.5) * (t0 + t1);
            if (root == t0 || root == t1)
            {
                // The numbers t0 and t1 are consecutive floating-point
                // numbers.
                return true;
            }

            Real fm = F(root);
            Real product = fm * f0;
            if (product < (Real)0)
            {
                t1 = root;
                f1 = fm;
            }
            else if (product >(Real)0)
            {
                t0 = root;
                f0 = fm;
            }
            else
            {
                return i;
            }
        }
    }

    return 0;
}
//----------------------------------------------------------------------------
