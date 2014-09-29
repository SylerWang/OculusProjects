// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline int VisibleSet::GetNumVisible () const
{
    return mNumVisible;
}
//----------------------------------------------------------------------------
inline Visual* VisibleSet::Get (int i) const
{
    if (0 <= i && i < mNumVisible)
    {
        return mVisible[i];
    }
    else
    {
        return 0;
    }
}
//----------------------------------------------------------------------------
inline void VisibleSet::Clear ()
{
    mNumVisible = 0;
}
//----------------------------------------------------------------------------
inline void VisibleSet::Resize (int numElements)
{
    mVisible.resize(numElements > 0 ? numElements : INITIALLY_VISIBLE);
}
//----------------------------------------------------------------------------
