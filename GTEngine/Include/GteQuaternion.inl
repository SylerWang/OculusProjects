// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.2 (2014/09/18)

//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real>::~Quaternion()
{
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real>::Quaternion()
{
    // Uninitialized.
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real>::Quaternion(Quaternion const& q)
{
    this->mTuple[0] = q[0];
    this->mTuple[1] = q[1];
    this->mTuple[2] = q[2];
    this->mTuple[3] = q[3];
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real>::Quaternion(Vector<4,Real> const& q)
{
    this->mTuple[0] = q[0];
    this->mTuple[1] = q[1];
    this->mTuple[2] = q[2];
    this->mTuple[3] = q[3];
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real>::Quaternion(Real x, Real y, Real z, Real w)
{
    this->mTuple[0] = x;
    this->mTuple[1] = y;
    this->mTuple[2] = z;
    this->mTuple[3] = w;
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real>& Quaternion<Real>::operator=(Quaternion const& q)
{
    Vector<4,Real>::operator=(q);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real>& Quaternion<Real>::operator=(Vector<4,Real> const& q)
{
    Vector<4,Real>::operator=(q);
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Quaternion<Real>::Zero()
{
    return Quaternion((Real)0, (Real)0, (Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Quaternion<Real>::I()
{
    return Quaternion((Real)1, (Real)0, (Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Quaternion<Real>::J()
{
    return Quaternion((Real)0, (Real)1, (Real)0, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Quaternion<Real>::K()
{
    return Quaternion((Real)0, (Real)0, (Real)1, (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Quaternion<Real>::Identity()
{
    return Quaternion((Real)0, (Real)0, (Real)0, (Real)1);
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> operator*(Quaternion<Real> const& q0,
    Quaternion<Real> const& q1)
{
    // (x0*i + y0*j + z0*k + w0)*(x1*i + y1*j + z1*k + w1)
    // =
    // i*(+x0*w1 + y0*z1 - z0*y1 + w0*x1) +
    // j*(-x0*z1 + y0*w1 + z0*x1 + w0*y1) +
    // k*(+x0*y1 - y0*x1 + z0*w1 + w0*z1) +
    // 1*(-x0*x1 - y0*y1 - z0*z1 + w0*w1)

    return Quaternion<Real>
    (
        +q0[0]*q1[3] + q0[1]*q1[2] - q0[2]*q1[1] + q0[3]*q1[0],
        -q0[0]*q1[2] + q0[1]*q1[3] + q0[2]*q1[0] + q0[3]*q1[1],
        +q0[0]*q1[1] - q0[1]*q1[0] + q0[2]*q1[3] + q0[3]*q1[2],
        -q0[0]*q1[0] - q0[1]*q1[1] - q0[2]*q1[2] + q0[3]*q1[3]
    );
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Inverse(Quaternion<Real> const& q)
{
    Real sqrLen = Dot(q, q);
    if (sqrLen > (Real)0)
    {
        Real invSqrLen = ((Real)1)/sqrLen;
        Quaternion<Real> inverse = Conjugate(q)*invSqrLen;
        return inverse;
    }
    else
    {
        return Quaternion<Real>::Zero();
    }
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Conjugate(Quaternion<Real> const& q)
{
    return Quaternion<Real>(-q[0], -q[1], -q[2], +q[3]);
}
//----------------------------------------------------------------------------
template <typename Real>
Vector<4,Real> Rotate(Quaternion<Real> const& q, Vector<4,Real> const& v)
{
    Vector<4,Real> u = q*Quaternion<Real>(v)*Conjugate(q);

    // Zero-out the w-component in remove numerical round-off error.
    u[3] = (Real)0;
    return u;
}
//----------------------------------------------------------------------------
template <typename Real>
Quaternion<Real> Slerp(Real t, Quaternion<Real> const& q0,
    Quaternion<Real> const& q1)
{
    Real const onePlusMuFPU = (Real)1.90110745351730037;

    Real const a[8] =
    {
        (Real)1/((Real)1*(Real)3),
        (Real)1/((Real)2*(Real)5),
        (Real)1/((Real)3*(Real)7),
        (Real)1/((Real)4*(Real)9),
        (Real)1/((Real)5*(Real)11),
        (Real)1/((Real)6*(Real)13),
        (Real)1/((Real)7*(Real)15),
        onePlusMuFPU*(Real)1/((Real)8*(Real)17)
    };

    Real const b[8] =
    {
        (Real)1/(Real)3,
        (Real)2/(Real)5,
        (Real)3/(Real)7,
        (Real)4/(Real)9,
        (Real)5/(Real)11,
        (Real)6/(Real)13,
        (Real)7/(Real)15,
        onePlusMuFPU*(Real)8/(Real)17
    };

    Real cs = Dot(q0, q1);
    Real sign;
    if (cs >= (Real)0)
    {
        sign = (Real)1;
    }
    else
    {
        cs = -cs;
        sign = (Real)-1;
    }

    Real csm1 = cs - (Real)1;
    Real term0 = (Real)1 - t, term1 = t;
    Real sqr0 = term0*term0, sqr1 = term1*term1;
    Real u0 = term0, u1 = term1;
    for (int i = 0; i <= 7; ++i)
    {
        term0 *= (a[i]*sqr0 - b[i])*csm1;
        term1 *= (a[i]*sqr1 - b[i])*csm1;
        u0 += term0;
        u1 += term1;
    }
    u1 *= sign;

    Quaternion<Real> slerp = q0*u0 + q1*u1;
    return slerp;
}
//----------------------------------------------------------------------------
