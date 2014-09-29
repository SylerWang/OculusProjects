// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/18)

//----------------------------------------------------------------------------
template <int N, typename Real>
BSplineSurface<N, Real>::~BSplineSurface()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
BSplineSurface<N, Real>::BSplineSurface(
    BasisFunctionInput<Real> const input[2],
    Vector<N, Real> const* controls)
    :
    ParametricSurface<N, Real>((Real)0, (Real)1, (Real)0, (Real)1, true)
{
    if (!controls)
    {
        LogError("Invalid controls pointer.");
        return;
    }

    for (int i = 0; i < 2; ++i)
    {
        mNumControls[i] = input[i].numControls;
        mBasisFunction[i].Create(input[i]);
        if (!mBasisFunction[i])
        {
            // Errors were already generated during construction of the
            // basis functions.
            return;
        }
    }

    // The mBasisFunction stores the domain but so does ParametricCurve.
    this->mUMin = mBasisFunction[0].GetMinDomain();
    this->mUMax = mBasisFunction[0].GetMaxDomain();
    this->mVMin = mBasisFunction[1].GetMinDomain();
    this->mVMax = mBasisFunction[1].GetMaxDomain();

    // The replication of control points for periodic splines is avoided
    // by wrapping the i-loop index in Evaluate.
    int numControls = mNumControls[0] * mNumControls[1];
    mControls.resize(numControls);
    std::copy(controls, controls + numControls, mControls.begin());
    this->mConstructed = true;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
int BSplineSurface<N, Real>::GetNumControls(int dim) const
{
    return mNumControls[dim];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> const* BSplineSurface<N, Real>::GetControls() const
{
    return &mControls[0];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
BasisFunction<Real> const& BSplineSurface<N, Real>::GetBasisFunction(int dim)
    const
{
    return mBasisFunction[dim];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void BSplineSurface<N, Real>::SetControl(int i0, int i1,
    Vector<N, Real> const& control)
{
    if (0 <= i0 && i0 < GetNumControls(0)
        && 0 <= i1 && i1 < GetNumControls(1))
    {
        mControls[i0 + mNumControls[0] * i1] = control;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> const& BSplineSurface<N, Real>::GetControl(int i0, int i1)
    const
{
    if (0 <= i0 && i0 < GetNumControls(0)
        && 0 <= i1 && i1 < GetNumControls(1))
    {
        return mControls[i0 + mNumControls[0] * i1];
    }
    else
    {
        return mControls[0];
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void BSplineSurface<N, Real>::Evaluate(Real u, Real v, unsigned int maxOrder,
    Vector<N, Real> values[6]) const
{
    if (!this->mConstructed)
    {
        // Errors were already generated during construction.
        for (int i = 0; i < 6; ++i)
        {
            values[i].MakeZero();
        }
        return;
    }

    int iumin, iumax, ivmin, ivmax;
    mBasisFunction[0].Evaluate(u, maxOrder, iumin, iumax);
    mBasisFunction[1].Evaluate(v, maxOrder, ivmin, ivmax);

    // Compute position.
    values[0] = Compute(0, 0, iumin, iumax, ivmin, ivmax);
    if (maxOrder >= 1)
    {
        // Compute first-order derivatives.
        values[1] = Compute(1, 0, iumin, iumax, ivmin, ivmax);
        values[2] = Compute(0, 1, iumin, iumax, ivmin, ivmax);
        if (maxOrder >= 2)
        {
            // Compute second-order derivatives.
            values[3] = Compute(2, 0, iumin, iumax, ivmin, ivmax);
            values[4] = Compute(1, 1, iumin, iumax, ivmin, ivmax);
            values[5] = Compute(0, 2, iumin, iumax, ivmin, ivmax);
        }
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> BSplineSurface<N, Real>::Compute(unsigned int uOrder,
    unsigned int vOrder, int iumin, int iumax, int ivmin, int ivmax) const
{
    // The j*-indices introduce a tiny amount of overhead in order to handle
    // both aperiodic and periodic splines.  For aperiodic splines, j* = i*
    // always.

    int const numControls0 = mNumControls[0];
    int const numControls1 = mNumControls[1];
    Vector<N, Real> result;
    result.MakeZero();
    for (int iv = ivmin; iv <= ivmax; ++iv)
    {
        Real tmpv = mBasisFunction[1].GetValue(vOrder, iv);
        int jv = (iv >= numControls1 ? iv - numControls1 : iv);
        for (int iu = iumin; iu <= iumax; ++iu)
        {
            Real tmpu = mBasisFunction[0].GetValue(uOrder, iu);
            int ju = (iu >= numControls0 ? iu - numControls0 : iu);
            result += (tmpu * tmpv) * mControls[ju + numControls0 * jv];
        }
    }
    return result;
}
//----------------------------------------------------------------------------
