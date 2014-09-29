// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
ApprGaussian3<Real>::ApprGaussian3()
{
    mParameters.center = Vector3<Real>::Zero();
    mParameters.axis[0] = Vector3<Real>::Zero();
    mParameters.axis[1] = Vector3<Real>::Zero();
    mParameters.axis[2] = Vector3<Real>::Zero();
    mParameters.extent = Vector3<Real>::Zero();
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprGaussian3<Real>::Fit(int numPoints, Vector3<Real> const* points)
{
    if (numPoints >= GetMinimumRequired() && points)
    {
        // Compute the mean of the points.
        Vector3<Real> mean = Vector3<Real>::Zero();
        for (int i = 0; i < numPoints; ++i)
        {
            mean += points[i];
        }
        Real invSize = ((Real)1) / (Real)numPoints;
        mean *= invSize;

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
        covar00 *= invSize;
        covar01 *= invSize;
        covar02 *= invSize;
        covar11 *= invSize;
        covar12 *= invSize;
        covar22 *= invSize;

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

        if (es.IsRotation())
        {
            mParameters.axis[0] = Vector3<Real>(R[0], R[3], R[6]);
            mParameters.axis[1] = Vector3<Real>(R[1], R[4], R[7]);
            mParameters.axis[2] = Vector3<Real>(R[2], R[5], R[8]);
        }
        else
        {
            mParameters.axis[0] = Vector3<Real>(R[0], R[3], R[6]);
            mParameters.axis[1] = Vector3<Real>(R[2], R[5], R[8]);
            mParameters.axis[2] = Vector3<Real>(R[1], R[4], R[7]);
        }

        mParameters.center = mean;
        mParameters.extent[0] = D[0];
        mParameters.extent[1] = D[1];
        mParameters.extent[2] = D[2];
        return true;
    }

    mParameters.center = Vector3<Real>::Zero();
    mParameters.axis[0] = Vector3<Real>::Zero();
    mParameters.axis[1] = Vector3<Real>::Zero();
    mParameters.axis[2] = Vector3<Real>::Zero();
    mParameters.extent = Vector3<Real>::Zero();
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
OrientedBox3<Real> const& ApprGaussian3<Real>::GetParameters() const
{
    return mParameters;
}
//----------------------------------------------------------------------------
template <typename Real>
int ApprGaussian3<Real>::GetMinimumRequired() const
{
    return 2;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprGaussian3<Real>::Error(Vector3<Real> const& observation) const
{
    Vector3<Real> diff = observation - mParameters.center;
    Real error = (Real)0;
    for (int i = 0; i < 3; ++i)
    {
        if (mParameters.extent[i] >(Real)0)
        {
            Real ratio = Dot(diff, mParameters.axis[i]) /
                mParameters.extent[i];
            error += ratio * ratio;
        }
    }
    return error;
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprGaussian3<Real>::Fit(
    std::vector<Vector3<Real>> const& observations,
    std::vector<int> const& indices)
{
    if (static_cast<int>(indices.size()) >= GetMinimumRequired())
    {
        // Compute the mean of the points.
        Vector3<Real> mean = Vector3<Real>::Zero();
        for (auto index : indices)
        {
            mParameters.center += observations[index];
        }
        Real invSize = ((Real)1) / (Real)indices.size();
        mean *= invSize;

        // Compute the covariance matrix of the points.
        Real covar00 = (Real)0, covar01 = (Real)0, covar02 = (Real)0;
        Real covar11 = (Real)0, covar12 = (Real)0, covar22 = (Real)0;
        for (auto index : indices)
        {
            Vector3<Real> diff = observations[index] - mean;
            covar00 += diff[0] * diff[0];
            covar01 += diff[0] * diff[1];
            covar02 += diff[0] * diff[2];
            covar11 += diff[1] * diff[1];
            covar12 += diff[1] * diff[2];
            covar22 += diff[2] * diff[2];
        }
        covar00 *= invSize;
        covar01 *= invSize;
        covar02 *= invSize;
        covar11 *= invSize;
        covar12 *= invSize;
        covar22 *= invSize;

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

        mParameters.center = mean;
        mParameters.axis[0] = Vector3<Real>(R[0], R[3], R[6]);
        mParameters.axis[1] = Vector3<Real>(R[1], R[4], R[7]);
        mParameters.axis[2] = Vector3<Real>(R[2], R[5], R[8]);
        mParameters.extent[0] = D[0];
        mParameters.extent[1] = D[1];
        mParameters.extent[2] = D[2];
    }

    mParameters.center = Vector3<Real>::Zero();
    mParameters.axis[0] = Vector3<Real>::Zero();
    mParameters.axis[1] = Vector3<Real>::Zero();
    mParameters.axis[2] = Vector3<Real>::Zero();
    mParameters.extent = Vector3<Real>::Zero();
    return false;
}
//----------------------------------------------------------------------------
