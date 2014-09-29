// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
Torus3<Real>::Torus3()
    :
    center(Vector3<Real>::Zero()),
    direction0(Vector3<Real>::Basis0()),
    direction1(Vector3<Real>::Basis1()),
    normal(Vector3<Real>::Basis2()),
    radius0((Real)2),
    radius1((Real)1)
{
}
//----------------------------------------------------------------------------
template <typename Real>
Torus3<Real>::Torus3(Vector3<Real> const& inCenter,
    Vector3<Real> const& inDirection0, Vector3<Real> const& inDirection1,
    Vector3<Real> const& inNormal, Real inRadius0, Real inRadius1)
    :
    center(inCenter),
    direction0(inDirection0),
    direction1(inDirection1),
    normal(inNormal),
    radius0(inRadius0),
    radius1(inRadius1)
{
}
//----------------------------------------------------------------------------
template <typename Real>
void Torus3<Real>::Evaluate(Real u, Real v, unsigned int maxOrder,
    Vector3<Real> values[6]) const
{
    // Compute position.
    Real csu = cos(u), snu = sin(u), csv = cos(v), snv = sin(v);
    Real r1csv = radius1 * csv;
    Real r1snv = radius1 * snv;
    Real r0pr1csv = radius0 + r1csv;
    Vector3<Real> combo0 = csu * direction0 + snu * direction1;
    Vector3<Real> r0pr1csvcombo0 = r0pr1csv * combo0;
    Vector3<Real> r1snvnormal = r1snv * normal;
    values[0] = center + r0pr1csvcombo0 + r1snvnormal;

    if (maxOrder >= 1)
    {
        // Compute first-order derivatives.
        Vector3<Real> combo1 = -snu * direction0 + csu * direction1;
        values[1] = r0pr1csv * combo1;
        values[2] = -r1snv * combo0 + r1csv * normal;

        if (maxOrder >= 2)
        {
            // Compute second-order derivatives.
            values[3] = -r0pr1csvcombo0;
            values[4] = -r1snv * combo1;
            values[5] = -r1csv * combo0 - r1snvnormal;

            if (maxOrder >= 3)
            {
                // These orders are not supported.
                for (int i = 0; i < 6; ++i)
                {
                    values[i] = Vector3<float>::Zero();
                }
            }
        }
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void Torus3<Real>::GetParameters(Vector3<Real> const& X, Real& u, Real& v)
    const
{
    Vector3<Real> delta = X - center;
    Real dot0 = Dot(direction0, delta);  // (r0 + r1*cos(v))*cos(u)
    Real dot1 = Dot(direction1, delta);  // (r0 + r1*cos(v))*sin(u)
    Real dot2 = Dot(normal, delta);      // r1*sin(v)
    Real r1csv = sqrt(dot0 * dot0 + dot1 * dot1) - radius0;  // r1*cos(v)
    u = atan2(dot1, dot0);
    v = atan2(dot2, r1csv);
}
//----------------------------------------------------------------------------
template <typename Real>
bool Torus3<Real>::IsEqualTo(Torus3 const& torus) const
{
    return center == torus.center
        && direction0 == torus.direction0
        && direction1 == torus.direction1
        && normal == torus.normal
        && radius0 == torus.radius0
        && radius1 == torus.radius1;
}
//----------------------------------------------------------------------------
template <typename Real>
bool Torus3<Real>::IsLessThan(Torus3 const& torus) const
{
    if (center < torus.center)
    {
        return true;
    }

    if (center > torus.center)
    {
        return false;
    }

    if (direction0 < torus.direction0)
    {
        return true;
    }

    if (direction0 > torus.direction0)
    {
        return false;
    }

    if (direction1 < torus.direction1)
    {
        return true;
    }

    if (direction1 > torus.direction1)
    {
        return false;
    }

    if (normal < torus.normal)
    {
        return true;
    }

    if (normal > torus.normal)
    {
        return false;
    }

    if (radius0 < torus.radius0)
    {
        return true;
    }

    if (radius0 > torus.radius0)
    {
        return false;
    }

    return radius1 < torus.radius1;
}
//----------------------------------------------------------------------------
