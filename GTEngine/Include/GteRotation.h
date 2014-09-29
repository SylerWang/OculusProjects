// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteConstants.h"
#include "GteAxisAngle.h"
#include "GteEulerAngles.h"
#include "GteMatrix.h"
#include "GteQuaternion.h"

namespace gte
{

// Conversions among various representations of rotations.  The value of
// N must be 3 or 4.  The latter case supports affine algebra when you use
// 4-tuple vectors (w-component is 1 for points and 0 for vector) and 4x4
// matrices for affine transformations.  Rotation axes must be unit length.
// The angles are in radians.  The Euler angles are in world coordinates;
// we have not yet added support for body coordinates.

template <int N, typename Real>
class Rotation
{
public:
    // Create rotations from various representations.
    Rotation(Matrix<N,N,Real> const& matrix);
    Rotation(Quaternion<Real> const& quaternion);
    Rotation(AxisAngle<N,Real> const& axisAngle);
    Rotation(EulerAngles<Real> const& eulerAngles);

    // Convert one representation to another.
    operator Matrix<N,N,Real>() const;
    operator Quaternion<Real>() const;
    operator AxisAngle<N,Real>() const;
    operator EulerAngles<Real>() const;

private:
    enum RepresentationType
    {
        IS_MATRIX,
        IS_QUATERNION,
        IS_AXIS_ANGLE,
        IS_EULER_ANGLES
    };

    RepresentationType mType;
    mutable Matrix<N,N,Real> mMatrix;
    mutable Quaternion<Real> mQuaternion;
    mutable AxisAngle<N,Real> mAxisAngle;
    mutable EulerAngles<Real> mEulerAngles;

    // Convert a rotation matrix to a quaternion.
    //
    // x^2 = (+r00 - r11 - r22 + 1)/4
    // y^2 = (-r00 + r11 - r22 + 1)/4
    // z^2 = (-r00 - r11 + r22 + 1)/4
    // w^2 = (+r00 + r11 + r22 + 1)/4
    // x^2 + y^2 = (1 - r22)/2
    // z^2 + w^2 = (1 + r22)/2
    // y^2 - x^2 = (r11 - r00)/2
    // w^2 - z^2 = (r11 + r00)/2
    // x*y = (r01 + r10)/4
    // x*z = (r02 + r20)/4
    // y*z = (r12 + r21)/4
    // [GTE_USE_MAT_VEC]
    //   x*w = (r21 - r12)/4
    //   y*w = (r02 - r20)/4
    //   z*w = (r10 - r01)/4
    // [GTE_USE_VEC_MAT]
    //   x*w = (r12 - r21)/4
    //   y*w = (r20 - r02)/4
    //   z*w = (r01 - r10)/4
    //
    // If Q is the 4x1 column vector (x,y,z,w), the previous equations give us
    //         +-                  -+
    //         | x*x  x*y  x*z  x*w |
    // Q*Q^T = | y*x  y*y  y*z  y*w |
    //         | z*x  z*y  z*z  z*w |
    //         | w*x  w*y  w*z  w*w |
    //         +-                  -+
    // The code extracts the row of maximum length, normalizing it to obtain
    // the result q.
    static void Convert(Matrix<N,N,Real> const& r, Quaternion<Real>& q);

    // Convert a quaterion q = x*i + y*j + z*k + w to a rotation matrix.
    // [GTE_USE_MAT_VEC]
    //     +-           -+   +-                                     -+
    // R = | r00 r01 r02 | = | 1-2y^2-2z^2  2(xy-zw)     2(xz+yw)    |
    //     | r10 r11 r12 |   | 2(xy+zw)     1-2x^2-2z^2  2(yz-xw)    |
    //     | r20 r21 r22 |   | 2(xz-yw)     2(yz+xw)     1-2x^2-2y^2 |
    //     +-           -+   +-                                     -+
    // [GTE_USE_VEC_MAT]
    //     +-           -+   +-                                     -+
    // R = | r00 r01 r02 | = | 1-2y^2-2z^2  2(xy+zw)     2(xz-yw)    |
    //     | r10 r11 r12 |   | 2(xy-zw)     1-2x^2-2z^2  2(yz+xw)    |
    //     | r20 r21 r22 |   | 2(xz+yw)     2(yz-xw)     1-2x^2-2y^2 |
    //     +-           -+   +-                                     -+
    static void Convert(Quaternion<Real> const& q, Matrix<N,N,Real>& r);

    // Convert a rotation matrix to an axis-angle pair.  Let (x0,x1,x2) be the
    // axis let t be an angle of rotation.  The rotation matrix is
    // [GTE_USE_MAT_VEC]
    //   R = I + sin(t)*S + (1-cos(t))*S^2
    // or
    // [GTE_USE_VEC_MAT]
    //   R = I - sin(t)*S + (1-cos(t))*S^2
    // where I is the identity and S = {{0,-x2,x1},{x2,0,-x0},{-x1,x0,0}}
    // where the inner-brace triples are the rows of the matrix.  If t > 0,
    // R represents a counterclockwise rotation; see the comments for the
    // constructor Matrix3x3(axis,angle).  It may be shown that cos(t) =
    // (trace(R)-1)/2 and R - Transpose(R) = 2*sin(t)*S.  As long as sin(t) is
    // not zero, we may solve for S in the second equation, which produces the
    // axis direction U = (S21,S02,S10).  When t = 0, the rotation is the
    // identity, in which case any axis direction is valid; we choose (1,0,0).
    // When t = pi, it must be that R - Transpose(R) = 0, which prevents us
    // from extracting the axis.  Instead, note that (R+I)/2 = I+S^2 = U*U^T,
    // where U is a unit-length axis direction.
    static void Convert(Matrix<N,N,Real> const& r, AxisAngle<N,Real>& a);

    // Convert an axis-angle pair to a rotation matrix.  Assuming (x0,x1,x2)
    // is for a right-handed world (x0 to right, x1 up, x2 out of plane of
    // page), a positive angle corresponds to a counterclockwise rotation from
    // the perspective of an observer looking at the origin of the plane of
    // rotation and having view direction the negative of the axis direction.
    // The coordinate-axis rotations are the following, where
    // unit(0) = (1,0,0), unit(1) = (0,1,0), unit(2) = (0,0,1),
    // [GTE_USE_MAT_VEC]
    //   R(unit(0),t) = {{ 1, 0, 0}, { 0, c,-s}, { 0, s, c}}
    //   R(unit(1),t) = {{ c, 0, s}, { 0, 1, 0}, {-s, 0, c}}
    //   R(unit(2),t) = {{ c,-s, 0}, { s, c, 0}, { 0, 0, 1}}
    // or
    // [GTE_USE_VEC_MAT]
    //   R(unit(0),t) = {{ 1, 0, 0}, { 0, c, s}, { 0,-s, c}}
    //   R(unit(1),t) = {{ c, 0,-s}, { 0, 1, 0}, { s, 0, c}}
    //   R(unit(2),t) = {{ c, s, 0}, {-s, c, 0}, { 0, 0, 1}}
    // where c = cos(t), s = sin(t), and the inner-brace triples are rows of
    // the matrix.  The general matrix is
    // [GTE_USE_MAT_VEC]
    //       +-                                                          -+
    //   R = | (1-c)*x0^2  + c     (1-c)*x0*x1 - s*x2  (1-c)*x0*x2 + s*x1 |
    //       | (1-c)*x0*x1 + s*x2  (1-c)*x1^2  + c     (1-c)*x1*x2 - s*x0 |
    //       | (1-c)*x0*x2 - s*x1  (1-c)*x1*x2 + s*x0  (1-c)*x2^2  + c    |
    //       +-                                                          -+
    // [GTE_USE_VEC_MAT]
    //       +-                                                          -+
    //   R = | (1-c)*x0^2  + c     (1-c)*x0*x1 + s*x2  (1-c)*x0*x2 - s*x1 |
    //       | (1-c)*x0*x1 - s*x2  (1-c)*x1^2  + c     (1-c)*x1*x2 + s*x0 |
    //       | (1-c)*x0*x2 + s*x1  (1-c)*x1*x2 - s*x0  (1-c)*x2^2  + c    |
    //       +-                                                          -+
    static void Convert(AxisAngle<N,Real> const& a, Matrix<N,N,Real>& r);

    // Convert a rotation matrix to Euler angles.  Factorization into Euler
    // angles is not necessarily unique.  If the result is ER_NOT_UNIQUE_SUM,
    // then the multiple solutions occur because angleN2+angleN0 is constant.
    // If the result is ER_NOT_UNIQUE_DIF, then the multiple solutions occur
    // because angleN2-angleN0 is constant.  In either type of nonuniqueness,
    // the function returns angleN0=0.
    static void Convert(Matrix<N,N,Real> const& r, EulerAngles<Real>& e);

    // Convert Euler angles to a rotation matrix.  The three integer inputs
    // are in {0,1,2} and correspond to world directions unit(0) = (1,0,0),
    // unit(1) = (0,1,0), or unit(2) = (0,0,1).  The triples (N0,N1,N2) must
    // be in the following set,
    //   {(0,1,2),(0,2,1),(1,0,2),(1,2,0),(2,0,1),(2,1,0),
    //    (0,1,0),(0,2,0),(1,0,1),(1,2,1),(2,0,2),(2,1,2)}
    // The rotation matrix is
    //   [GTE_USE_MAT_VEC]
    //     R(unit(N2),angleN2)*R(unit(N1),angleN1)*R(unit(N0),angleN0)
    // or
    //   [GTE_USE_VEC_MAT]
    //     R(unit(N0),angleN0)*R(unit(N1),angleN1)*R(unit(N2),angleN2)
    // The conventions of constructor Matrix3(axis,angle) apply here as well.
    //
    // NOTE:  The reversal of order is chosen so that a rotation matrix built
    // with one multiplication convention is the transpose of the rotation
    // matrix built with the other multiplication convention.  Thus,
    //   [GTE_USE_MAT_VEC]
    //     Matrix3x3<Real> R_mvconvention(N0,N1,N2,angleN0,angleN1,angleN2);
    //     Vector3<Real> V(...);
    //     Vector3<Real> U = R_mvconvention*V;  // (u0,u1,u2) = R2*R1*R0*V
    //   [GTE_USE_VEC_MAT]
    //     Matrix3x3<Real> R_vmconvention(N0,N1,N2,angleN0,angleN1,angleN2);
    //     Vector3<Real> V(...);
    //     Vector3<Real> U = R_mvconvention*V;  // (u0,u1,u2) = V*R0*R1*R2
    // In either convention, you get the same 3-tuple U.
    static void Convert(EulerAngles<Real> const& e, Matrix<N,N,Real>& r);

    // Convert a quaternion to an axis-angle pair, where
    //   q = sin(angle/2)*(axis[0]*i + axis[1]*j + axis[2]*k) + cos(angle/2)
    static void Convert(Quaternion<Real> const& q, AxisAngle<N,Real>& a);

    // Convert an axis-angle pair to a quaternion, where
    //   q = sin(angle/2)*(axis[0]*i + axis[1]*j + axis[2]*k) + cos(angle/2)
    static void Convert(AxisAngle<N,Real> const& a, Quaternion<Real>& q);

    // Convert a quaternion to Euler angles.  The quaternion is converted to
    // a matrix which is then converted to Euler angles.
    static void Convert(Quaternion<Real> const& q, EulerAngles<Real>& e);

    // Convert Euler angles to a quaternion.  The Euler angles are converted
    // to a matrix which is then converted to a quaternion.
    static void Convert(EulerAngles<Real> const& e, Quaternion<Real>& q);

    // Convert an axis-angle pair to Euler angles.  The axis-angle pair is
    // converted to a quaternion which is then converted to Euler angles.
    static void Convert(AxisAngle<N,Real> const& a, EulerAngles<Real>& e);

    // Convert Euler angles to an axis-angle pair.  The Euler angles are
    // converted to a quaternion which is then converted to an axis-angle
    // pair.
    static void Convert(EulerAngles<Real> const& e, AxisAngle<N,Real>& a);
};

#include "GteRotation.inl"

}
