// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
ApprGaussian2<Real>::ApprGaussian2()
{
    mParameters.center = Vector2<Real>::Zero();
    mParameters.axis[0] = Vector2<Real>::Zero();
    mParameters.axis[1] = Vector2<Real>::Zero();
    mParameters.extent = Vector2<Real>::Zero();
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprGaussian2<Real>::Fit(int numPoints, Vector2<Real> const* points)
{
    if (numPoints >= GetMinimumRequired() && points)
    {
        // Compute the mean of the points.
        Vector2<Real> mean = Vector2<Real>::Zero();
        for (int i = 0; i < numPoints; ++i)
        {
            mean += points[i];
        }
        Real invSize = ((Real)1) / (Real)numPoints;
        mean *= invSize;

        // Compute the covariance matrix of the points.
        Real covar00 = (Real)0, covar01 = (Real)0, covar11 = (Real)0;
        for (int i = 0; i < numPoints; ++i)
        {
            Vector2<Real> diff = points[i] - mean;
            covar00 += diff[0] * diff[0];
            covar01 += diff[0] * diff[1];
            covar11 += diff[1] * diff[1];
        }
        covar00 *= invSize;
        covar01 *= invSize;
        covar11 *= invSize;

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

        if (es.IsRotation())
        {
            mParameters.axis[0] = Vector2<Real>(R[0], R[2]);
            mParameters.axis[1] = Vector2<Real>(R[1], R[3]);
        }
        else
        {
            mParameters.axis[0] = Vector2<Real>(R[1], R[3]);
            mParameters.axis[1] = Vector2<Real>(R[0], R[2]);
        }

        mParameters.center = mean;
        mParameters.extent[0] = D[0];
        mParameters.extent[1] = D[1];
        return true;
    }

    mParameters.center = Vector2<Real>::Zero();
    mParameters.axis[0] = Vector2<Real>::Zero();
    mParameters.axis[1] = Vector2<Real>::Zero();
    mParameters.extent = Vector2<Real>::Zero();
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
OrientedBox2<Real> const& ApprGaussian2<Real>::GetParameters() const
{
    return mParameters;
}
//----------------------------------------------------------------------------
template <typename Real>
int ApprGaussian2<Real>::GetMinimumRequired() const
{
    return 2;
}
//----------------------------------------------------------------------------
template <typename Real>
bool ApprGaussian2<Real>::Fit(
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
        Real invSize = ((Real)1) / (Real)indices.size();
        mean *= invSize;

        // Compute the covariance matrix of the points.
        Real covar00 = (Real)0, covar01 = (Real)0, covar11 = (Real)0;
        for (auto index : indices)
        {
            Vector2<Real> diff = observations[index] - mean;
            covar00 += diff[0] * diff[0];
            covar01 += diff[0] * diff[1];
            covar11 += diff[1] * diff[1];
        }
        covar00 *= invSize;
        covar01 *= invSize;
        covar11 *= invSize;

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

        mParameters.center = mean;
        mParameters.axis[0] = Vector2<Real>(R[0], R[2]);
        mParameters.axis[1] = Vector2<Real>(R[1], R[3]);
        mParameters.extent[0] = D[0];
        mParameters.extent[1] = D[1];
    }

    mParameters.center = Vector2<Real>::Zero();
    mParameters.axis[0] = Vector2<Real>::Zero();
    mParameters.axis[1] = Vector2<Real>::Zero();
    mParameters.extent = Vector2<Real>::Zero();
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprGaussian2<Real>::Error(Vector2<Real> const& observation) const
{
    Vector2<Real> diff = observation - mParameters.center;
    Real error = (Real)0;
    for (int i = 0; i < 2; ++i)
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
