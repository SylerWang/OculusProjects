// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteRotation.h"
#include "GteMatrix4x4.h"
#include "GteVector3.h"
#include "GteLogger.h"
#include <cassert>

// Verify that the inputs to SetAxisAngle, SetRotation, and SetScale are
// valid.
//#define GTE_ASSERT_ON_INVALID_TRANSFORM_INPUT

namespace gte
{
// This class is a convenient wrapper for invertible affine matrices M formed
// by rotation, translation, and nonzero uniform scaling.  As block matrices,
// the format of M depends on your matrix-vector multiplication convention.
//   [GTE_USE_MAT_VEC]  M = {{R*s,u},{0,1}}
//   [GTE_USE_VEC_MAT]  M = {{s*R,0},{v,1}}
// where R is a 3x3 rotation matrix, s is a nonzero scalar, u is a 3x1
// translation, and v is a 1x3 translation.  The 0 blocks are 3x1 or 1x3 and
// the 1 block is 1x1.  The product of two Transform matrices is a Transform
// matrix; for example, when GTE_USE_MAT_VEC is active,
//   M0 = {{R0*s0,u0},{0,1}}, M1 = {{R1*s1,u1},{0,1}}
//   M0*M1 = {{(R0*R1)*(s0*s1),R0*s0*u1+u0},{0,1}}

template <typename Real>
class Transform : public Matrix4x4<Real>
{
public:
    // Construction and destruction.  The default constructor generates the
    // identity transformation.
    ~Transform();
    Transform();
    Transform(Transform const& transform);

    // Assignment.
    Transform& operator=(Transform const& transform);

    // Set the transformation to the identity.
    void SetIdentity();

    // The quaternion is unit length.
    void SetQuaternion (Quaternion<Real> const& q);
    Quaternion<Real> GetQuaternion() const;

    // The axis is unit length and the angle is in radians.
    void SetAxisAngle(AxisAngle<4,Real> const& axisAngle);
    AxisAngle<4,Real> GetAxisAngle() const;

    // The Euler angles are in radians.  The GetEulerAngles function
    // expects the eulerAngles.axis[] values to be set to the axis order
    // you want.
    void SetEulerAngles(EulerAngles<Real> const& eulerAngles);
    void GetEulerAngles(EulerAngles<Real>& eulerAngles) const;

    // The caller must ensure that the input to SetRotation is a rotation
    // matrix.
    void SetRotation(Matrix4x4<Real> const& rotation);
    Matrix4x4<Real> GetRotation() const;

    // The scale is a nonzero number.
    void SetScale(Real scale);
    Real GetScale() const;

    // No constraints exist for the translation components.  The third Set*
    // function uses only the first three components of 'translation'.  The
    // Get*W* functions store the translation in the first three components
    // of the output.  The fourth component is w=0 or w=1 depending on
    // which function you call.
    void SetTranslation(Real x0, Real x1, Real x2);
    void SetTranslation(Vector3<Real> const& translation);
    void SetTranslation(Vector4<Real> const& translation);
    Vector3<Real> GetTranslation() const;
    Vector4<Real> GetTranslationW0() const;
    Vector4<Real> GetTranslationW1() const;

    // Multiplication of transforms.  M0 is 'this', M1 is 'transform', the
    // function returns M0*M1.
    Transform<Real> operator*(Transform<Real> const& transform) const;

private:
    // Compute the base-class Matrix4x4<Real> from the channels.
    void UpdateMatrix();

    Quaternion<Real> mQuaternion;
    Real mTranslation[3], mScale;

#if defined(GTE_ASSERT_ON_INVALID_TRANSFORM_INPUT)
    static bool IsRotation(Matrix4x4<Real> const& rotate, Real epsilon);
    static bool IsUnitLength(Vector4<Real> const& axis, Real epsilon);
#endif
};

#include "GteTransform.inl"

}
