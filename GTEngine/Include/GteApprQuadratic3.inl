// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Real ApprQuadratic3<Real>::operator()(int numPoints,
    Vector3<Real> const* points, Real coefficients[10])
{
    Matrix<10, 10, Real> A;
    for (int i = 0; i < numPoints; ++i)
    {
        Real x = points[i][0];
        Real y = points[i][1];
        Real z = points[i][2];
        Real x2 = x*x;
        Real y2 = y*y;
        Real z2 = z*z;
        Real xy = x*y;
        Real xz = x*z;
        Real yz = y*z;
        Real x3 = x*x2;
        Real xy2 = x*y2;
        Real xz2 = x*z2;
        Real x2y = x*xy;
        Real x2z = x*xz;
        Real xyz = x*y*z;
        Real y3 = y*y2;
        Real yz2 = y*z2;
        Real y2z = y*yz;
        Real z3 = z*z2;
        Real x4 = x*x3;
        Real x2y2 = x*xy2;
        Real x2z2 = x*xz2;
        Real x3y = x*x2y;
        Real x3z = x*x2z;
        Real x2yz = x*xyz;
        Real y4 = y*y3;
        Real y2z2 = y*yz2;
        Real xy3 = x*y3;
        Real xy2z = x*y2z;
        Real y3z = y*y2z;
        Real z4 = z*z3;
        Real xyz2 = x*yz2;
        Real xz3 = x*z3;
        Real yz3 = y*z3;

        A(0, 1) += x;
        A(0, 2) += y;
        A(0, 3) += z;
        A(0, 4) += x2;
        A(0, 5) += y2;
        A(0, 6) += z2;
        A(0, 7) += xy;
        A(0, 8) += xz;
        A(0, 9) += yz;
        A(1, 4) += x3;
        A(1, 5) += xy2;
        A(1, 6) += xz2;
        A(1, 7) += x2y;
        A(1, 8) += x2z;
        A(1, 9) += xyz;
        A(2, 5) += y3;
        A(2, 6) += yz2;
        A(2, 9) += y2z;
        A(3, 6) += z3;
        A(4, 4) += x4;
        A(4, 5) += x2y2;
        A(4, 6) += x2z2;
        A(4, 7) += x3y;
        A(4, 8) += x3z;
        A(4, 9) += x2yz;
        A(5, 5) += y4;
        A(5, 6) += y2z2;
        A(5, 7) += xy3;
        A(5, 8) += xy2z;
        A(5, 9) += y3z;
        A(6, 6) += z4;
        A(6, 7) += xyz2;
        A(6, 8) += xz3;
        A(6, 9) += yz3;
        A(9, 9) += y2z2;
    }

    A(0, 0) = static_cast<Real>(numPoints);
    A(1, 1) = A(0, 4);
    A(1, 2) = A(0, 7);
    A(1, 3) = A(0, 8);
    A(2, 2) = A(0, 5);
    A(2, 3) = A(0, 9);
    A(2, 4) = A(1, 7);
    A(2, 7) = A(1, 5);
    A(2, 8) = A(1, 9);
    A(3, 3) = A(0, 6);
    A(3, 4) = A(1, 8);
    A(3, 5) = A(2, 9);
    A(3, 7) = A(1, 9);
    A(3, 8) = A(1, 6);
    A(3, 9) = A(2, 6);
    A(7, 7) = A(4, 5);
    A(7, 8) = A(4, 9);
    A(7, 9) = A(5, 8);
    A(8, 8) = A(4, 6);
    A(8, 9) = A(6, 7);
    A(9, 9) = A(5, 6);

    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < row; ++col)
        {
            A(row, col) = A(col, row);
        }
    }

    Real invNumPoints = ((Real)1) / static_cast<Real>(numPoints);
    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 10; ++col)
        {
            A(row, col) *= invNumPoints;
        }
    }

    SymmetricEigensolver<Real> es(10, 1024);
    es.Solve(&A[0], +1);
    es.GetEigenvector(0, &coefficients[0]);

    // For an exact fit, numeric round-off errors might make the minimum
    // eigenvalue just slightly negative.  Return the absolute value since
    // the application might rely on the return value being nonnegative.
    return std::abs(es.GetEigenvalue(0));
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprQuadraticSphere3<Real>::operator()(int numPoints,
    Vector3<Real> const* points, Sphere3<Real>& sphere)
{
    Matrix<5, 5, Real> A;
    for (int i = 0; i < numPoints; ++i)
    {
        Real x = points[i][0];
        Real y = points[i][1];
        Real z = points[i][2];
        Real x2 = x*x;
        Real y2 = y*y;
        Real z2 = z*z;
        Real xy = x*y;
        Real xz = x*z;
        Real yz = y*z;
        Real r2 = x2+y2+z2;
        Real xr2 = x*r2;
        Real yr2 = y*r2;
        Real zr2 = z*r2;
        Real r4 = r2*r2;

        A(0, 1) += x;
        A(0, 2) += y;
        A(0, 3) += z;
        A(0, 4) += r2;
        A(1, 1) += x2;
        A(1, 2) += xy;
        A(1, 3) += xz;
        A(1, 4) += xr2;
        A(2, 2) += y2;
        A(2, 3) += yz;
        A(2, 4) += yr2;
        A(3, 3) += z2;
        A(3, 4) += zr2;
        A(4, 4) += r4;
    }

    A(0, 0) = static_cast<Real>(numPoints);

    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < row; ++col)
        {
            A(row, col) = A(col, row);
        }
    }

    Real invNumPoints = ((Real)1) / static_cast<Real>(numPoints);
    for (int row = 0; row < 5; ++row)
    {
        for (int col = 0; col < 5; ++col)
        {
            A(row, col) *= invNumPoints;
        }
    }

    SymmetricEigensolver<Real> es(5, 1024);
    es.Solve(&A[0], +1);
    Vector<5, Real> evector;
    es.GetEigenvector(0, &evector[0]);

    Real inv = ((Real)1) / evector[4];  // TODO: Guard against zero divide?
    Real coefficients[4];
    for (int row = 0; row < 4; ++row)
    {
        coefficients[row] = inv * evector[row];
    }

    sphere.center[0] = ((Real)-0.5) * coefficients[1];
    sphere.center[1] = ((Real)-0.5) * coefficients[2];
    sphere.center[2] = ((Real)-0.5) * coefficients[3];
    sphere.radius = sqrt(std::abs(Dot(sphere.center, sphere.center) -
        coefficients[0]));

    // For an exact fit, numeric round-off errors might make the minimum
    // eigenvalue just slightly negative.  Return the absolute value since
    // the application might rely on the return value being nonnegative.
    return std::abs(es.GetEigenvalue(0));
}
//----------------------------------------------------------------------------
