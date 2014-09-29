// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
bool ApprParaboloid3<Real>::operator()(int numPoints,
    Vector3<Real> const* points, Real coefficients[6])
{
    Matrix<6, 6, Real> A;
    Vector<6, Real> B;
    for (int i = 0; i < numPoints; i++)
    {
        Real x2 = points[i][0]*points[i][0];
        Real xy = points[i][0]*points[i][1];
        Real y2 = points[i][1]*points[i][1];
        Real zx = points[i][2]*points[i][0];
        Real zy = points[i][2]*points[i][1];
        Real x3 = points[i][0]*x2;
        Real x2y = x2*points[i][1];
        Real xy2 = points[i][0]*y2;
        Real y3 = points[i][1]*y2;
        Real zx2 = points[i][2]*x2;
        Real zxy = points[i][2]*xy;
        Real zy2 = points[i][2]*y2;
        Real x4 = x2*x2;
        Real x3y = x3*points[i][1];
        Real x2y2 = x2*y2;
        Real xy3 = points[i][0]*y3;
        Real y4 = y2*y2;

        A(0, 0) += x4;
        A(0, 1) += x3y;
        A(0, 2) += x2y2;
        A(0, 3) += x3;
        A(0, 4) += x2y;
        A(0, 5) += x2;
        A(1, 2) += xy3;
        A(1, 4) += xy2;
        A(1, 5) += xy;
        A(2, 2) += y4;
        A(2, 4) += y3;
        A(2, 5) += y2;
        A(3, 3) += x2;
        A(3, 5) += points[i][0];
        A(4, 5) += points[i][1];

        B[0] += zx2;
        B[1] += zxy;
        B[2] += zy2;
        B[3] += zx;
        B[4] += zy;
        B[5] += points[i][2];
    }

    A(1, 0) = A(0, 1);
    A(1, 1) = A(0, 2);
    A(1, 3) = A(0, 4);
    A(2, 0) = A(0, 2);
    A(2, 1) = A(1, 2);
    A(2, 3) = A(1, 4);
    A(3, 0) = A(0, 3);
    A(3, 1) = A(1, 3);
    A(3, 2) = A(2, 3);
    A(3, 4) = A(1, 5);
    A(4, 0) = A(0, 4);
    A(4, 1) = A(1, 4);
    A(4, 2) = A(2, 4);
    A(4, 3) = A(3, 4);
    A(4, 4) = A(2, 5);
    A(5, 0) = A(0, 5);
    A(5, 1) = A(1, 5);
    A(5, 2) = A(2, 5);
    A(5, 3) = A(3, 5);
    A(5, 4) = A(4, 5);
    A(5, 5) = static_cast<Real>(numPoints);

    return LinearSystem<Real>().Solve(6, &A[0], &B[0], &coefficients[0]);
}
//----------------------------------------------------------------------------
