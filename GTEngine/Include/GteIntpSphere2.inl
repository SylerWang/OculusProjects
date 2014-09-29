// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
IntpSphere2<InputType, ComputeType, RationalType>::~IntpSphere2()
{
    delete mInterp;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
IntpSphere2<InputType, ComputeType, RationalType>::IntpSphere2(int numPoints,
    InputType const* theta, InputType const* phi, InputType const* F)
    :
    mMesh(mDelaunay)
{
    // Copy the input data.  The larger arrays are used to support wrap-around
    // in the Delaunay triangulation for the interpolator.
    int totalPoints = 3 * numPoints;
    mWrapAngles.resize(totalPoints);
    mWrapF.resize(totalPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        mWrapAngles[i][0] = theta[i];
        mWrapAngles[i][1] = phi[i];
        mWrapF[i] = F[i];
    }

    // Use periodicity to get wrap-around in the Delaunay triangulation.
    int i0 = 0, i1 = numPoints, i2 = 2 * numPoints;
    for (/**/; i0 < numPoints; ++i0, ++i1, ++i2)
    {
        mWrapAngles[i1][0] = mWrapAngles[i0][0] + (InputType)GTE_C_TWO_PI;
        mWrapAngles[i2][0] = mWrapAngles[i0][0] - (InputType)GTE_C_TWO_PI;
        mWrapAngles[i1][1] = mWrapAngles[i0][1];
        mWrapAngles[i2][1] = mWrapAngles[i0][1];
        mWrapF[i1] = mWrapF[i0];
        mWrapF[i2] = mWrapF[i0];
    }

    mDelaunay(totalPoints, &mWrapAngles[0], (ComputeType)0);
    mInterp = new IntpQuadraticNonuniform2<InputType, TriangleMesh>(mMesh,
        &mWrapF[0], (InputType)1);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
void IntpSphere2<InputType, ComputeType, RationalType>::
GetSphericalCoordinates(InputType x, InputType y, InputType z,
    InputType& theta, InputType& phi)
{
    // Assumes (x,y,z) is unit length.  Returns -pi <= theta <= pi and
    // 0 <= phiAngle <= pi.

    if (z < (InputType)1)
    {
        if (z > -(InputType)1)
        {
            theta = atan2(y, x);
            phi = acos(z);
        }
        else
        {
            theta = -(InputType)GTE_C_PI;
            phi = (InputType)GTE_C_PI;
        }
    }
    else
    {
        theta = -(InputType)GTE_C_PI;
        phi = (InputType)0;
    }
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
bool IntpSphere2<InputType, ComputeType, RationalType>::operator()(
    InputType theta, InputType phi, InputType& F) const
{
    Vector2<InputType> angles(theta, phi);
    InputType thetaDeriv, phiDeriv;
    return (*mInterp)(angles, F, thetaDeriv, phiDeriv);
}
//----------------------------------------------------------------------------
