//
//  RAES2DepthBuffer.cpp
//  PAM2
//
//  Created by Rinat Abdrashitov on 2014-07-07.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#include "RAES2OffScreenBuffer.h"
#include "RALogManager.h"

namespace RAEngine {
    
    RAES2OffScreenBuffer::RAES2OffScreenBuffer(){ }
    
    RAES2OffScreenBuffer::~RAES2OffScreenBuffer()
    {
        glDeleteRenderbuffers(1, &colorBuffer);
        glDeleteRenderbuffers(1, &depthBuffer);
        glDeleteFramebuffers(1, &frameBuffer);
        glDeleteTextures(1, &texture);
    }
    
    int RAES2OffScreenBuffer::createOffScreenColorDepthBuffer(GLsizei width, GLsizei height)
    {
        //Create additional Buffers
        //Create framebuffer and attach color/depth renderbuffers
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        
        glGenRenderbuffers(1, &colorBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorBuffer);

#if defined(RA_OS_IPHONE)
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8_OES, width, height);
#elif defined(RA_OS_MAC)
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);
#endif
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBuffer);
        
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        
        int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            RA_LOG_ERROR("Couldnt create offscreen buffer");
            glDeleteRenderbuffers(1, &colorBuffer);
            glDeleteRenderbuffers(1, &depthBuffer);
            glDeleteFramebuffers(1, &frameBuffer);
            glDeleteTextures(1, &texture);
            return 0;
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return 1;
    }
    
    int RAES2OffScreenBuffer::createOffScreenTextureBufffer(GLsizei width, GLsizei height)
    {
        //Create framebuffer and attach texture/depth renderbuffers
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        
        //Texture atttachment
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                     0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, texture, 0);
        
        //Depth attachment
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        
        //Check status
        int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            RA_LOG_ERROR("Couldnt create offscreen buffer");
            glDeleteRenderbuffers(1, &colorBuffer);
            glDeleteRenderbuffers(1, &depthBuffer);
            glDeleteFramebuffers(1, &frameBuffer);
            glDeleteTextures(1, &texture);
            return 0;
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return 1;
    }
    
    void RAES2OffScreenBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    }
    
    void RAES2OffScreenBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}