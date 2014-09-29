// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Real ApprEllipse2<Real>::operator()(int numPoints,
    Vector2<Real> const* points, Vector2<Real>& center,
    Matrix2x2<Real>& rotate, Real diagonal[2])
{
    // Energy function is E : R^5 -> R where
    //   V = (V0, V1, V2, V3, V4)
    //     = (D[0], D[1], U.x, U.y, atan2(R(0,1),R(0,0))).
    std::function<Real(Real const*)> energy =
        [numPoints, points](Real const* input)
        {
            return Energy(numPoints, points, input);
        };

    MinimizeN<Real> minimizer(5, energy, 8, 8, 32);

    // The initial guess for the minimizer is based on an oriented box that
    // contains the points.
    OrientedBox2<Real> box;
    GetContainer(numPoints, points, box);
    center = box.center;
    for (int i = 0; i < 2; ++i)
    {
        rotate.SetRow(i, box.axis[i]);
        diagonal[i] = box.extent[i];
    }

    Real angle = atan2(rotate(0, 1), rotate(0, 0));
    Real e0 = 
        diagonal[0] * std::abs(rotate(0, 0)) +
        diagonal[1] * std::abs(rotate(1, 0));
    Real e1 =
        diagonal[0] * std::abs(rotate(0, 1)) +
        diagonal[1] * std::abs(rotate(1, 1));

    Real v0[5] =
    {
        ((Real)0.5)*diagonal[0],
        ((Real)0.5)*diagonal[1],
        center[0] - e0,
        center[1] - e1,
        -(Real)GTE_C_PI
    };

    Real v1[5] =
    {
        ((Real)2)*diagonal[0],
        ((Real)2)*diagonal[1],
        center[0] + e0,
        center[1] + e1,
        (Real)GTE_C_PI
    };

    Real vInitial[5] =
    {
        diagonal[0],
        diagonal[1],
        center[0],
        center[1],
        angle
    };

    Real vMin[5], error;
    minimizer.GetMinimum(v0, v1, vInitial, vMin, error);

    diagonal[0] = vMin[0];
    diagonal[1] = vMin[1];
    center[0] = vMin[2];
    center[1] = vMin[3];
    rotate.MakeRotation(-vMin[4]);

    return error;
}
//----------------------------------------------------------------------------
template <typename Real>
Real ApprEllipse2<Real>::Energy(int numPoints, Vector2<Real> const* points,
    Real const* input)
{
    // Build rotation matrix.
    Matrix2x2<Real> rotate(-input[4]);

    Ellipse2<Real> ellipse(Vector2<Real>::Zero(),
        Vector2<Real>::Basis0(), Vector2<Real>::Basis1(),
        input[0], input[1]);

    // Transform the points to the coordinate system of center C and
    // columns of rotation R.
    DCPQuery<Real, Vector2<Real>, Ellipse2<Real>> peQuery;
    Real energy = (Real)0;
    for (int i = 0; i < numPoints; ++i)
    {
        Vector2<Real> diff = points[i] - Vector2<Real>(input[2], input[3]);
        Vector2<Real> prod = rotate * diff;
        Real dist = peQuery(prod, ellipse).distance;
        energy += dist;
    }

    return energy;
}
//----------------------------------------------------------------------------
