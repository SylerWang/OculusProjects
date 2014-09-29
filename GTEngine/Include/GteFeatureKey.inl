// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <int N, bool Ordered>
FeatureKey<N, Ordered>::FeatureKey()
{
}
//----------------------------------------------------------------------------
template <int N, bool Ordered>
bool FeatureKey<N, Ordered>::operator<(FeatureKey const& key) const
{
    for (int i = N-1; i >= 0; --i)
    {
        if (V[i] < key.V[i])
        {
            return true;
        }

        if (V[i] > key.V[i])
        {
            return false;
        }
    }

    return false;
}
//----------------------------------------------------------------------------
