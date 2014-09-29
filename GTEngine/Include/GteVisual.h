// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#pragma once

#include "GTEngineDEF.h"
#include "GteSpatial.h"
#include "GteVertexBuffer.h"
#include "GteIndexBuffer.h"
#include "GteVisualEffect.h"

namespace gte
{

class GTE_IMPEXP Visual : public Spatial
{
public:
    // Construction and destruction.
    virtual ~Visual ();
    Visual (
        std::shared_ptr<VertexBuffer> const& vbuffer =
            std::shared_ptr<VertexBuffer>(),
        std::shared_ptr<IndexBuffer> const& ibuffer =
            std::shared_ptr<IndexBuffer>(),
        std::shared_ptr<VisualEffect> const& effect =
            std::shared_ptr<VisualEffect>());

    // Member access.
    inline void SetVertexBuffer (std::shared_ptr<VertexBuffer> const& vbuffer);
    inline void SetIndexBuffer (std::shared_ptr<IndexBuffer> const& ibuffer);
    inline void SetEffect (std::shared_ptr<VisualEffect> const& effect);
    inline std::shared_ptr<VertexBuffer> const& GetVertexBuffer () const;
    inline std::shared_ptr<IndexBuffer> const& GetIndexBuffer () const;
    inline std::shared_ptr<VisualEffect> const& GetEffect () const;

    // Support for geometric updates.
    bool UpdateModelBound ();
    bool UpdateModelNormals ();

    // Public member access.
    BoundingSphere modelBound;

    // Naming support, used in the DX11 debug layer.  The default name is "".
    // If you want the name to show up in the DX11 destruction messages when
    // the associated DX11GraphicsObject is destroyed, set the name to
    // something other than "".
    virtual void SetName (std::string const& name);
    std::string const& GetName () const;

protected:
    // Support for geometric updates.
    inline virtual void UpdateWorldBound ();

    // Support for hierarchical culling.
    inline virtual void GetVisibleSet (Culler& culler, bool noCull);

    std::string mName;
    std::shared_ptr<VertexBuffer> mVBuffer;
    std::shared_ptr<IndexBuffer> mIBuffer;
    std::shared_ptr<VisualEffect> mEffect;
};

#include "GteVisual.inl"

}
