//
//  RAES2OffScreenBuffer.h
//  PAM2
//
//  Created by Rinat Abdrashitov on 2014-07-07.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#ifndef __PAM2__RAES2OffScreenBuffer__
#define __PAM2__RAES2OffScreenBuffer__

#include <iostream>

#include "RA_Types.h"
#if defined(RA_OS_IPHONE)
#import <OpenGLES/ES2/gl.h>
#elif defined(RA_OS_MAC)
#import <OpenGL/gl.h>
#endif


namespace RAEngine {

    class RAES2OffScreenBuffer
    {
    public:
        RAES2OffScreenBuffer();
        ~RAES2OffScreenBuffer();
        int createOffScreenColorDepthBuffer(GLsizei width, GLsizei height);
        int createOffScreenTextureBufffer(GLsizei width, GLsizei height);
        void bind();
        void unbind();
    
        GLuint frameBuffer;
        GLuint colorBuffer;
        GLuint depthBuffer;
        GLuint texture;
    };
}

#endif /* defined(__PAM2__RAES2OffScreenBuffer__) */
