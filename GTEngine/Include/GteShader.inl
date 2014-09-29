// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename T>
int Shader::Set(std::string const& name, std::shared_ptr<T> const& object)
{
    int handle = 0;
    for (auto& data : mData[T::shaderDataLookup])
    {
        if (name == data.name)
        {
            if (IsValid(data, object.get()))
            {
                data.object = object;
                return handle;
            }
            return -1;
        }
        ++handle;
    }

    LogError("Cannot find object " + name + ".");
    return -1;
}
//----------------------------------------------------------------------------
template <typename T>
std::shared_ptr<T> const Shader::Get(std::string const& name) const
{
    for (auto const& data : mData[T::shaderDataLookup])
    {
        if (name == data.name)
        {
            return std::static_pointer_cast<T>(data.object);
        }
    }

    LogError("Cannot find object " + name + ".");
    return nullptr;
}
//----------------------------------------------------------------------------
template <typename T>
void Shader::Set(int handle, std::shared_ptr<T> const& object)
{
    std::vector<Data>& data = mData[T::shaderDataLookup];
    if (0 <= handle && handle < static_cast<int>(data.size()))
    {
        auto& d = data[handle];
        if (IsValid(d, object.get()))
        {
            d.object = object;
        }
        return;
    }

    LogError("Invalid handle for object.");
}
//----------------------------------------------------------------------------
template <typename T>
std::shared_ptr<T> const Shader::Get(int handle) const
{
    std::vector<Data> const& data = mData[T::shaderDataLookup];
    if (0 <= handle && handle < static_cast<int>(data.size()))
    {
        return data[handle].object;
    }

    LogError("Cannot find object.");
    return nullptr;
}
//----------------------------------------------------------------------------
template <>
int Shader::Set(std::string const& name,
    std::shared_ptr<ConstantBuffer> const& object)
{
    int handle = 0;
    for (auto& data : mData[ConstantBuffer::shaderDataLookup])
    {
        if (name == data.name)
        {
            if (IsValid(data, object.get()))
            {
                data.object = object;
                object->mLayout = mCBufferLayouts[handle];
                return handle;
            }
            return -1;
        }
        ++handle;
    }

    LogError("Cannot find object " + name + ".");
    return -1;
}
//----------------------------------------------------------------------------
template <>
int Shader::Set(std::string const& name,
    std::shared_ptr<TextureBuffer> const& object)
{
    int handle = 0;
    for (auto& data : mData[TextureBuffer::shaderDataLookup])
    {
        if (name == data.name)
        {
            if (IsValid(data, object.get()))
            {
                data.object = object;
                object->mLayout = mTBufferLayouts[handle];
                return handle;
            }
            return -1;
        }
        ++handle;
    }

    LogError("Cannot find object " + name + ".");
    return -1;
}
//----------------------------------------------------------------------------
template<>
void Shader::Set(int handle, std::shared_ptr<ConstantBuffer> const& object)
{
    std::vector<Data>& data = mData[ConstantBuffer::shaderDataLookup];
    if (0 <= handle && handle < static_cast<int>(data.size()))
    {
        auto& d = data[handle];
        if (IsValid(d, object.get()))
        {
            d.object = object;
            object->mLayout = mCBufferLayouts[handle];
        }
        return;
    }

    LogError("Invalid handle for object.");
}
//----------------------------------------------------------------------------
template<>
void Shader::Set(int handle, std::shared_ptr<TextureBuffer> const& object)
{
    std::vector<Data>& data = mData[TextureBuffer::shaderDataLookup];
    if (0 <= handle && handle < static_cast<int>(data.size()))
    {
        auto& d = data[handle];
        if (IsValid(d, object.get()))
        {
            d.object = object;
            object->mLayout = mTBufferLayouts[handle];
        }
        return;
    }

    LogError("Invalid handle for object.");
}
//----------------------------------------------------------------------------
inline unsigned int Shader::GetNumXThreads() const
{
    return mNumXThreads;
}
//----------------------------------------------------------------------------
inline unsigned int Shader::GetNumYThreads() const
{
    return mNumYThreads;
}
//----------------------------------------------------------------------------
inline unsigned int Shader::GetNumZThreads() const
{
    return mNumZThreads;
}
//----------------------------------------------------------------------------
inline std::vector<unsigned char> const& Shader::GetCompiledCode() const
{
    return mCompiledCode;
}
//----------------------------------------------------------------------------
inline std::vector<Shader::Data> const& Shader::GetData(int lookup) const
{
    return mData[lookup];
}
//----------------------------------------------------------------------------
