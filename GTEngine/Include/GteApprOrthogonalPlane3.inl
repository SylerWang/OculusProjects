// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
ApprOrthogonalPlane3<Real>::ApprOrthogonalPlane3()
{
    mParameters.first = Vector3<Real>::Zero();
    mParameters.second = Vector3<Real>::Zero();
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprOrthogonalPlane3<Real>::Fit(int numPoints,
    Vector3<Real> const* points)
{
    if (numPoints >= GetMinimumRequired() && points)
    {
        // Compute the mean of the points.
        Vector3<Real> mean = Vector3<Real>::Zero();
        for (int i = 0; i < numPoints; ++i)
        {
            mean += points[i];
        }
        mean /= (Real)numPoints;

        // Compute the covariance matrix of the points.
        Real covar00 = (Real)0, covar01 = (Real)0, covar02 = (Real)0;
        Real covar11 = (Real)0, covar12 = (Real)0, covar22 = (Real)0;
        for (int i = 0; i < numPoints; ++i)
        {
            Vector3<Real> diff = points[i] - mean;
            covar00 += diff[0] * diff[0];
            covar01 += diff[0] * diff[1];
            covar02 += diff[0] * diff[2];
            covar11 += diff[1] * diff[1];
            covar12 += diff[1] * diff[2];
            covar22 += diff[2] * diff[2];
        }

        // Solve the eigensystem.
        SymmetricEigensolver<Real> es(3, 32);
        std::array<Real, 9> M =
        {
            covar00, covar01, covar02,
            covar01, covar11, covar12,
            covar02, covar12, covar22
        };
        std::array<Real, 9> R;
        std::array<Real, 3> D;
        es.Solve(&M[0], +1);  // D[0] <= D[1] <= D[2]
        es.GetEigenvalues(&D[0]);
        es.GetEigenvectors(&R[0]);

        // The plane normal is the eigenvector in the direction of smallest
        // variance of the points.
        mParameters.first = mean;
        mParameters.second = Vector3<Real>(R[0], R[3], R[6]);

        // The fitted plane is unique when the minimum eigenvalue has
        // multiplicity 1.
        return D[0] < D[1];
    }

    mParameters.first = Vector3<Real>::Zero();
    mParameters.second = Vector3<Real>::Zero();
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
std::pair<Vector3<Real>, Vector3<Real>> const&
ApprOrthogonalPlane3<Real>::GetParameters() const
{
    return mParameters;
}
//----------------------------------------------------------------------------
template <typename Real>
int ApprOrthogonalPlane3<Real>::GetMinimumRequired() const
{
    return 3;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprOrthogonalPlane3<Real>::Error(Vector3<Real> const& observation)
const
{
    Vector3<Real> diff = observation - mParameters.first;
    Real sqrlen = Dot(diff, diff);
    Real dot = Dot(diff, mParameters.second);
    Real error = std::abs(sqrlen - dot*dot);
    return error;
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprOrthogonalPlane3<Real>::Fit(
    std::vector<Vector3<Real>> const& observations,
    std::vector<int> const& indices)
{
    if (static_cast<int>(indices.size()) >= GetMinimumRequired())
    {
        // Compute the mean of the points.
        Vector3<Real> mean = Vector3<Real>::Zero();
        for (auto index : indices)
        {
            mean += observations[index];
        }
        mean /= (Real)indices.size();

        // Compute the covariance matrix of the points.
        Real covar00 = (Real)0, covar01 = (Real)0, covar02 = (Real)0;
        Real covar11 = (Real)0, covar12 = (Real)0, covar22 = (Real)0;
        for (auto index : indices)
        {
            Vector3<Real> diff = observations[index] - mean;
            covar00 += diff[0]*diff[0];
            covar01 += diff[0]*diff[1];
            covar02 += diff[0]*diff[2];
            covar11 += diff[1]*diff[1];
            covar12 += diff[1]*diff[2];
            covar22 += diff[2]*diff[2];
        }

        // Solve the eigensystem.
        SymmetricEigensolver<Real> es(3, 32);
        std::array<Real, 9> M =
        {
            covar00, covar01, covar02,
            covar01, covar11, covar12,
            covar02, covar12, covar22
        };
        std::array<Real, 9> R;
        std::array<Real, 3> D;
        es.Solve(&M[0], +1);  // D[0] <= D[1] <= D[2]
        es.GetEigenvalues(&D[0]);
        es.GetEigenvectors(&R[0]);

        // The plane normal is the eigenvector in the direction of smallest
        // variance of the points.
        mParameters.first = mean;
        mParameters.second = Vector3<Real>(R[0], R[3], R[6]);

        // The fitted plane is unique when the minimum eigenvalue has
        // multiplicity 1.
        return D[0] < D[1];
    }

    mParameters.first = Vector3<Real>::Zero();
    mParameters.second = Vector3<Real>::Zero();
    return false;
}
//----------------------------------------------------------------------------
