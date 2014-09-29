// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>::~GVector()
{
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>::GVector(int size)
{
    SetSize(size);
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>::GVector(GVector const& vec)
{
    *this = vec;
}
//----------------------------------------------------------------------------
template <typename Real>
void GVector<Real>::MakeZero()
{
    std::fill(mTuple.begin(), mTuple.end(), (Real)0);
}
//----------------------------------------------------------------------------
template <typename Real>
void GVector<Real>::MakeUnit(int d)
{
    std::fill(mTuple.begin(), mTuple.end(), (Real)0);
    mTuple[d] = (Real)1;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>& GVector<Real>::operator=(GVector const& vec)
{
    mTuple = vec.mTuple;
    return *this;
}
//----------------------------------------------------------------------------
template <typename Real>
void GVector<Real>::SetSize(int size)
{
#ifdef GTE_ASSERT_ON_GVECTOR_SIZE_MISMATCH
    LogAssert(size >= 0, "Mismatched size.");
#endif
    if (size > 0)
    {
        mTuple.resize(size);
    }
}
//----------------------------------------------------------------------------
template <typename Real> inline
int GVector<Real>::GetSize() const
{
    return static_cast<int>(mTuple.size());
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real const& GVector<Real>::operator[](int i) const
{
    return mTuple[i];
}
//----------------------------------------------------------------------------
template <typename Real> inline
Real& GVector<Real>::operator[](int i)
{
    return mTuple[i];
}
//----------------------------------------------------------------------------
template <typename Real>
bool GVector<Real>::operator==(GVector const& vec) const
{
    ValidateSize(vec);
    return std::equal(mTuple.begin(), mTuple.end(), vec.mTuple.begin());
}
//----------------------------------------------------------------------------
template <typename Real>
bool GVector<Real>::operator!=(GVector const& vec) const
{
    return !operator==(vec);
}
//----------------------------------------------------------------------------
template <typename Real>
bool GVector<Real>::operator<(const GVector& vec) const
{
    ValidateSize(vec);
    for (int i = 0; i < GetSize(); ++i)
    {
        if (mTuple[i] < vec.mTuple[i])
        {
            return true;
        }

        if (mTuple[i] > vec.mTuple[i])
        {
            return false;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GVector<Real>::operator<=(const GVector& vec) const
{
    ValidateSize(vec);
    for (int i = 0; i < GetSize(); ++i)
    {
        if (mTuple[i] < vec.mTuple[i])
        {
            return true;
        }

        if (mTuple[i] > vec.mTuple[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GVector<Real>::operator>(const GVector& vec) const
{
    ValidateSize(vec);
    for (int i = 0; i < GetSize(); ++i)
    {
        if (mTuple[i] > vec.mTuple[i])
        {
            return true;
        }

        if (mTuple[i] < vec.mTuple[i])
        {
            return false;
        }
    }
    return false;
}
//----------------------------------------------------------------------------
template <typename Real>
bool GVector<Real>::operator>=(const GVector& vec) const
{
    ValidateSize(vec);
    for (int i = 0; i < GetSize(); ++i)
    {
        if (mTuple[i] > vec.mTuple[i])
        {
            return true;
        }

        if (mTuple[i] < vec.mTuple[i])
        {
            return false;
        }
    }
    return true;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> GVector<Real>::Zero(int size)
{
    GVector<Real> v(size);
    v.MakeZero();
    return v;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> GVector<Real>::Unit(int size, int d)
{
    GVector<Real> v(size);
    v.MakeUnit(d);
    return v;
}
//----------------------------------------------------------------------------
template <typename Real> inline
void GVector<Real>::ValidateSize(GVector const& vec) const
{
#ifdef GTE_ASSERT_ON_GVECTOR_SIZE_MISMATCH
    LogAssert(GetSize() == vec.GetSize(), "Mismatched size.");
#endif
    (void)vec;
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator+(GVector<Real> const& v)
{
    return v;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator-(GVector<Real> const& v)
{
    GVector<Real> result(v.GetSize());
    for (int i = 0; i < v.GetSize(); ++i)
    {
        result[i] = -v[i];
    }
    return result;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator+(GVector<Real> const& v0, GVector<Real> const& v1)
{
    GVector<Real> result = v0;
    return result += v1;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator-(GVector<Real> const& v0, GVector<Real> const& v1)
{
    GVector<Real> result = v0;
    return result -= v1;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator*(GVector<Real> const& v, Real scalar)
{
    GVector<Real> result = v;
    return result *= scalar;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator*(Real scalar, GVector<Real> const& v)
{
    GVector<Real> result = v;
    return result *= scalar;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real> operator/(GVector<Real> const& v, Real scalar)
{
    GVector<Real> result = v;
    return result /= scalar;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>& operator+=(GVector<Real>& v0, GVector<Real> const& v1)
{
    v0.ValidateSize(v1);
    for (int i = 0; i < v0.GetSize(); ++i)
    {
        v0[i] += v1[i];
    }
    return v0;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>& operator-=(GVector<Real>& v0, GVector<Real> const& v1)
{
    v0.ValidateSize(v1);
    for (int i = 0; i < v0.GetSize(); ++i)
    {
        v0[i] -= v1[i];
    }
    return v0;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>& operator*=(GVector<Real>& v, Real scalar)
{
    for (int i = 0; i < v.GetSize(); ++i)
    {
        v[i] *= scalar;
    }
    return v;
}
//----------------------------------------------------------------------------
template <typename Real>
GVector<Real>& operator/=(GVector<Real>& v, Real scalar)
{
    if (scalar != (Real)0)
    {
        Real invScalar = ((Real)1) / scalar;
        for (int i = 0; i < v.GetSize(); ++i)
        {
            v[i] *= invScalar;
        }
    }
    else
    {
        for (int i = 0; i < v.GetSize(); ++i)
        {
            v[i] = (Real)0;
        }
    }
    return v;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Dot(GVector<Real> const& v0, GVector<Real> const& v1)
{
    v0.ValidateSize(v1);
    Real dot = v0[0] * v1[0];
    for (int i = 1; i < v0.GetSize(); ++i)
    {
        dot += v0[i] * v1[i];
    }
    return dot;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Length(GVector<Real> const& v)
{
    return sqrt(Dot(v, v));
}
//----------------------------------------------------------------------------
template <typename Real>
Real LengthRobust(GVector<Real> const& v)
{
    Real maxAbsComp = std::abs(v[0]);
    for (int i = 1; i < v.GetSize(); ++i)
    {
        Real absComp = std::abs(v[i]);
        if (absComp > maxAbsComp)
        {
            maxAbsComp = absComp;
        }
    }

    Real length;
    if (maxAbsComp > (Real)0)
    {
        GVector<Real> scaled = v / maxAbsComp;
        length = maxAbsComp*Length(scaled);
    }
    else
    {
        length = (Real)0;
    }
    return length;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Normalize(GVector<Real>& v)
{
    Real length = Length(v);
    v /= length;
    return length;
}
//----------------------------------------------------------------------------
template <typename Real>
Real NormalizeRobust(GVector<Real>& v)
{
    Real maxAbsComp = std::abs(v[0]);
    for (int i = 1; i < v.GetSize(); ++i)
    {
        Real absComp = std::abs(v[i]);
        if (absComp > maxAbsComp)
        {
            maxAbsComp = absComp;
        }
    }

    Real length;
    if (maxAbsComp > (Real)0)
    {
        v /= maxAbsComp;
        length = Length(v);
        v /= length;
        length *= maxAbsComp;
    }
    else
    {
        length = (Real)0;
        for (int i = 0; i < v.GetSize(); ++i)
        {
            v[i] = (Real)0;
        }
    }
    return length;
}
//----------------------------------------------------------------------------
template <typename Real>
Real Orthonormalize(int numInputs, GVector<Real>* v)
{
    if (v && 1 <= numInputs && numInputs <= v[0].GetSize())
    {
#ifdef GTE_ASSERT_ON_GVECTOR_SIZE_MISMATCH
        for (int i = 1; i < numInputs; ++i)
        {
            v[0].ValidateSize(v[i]);
        }
#endif
        Real minLength = Normalize(v[0]);
        for (int i = 1; i < numInputs; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                Real dot = Dot(v[i], v[j]);
                v[i] -= v[j] * dot;
            }
            Real length = Normalize(v[i]);
            if (length < minLength)
            {
                minLength = length;
            }
        }
        return minLength;
    }

    LogError("Invalid input.");
    return (Real)0;
}
//----------------------------------------------------------------------------
template <typename Real>
bool ComputeExtremes(int numVectors, GVector<Real> const* v,
    GVector<Real>& vmin, GVector<Real>& vmax)
{
    if (v && numVectors > 0)
    {
#ifdef GTE_ASSERT_ON_GVECTOR_SIZE_MISMATCH
        for (int i = 1; i < numVectors; ++i)
        {
            v[0].ValidateSize(v[i]);
        }
#endif
        int const size = v[0].GetSize();
        vmin = v[0];
        vmax = vmin;
        for (int j = 1; j < numVectors; ++j)
        {
            GVector<Real> const& vec = v[j];
            for (int i = 0; i < size; ++i)
            {
                if (vec[i] < vmin[i])
                {
                    vmin[i] = vec[i];
                }
                else if (vec[i] > vmax[i])
                {
                    vmax[i] = vec[i];
                }
            }
        }
        return true;
    }

    LogError("Invalid input.");
    return false;
}
//----------------------------------------------------------------------------
