// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.1.0 (2014/08/17)

//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
IntpVectorField2<InputType, ComputeType, RationalType>::~IntpVectorField2()
{
    delete mXInterp;
    delete mYInterp;
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
IntpVectorField2<InputType, ComputeType, RationalType>::IntpVectorField2(
    int numPoints, Vector2<InputType> const* domain,
    Vector2<InputType> const* range)
    :
    mMesh(mDelaunay)
{
    // Repackage the output vectors into individual components.  This is
    // required because of the format that the quadratic interpolator expects
    // for its input data.
    mXRange.resize(numPoints);
    mYRange.resize(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        mXRange[i] = range[i][0];
        mYRange[i] = range[i][1];
    }

    // Common triangulator for the interpolators.
    mDelaunay(numPoints, &domain[0], (ComputeType)0);

    // Create interpolator for x-coordinate of vector field.
    mXInterp = new IntpQuadraticNonuniform2<InputType, TriangleMesh>(mMesh,
        &mXRange[0], (InputType)1);

    // Create interpolator for y-coordinate of vector field, but share the
    // already created triangulation for the x-interpolator.
    mYInterp = new IntpQuadraticNonuniform2<InputType, TriangleMesh>(mMesh,
        &mYRange[0], (InputType)1);
}
//----------------------------------------------------------------------------
template <typename InputType, typename ComputeType, typename RationalType>
bool IntpVectorField2<InputType, ComputeType, RationalType>::operator()(
    Vector2<InputType> const& input, Vector2<InputType>& output) const
{
    InputType xDeriv, yDeriv;
    return (*mXInterp)(input, output[0], xDeriv, yDeriv)
        && (*mYInterp)(input, output[1], xDeriv, yDeriv);
}
//----------------------------------------------------------------------------
