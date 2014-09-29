// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

//----------------------------------------------------------------------------
template <typename WindowType>
WindowType* WindowSystem::Create (typename WindowType::Parameters& parameters)
{
    CreateFrom(parameters);
    if (parameters.created)
    {
        WindowType* window = new WindowType(parameters);
        mHandleMap[parameters.handle] = window;
        if (parameters.created)
        {
            return window;
        }
        Destroy(window);
    }
    else
    {
        LogError("WindowSystem::Create failed.");
    }
    return nullptr;
}
//----------------------------------------------------------------------------
template <typename WindowType>
void WindowSystem::Destroy (WindowType*& window)
{
    if (window)
    {
        HWND handle = window->GetHandle();
        mHandleMap.erase(handle);
        delete window;
        window = nullptr;
        DestroyWindow(handle);
    }
}
//----------------------------------------------------------------------------
