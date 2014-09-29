// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
EulerAngles<Real>::EulerAngles()
    :
    result(ER_INVALID)
{
    for (int i = 0; i < 3; ++i)
    {
        axis[i] = 0;
        angle[i] = (Real)0;
    }
}
//----------------------------------------------------------------------------
template <typename Real>
EulerAngles<Real>::EulerAngles(int i0, int i1, int i2, Real a0, Real a1,
    Real a2)
    :
    result(ER_UNIQUE)
{
    axis[0] = i0;
    axis[1] = i1;
    axis[2] = i2;
    angle[0] = a0;
    angle[1] = a1;
    angle[2] = a2;
}
//----------------------------------------------------------------------------
