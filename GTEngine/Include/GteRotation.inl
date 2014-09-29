// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::Rotation(Matrix<N,N,Real> const& matrix)
    :
    mType(IS_MATRIX),
    mMatrix(matrix)
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::Rotation(Quaternion<Real> const& quaternion)
    :
    mType(IS_QUATERNION),
    mQuaternion(quaternion)
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::Rotation(AxisAngle<N,Real> const& axisAngle)
    :
    mType(IS_AXIS_ANGLE),
    mAxisAngle(axisAngle)
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::Rotation(EulerAngles<Real> const& eulerAngles)
    :
    mType(IS_EULER_ANGLES),
    mEulerAngles(eulerAngles)
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::operator Matrix<N,N,Real>() const
{
    switch (mType)
    {
    case IS_MATRIX:
        break;
    case IS_QUATERNION:
        Convert(mQuaternion, mMatrix);
        break;
    case IS_AXIS_ANGLE:
        Convert(mAxisAngle, mMatrix);
        break;
    case IS_EULER_ANGLES:
        Convert(mEulerAngles, mMatrix);
        break;
    }

    return mMatrix;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::operator Quaternion<Real>() const
{
    switch (mType)
    {
    case IS_MATRIX:
        Convert(mMatrix, mQuaternion);
        break;
    case IS_QUATERNION:
        break;
    case IS_AXIS_ANGLE:
        Convert(mAxisAngle, mQuaternion);
        break;
    case IS_EULER_ANGLES:
        Convert(mEulerAngles, mQuaternion);
        break;
    }

    return mQuaternion;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::operator AxisAngle<N,Real>() const
{
    switch (mType)
    {
    case IS_MATRIX:
        Convert(mMatrix, mAxisAngle);
        break;
    case IS_QUATERNION:
        Convert(mQuaternion, mAxisAngle);
        break;
    case IS_AXIS_ANGLE:
        break;
    case IS_EULER_ANGLES:
        Convert(mEulerAngles, mAxisAngle);
        break;
    }

    return mAxisAngle;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Rotation<N,Real>::operator EulerAngles<Real>() const
{
    switch (mType)
    {
    case IS_MATRIX:
        Convert(mMatrix, mEulerAngles);
        break;
    case IS_QUATERNION:
        Convert(mQuaternion, mEulerAngles);
        break;
    case IS_AXIS_ANGLE:
        Convert(mAxisAngle, mEulerAngles);
        break;
    case IS_EULER_ANGLES:
        break;
    }

    return mEulerAngles;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert (Matrix<N,N,Real> const& r,
    Quaternion<Real>& q)
{
    Real r22 = r(2,2);
    if (r22 <= (Real)0)  // x^2 + y^2 >= z^2 + w^2
    {
        Real dif10 = r(1,1) - r(0,0);
        Real omr22 = (Real)1 - r22;
        if (dif10 <= (Real)0)  // x^2 >= y^2
        {
            Real fourXSqr = omr22 - dif10;
            Real inv4x = ((Real)0.5)/sqrt(fourXSqr);
            q[0] = fourXSqr*inv4x;
            q[1] = (r(0,1) + r(1,0))*inv4x;
            q[2] = (r(0,2) + r(2,0))*inv4x;
#if defined(GTE_USE_MAT_VEC)
            q[3] = (r(2,1) - r(1,2))*inv4x;
#else
            q[3] = (r(1,2) - r(2,1))*inv4x;
#endif
        }
        else  // y^2 >= x^2
        {
            Real fourYSqr = omr22 + dif10;
            Real inv4y = ((Real)0.5)/sqrt(fourYSqr);
            q[0] = (r(0,1) + r(1,0))*inv4y;
            q[1] = fourYSqr*inv4y;
            q[2] = (r(1,2) + r(2,1))*inv4y;
#if defined(GTE_USE_MAT_VEC)
            q[3] = (r(0,2) - r(2,0))*inv4y;
#else
            q[3] = (r(2,0) - r(0,2))*inv4y;
#endif
        }
    }
    else  // z^2 + w^2 >= x^2 + y^2
    {
        Real sum10 = r(1,1) + r(0,0);
        Real opr22 = (Real)1 + r22;
        if (sum10 <= (Real)0)  // z^2 >= w^2
        {
            Real fourZSqr = opr22 - sum10;
            Real inv4z = ((Real)0.5)/sqrt(fourZSqr);
            q[0] = (r(0,2) + r(2,0))*inv4z;
            q[1] = (r(1,2) + r(2,1))*inv4z;
            q[2] = fourZSqr*inv4z;
#if defined(GTE_USE_MAT_VEC)
            q[3] = (r(1,0) - r(0,1))*inv4z;
#else
            q[3] = (r(0,1) - r(1,0))*inv4z;
#endif
        }
        else  // w^2 >= z^2
        {
            Real fourWSqr = opr22 + sum10;
            Real inv4w = ((Real)0.5)/sqrt(fourWSqr);
#if defined(GTE_USE_MAT_VEC)
            q[0] = (r(2,1) - r(1,2))*inv4w;
            q[1] = (r(0,2) - r(2,0))*inv4w;
            q[2] = (r(1,0) - r(0,1))*inv4w;
#else
            q[0] = (r(1,2) - r(2,1))*inv4w;
            q[1] = (r(2,0) - r(0,2))*inv4w;
            q[2] = (r(0,1) - r(1,0))*inv4w;
#endif
            q[3] = fourWSqr*inv4w;
        }
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(Quaternion<Real> const& q, Matrix<N,N,Real>& r)
{
    MakeIdentity(r);

    Real twoX  = ((Real)2)*q[0];
    Real twoY  = ((Real)2)*q[1];
    Real twoZ  = ((Real)2)*q[2];
    Real twoXX = twoX*q[0];
    Real twoXY = twoX*q[1];
    Real twoXZ = twoX*q[2];
    Real twoXW = twoX*q[3];
    Real twoYY = twoY*q[1];
    Real twoYZ = twoY*q[2];
    Real twoYW = twoY*q[3];
    Real twoZZ = twoZ*q[2];
    Real twoZW = twoZ*q[3];

#if defined(GTE_USE_MAT_VEC)
    r(0,0) = (Real)1 - twoYY - twoZZ;
    r(0,1) = twoXY - twoZW;
    r(0,2) = twoXZ + twoYW;
    r(1,0) = twoXY + twoZW;
    r(1,1) = (Real)1 - twoXX - twoZZ;
    r(1,2) = twoYZ - twoXW;
    r(2,0) = twoXZ - twoYW;
    r(2,1) = twoYZ + twoXW;
    r(2,2) = (Real)1 - twoXX - twoYY;
#else
    r(0,0) = (Real)1 - twoYY - twoZZ;
    r(1,0) = twoXY - twoZW;
    r(2,0) = twoXZ + twoYW;
    r(0,1) = twoXY + twoZW;
    r(1,1) = (Real)1 - twoXX - twoZZ;
    r(2,1) = twoYZ - twoXW;
    r(0,2) = twoXZ - twoYW;
    r(1,2) = twoYZ + twoXW;
    r(2,2) = (Real)1 - twoXX - twoYY;
#endif
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(Matrix<N,N,Real> const& r,
    AxisAngle<N,Real>& a)
{
    Real trace = r(0,0) + r(1,1) + r(2,2);
    Real half = (Real)0.5;
    Real cs = half*(trace - (Real)1);
    cs = std::min(std::max(cs, (Real)1), (Real)-1);
    a.angle = acos(cs);  // The angle is in [0,pi].
    a.axis.MakeZero();

    if (a.angle > (Real)0)
    {
        if (a.angle < (Real)GTE_C_PI)
        {
            // The angle is in (0,pi).
#if defined(GTE_USE_MAT_VEC)
            a.axis[0] = r(2,1) - r(1,2);
            a.axis[1] = r(0,2) - r(2,0);
            a.axis[2] = r(1,0) - r(0,1);
            Normalize(a.axis);
#else
            a.axis[0] = r(1,2) - r(2,1);
            a.axis[1] = r(2,0) - r(0,2);
            a.axis[2] = r(0,1) - r(1,0);
            Normalize(a.axis);
#endif
        }
        else
        {
            // The angle is pi, in which case R is symmetric and
            // R+I = 2*(I+S^2) = 2*U*U^T, where U = (u0,u1,u2) is the
            // unit-length direction of the rotation axis.  Determine the
            // largest diagonal entry of R+I and normalize the
            // corresponding row to produce U.  It does not matter the
            // sign on u[d] for chosen diagonal d, because R(U,pi) = R(-U,pi).
            Real one = (Real)1;
            if (r(0,0) >= r(1,1))
            {
                if (r(0,0) >= r(2,2))
                {
                    // r00 is maximum diagonal term
                    a.axis[0] = r(0,0) + one;
                    a.axis[1] = half*(r(0,1) + r(1,0));
                    a.axis[2] = half*(r(0,2) + r(2,0));
                }
                else
                {
                    // r22 is maximum diagonal term
                    a.axis[0] = half*(r(2,0) + r(0,2));
                    a.axis[1] = half*(r(2,1) + r(1,2));
                    a.axis[2] = r(2,2) + one;
                }
            }
            else
            {
                if (r(1,1) >= r(2,2))
                {
                    // r11 is maximum diagonal term
                    a.axis[0] = half*(r(1,0) + r(0,1));
                    a.axis[1] = r(1,1) + one;
                    a.axis[2] = half*(r(1,2) + r(2,1));
                }
                else
                {
                    // r22 is maximum diagonal term
                    a.axis[0] = half*(r(2,0) + r(0,2));
                    a.axis[1] = half*(r(2,1) + r(1,2));
                    a.axis[2] = r(2,2) + one;
                }
            }
            Normalize(a.axis);
        }
    }
    else
    {
        // The angle is 0 and the matrix is the identity.  Any axis will
        // work, so choose the Unit(0) axis.
        a.axis[0] = (Real)1;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(AxisAngle<N,Real> const& a,
    Matrix<N,N,Real>& r)
{
    MakeIdentity(r);

    Real cs = cos(a.angle);
    Real sn = sin(a.angle);
    Real oneMinusCos = ((Real)1) - cs;
    Real x0sqr = a.axis[0]*a.axis[0];
    Real x1sqr = a.axis[1]*a.axis[1];
    Real x2sqr = a.axis[2]*a.axis[2];
    Real x0x1m = a.axis[0]*a.axis[1]*oneMinusCos;
    Real x0x2m = a.axis[0]*a.axis[2]*oneMinusCos;
    Real x1x2m = a.axis[1]*a.axis[2]*oneMinusCos;
    Real x0Sin = a.axis[0]*sn;
    Real x1Sin = a.axis[1]*sn;
    Real x2Sin = a.axis[2]*sn;
    
#if defined(GTE_USE_MAT_VEC)
    r(0,0) = x0sqr*oneMinusCos + cs;
    r(0,1) = x0x1m - x2Sin;
    r(0,2) = x0x2m + x1Sin;
    r(1,0) = x0x1m + x2Sin;
    r(1,1) = x1sqr*oneMinusCos + cs;
    r(1,2) = x1x2m - x0Sin;
    r(2,0) = x0x2m - x1Sin;
    r(2,1) = x1x2m + x0Sin;
    r(2,2) = x2sqr*oneMinusCos + cs;
#else
    r(0,0) = x0sqr*oneMinusCos + cs;
    r(1,0) = x0x1m - x2Sin;
    r(2,0) = x0x2m + x1Sin;
    r(0,1) = x0x1m + x2Sin;
    r(1,1) = x1sqr*oneMinusCos + cs;
    r(2,1) = x1x2m - x0Sin;
    r(0,2) = x0x2m - x1Sin;
    r(1,2) = x1x2m + x0Sin;
    r(2,2) = x2sqr*oneMinusCos + cs;
#endif
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(Matrix<N,N,Real> const& r,
    EulerAngles<Real>& e)
{
    if (0 <= e.axis[0] && e.axis[0] < 3
    &&  0 <= e.axis[1] && e.axis[1] < 3
    &&  0 <= e.axis[2] && e.axis[2] < 3
    &&  e.axis[1] != e.axis[0]
    &&  e.axis[1] != e.axis[2])
    {
        if (e.axis[0] != e.axis[2])
        {
#if defined(GTE_USE_MAT_VEC)
            // Map (0,1,2), (1,2,0), and (2,0,1) to +1.
            // Map (0,2,1), (2,1,0), and (1,0,2) to -1.
            int parity = (((e.axis[2] | (e.axis[1] << 2)) >> e.axis[0]) & 1);
            Real const sgn = (parity & 1 ? (Real)-1 : (Real)+1);

            if (r(e.axis[2],e.axis[0]) < (Real)1)
            {
                if (r(e.axis[2],e.axis[0]) > (Real)-1)
                {
                    e.angle[2] = atan2(sgn*r(e.axis[1],e.axis[0]),
                        r(e.axis[0],e.axis[0]));
                    e.angle[1] = asin(-sgn*r(e.axis[2],e.axis[0]));
                    e.angle[0] = atan2(sgn*r(e.axis[2],e.axis[1]),
                        r(e.axis[2],e.axis[2]));
                    e.result = ER_UNIQUE;
                }
                else
                {
                    e.angle[2] = (Real)0;
                    e.angle[1] = sgn*(Real)GTE_C_HALF_PI;
                    e.angle[0] = atan2(-sgn*r(e.axis[1],e.axis[2]),
                        r(e.axis[1],e.axis[1]));
                    e.result = ER_NOT_UNIQUE_DIF;
                }
            }
            else
            {
                e.angle[2] = (Real)0;
                e.angle[1] = -sgn*(Real)GTE_C_HALF_PI;
                e.angle[0] = atan2(-sgn*r(e.axis[1],e.axis[2]),
                    r(e.axis[1],e.axis[1]));
                e.result = ER_NOT_UNIQUE_SUM;
            }
#else
            // Map (0,1,2), (1,2,0), and (2,0,1) to +1.
            // Map (0,2,1), (2,1,0), and (1,0,2) to -1.
            int parity = (((e.axis[0] | (e.axis[1] << 2)) >> e.axis[2]) & 1);
            Real const sgn = (parity & 1 ? (Real)+1 : (Real)-1);

            if (r(e.axis[0],e.axis[2]) < (Real)1)
            {
                if (r(e.axis[0],e.axis[2]) > (Real)-1)
                {
                    e.angle[0] = atan2(sgn*r(e.axis[1],e.axis[2]),
                        r(e.axis[2],e.axis[2]));
                    e.angle[1] = asin(-sgn*r(e.axis[0],e.axis[2]));
                    e.angle[2] = atan2(sgn*r(e.axis[0],e.axis[1]),
                        r(e.axis[0],e.axis[0]));
                    e.result = ER_UNIQUE;
                }
                else
                {
                    e.angle[0] = (Real)0;
                    e.angle[1] = sgn*(Real)GTE_C_HALF_PI;
                    e.angle[2] = atan2(-sgn*r(e.axis[1],e.axis[0]),
                        r(e.axis[1],e.axis[1]));
                    e.result = ER_NOT_UNIQUE_DIF;
                }
            }
            else
            {
                e.angle[0] = (Real)0;
                e.angle[1] = -sgn*(Real)GTE_C_HALF_PI;
                e.angle[2] = atan2(-sgn*r(e.axis[1],e.axis[0]),
                    r(e.axis[1],e.axis[1]));
                e.result = ER_NOT_UNIQUE_SUM;
            }
#endif
        }
        else
        {
#if defined(GTE_USE_MAT_VEC)
            // Map (0,2,0), (1,0,1), and (2,1,2) to +1.
            // Map (0,1,0), (1,2,1), and (2,0,2) to -1.
            int b0 = 3 - e.axis[1] - e.axis[2];
            int parity = (((b0 | (e.axis[1] << 2)) >> e.axis[2]) & 1);
            Real const sgn = (parity & 1 ? (Real)+1 : (Real)-1);

            if (r(e.axis[2],e.axis[2]) < (Real)1)
            {
                if (r(e.axis[2],e.axis[2]) > (Real)-1)
                {
                    e.angle[2] = atan2(r(e.axis[1],e.axis[2]),
                        sgn*r(b0,e.axis[2]));
                    e.angle[1] = acos(r(e.axis[2],e.axis[2]));
                    e.angle[0] = atan2(r(e.axis[2],e.axis[1]),
                        -sgn*r(e.axis[2],b0));
                    e.result = ER_UNIQUE;
                }
                else
                {
                    e.angle[2] = (Real)0;
                    e.angle[1] = (Real)GTE_C_PI;
                    e.angle[0] = atan2(sgn*r(e.axis[1],b0),
                        r(e.axis[1],e.axis[1]));
                    e.result = ER_NOT_UNIQUE_DIF;
                }
            }
            else
            {
                e.angle[2] = (Real)0;
                e.angle[1] = (Real)0;
                e.angle[0] = atan2(sgn*r(e.axis[1],b0),
                    r(e.axis[1],e.axis[1]));
                e.result = ER_NOT_UNIQUE_SUM;
            }
#else
            // Map (0,2,0), (1,0,1), and (2,1,2) to -1.
            // Map (0,1,0), (1,2,1), and (2,0,2) to +1.
            int b2 = 3 - e.axis[0] - e.axis[1];
            int parity = (((b2 | (e.axis[1] << 2)) >> e.axis[0]) & 1);
            Real const sgn = (parity & 1 ? (Real)-1 : (Real)+1);

            if (r(e.axis[0],e.axis[0]) < (Real)1)
            {
                if (r(e.axis[0],e.axis[0]) > (Real)-1)
                {
                    e.angle[0] = atan2(r(e.axis[1],e.axis[0]),
                        sgn*r(b2,e.axis[0]));
                    e.angle[1] = acos(r(e.axis[0],e.axis[0]));
                    e.angle[2] = atan2(r(e.axis[0],e.axis[1]),
                        -sgn*r(e.axis[0],b2));
                    e.result = ER_UNIQUE;
                }
                else
                {
                    e.angle[0] = (Real)0;
                    e.angle[1] = (Real)GTE_C_PI;
                    e.angle[2] = atan2(sgn*r(e.axis[1],b2),
                        r(e.axis[1],e.axis[1]));
                    e.result = ER_NOT_UNIQUE_DIF;
                }
            }
            else
            {
                e.angle[0] = (Real)0;
                e.angle[1] = (Real)0;
                e.angle[2] = atan2(sgn*r(e.axis[1],b2),
                    r(e.axis[1],e.axis[1]));
                e.result = ER_NOT_UNIQUE_SUM;
            }
#endif
        }
    }
    else
    {
        // Invalid angles.
        e.angle[0] = (Real)0;
        e.angle[1] = (Real)0;
        e.angle[2] = (Real)0;
        e.result = ER_INVALID;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(EulerAngles<Real> const& e,
    Matrix<N,N,Real>& r)
{
    if (0 <= e.axis[0] && e.axis[0] < 3
    &&  0 <= e.axis[1] && e.axis[1] < 3
    &&  0 <= e.axis[2] && e.axis[2] < 3
    &&  e.axis[1] != e.axis[0]
    &&  e.axis[1] != e.axis[2])
    {
        Matrix<N,N,Real> r0, r1, r2;
        Convert(AxisAngle<N,Real>(Vector<N,Real>::Unit(e.axis[0]),
            e.angle[0]), r0);
        Convert(AxisAngle<N,Real>(Vector<N,Real>::Unit(e.axis[1]),
            e.angle[1]), r1);
        Convert(AxisAngle<N,Real>(Vector<N,Real>::Unit(e.axis[2]),
            e.angle[2]), r2);
#if defined(GTE_USE_MAT_VEC)
        r = r2*r1*r0;
#else
        r = r0*r1*r2;
#endif
    }
    else
    {
        // Invalid angles.
        MakeIdentity(r);
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(Quaternion<Real> const& q,
    AxisAngle<N,Real>& a)
{
    a.axis.MakeZero();

    Real axisSqrLen = q[0]*q[0] + q[1]*q[1] + q[2]*q[2];
    if (axisSqrLen > (Real)0)
    {
#if defined(GTE_USE_MAT_VEC)
        Real adjust = ((Real)1)/sqrt(axisSqrLen);
#else
        Real adjust = ((Real)-1)/sqrt(axisSqrLen);
#endif
        a.axis[0] = q[0]*adjust;
        a.axis[1] = q[1]*adjust;
        a.axis[2] = q[2]*adjust;
        Real cs = std::min(std::max(q[3], (Real)1), (Real)-1);
        a.angle = ((Real)2)*acos(cs);
    }
    else
    {
        // The angle is 0 (modulo 2*pi). Any axis will work, so choose the
        // Unit(0) axis.
        a.axis[0] = (Real)1;
        a.angle = (Real)0;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(AxisAngle<N,Real> const& a,
    Quaternion<Real>& q)
{
#if defined(GTE_USE_MAT_VEC)
    Real halfAngle = ((Real)0.5)*a.angle;
#else
    Real halfAngle = ((Real)-0.5)*a.angle;
#endif
    Real sn = sin(halfAngle);
    q[0] = sn*a.axis[0];
    q[1] = sn*a.axis[1];
    q[2] = sn*a.axis[2];
    q[3] = cos(halfAngle);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(Quaternion<Real> const& q,
    EulerAngles<Real>& e)
{
    Matrix<N,N,Real> r;
    Convert(q, r);
    Convert(r, e);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(EulerAngles<Real> const& e,
    Quaternion<Real>& q)
{
    Matrix<N,N,Real> r;
    Convert(e, r);
    Convert(r, q);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(AxisAngle<N,Real> const& a,
    EulerAngles<Real>& e)
{
    Quaternion<Real> q;
    Convert(a, q);
    Convert(q, e);
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void Rotation<N,Real>::Convert(EulerAngles<Real> const& e,
    AxisAngle<N,Real>& a)
{
    Quaternion<Real> q;
    Convert(e, q);
    Convert(q, a);
}
//----------------------------------------------------------------------------
