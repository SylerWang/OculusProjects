//
//  RAES2VertexArray.h
//  PAM2
//
//  Created by Rinat Abdrashitov on 2014-06-23.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#ifndef __PAM2__RAES2VertexArray__
#define __PAM2__RAES2VertexArray__

#include <iostream>

#include "RA_Types.h"
#if defined(RA_OS_IPHONE)
#import <OpenGLES/ES2/gl.h>
#elif defined(RA_OS_MAC)
#import <OpenGL/gl.h>
#endif

namespace RAEngine {
    class RAES2VertexArray
    {
    public:
        RAES2VertexArray();
        GLuint getName() const;
        void bind() const;
        static void unbind();
    private:
        GLuint name;
    };
}

#endif /* defined(__PAM2__RAES2VertexArray__) */
