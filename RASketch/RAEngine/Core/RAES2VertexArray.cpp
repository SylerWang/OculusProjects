//
//  RAES2VertexArray.cpp
//  PAM2
//
//  Created by Rinat Abdrashitov on 2014-06-23.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#include "RAES2VertexArray.h"
#include "RALogManager.h"

namespace RAEngine
{
    RAES2VertexArray::RAES2VertexArray()
    {
#if defined(RA_OS_IPHONE)
        glGenVertexArraysOES(1, &name);
#elif defined(RA_OS_MAC)
        glGenVertexArraysAPPLE(1, &name);
#endif
        GL_CHECK_ERROR;
    }
    
    void RAES2VertexArray::bind() const
    {
#if defined(RA_OS_IPHONE)
        glBindVertexArrayOES(name);
#elif defined(RA_OS_MAC)
        glBindVertexArrayAPPLE(name);
#endif
        GL_CHECK_ERROR;
    }
    
    void RAES2VertexArray::unbind()
    {
#if defined(RA_OS_IPHONE)
        glBindVertexArrayOES(0);
#elif defined(RA_OS_MAC)
        glBindVertexArrayAPPLE(0);
#endif
    }
    
    GLuint RAES2VertexArray::getName() const
    {
        return name;
    }
}