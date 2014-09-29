// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
void ApprGreatCircle3<Real>::operator()(int numPoints,
    Vector3<Real> const* points, Vector3<Real>& normal)
{
    // Compute the covariance matrix of the vectors.
    Matrix3x3<Real> A;
    A.MakeZero();
    for (int i = 0; i < numPoints; i++) 
    {
        Vector3<Real> diff = points[i];
        A(0, 0) += diff[0]*diff[0];
        A(0, 1) += diff[0]*diff[1];
        A(0, 2) += diff[0]*diff[2];
        A(1, 1) += diff[1]*diff[1];
        A(1, 2) += diff[1]*diff[2];
        A(2, 2) += diff[2]*diff[2];
    }

    Real invNumPoints = ((Real)1) / static_cast<Real>(numPoints);
    A(0, 0) *= invNumPoints;
    A(0, 1) *= invNumPoints;
    A(0, 2) *= invNumPoints;
    A(1, 1) *= invNumPoints;
    A(1, 2) *= invNumPoints;
    A(2, 2) *= invNumPoints;
    A(1, 0) = A(0, 1);
    A(2, 0) = A(0, 2);
    A(2, 1) = A(1, 2);

    // Set up the eigensolver.
    SymmetricEigensolver<Real> es(3, 64);
    es.Solve(&A[0], +1);
    es.GetEigenvector(0, &normal[0]);
}
//----------------------------------------------------------------------------
template <typename Real>
void ApprGreatArc3<Real>::operator()(int numPoints,
    Vector3<Real> const* points, Vector3<Real>& normal,
    Vector3<Real>& arcEnd0, Vector3<Real>& arcEnd1)
{
    // Get the least-squares great circle for the vectors.  The circle is on
    // the plane Dot(N,X) = 0.  Generate a basis from N.
    Vector3<Real> basis[3];  // { N, U, V }
    ApprGreatCircle3<Real>()(numPoints, points, basis[0]);
    ComputeOrthogonalComplement(1, basis);

    // The vectors are X[i] = u[i]*U + v[i]*V + w[i]*N.  The projections
    // are P[i] = (u[i]*U + v[i]*V)/sqrt(u[i]*u[i] + v[i]*v[i]).  The great
    // circle is parameterized by C(t) = cos(t)*U + sin(t)*V.  Compute the
    // angles t in [-pi,pi] for the projections onto the great circle.  It
    // is not necesarily to normalize (u[i],v[i]), instead computing
    // t = atan2(v[i],u[i]).
    std::vector<std::array<Real, 3>> items(numPoints);  // item (u, v, angle)
    for (int i = 0; i < numPoints; ++i)
    {
        items[i][0] = Dot(basis[1], points[i]);
        items[i][1] = Dot(basis[2], points[i]);
        items[i][2] = atan2(items[i][1], items[i][0]);
    }
    std::sort(items.begin(), items.end(),
        [](std::array<Real, 3> const& item0, std::array<Real, 3> const& item1)
        {
            return item0[2] < item1[2];
        }
    );

    // Locate the pair of consecutive angles whose difference is a maximum.
    // Effectively, we are constructing a cone of minimum angle that contains
    // the unit-length vectors.
    int numPointsM1 = numPoints - 1;
    Real maxDiff = (Real)GTE_C_TWO_PI + items[0][2] - items[numPointsM1][2];
    int end0 = 0, end1 = numPointsM1;
    for (int i0 = 0, i1 = 1; i0 < numPointsM1; i0 = i1++)
    {
        Real diff = items[i1][2] - items[i0][2];
        if (diff > maxDiff)
        {
            maxDiff = diff;
            end0 = i1;
            end1 = i0;
        }
    }

    normal = basis[0];
    arcEnd0 = items[end0][0] * basis[1] + items[end0][1] * basis[2];
    arcEnd1 = items[end1][0] * basis[1] + items[end1][1] * basis[2];
    Normalize(arcEnd0);
    Normalize(arcEnd1);
}
//----------------------------------------------------------------------------
