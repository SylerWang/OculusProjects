// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <int N, typename Real>
NURBSVolume<N, Real>::~NURBSVolume()
{
}
//----------------------------------------------------------------------------
template <int N, typename Real>
NURBSVolume<N, Real>::NURBSVolume(
    BasisFunctionInput<Real> const input[3],
    Vector<N, Real> const* controls, Real const* weights)
    :
    mConstructed(false)
{
    if (!controls || !weights)
    {
        LogError("Invalid controls or weights pointer.");
        return;
    }

    for (int i = 0; i < 3; ++i)
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

    // The replication of control points for periodic splines is avoided
    // by wrapping the i-loop index in Evaluate.
    int numControls = mNumControls[0] * mNumControls[1] * mNumControls[2];
    mControls.resize(numControls);
    mWeights.resize(numControls);
    std::copy(controls, controls + numControls, mControls.begin());
    std::copy(weights, weights + numControls, mWeights.begin());
    mConstructed = true;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
NURBSVolume<N, Real>::operator bool() const
{
    return mConstructed;
}
//----------------------------------------------------------------------------
template <int N, typename Real>
int NURBSVolume<N, Real>::GetNumControls(int dim) const
{
    return mNumControls[dim];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Vector<N, Real> const* NURBSVolume<N, Real>::GetControls() const
{
    return &mControls[0];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real const* NURBSVolume<N, Real>::GetWeights() const
{
    return &mWeights[0];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
BasisFunction<Real> const& NURBSVolume<N, Real>::GetBasisFunction(int dim)
    const
{
    return mBasisFunction[dim];
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real NURBSVolume<N, Real>::GetMinDomain(int dim) const
{
    return mBasisFunction[dim].GetMinDomain();
}
//----------------------------------------------------------------------------
template <int N, typename Real>
Real NURBSVolume<N, Real>::GetMaxDomain(int dim) const
{
    return mBasisFunction[dim].GetMaxDomain();
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void NURBSVolume<N, Real>::Evaluate(Real u, Real v, Real w,
    unsigned int maxOrder, Vector<N, Real> values[10]) const
{
    if (!mConstructed)
    {
        // Errors were already generated during construction.
        for (int i = 0; i < 10; ++i)
        {
            values[i].MakeZero();
        }
        return;
    }

    int iumin, iumax, ivmin, ivmax, iwmin, iwmax;
    mBasisFunction[0].Evaluate(u, maxOrder, iumin, iumax);
    mBasisFunction[1].Evaluate(v, maxOrder, ivmin, ivmax);
    mBasisFunction[2].Evaluate(w, maxOrder, iwmin, iwmax);

    // Compute position.
    Vector<N, Real> X;
    Real h;
    Compute(0, 0, 0, iumin, iumax, ivmin, ivmax, iwmin, iwmax, X, h);
    Real invH = ((Real)1) / h;
    values[0] = invH * X;

    if (maxOrder >= 1)
    {
        // Compute first-order derivatives.
        Vector<N, Real> XDerU;
        Real hDerU;
        Compute(1, 0, 0, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
            XDerU, hDerU);
        values[1] = invH * (XDerU - hDerU * values[0]);

        Vector<N, Real> XDerV;
        Real hDerV;
        Compute(0, 1, 0, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
            XDerV, hDerV);
        values[2] = invH * (XDerV - hDerV * values[0]);

        Vector<N, Real> XDerW;
        Real hDerW;
        Compute(0, 1, 0, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
            XDerW, hDerW);
        values[3] = invH * (XDerW - hDerW * values[0]);

        if (maxOrder >= 2)
        {
            // Compute second-order derivatives.
            Vector<N, Real> XDerUU;
            Real hDerUU;
            Compute(2, 0, 0, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
                XDerUU, hDerUU);
            values[4] = invH * (XDerUU - ((Real)2) * hDerU * values[1] -
                hDerUU * values[0]);

            Vector<N, Real> XDerVV;
            Real hDerVV;
            Compute(0, 2, 0, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
                XDerVV, hDerVV);
            values[5] = invH * (XDerVV - ((Real)2) * hDerV * values[2] -
                hDerVV * values[0]);

            Vector<N, Real> XDerWW;
            Real hDerWW;
            Compute(0, 0, 2, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
                XDerWW, hDerWW);
            values[6] = invH * (XDerWW - ((Real)2) * hDerW * values[3] -
                hDerWW * values[0]);

            Vector<N, Real> XDerUV;
            Real hDerUV;
            Compute(1, 1, 0, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
                XDerUV, hDerUV);
            values[7] = invH * (XDerUV - hDerU * values[2]
                - hDerV * values[1] - hDerUV * values[0]);

            Vector<N, Real> XDerUW;
            Real hDerUW;
            Compute(1, 0, 1, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
                XDerUW, hDerUW);
            values[8] = invH * (XDerUW - hDerU * values[3]
                - hDerW * values[1] - hDerUW * values[0]);

            Vector<N, Real> XDerVW;
            Real hDerVW;
            Compute(0, 1, 1, iumin, iumax, ivmin, ivmax, iwmin, iwmax,
                XDerVW, hDerVW);
            values[9] = invH * (XDerVW - hDerV * values[3]
                - hDerW * values[2] - hDerVW * values[0]);
        }
    }
}
//----------------------------------------------------------------------------
template <int N, typename Real>
void NURBSVolume<N, Real>::Compute(unsigned int uOrder, unsigned int vOrder,
    unsigned int wOrder, int iumin, int iumax, int ivmin, int ivmax,
    int iwmin, int iwmax, Vector<N, Real>& X, Real& h) const
{
    // The j*-indices introduce a tiny amount of overhead in order to handle
    // both aperiodic and periodic splines.  For aperiodic splines, j* = i*
    // always.

    int const numControls0 = mNumControls[0];
    int const numControls1 = mNumControls[1];
    int const numControls2 = mNumControls[2];
    X.MakeZero();
    h = (Real)0;
    for (int iw = iwmin; iw <= iwmax; ++iw)
    {
        Real tmpw = mBasisFunction[2].GetValue(wOrder, iw);
        int jw = (iw >= numControls2 ? iw - numControls2 : iw);
        for (int iv = ivmin; iv <= ivmax; ++iv)
        {
            Real tmpv = mBasisFunction[1].GetValue(vOrder, iv);
            Real tmpvw = tmpv * tmpw;
            int jv = (iv >= numControls1 ? iv - numControls1 : iv);
            for (int iu = iumin; iu <= iumax; ++iu)
            {
                Real tmpu = mBasisFunction[0].GetValue(uOrder, iu);
                int ju = (iu >= numControls0 ? iu - numControls0 : iu);
                int index = ju + numControls0*(jv + numControls1*jw);
                Real tmp = (tmpu * tmpvw) * mWeights[index];
                X += tmp * mControls[index];
                h += tmp;
            }
        }
    }
}
//----------------------------------------------------------------------------
