// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteDX11Include.h"
#include "GteGraphicsObject.h"

namespace gte
{

class GTE_IMPEXP DX11GraphicsObject
{
public:
    // Abstract base class.
    virtual ~DX11GraphicsObject();
protected:
    DX11GraphicsObject(GraphicsObject const* gtObject);

public:
    // Member access.
    GraphicsObject* GetGraphicsObject() const;
    ID3D11DeviceChild* GetDXDeviceChild() const;

    // Support for the DX11 debug layer.  Set the name if you want to have
    // ID3D11DeviceChild destruction messages show your name rather than
    // "<unnamed>".  The typical usage is
    //   Texture2* texture = new Texture2(...);
    //   engine->Bind(texture)->SetName("MyTexture");
    // The virtual override is used to allow derived classes to use the
    // same name for associated resources.
    virtual void SetName(std::string const& name);
    std::string const& GetName() const;

protected:
    GraphicsObject* mGTObject;
    ID3D11DeviceChild* mDXObject;
    std::string mName;
};

}
