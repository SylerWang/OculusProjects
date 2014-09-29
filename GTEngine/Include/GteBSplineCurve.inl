// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.1 (2014/09/15)

//----------------------------------------------------------------------------
template <int N, typename Real>
BSplineCurve<N, Real>::~BSplineCurve()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
BSplineCurve<N, Real>::BSplineCurve(BasisFunctionInput<Real> const& input,
    Vector<N, Real> const* controls)
    :
    ParametricCurve<N, Real>((Real)0, (Real)1),
    mBasisFunction(input)
{
    if (!controls)
    {
        LogError("Invalid controls pointer.");
        return;
    }

    if (!mBasisFunction)
    {
        // Errors were already generated during construction of the
        // basis function.
        return;
    }

    // The mBasisFunction stores the domain but so does ParametricCurve.
    this->mTime.front() = mBasisFunction.GetMinDomain();
    this->mTime.back() = mBasisFunction.GetMaxDomain();

    // The replication of control points for periodic splines is avoided
    // by wrapping the i-loop index in Evaluate.
    mControls.resize(input.numControls);
    std::copy(controls, controls + input.numControls, mControls.begin());
    this->mConstructed = true;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
int BSplineCurve<N, Real>::GetNumControls() const
{
    return static_cast<int>(mControls.size());
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> const* BSplineCurve<N, Real>::GetControls() const
{
    return &mControls[0];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
BasisFunction<Real> const& BSplineCurve<N, Real>::GetBasisFunction() const
{
    return mBasisFunction;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void BSplineCurve<N, Real>::SetControl(int i, Vector<N, Real> const& control)
{
    if (0 <= i && i < GetNumControls())
    {
        mControls[i] = control;
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> const& BSplineCurve<N, Real>::GetControl(int i) const
{
    if (0 <= i && i < GetNumControls())
    {
        return mControls[i];
    }
    else
    {
        return mControls[0];
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void BSplineCurve<N, Real>::Evaluate(Real t, unsigned int maxOrder,
    Vector<N, Real> values[4]) const
{
    if (!this->mConstructed)
    {
        // Errors were already generated during construction.
        for (unsigned int order = 0; order < 4; ++order)
        {
            values[order].MakeZero();
        }
        return;
    }

    int imin, imax;
    mBasisFunction.Evaluate(t, maxOrder, imin, imax);

    // Compute position.
    values[0] = Compute(0, imin, imax);
    if (maxOrder >= 1)
    {
        // Compute first derivative.
        values[1] = Compute(1, imin, imax);
        if (maxOrder >= 2)
        {
            // Compute second derivative.
            values[2] = Compute(2, imin, imax);
            if (maxOrder == 3)
            {
                values[3] = Compute(3, imin, imax);
            }
            else
            {
                values[3].MakeZero();
            }
        }
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> BSplineCurve<N, Real>::Compute(unsigned int order, int imin,
    int imax) const
{
    // The j-index introduces a tiny amount of overhead in order to handle
    // both aperiodic and periodic splines.  For aperiodic splines, j = i
    // always.

    int numControls = GetNumControls();
    Vector<N, Real> result;
    result.MakeZero();
    for (int i = imin; i <= imax; ++i)
    {
        Real tmp = mBasisFunction.GetValue(order, i);
        int j = (i >= numControls ? i - numControls : i);
        result += tmp * mControls[j];
    }
    return result;
}
//----------------------------------------------------------------------------
