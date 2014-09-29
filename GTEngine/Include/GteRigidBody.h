// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.4.0 (2014/09/14)

#pragma once

#include "GteMatrix3x3.h"
#include "GteRotation.h"
#include <functional>
#include <limits>

namespace gte
{

template <typename Real>
class RigidBody
{
public:
    // Construction and destruction.  The rigid body state is uninitialized.
    // Use the set functions to initialize the state before starting the
    // simulation.
    virtual ~RigidBody();
    RigidBody();

    // Set rigid body state.
    void SetMass(float mass);
    void SetBodyInertia(Matrix3x3<Real> const& inertia);
    inline void SetPosition(Vector3<Real> const& position);
    void SetQOrientation(Quaternion<Real> const& quatOrient);
    void SetLinearMomentum(Vector3<Real> const& linearMomentum);
    void SetAngularMomentum(Vector3<Real> const& angularMomentum);
    void SetROrientation(Matrix3x3<Real> const& rotOrient);
    void SetLinearVelocity(Vector3<Real> const& linearVelocity);
    void SetAngularVelocity(Vector3<Real> const& angularVelocity);

    // Get rigid body state.
    inline Real GetMass() const;
    inline Real GetInverseMass() const;
    inline Matrix3x3<Real> const& GetBodyInertia() const;
    inline Matrix3x3<Real> const& GetBodyInverseInertia() const;
    Matrix3x3<Real> GetWorldInertia() const;
    Matrix3x3<Real> GetWorldInverseInertia() const;
    inline Vector3<Real> const& GetPosition() const;
    Quaternion<Real> const& GetQOrientation() const;
    inline Vector3<Real> const& GetLinearMomentum() const;
    inline Vector3<Real> const& GetAngularMomentum() const;
    inline Matrix3x3<Real> const& GetROrientation() const;
    inline Vector3<Real> const& GetLinearVelocity() const;
    inline Vector3<Real> const& GetAngularVelocity() const;

    // Force/torque function format.
    typedef std::function
    <
        Vector3<Real>
        (
            Real,                       // time of application
            Real,                       // mass
            Vector3<Real> const&,       // position
            Quaternion<Real> const&,    // orientation
            Vector3<Real> const&,       // linear momentum
            Vector3<Real> const&,       // angular momentum
            Matrix3x3<Real> const&,     // orientation
            Vector3<Real> const&,       // linear velocity
            Vector3<Real> const&        // angular velocity
        )
    >
    Function;

    // Force and torque functions.
    Function mForce;
    Function mTorque;

    // Runge-Kutta fourth-order differential equation solver
    void Update(Real t, Real dt);

protected:
    // Constant quantities (matrices in body coordinates).
    Real mMass, mInvMass;
    Matrix3x3<Real> mInertia, mInvInertia;

    // State variables.
    Vector3<Real> mPosition;
    Quaternion<Real> mQuatOrient;
    Vector3<Real> mLinearMomentum;
    Vector3<Real> mAngularMomentum;

    // Derived state variables.
    Matrix3x3<Real> mRotOrient;
    Vector3<Real> mLinearVelocity;
    Vector3<Real> mAngularVelocity;
};

#include "GteRigidBody.inl"

}
