// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Real ApprQuadratic2<Real>::operator()(int numPoints,
    Vector2<Real> const* points, Real coefficients[6])
{
    Matrix<6, 6, Real> A;
    for (int i = 0; i < numPoints; ++i)
    {
        Real x = points[i][0];
        Real y = points[i][1];
        Real x2 = x*x;
        Real y2 = y*y;
        Real xy = x*y;
        Real x3 = x*x2;
        Real xy2 = x*y2;
        Real x2y = x*xy;
        Real y3 = y*y2;
        Real x4 = x*x3;
        Real x2y2 = x*xy2;
        Real x3y = x*x2y;
        Real y4 = y*y3;
        Real xy3 = x*y3;

        A(0, 1) += x;
        A(0, 2) += y;
        A(0, 3) += x2;
        A(0, 4) += y2;
        A(0, 5) += xy;
        A(1, 3) += x3;
        A(1, 4) += xy2;
        A(1, 5) += x2y;
        A(2, 4) += y3;
        A(3, 3) += x4;
        A(3, 4) += x2y2;
        A(3, 5) += x3y;
        A(4, 4) += y4;
        A(4, 5) += xy3;
    }

    A(0, 0) = static_cast<Real>(numPoints);
    A(1, 1) = A(0, 3);
    A(1, 2) = A(0, 5);
    A(2, 2) = A(0, 4);
    A(2, 3) = A(1, 5);
    A(2, 5) = A(1, 4);
    A(5, 5) = A(3, 4);

    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < row; ++col)
        {
            A(row, col) = A(col, row);
        }
    }

    Real invNumPoints = ((Real)1) / static_cast<Real>(numPoints);
    for (int row = 0; row < 6; ++row)
    {
        for (int col = 0; col < 6; ++col)
        {
            A(row, col) *= invNumPoints;
        }
    }

    SymmetricEigensolver<Real> es(6, 1024);
    es.Solve(&A[0], +1);
    es.GetEigenvector(0, &coefficients[0]);

    // For an exact fit, numeric round-off errors might make the minimum
    // eigenvalue just slightly negative.  Return the absolute value since
    // the application might rely on the return value being nonnegative.
    return std::abs(es.GetEigenvalue(0));
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprQuadraticCircle2<Real>::operator()(int numPoints,
    Vector2<Real> const* points, Circle2<Real>& circle)
{
    Matrix<4, 4, Real> A;
    for (int i = 0; i < numPoints; ++i)
    {
        Real x = points[i][0];
        Real y = points[i][1];
        Real x2 = x*x;
        Real y2 = y*y;
        Real xy = x*y;
        Real r2 = x2+y2;
        Real xr2 = x*r2;
        Real yr2 = y*r2;
        Real r4 = r2*r2;

        A(0, 1) += x;
        A(0, 2) += y;
        A(0, 3) += r2;
        A(1, 1) += x2;
        A(1, 2) += xy;
        A(1, 3) += xr2;
        A(2, 2) += y2;
        A(2, 3) += yr2;
        A(3, 3) += r4;
    }

    A(0, 0) = static_cast<Real>(numPoints);

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < row; ++col)
        {
            A(row, col) = A(col, row);
        }
    }

    Real invNumPoints = ((Real)1) / static_cast<Real>(numPoints);
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            A(row, col) *= invNumPoints;
        }
    }

    SymmetricEigensolver<Real> es(4, 1024);
    es.Solve(&A[0], +1);
    Vector<4, Real> evector;
    es.GetEigenvector(0, &evector[0]);

    Real inv = ((Real)1) / evector[3];  // TODO: Guard against zero divide?
    Real coefficients[3];
    for (int row = 0; row < 3; ++row)
    {
        coefficients[row] = inv * evector[row];
    }

    circle.center[0] = ((Real)-0.5) * coefficients[1];
    circle.center[1] = ((Real)-0.5) * coefficients[2];
    circle.radius = sqrt(std::abs(Dot(circle.center, circle.center) -
        coefficients[0]));

    // For an exact fit, numeric round-off errors might make the minimum
    // eigenvalue just slightly negative.  Return the absolute value since
    // the application might rely on the return value being nonnegative.
    return std::abs(es.GetEigenvalue(0));
}
//----------------------------------------------------------------------------
