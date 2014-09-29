// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
inline std::vector<MemberLayout> const& ConstantBuffer::GetLayout() const
{
    return mLayout;
}
//----------------------------------------------------------------------------
template <typename T>
bool ConstantBuffer::SetMember(std::string const& name, T const& value)
{
    auto iter = std::find_if(mLayout.begin(), mLayout.end(),
        [&name](MemberLayout const& item){ return name == item.name; });

    if (iter == mLayout.end())
    {
        LogError("Failed to find member name " + name + ".");
        return false;
    }

    if (iter->numElements > 0)
    {
        LogError("Member is an array, use SetMember(name,index,value).");
        return false;
    }

    if (iter->offset + sizeof(T) > mNumBytes)
    {
        LogError("Writing will access memory outside the buffer.");
        return false;
    }

    T* target = reinterpret_cast<T*>(mData + iter->offset);
    *target = value;
    return true;
}
//----------------------------------------------------------------------------
template <typename T>
bool ConstantBuffer::GetMember(std::string const& name, T& value) const
{
    auto iter = std::find_if(mLayout.begin(), mLayout.end(),
        [&name](MemberLayout const& item){ return name == item.name; });

    if (iter == mLayout.end())
    {
        LogError("Failed to find member name " + name + ".");
        return false;
    }

    if (iter->numElements > 0)
    {
        LogError("Member is an array, use GetMember(name,index,value).");
        return false;
    }

    if (iter->offset + sizeof(T) > mNumBytes)
    {
        LogError("Reading will access memory outside the buffer.");
        return false;
    }

    T* target = reinterpret_cast<T*>(mData + iter->offset);
    value = *target;
    return true;
}
//----------------------------------------------------------------------------
template <typename T>
bool ConstantBuffer::SetMember(std::string const& name, unsigned int index,
    T const& value)
{
    auto iter = std::find_if(mLayout.begin(), mLayout.end(),
        [&name](MemberLayout const& item){ return name == item.name; });

    if (iter == mLayout.end())
    {
        LogError("Failed to find member name " + name + ".");
        return false;
    }

    if (iter->numElements == 0)
    {
        LogError("Member is a singleton, use SetMember(name,value).");
        return false;
    }

    if (index >= iter->numElements)
    {
        LogError("Index is out of range for the member array.");
        return false;
    }

    if (iter->offset + (index + 1)*sizeof(T) > mNumBytes)
    {
        LogError("Writing will access memory outside the buffer.");
        return false;
    }

    T* target = reinterpret_cast<T*>(mData + iter->offset + index*sizeof(T));
    *target = value;
    return true;
}
//----------------------------------------------------------------------------
template <typename T>
bool ConstantBuffer::GetMember(std::string const& name, unsigned int index,
    T& value) const
{
    auto iter = std::find_if(mLayout.begin(), mLayout.end(),
        [&name](MemberLayout const& item){ return name == item.name; });

    if (iter == mLayout.end())
    {
        LogError("Failed to find member name " + name + ".");
        return false;
    }

    if (iter->numElements == 0)
    {
        LogError("Member is a singleton, use GetMember(name,value).");
        return false;
    }

    if (index >= iter->numElements)
    {
        LogError("Index is out of range for the member array.");
        return false;
    }

    if (iter->offset + (index + 1)*sizeof(T) > mNumBytes)
    {
        LogError("Reading will access memory outside the buffer.");
        return false;
    }

    T* target = reinterpret_cast<T*>(mData + iter->offset + index*sizeof(T));
    value = *target;
    return true;
}
//----------------------------------------------------------------------------
