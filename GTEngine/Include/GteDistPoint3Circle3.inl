// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
typename DCPQuery<Real, Vector3<Real>, Circle3<Real>>::Result
DCPQuery<Real, Vector3<Real>, Circle3<Real>>::operator()(
    Vector3<Real> const& point, Circle3<Real> const& circle)
{
    Result result;

    // Projection of P-C onto plane is Q-C = P-C - Dot(N,P-C)*N.
    Vector3<Real> PmC = point - circle.center;
    Vector3<Real> QmC = PmC - Dot(circle.normal, PmC)*circle.normal;
    Real lengthQmC = Length(QmC);
    if (lengthQmC > (Real)0)
    {
        result.numClosestPoints = 1;
        result.circleClosestPoint =
            circle.center + circle.radius*QmC / lengthQmC;
    }
    else
    {
        // All circle points are equidistant from P.  Return one of them.
        result.numClosestPoints = std::numeric_limits<int>::max();
        Vector3<Real> basis[3];
        basis[0] = circle.normal;
        ComputeOrthogonalComplement(1, basis);
        result.circleClosestPoint =
            circle.center + circle.radius*basis[1];
    }

    Vector3<Real> diff = point - result.circleClosestPoint;
    result.sqrDistance = Dot(diff, diff);
    result.distance = sqrt(result.sqrDistance);
    return result;
}
//----------------------------------------------------------------------------
