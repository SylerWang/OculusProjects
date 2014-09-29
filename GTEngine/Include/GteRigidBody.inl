// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

//----------------------------------------------------------------------------
template <typename Real>
RigidBody<Real>::~RigidBody()
{
}
//----------------------------------------------------------------------------
template <typename Real>
RigidBody<Real>::RigidBody()
    :
    mMass(std::numeric_limits<Real>::max()),
    mInvMass((Real)0),
    mInertia(Matrix3x3<Real>::Identity()),
    mInvInertia(Matrix3x3<Real>::Zero()),
    mPosition(Vector3<Real>::Zero()),
    mQuatOrient(Quaternion<Real>::Identity()),
    mLinearMomentum(Vector3<Real>::Zero()),
    mAngularMomentum(Vector3<Real>::Zero()),
    mRotOrient(Matrix3x3<Real>::Identity()),
    mLinearVelocity(Vector3<Real>::Zero()),
    mAngularVelocity(Vector3<Real>::Zero())
{
    // The default body is immovable.
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetMass(float mass)
{
    if ((Real)0 < mass && mass < std::numeric_limits<Real>::max())
    {
        mMass = mass;
        mInvMass = ((Real)1) / mass;
    }
    else
    {
        // Assume the body as immovable.
        mMass = std::numeric_limits<Real>::max();
        mInvMass = (Real)0;
        mInertia = Matrix3x3<Real>::Identity();
        mInvInertia = Matrix3x3<Real>::Zero();
        mQuatOrient = Quaternion<Real>::Identity();
        mLinearMomentum = Vector3<Real>::Zero();
        mAngularMomentum = Vector3<Real>::Zero();
        mRotOrient = Matrix3x3<Real>::Identity();
        mLinearVelocity = Vector3<Real>::Zero();
        mAngularVelocity = Vector3<Real>::Zero();
    }
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetBodyInertia(Matrix3x3<Real> const& inertia)
{
    mInertia = inertia;
    mInvInertia = Inverse(mInertia);
}
//----------------------------------------------------------------------------
template <typename Real> inline
void RigidBody<Real>::SetPosition(Vector3<Real> const& position)
{
    mPosition = position;
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetQOrientation(Quaternion<Real> const& quatOrient)
{
    mQuatOrient = quatOrient;
    mRotOrient = Rotation<3, Real>(mQuatOrient);
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetLinearMomentum(Vector3<Real> const& linearMomentum)
{
    mLinearMomentum = linearMomentum;
    mLinearVelocity = mInvMass * mLinearMomentum;
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetAngularMomentum(Vector3<Real> const& angularMomentum)
{
    mAngularMomentum = angularMomentum;
    mAngularVelocity = mAngularMomentum * mRotOrient;   // V = R^T*M
    mAngularVelocity = mInvInertia * mAngularVelocity;  // V = J^{-1}*R^T*M
    mAngularVelocity = mRotOrient * mAngularVelocity;   // V = R*J^{-1}*R^T*M
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetROrientation(Matrix3x3<Real> const& rotOrient)
{
    mRotOrient = rotOrient;
    mQuatOrient = Rotation<3, Real>(mRotOrient);
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetLinearVelocity(Vector3<Real> const& linearVelocity)
{
    mLinearVelocity = linearVelocity;
    mLinearMomentum = mMass * mLinearVelocity;
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::SetAngularVelocity(Vector3<Real> const& angularVelocity)
{
    mAngularVelocity = angularVelocity;
    mAngularMomentum = mAngularVelocity * mRotOrient;   // M = R^T*V
    mAngularMomentum = mInertia * mAngularMomentum;     // M = J*R^T*V
    mAngularMomentum = mRotOrient * mAngularMomentum;   // M = R*J*R^T*V
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real RigidBody<Real>::GetMass() const
{
    return mMass;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real RigidBody<Real>::GetInverseMass() const
{
    return mInvMass;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Matrix3x3<Real> const& RigidBody<Real>::GetBodyInertia() const
{
    return mInertia;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Matrix3x3<Real> const& RigidBody<Real>::GetBodyInverseInertia() const
{
    return mInvInertia;
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real> RigidBody<Real>::GetWorldInertia() const
{
    return MultiplyABT(mRotOrient * mInertia, mRotOrient);  // R*J*R^T
}
//----------------------------------------------------------------------------
template <typename Real>
Matrix3x3<Real> RigidBody<Real>::GetWorldInverseInertia () const
{
    return MultiplyABT(mRotOrient * mInvInertia, mRotOrient);  // R*J^{-1}*R^T
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real> const& RigidBody<Real>::GetPosition() const
{
    return mPosition;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Quaternion<Real> const& RigidBody<Real>::GetQOrientation() const
{
    return mQuatOrient;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real> const& RigidBody<Real>::GetLinearMomentum() const
{
    return mLinearMomentum;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real> const& RigidBody<Real>::GetAngularMomentum() const
{
    return mAngularMomentum;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Matrix3x3<Real> const& RigidBody<Real>::GetROrientation() const
{
    return mRotOrient;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real> const& RigidBody<Real>::GetLinearVelocity() const
{
    return mLinearVelocity;
}
//----------------------------------------------------------------------------
template <typename Real> inline
Vector3<Real> const& RigidBody<Real>::GetAngularVelocity() const
{
    return mAngularVelocity;
}
//----------------------------------------------------------------------------
template <typename Real>
void RigidBody<Real>::Update(Real t, Real dt)
{
    // TODO: When GTE_USE_VEC_MAT is the convention, test to see whether
    // dq/dt = 0.5 * w * q (mat-vec convention) needs to become a different
    // equation.
    Real halfDT = ((Real)0.5)*dt;
    Real sixthDT = dt / ((Real)6);
    Real TpHalfDT = t + halfDT;
    Real TpDT = t + dt;

    Vector3<Real> newPosition, newLinearMomentum, newAngularMomentum,
        newLinearVelocity, newAngularVelocity;
    Quaternion<Real> newQuatOrient;
    Matrix3x3<Real> newRotOrient;

    // A1 = G(T,S0), B1 = S0 + (DT/2)*A1
    Vector3<Real> A1DXDT = mLinearVelocity;
    Quaternion<Real> W = Quaternion<Real>(mAngularVelocity[0],
        mAngularVelocity[1], mAngularVelocity[2], (Real)0);
    Quaternion<Real> A1DQDT = ((Real)0.5) * W * mQuatOrient;

    Vector3<Real> A1DPDT = mForce(t, mMass, mPosition, mQuatOrient,
        mLinearMomentum, mAngularMomentum, mRotOrient, mLinearVelocity,
        mAngularVelocity);

    Vector3<Real> A1DLDT = mTorque(t, mMass, mPosition, mQuatOrient,
        mLinearMomentum, mAngularMomentum, mRotOrient, mLinearVelocity,
        mAngularVelocity);

    newPosition = mPosition + halfDT * A1DXDT;
    newQuatOrient = mQuatOrient + halfDT * A1DQDT;
    newLinearMomentum = mLinearMomentum + halfDT * A1DPDT;
    newAngularMomentum = mAngularMomentum + halfDT * A1DLDT;
    newRotOrient = Rotation<3, Real>(newQuatOrient);
    newLinearVelocity = mInvMass * newLinearMomentum;
    newAngularVelocity = newAngularMomentum * newRotOrient;
    newAngularVelocity = mInvInertia * newAngularVelocity;
    newAngularVelocity = newRotOrient * newAngularVelocity;

    // A2 = G(T+DT/2,B1), B2 = S0 + (DT/2)*A2
    Vector3<Real> A2DXDT = newLinearVelocity;
    W = Quaternion<Real>(newAngularVelocity[0], newAngularVelocity[1],
        newAngularVelocity[2], (Real)0);
    Quaternion<Real> A2DQDT = ((Real)0.5) * W * newQuatOrient;

    Vector3<Real> A2DPDT = mForce(TpHalfDT, mMass, newPosition,
        newQuatOrient, newLinearMomentum, newAngularMomentum, newRotOrient,
        newLinearVelocity, newAngularVelocity);

    Vector3<Real> A2DLDT = mTorque(TpHalfDT, mMass, newPosition,
        newQuatOrient, newLinearMomentum, newAngularMomentum, newRotOrient,
        newLinearVelocity, newAngularVelocity);

    newPosition = mPosition + halfDT * A2DXDT;
    newQuatOrient = mQuatOrient + halfDT * A2DQDT;
    newLinearMomentum = mLinearMomentum + halfDT * A2DPDT;
    newAngularMomentum = mAngularMomentum + halfDT * A2DLDT;
    newRotOrient = Rotation<3, Real>(newQuatOrient);
    newLinearVelocity = mInvMass * newLinearMomentum;
    newAngularVelocity = newAngularMomentum * newRotOrient;
    newAngularVelocity = mInvInertia * newAngularVelocity;
    newAngularVelocity = newRotOrient * newAngularVelocity;

    // A3 = G(T+DT/2,B2), B3 = S0 + DT*A3
    Vector3<Real> A3DXDT = newLinearVelocity;
    W = Quaternion<Real>(newAngularVelocity[0], newAngularVelocity[1],
        newAngularVelocity[2], (Real)0);
    Quaternion<Real> A3DQDT = ((Real)0.5) * W * newQuatOrient;

    Vector3<Real> A3DPDT = mForce(TpHalfDT, mMass, newPosition,
        newQuatOrient, newLinearMomentum, newAngularMomentum, newRotOrient,
        newLinearVelocity, newAngularVelocity);

    Vector3<Real> A3DLDT = mTorque(TpHalfDT, mMass, newPosition,
        newQuatOrient, newLinearMomentum, newAngularMomentum, newRotOrient,
        newLinearVelocity, newAngularVelocity);

    newPosition = mPosition + dt * A3DXDT;
    newQuatOrient = mQuatOrient + dt * A3DQDT;
    newLinearMomentum = mLinearMomentum + dt * A3DPDT;
    newAngularMomentum = mAngularMomentum + dt * A3DLDT;
    newRotOrient = Rotation<3, Real>(newQuatOrient);
    newLinearVelocity = mInvMass * newLinearMomentum;
    newAngularVelocity = newAngularMomentum * newRotOrient;
    newAngularVelocity = mInvInertia * newAngularVelocity;
    newAngularVelocity = newRotOrient * newAngularVelocity;

    // A4 = G(T+DT,B3), S1 = S0 + (DT/6)*(A1+2*(A2+A3)+A4)
    Vector3<Real> A4DXDT = newLinearVelocity;
    W = Quaternion<Real>(newAngularVelocity[0], newAngularVelocity[1],
        newAngularVelocity[2], (Real)0);
    Quaternion<Real> A4DQDT = ((Real)0.5) * W * newQuatOrient;

    Vector3<Real> A4DPDT = mForce(TpDT, mMass, newPosition,
        newQuatOrient, newLinearMomentum, newAngularMomentum, newRotOrient,
        newLinearVelocity, newAngularVelocity);

    Vector3<Real> A4DLDT = mTorque(TpDT, mMass, newPosition, newQuatOrient,
        newLinearMomentum, newAngularMomentum, newRotOrient,
        newLinearVelocity, newAngularVelocity);

    mPosition += sixthDT * (A1DXDT + ((Real)2) * (A2DXDT + A3DXDT) + A4DXDT);
    mQuatOrient += sixthDT * (A1DQDT + ((Real)2)*(A2DQDT + A3DQDT) + A4DQDT);
    mLinearMomentum += sixthDT * (A1DPDT + ((Real)2)*(A2DPDT + A3DPDT) +
        A4DPDT);
    mAngularMomentum += sixthDT * (A1DLDT + ((Real)2)*(A2DLDT + A3DLDT) +
        A4DLDT);

    mRotOrient = Rotation<3, Real>(mQuatOrient);
    mLinearVelocity = mInvMass * mLinearMomentum;
    mAngularVelocity = mAngularMomentum * mRotOrient;
    mAngularVelocity = mInvInertia * mAngularVelocity;
    mAngularVelocity = mRotOrient * mAngularVelocity;
}
//----------------------------------------------------------------------------
