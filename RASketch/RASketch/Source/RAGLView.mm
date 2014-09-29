//
//  RAGLView.m
//  RASketch
//
//  Created by Rinat Abdrashitov on 2014-09-26.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#define OVR_OS_MAC


#import "RAGLView.h"
#include <OpenGL/gl.h>
#include <OVR_CAPI_GL.h>
#include "RALogManager.h"
#include <Kernel/OVR_Math.h>
#include <OpenGL/glu.h>
#include "RAES2OffScreenBuffer.h"

using namespace OVR;
using namespace RAEngine;

@interface RAGLView() {
    ovrHmd hmd;
    ovrRecti eyeRenderViewport[2];
    RAES2OffScreenBuffer* textureOffscreenBuffer;
    ovrGLTexture eyeTexture[2];
}

@end

@implementation RAGLView


//
//-(void)awakeFromNib
//{
//    
// 
//}

-(void)OculusInitiliaze
{
    ovr_Initialize();
    hmd = ovrHmd_Create(0);
    
    if (hmd) {
        ovrSizei resolution = hmd->Resolution;
        RA_LOG_INFO("Resolution: %ix%i", resolution.w, resolution.h);
    } else {
        hmd = ovrHmd_CreateDebug(ovrHmd_DK2);
        RA_LOG_INFO("Created a debug DK2");
    }
    
    ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation |
                             ovrTrackingCap_MagYawCorrection |
                             ovrTrackingCap_Position, 0);
    
    // Configure Stereo settings.
    Sizei recommenedTex0Size = ovrHmd_GetFovTextureSize(hmd, ovrEye_Left,
                                                        hmd->DefaultEyeFov[0], 1.0f);
    Sizei recommenedTex1Size = ovrHmd_GetFovTextureSize(hmd, ovrEye_Right,
                                                        hmd->DefaultEyeFov[1], 1.0f);
    
    Sizei renderTargetSize;
    renderTargetSize.w  = recommenedTex0Size.w + recommenedTex1Size.w;
    renderTargetSize.h = fmax( recommenedTex0Size.h, recommenedTex1Size.h );
    textureOffscreenBuffer = new RAES2OffScreenBuffer();
    textureOffscreenBuffer->createOffScreenTextureBufffer(renderTargetSize.w, renderTargetSize.h);
    
    ovrFovPort eyeFov[2] = { hmd->DefaultEyeFov[0], hmd->DefaultEyeFov[1] };
    
    
    eyeRenderViewport[0].Pos = Vector2i(0, 0);
    eyeRenderViewport[0].Size = Sizei(renderTargetSize.w / 2, renderTargetSize.h);
    eyeRenderViewport[1].Pos = Vector2i((renderTargetSize.w + 1) / 2, 0);
    eyeRenderViewport[1].Size = eyeRenderViewport[0].Size;
    
    
    eyeTexture[0].OGL.Header.API = ovrRenderAPI_OpenGL;
    eyeTexture[0].OGL.Header.TextureSize = renderTargetSize;
    eyeTexture[0].OGL.Header.RenderViewport = eyeRenderViewport[0];
    eyeTexture[0].OGL.TexId = textureOffscreenBuffer->texture;
    
    eyeTexture[1] = eyeTexture[0];
    eyeTexture[1].OGL.Header.RenderViewport = eyeRenderViewport[1];
    
    ovrGLConfig cfg;
    cfg.OGL.Header.API = ovrRenderAPI_OpenGL;
    cfg.OGL.Header.RTSize = Sizei(hmd->Resolution.w, hmd->Resolution.h);
    cfg.OGL.Header.Multisample = 1;
    
    ovrEyeRenderDesc eyeRenderDesc[2];
    
    if (!ovrHmd_ConfigureRendering(hmd, &cfg.Config, ovrDistortionCap_Chromatic | ovrDistortionCap_Vignette | ovrDistortionCap_TimeWarp | ovrDistortionCap_Overdrive, eyeFov, eyeRenderDesc))
    {
        RA_LOG_ERROR("Couldnt configure Oculus");
        return;
    }
 
}

- (void)timerEvent:(NSTimer *)t
{
    [self setNeedsDisplay:YES];
}

-(void)prepareOpenGL
{
    glClearColor(0, 0, 0, 0);
    printf("Version: %s\r\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\r\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    [self OculusInitiliaze];
    
    
    NSTimer* renderTimer = [NSTimer timerWithTimeInterval:0.013f   //a 1ms time interval
                                                   target:self
                                                 selector:@selector(timerEvent:)
                                                 userInfo:nil
                                                  repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:renderTimer
                                 forMode:NSDefaultRunLoopMode];
    
    [self performSelector:@selector(dismissHealthWarning) withObject:nil afterDelay:3];
}

-(void)dismissHealthWarning {
    ovrHmd_DismissHSWDisplay(hmd);
}
-(void)reshape
{
    //added autoresizing constraints in the interface builder
    NSRect bounds = [self bounds];
    glViewport(0, 0, NSWidth(bounds), NSHeight(bounds));
}

-(void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    
    ovrTrackingState ts  = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
    if (ts.StatusFlags & (ovrStatus_OrientationTracked|ovrStatus_PositionTracked)) {
        Quatf orient = ts.HeadPose.ThePose.Orientation;
        float yaw, eyePitch, eyeRoll;
        orient.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &eyePitch, &eyeRoll);
        RA_LOG_INFO("Yaw:%f, Pitch:%f, Roll:%f", yaw, eyePitch, eyeRoll);
        
    }
    
    ovrFrameTiming frameTiming = ovrHmd_BeginFrame(hmd, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, textureOffscreenBuffer->frameBuffer);
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    ovrPosef eyeRenderPose[2];
    
    for (int eyeIndex = 0; eyeIndex < ovrEye_Count; eyeIndex++)
    {
        ovrEyeType eye = hmd->EyeRenderOrder[eyeIndex];
        eyeRenderPose[eye] = ovrHmd_GetEyePose(hmd, eye);
        
//        Matrix4f MVPMatrix = Matrix4f(ovrMatrix4f_Projection(eyeRenderDesc[eye].Fov, 0.01f, 10000.0f, true)) * Matrix4f::Translation(eyeRenderDesc[eye].ViewAdjust) * Matrix4f(Quatf(eyeRenderPose[eye].Orientation).Inverted());
//        
//        glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, &MVPMatrix.Transposed().M[0][0]);
//        
        glViewport(eyeRenderViewport[eye].Pos.x, eyeRenderViewport[eye].Pos.y, eyeRenderViewport[eye].Size.w, eyeRenderViewport[eye].Size.h);
        
        [self drawObjects];
    }

    ovrHmd_EndFrame(hmd, eyeRenderPose, &eyeTexture[0].Texture);

    glFlush();
}

-(void)drawObjects
{
    glColor3f(1.0f, 0.85f, 0.35f);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(  0.0,  0.6, 0.0);
        glVertex3f( -0.2, -0.3, 0.0);
        glVertex3f(  0.2, -0.3 ,0.0);
    }
    glEnd();
}

-(void)dealloc
{
    delete textureOffscreenBuffer;
    ovrHmd_Destroy(hmd);
    ovr_Shutdown();
}
@end
