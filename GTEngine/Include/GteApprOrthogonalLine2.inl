// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
ApprOrthogonalLine2<Real>::ApprOrthogonalLine2()
    :
    mParameters(Vector2<Real>::Zero(), Vector2<Real>::Zero())
{
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprOrthogonalLine2<Real>::Fit(int numPoints,
    Vector2<Real> const* points)
{
    if (numPoints >= GetMinimumRequired() && points)
    {
        // Compute the mean of the points.
        Vector2<Real> mean = Vector2<Real>::Zero();
        for (int i = 0; i < numPoints; ++i)
        {
            mean += points[i];
        }
        mean /= (Real)numPoints;

        // Compute the covariance matrix of the points.
        Real covar00 = (Real)0, covar01 = (Real)0, covar11 = (Real)0;
        for (int i = 0; i < numPoints; ++i)
        {
            Vector2<Real> diff = points[i] - mean;
            covar00 += diff[0] * diff[0];
            covar01 += diff[0] * diff[1];
            covar11 += diff[1] * diff[1];
        }

        // Solve the eigensystem.
        SymmetricEigensolver<Real> es(2, 32);
        std::array<Real, 4> M =
        {
            covar00, covar01,
            covar01, covar11
        };
        std::array<Real, 4> R;
        std::array<Real, 2> D;
        es.Solve(&M[0], +1);  // D[0] <= D[1]
        es.GetEigenvalues(&D[0]);
        es.GetEigenvectors(&R[0]);

        // The line direction is the eigenvector in the direction of largest
        // variance of the points.
        mParameters.origin = mean;
        mParameters.direction = Vector2<Real>(R[1], R[3]);

        // The fitted line is unique when the maximum eigenvalue has
        // multiplicity 1.
        return D[0] < D[1];
    }

    mParameters = Line2<Real>(Vector2<Real>::Zero(), Vector2<Real>::Zero());
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
Line2<Real> const& ApprOrthogonalLine2<Real>::GetParameters() const
{
    return mParameters;
}
//----------------------------------------------------------------------------
template <typename Real>
int ApprOrthogonalLine2<Real>::GetMinimumRequired() const
{
    return 2;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprOrthogonalLine2<Real>::Error(Vector2<Real> const& observation) const
{
    Vector2<Real> diff = observation - mParameters.origin;
    Real sqrlen = Dot(diff, diff);
    Real dot = Dot(diff, mParameters.direction);
    Real error = std::abs(sqrlen - dot*dot);
    return error;
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprOrthogonalLine2<Real>::Fit(
    std::vector<Vector2<Real>> const& observations,
    std::vector<int> const& indices)
{
    if (static_cast<int>(indices.size()) >= GetMinimumRequired())
    {
        // Compute the mean of the points.
        Vector2<Real> mean = Vector2<Real>::Zero();
        for (auto index : indices)
        {
            mean += observations[index];
        }
        mean /= (Real)indices.size();

        // Compute the covariance matrix of the points.
        Real covar00 = (Real)0, covar01 = (Real)0, covar11 = (Real)0;
        for (auto index : indices)
        {
            Vector2<Real> diff = observations[index] - mean;
            covar00 += diff[0]*diff[0];
            covar01 += diff[0]*diff[1];
            covar11 += diff[1]*diff[1];
        }

        // Solve the eigensystem.
        SymmetricEigensolver<Real> es(2, 32);
        std::array<Real, 4> M =
        {
            covar00, covar01,
            covar01, covar11
        };
        std::array<Real, 4> R;
        std::array<Real, 2> D;
        es.Solve(&M[0], +1);  // D[0] <= D[1]
        es.GetEigenvalues(&D[0]);
        es.GetEigenvectors(&R[0]);

        // The line direction is the eigenvector in the direction of largest
        // variance of the points.
        mParameters.origin = mean;
        mParameters.direction = Vector2<Real>(R[1], R[3]);

        // The fitted line is unique when the maximum eigenvalue has
        // multiplicity 1.
        return D[0] < D[1];
    }

    mParameters = Line2<Real>(Vector2<Real>::Zero(), Vector2<Real>::Zero());
    return false;
}
//----------------------------------------------------------------------------
