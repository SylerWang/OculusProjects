// Geometric Tools LLC, Redmond WA 98052
// Copyright (c) 1998-2014
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
// http://www.geometrictools.com/License/Boost/LICENSE_1_0.txt
// File Version: 1.0.0 (2014/08/11)

#include "OpenGL.h"
#include <cassert>
#include <cstring>
#include <fstream>

// Support for versioning.
#define OPENGL_VERSION_NONE  0
#define OPENGL_VERSION_1_0  10
#define OPENGL_VERSION_1_1  11
#define OPENGL_VERSION_1_2  12
#define OPENGL_VERSION_1_3  13
#define OPENGL_VERSION_1_4  14
#define OPENGL_VERSION_1_5  15
#define OPENGL_VERSION_2_0  20
#define OPENGL_VERSION_2_1  21
#define OPENGL_VERSION_3_0  30
#define OPENGL_VERSION_3_1  31
#define OPENGL_VERSION_3_2  32
#define OPENGL_VERSION_3_3  33
#define OPENGL_VERSION_4_0  40
#define OPENGL_VERSION_4_1  41
#define OPENGL_VERSION_4_2  42
#define OPENGL_VERSION_4_3  43
#define OPENGL_VERSION_4_4  44

// Support for querying the OpenGL function pointers.  Each platform must
// provide its own GetOpenGLFunctionPointer.
template <typename PGLFunction>
static void GetOpenGLFunction(char const* name, PGLFunction& function)
{
    extern void* GetOpenGLFunctionPointer(char const*);
    function = (PGLFunction)GetOpenGLFunctionPointer(name);
}

//----------------------------------------------------------------------------
static int GetOpenGLVersion()
{
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    return 10 * major + minor;
}
//----------------------------------------------------------------------------
static void ReportGLError(const char* glFunction)
{
    GLenum code = glGetError();
    while (code != GL_NO_ERROR)
    {
        const char* errorString = GTGetErrorString(code);
        (void)errorString;
        assert(false);
        code = glGetError();
    }
    (void)glFunction;
}
//----------------------------------------------------------------------------

#if !defined(WIN32)
//----------------------------------------------------------------------------
// GL_VERSION_1_0
//----------------------------------------------------------------------------
static PFNGLCULLFACEPROC sglCullFace = nullptr;
static PFNGLFRONTFACEPROC sglFrontFace = nullptr;
static PFNGLHINTPROC sglHint = nullptr;
static PFNGLLINEWIDTHPROC sglLineWidth = nullptr;
static PFNGLPOINTSIZEPROC sglPointSize = nullptr;
static PFNGLPOLYGONMODEPROC sglPolygonMode = nullptr;
static PFNGLSCISSORPROC sglScissor = nullptr;
static PFNGLTEXPARAMETERFPROC sglTexParameterf = nullptr;
static PFNGLTEXPARAMETERFVPROC sglTexParameterfv = nullptr;
static PFNGLTEXPARAMETERIPROC sglTexParameteri = nullptr;
static PFNGLTEXPARAMETERIVPROC sglTexParameteriv = nullptr;
static PFNGLTEXIMAGE1DPROC sglTexImage1D = nullptr;
static PFNGLTEXIMAGE2DPROC sglTexImage2D = nullptr;
static PFNGLDRAWBUFFERPROC sglDrawBuffer = nullptr;
static PFNGLCLEARPROC sglClear = nullptr;
static PFNGLCLEARCOLORPROC sglClearColor = nullptr;
static PFNGLCLEARSTENCILPROC sglClearStencil = nullptr;
static PFNGLCLEARDEPTHPROC sglClearDepth = nullptr;
static PFNGLSTENCILMASKPROC sglStencilMask = nullptr;
static PFNGLCOLORMASKPROC sglColorMask = nullptr;
static PFNGLDEPTHMASKPROC sglDepthMask = nullptr;
static PFNGLDISABLEPROC sglDisable = nullptr;
static PFNGLENABLEPROC sglEnable = nullptr;
static PFNGLFINISHPROC sglFinish = nullptr;
static PFNGLFLUSHPROC sglFlush = nullptr;
static PFNGLBLENDFUNCPROC sglBlendFunc = nullptr;
static PFNGLLOGICOPPROC sglLogicOp = nullptr;
static PFNGLSTENCILFUNCPROC sglStencilFunc = nullptr;
static PFNGLSTENCILOPPROC sglStencilOp = nullptr;
static PFNGLDEPTHFUNCPROC sglDepthFunc = nullptr;
static PFNGLPIXELSTOREFPROC sglPixelStoref = nullptr;
static PFNGLPIXELSTOREIPROC sglPixelStorei = nullptr;
static PFNGLREADBUFFERPROC sglReadBuffer = nullptr;
static PFNGLREADPIXELSPROC sglReadPixels = nullptr;
static PFNGLGETBOOLEANVPROC sglGetBooleanv = nullptr;
static PFNGLGETDOUBLEVPROC sglGetDoublev = nullptr;
static PFNGLGETERRORPROC sglGetError = nullptr;
static PFNGLGETFLOATVPROC sglGetFloatv = nullptr;
static PFNGLGETINTEGERVPROC sglGetIntegerv = nullptr;
static PFNGLGETSTRINGPROC sglGetString = nullptr;
static PFNGLGETTEXIMAGEPROC sglGetTexImage = nullptr;
static PFNGLGETTEXPARAMETERFVPROC sglGetTexParameterfv = nullptr;
static PFNGLGETTEXPARAMETERIVPROC sglGetTexParameteriv = nullptr;
static PFNGLGETTEXLEVELPARAMETERFVPROC sglGetTexLevelParameterfv = nullptr;
static PFNGLGETTEXLEVELPARAMETERIVPROC sglGetTexLevelParameteriv = nullptr;
static PFNGLISENABLEDPROC sglIsEnabled = nullptr;
static PFNGLDEPTHRANGEPROC sglDepthRange = nullptr;
static PFNGLVIEWPORTPROC sglViewport = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glCullFace(GLenum mode)
{
    if (sglCullFace)
    {
        sglCullFace(mode);
        ReportGLError("glCullFace");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFrontFace(GLenum mode)
{
    if (sglFrontFace)
    {
        sglFrontFace(mode);
        ReportGLError("glFrontFace");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glHint(GLenum target, GLenum mode)
{
    if (sglHint)
    {
        sglHint(target, mode);
        ReportGLError("glHint");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glLineWidth(GLfloat width)
{
    if (sglLineWidth)
    {
        sglLineWidth(width);
        ReportGLError("glLineWidth");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPointSize(GLfloat size)
{
    if (sglPointSize)
    {
        sglPointSize(size);
        ReportGLError("glPointSize");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPolygonMode(GLenum face, GLenum mode)
{
    if (sglPolygonMode)
    {
        sglPolygonMode(face, mode);
        ReportGLError("glPolygonMode");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (sglScissor)
    {
        sglScissor(x, y, width, height);
        ReportGLError("glScissor");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
    if (sglTexParameterf)
    {
        sglTexParameterf(target, pname, param);
        ReportGLError("glTexParameterf");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
    if (sglTexParameterfv)
    {
        sglTexParameterfv(target, pname, params);
        ReportGLError("glTexParameterfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param)
{
    if (sglTexParameteri)
    {
        sglTexParameteri(target, pname, param);
        ReportGLError("glTexParameteri");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint *params)
{
    if (sglTexParameteriv)
    {
        sglTexParameteriv(target, pname, params);
        ReportGLError("glTexParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels)
{
    if (sglTexImage1D)
    {
        sglTexImage1D(target, level, internalformat, width, border, format, type, pixels);
        ReportGLError("glTexImage1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels)
{
    if (sglTexImage2D)
    {
        sglTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
        ReportGLError("glTexImage2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawBuffer(GLenum mode)
{
    if (sglDrawBuffer)
    {
        sglDrawBuffer(mode);
        ReportGLError("glDrawBuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClear(GLbitfield mask)
{
    if (sglClear)
    {
        sglClear(mask);
        ReportGLError("glClear");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    if (sglClearColor)
    {
        sglClearColor(red, green, blue, alpha);
        ReportGLError("glClearColor");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearStencil(GLint s)
{
    if (sglClearStencil)
    {
        sglClearStencil(s);
        ReportGLError("glClearStencil");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearDepth(GLdouble depth)
{
    if (sglClearDepth)
    {
        sglClearDepth(depth);
        ReportGLError("glClearDepth");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glStencilMask(GLuint mask)
{
    if (sglStencilMask)
    {
        sglStencilMask(mask);
        ReportGLError("glStencilMask");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    if (sglColorMask)
    {
        sglColorMask(red, green, blue, alpha);
        ReportGLError("glColorMask");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDepthMask(GLboolean flag)
{
    if (sglDepthMask)
    {
        sglDepthMask(flag);
        ReportGLError("glDepthMask");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDisable(GLenum cap)
{
    if (sglDisable)
    {
        sglDisable(cap);
        ReportGLError("glDisable");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glEnable(GLenum cap)
{
    if (sglEnable)
    {
        sglEnable(cap);
        ReportGLError("glEnable");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFinish()
{
    if (sglFinish)
    {
        sglFinish();
        ReportGLError("glFinish");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFlush()
{
    if (sglFlush)
    {
        sglFlush();
        ReportGLError("glFlush");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    if (sglBlendFunc)
    {
        sglBlendFunc(sfactor, dfactor);
        ReportGLError("glBlendFunc");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glLogicOp(GLenum opcode)
{
    if (sglLogicOp)
    {
        sglLogicOp(opcode);
        ReportGLError("glLogicOp");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
    if (sglStencilFunc)
    {
        sglStencilFunc(func, ref, mask);
        ReportGLError("glStencilFunc");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
    if (sglStencilOp)
    {
        sglStencilOp(fail, zfail, zpass);
        ReportGLError("glStencilOp");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDepthFunc(GLenum func)
{
    if (sglDepthFunc)
    {
        sglDepthFunc(func);
        ReportGLError("glDepthFunc");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPixelStoref(GLenum pname, GLfloat param)
{
    if (sglPixelStoref)
    {
        sglPixelStoref(pname, param);
        ReportGLError("glPixelStoref");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPixelStorei(GLenum pname, GLint param)
{
    if (sglPixelStorei)
    {
        sglPixelStorei(pname, param);
        ReportGLError("glPixelStorei");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glReadBuffer(GLenum mode)
{
    if (sglReadBuffer)
    {
        sglReadBuffer(mode);
        ReportGLError("glReadBuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void *pixels)
{
    if (sglReadPixels)
    {
        sglReadPixels(x, y, width, height, format, type, pixels);
        ReportGLError("glReadPixels");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetBooleanv(GLenum pname, GLboolean *data)
{
    if (sglGetBooleanv)
    {
        sglGetBooleanv(pname, data);
        ReportGLError("glGetBooleanv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetDoublev(GLenum pname, GLdouble *data)
{
    if (sglGetDoublev)
    {
        sglGetDoublev(pname, data);
        ReportGLError("glGetDoublev");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLenum APIENTRY glGetError()
{
    GLenum result;
    if (sglGetError)
    {
        result = sglGetError();
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetFloatv(GLenum pname, GLfloat *data)
{
    if (sglGetFloatv)
    {
        sglGetFloatv(pname, data);
        ReportGLError("glGetFloatv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetIntegerv(GLenum pname, GLint *data)
{
    if (sglGetIntegerv)
    {
        sglGetIntegerv(pname, data);
        ReportGLError("glGetIntegerv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
const GLubyte * APIENTRY glGetString(GLenum name)
{
    const GLubyte * result;
    if (sglGetString)
    {
        result = sglGetString(name);
        ReportGLError("glGetString");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void *pixels)
{
    if (sglGetTexImage)
    {
        sglGetTexImage(target, level, format, type, pixels);
        ReportGLError("glGetTexImage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    if (sglGetTexParameterfv)
    {
        sglGetTexParameterfv(target, pname, params);
        ReportGLError("glGetTexParameterfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint *params)
{
    if (sglGetTexParameteriv)
    {
        sglGetTexParameteriv(target, pname, params);
        ReportGLError("glGetTexParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params)
{
    if (sglGetTexLevelParameterfv)
    {
        sglGetTexLevelParameterfv(target, level, pname, params);
        ReportGLError("glGetTexLevelParameterfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params)
{
    if (sglGetTexLevelParameteriv)
    {
        sglGetTexLevelParameteriv(target, level, pname, params);
        ReportGLError("glGetTexLevelParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsEnabled(GLenum cap)
{
    GLboolean result;
    if (sglIsEnabled)
    {
        result = sglIsEnabled(cap);
        ReportGLError("glIsEnabled");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glDepthRange(GLdouble near, GLdouble far)
{
    if (sglDepthRange)
    {
        sglDepthRange(near, far);
        ReportGLError("glDepthRange");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (sglViewport)
    {
        sglViewport(x, y, width, height);
        ReportGLError("glViewport");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_1_0()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_1_0)
    {
        GetOpenGLFunction("glCullFace", sglCullFace);
        GetOpenGLFunction("glFrontFace", sglFrontFace);
        GetOpenGLFunction("glHint", sglHint);
        GetOpenGLFunction("glLineWidth", sglLineWidth);
        GetOpenGLFunction("glPointSize", sglPointSize);
        GetOpenGLFunction("glPolygonMode", sglPolygonMode);
        GetOpenGLFunction("glScissor", sglScissor);
        GetOpenGLFunction("glTexParameterf", sglTexParameterf);
        GetOpenGLFunction("glTexParameterfv", sglTexParameterfv);
        GetOpenGLFunction("glTexParameteri", sglTexParameteri);
        GetOpenGLFunction("glTexParameteriv", sglTexParameteriv);
        GetOpenGLFunction("glTexImage1D", sglTexImage1D);
        GetOpenGLFunction("glTexImage2D", sglTexImage2D);
        GetOpenGLFunction("glDrawBuffer", sglDrawBuffer);
        GetOpenGLFunction("glClear", sglClear);
        GetOpenGLFunction("glClearColor", sglClearColor);
        GetOpenGLFunction("glClearStencil", sglClearStencil);
        GetOpenGLFunction("glClearDepth", sglClearDepth);
        GetOpenGLFunction("glStencilMask", sglStencilMask);
        GetOpenGLFunction("glColorMask", sglColorMask);
        GetOpenGLFunction("glDepthMask", sglDepthMask);
        GetOpenGLFunction("glDisable", sglDisable);
        GetOpenGLFunction("glEnable", sglEnable);
        GetOpenGLFunction("glFinish", sglFinish);
        GetOpenGLFunction("glFlush", sglFlush);
        GetOpenGLFunction("glBlendFunc", sglBlendFunc);
        GetOpenGLFunction("glLogicOp", sglLogicOp);
        GetOpenGLFunction("glStencilFunc", sglStencilFunc);
        GetOpenGLFunction("glStencilOp", sglStencilOp);
        GetOpenGLFunction("glDepthFunc", sglDepthFunc);
        GetOpenGLFunction("glPixelStoref", sglPixelStoref);
        GetOpenGLFunction("glPixelStorei", sglPixelStorei);
        GetOpenGLFunction("glReadBuffer", sglReadBuffer);
        GetOpenGLFunction("glReadPixels", sglReadPixels);
        GetOpenGLFunction("glGetBooleanv", sglGetBooleanv);
        GetOpenGLFunction("glGetDoublev", sglGetDoublev);
        GetOpenGLFunction("glGetError", sglGetError);
        GetOpenGLFunction("glGetFloatv", sglGetFloatv);
        GetOpenGLFunction("glGetIntegerv", sglGetIntegerv);
        GetOpenGLFunction("glGetString", sglGetString);
        GetOpenGLFunction("glGetTexImage", sglGetTexImage);
        GetOpenGLFunction("glGetTexParameterfv", sglGetTexParameterfv);
        GetOpenGLFunction("glGetTexParameteriv", sglGetTexParameteriv);
        GetOpenGLFunction("glGetTexLevelParameterfv", sglGetTexLevelParameterfv);
        GetOpenGLFunction("glGetTexLevelParameteriv", sglGetTexLevelParameteriv);
        GetOpenGLFunction("glIsEnabled", sglIsEnabled);
        GetOpenGLFunction("glDepthRange", sglDepthRange);
        GetOpenGLFunction("glViewport", sglViewport);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_1_1
//----------------------------------------------------------------------------
static PFNGLDRAWARRAYSPROC sglDrawArrays = nullptr;
static PFNGLDRAWELEMENTSPROC sglDrawElements = nullptr;
static PFNGLGETPOINTERVPROC sglGetPointerv = nullptr;
static PFNGLPOLYGONOFFSETPROC sglPolygonOffset = nullptr;
static PFNGLCOPYTEXIMAGE1DPROC sglCopyTexImage1D = nullptr;
static PFNGLCOPYTEXIMAGE2DPROC sglCopyTexImage2D = nullptr;
static PFNGLCOPYTEXSUBIMAGE1DPROC sglCopyTexSubImage1D = nullptr;
static PFNGLCOPYTEXSUBIMAGE2DPROC sglCopyTexSubImage2D = nullptr;
static PFNGLTEXSUBIMAGE1DPROC sglTexSubImage1D = nullptr;
static PFNGLTEXSUBIMAGE2DPROC sglTexSubImage2D = nullptr;
static PFNGLBINDTEXTUREPROC sglBindTexture = nullptr;
static PFNGLDELETETEXTURESPROC sglDeleteTextures = nullptr;
static PFNGLGENTEXTURESPROC sglGenTextures = nullptr;
static PFNGLISTEXTUREPROC sglIsTexture = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    if (sglDrawArrays)
    {
        sglDrawArrays(mode, first, count);
        ReportGLError("glDrawArrays");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
{
    if (sglDrawElements)
    {
        sglDrawElements(mode, count, type, indices);
        ReportGLError("glDrawElements");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetPointerv(GLenum pname, void **params)
{
    if (sglGetPointerv)
    {
        sglGetPointerv(pname, params);
        ReportGLError("glGetPointerv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPolygonOffset(GLfloat factor, GLfloat units)
{
    if (sglPolygonOffset)
    {
        sglPolygonOffset(factor, units);
        ReportGLError("glPolygonOffset");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
    if (sglCopyTexImage1D)
    {
        sglCopyTexImage1D(target, level, internalformat, x, y, width, border);
        ReportGLError("glCopyTexImage1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    if (sglCopyTexImage2D)
    {
        sglCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
        ReportGLError("glCopyTexImage2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    if (sglCopyTexSubImage1D)
    {
        sglCopyTexSubImage1D(target, level, xoffset, x, y, width);
        ReportGLError("glCopyTexSubImage1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (sglCopyTexSubImage2D)
    {
        sglCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
        ReportGLError("glCopyTexSubImage2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *pixels)
{
    if (sglTexSubImage1D)
    {
        sglTexSubImage1D(target, level, xoffset, width, format, type, pixels);
        ReportGLError("glTexSubImage1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
{
    if (sglTexSubImage2D)
    {
        sglTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
        ReportGLError("glTexSubImage2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindTexture(GLenum target, GLuint texture)
{
    if (sglBindTexture)
    {
        sglBindTexture(target, texture);
        ReportGLError("glBindTexture");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteTextures(GLsizei n, const GLuint *textures)
{
    if (sglDeleteTextures)
    {
        sglDeleteTextures(n, textures);
        ReportGLError("glDeleteTextures");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenTextures(GLsizei n, GLuint *textures)
{
    if (sglGenTextures)
    {
        sglGenTextures(n, textures);
        ReportGLError("glGenTextures");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsTexture(GLuint texture)
{
    GLboolean result;
    if (sglIsTexture)
    {
        result = sglIsTexture(texture);
        ReportGLError("glIsTexture");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_1_1()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_1_1)
    {
        GetOpenGLFunction("glDrawArrays", sglDrawArrays);
        GetOpenGLFunction("glDrawElements", sglDrawElements);
        GetOpenGLFunction("glGetPointerv", sglGetPointerv);
        GetOpenGLFunction("glPolygonOffset", sglPolygonOffset);
        GetOpenGLFunction("glCopyTexImage1D", sglCopyTexImage1D);
        GetOpenGLFunction("glCopyTexImage2D", sglCopyTexImage2D);
        GetOpenGLFunction("glCopyTexSubImage1D", sglCopyTexSubImage1D);
        GetOpenGLFunction("glCopyTexSubImage2D", sglCopyTexSubImage2D);
        GetOpenGLFunction("glTexSubImage1D", sglTexSubImage1D);
        GetOpenGLFunction("glTexSubImage2D", sglTexSubImage2D);
        GetOpenGLFunction("glBindTexture", sglBindTexture);
        GetOpenGLFunction("glDeleteTextures", sglDeleteTextures);
        GetOpenGLFunction("glGenTextures", sglGenTextures);
        GetOpenGLFunction("glIsTexture", sglIsTexture);
    }
}
//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
// GL_VERSION_1_2
//----------------------------------------------------------------------------
static PFNGLDRAWRANGEELEMENTSPROC sglDrawRangeElements = nullptr;
static PFNGLTEXIMAGE3DPROC sglTexImage3D = nullptr;
static PFNGLTEXSUBIMAGE3DPROC sglTexSubImage3D = nullptr;
static PFNGLCOPYTEXSUBIMAGE3DPROC sglCopyTexSubImage3D = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices)
{
    if (sglDrawRangeElements)
    {
        sglDrawRangeElements(mode, start, end, count, type, indices);
        ReportGLError("glDrawRangeElements");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)
{
    if (sglTexImage3D)
    {
        sglTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
        ReportGLError("glTexImage3D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)
{
    if (sglTexSubImage3D)
    {
        sglTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
        ReportGLError("glTexSubImage3D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (sglCopyTexSubImage3D)
    {
        sglCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
        ReportGLError("glCopyTexSubImage3D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_1_2()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_1_2)
    {
        GetOpenGLFunction("glDrawRangeElements", sglDrawRangeElements);
        GetOpenGLFunction("glTexImage3D", sglTexImage3D);
        GetOpenGLFunction("glTexSubImage3D", sglTexSubImage3D);
        GetOpenGLFunction("glCopyTexSubImage3D", sglCopyTexSubImage3D);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_1_3
//----------------------------------------------------------------------------
static PFNGLACTIVETEXTUREPROC sglActiveTexture = nullptr;
static PFNGLSAMPLECOVERAGEPROC sglSampleCoverage = nullptr;
static PFNGLCOMPRESSEDTEXIMAGE3DPROC sglCompressedTexImage3D = nullptr;
static PFNGLCOMPRESSEDTEXIMAGE2DPROC sglCompressedTexImage2D = nullptr;
static PFNGLCOMPRESSEDTEXIMAGE1DPROC sglCompressedTexImage1D = nullptr;
static PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC sglCompressedTexSubImage3D = nullptr;
static PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC sglCompressedTexSubImage2D = nullptr;
static PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC sglCompressedTexSubImage1D = nullptr;
static PFNGLGETCOMPRESSEDTEXIMAGEPROC sglGetCompressedTexImage = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glActiveTexture(GLenum texture)
{
    if (sglActiveTexture)
    {
        sglActiveTexture(texture);
        ReportGLError("glActiveTexture");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSampleCoverage(GLfloat value, GLboolean invert)
{
    if (sglSampleCoverage)
    {
        sglSampleCoverage(value, invert);
        ReportGLError("glSampleCoverage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void *data)
{
    if (sglCompressedTexImage3D)
    {
        sglCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
        ReportGLError("glCompressedTexImage3D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void *data)
{
    if (sglCompressedTexImage2D)
    {
        sglCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
        ReportGLError("glCompressedTexImage2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void *data)
{
    if (sglCompressedTexImage1D)
    {
        sglCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
        ReportGLError("glCompressedTexImage1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void *data)
{
    if (sglCompressedTexSubImage3D)
    {
        sglCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
        ReportGLError("glCompressedTexSubImage3D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void *data)
{
    if (sglCompressedTexSubImage2D)
    {
        sglCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
        ReportGLError("glCompressedTexSubImage2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void *data)
{
    if (sglCompressedTexSubImage1D)
    {
        sglCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
        ReportGLError("glCompressedTexSubImage1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetCompressedTexImage(GLenum target, GLint level, void *img)
{
    if (sglGetCompressedTexImage)
    {
        sglGetCompressedTexImage(target, level, img);
        ReportGLError("glGetCompressedTexImage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_1_3()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_1_3)
    {
        GetOpenGLFunction("glActiveTexture", sglActiveTexture);
        GetOpenGLFunction("glSampleCoverage", sglSampleCoverage);
        GetOpenGLFunction("glCompressedTexImage3D", sglCompressedTexImage3D);
        GetOpenGLFunction("glCompressedTexImage2D", sglCompressedTexImage2D);
        GetOpenGLFunction("glCompressedTexImage1D", sglCompressedTexImage1D);
        GetOpenGLFunction("glCompressedTexSubImage3D", sglCompressedTexSubImage3D);
        GetOpenGLFunction("glCompressedTexSubImage2D", sglCompressedTexSubImage2D);
        GetOpenGLFunction("glCompressedTexSubImage1D", sglCompressedTexSubImage1D);
        GetOpenGLFunction("glGetCompressedTexImage", sglGetCompressedTexImage);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_1_4
//----------------------------------------------------------------------------
static PFNGLBLENDFUNCSEPARATEPROC sglBlendFuncSeparate = nullptr;
static PFNGLMULTIDRAWARRAYSPROC sglMultiDrawArrays = nullptr;
static PFNGLMULTIDRAWELEMENTSPROC sglMultiDrawElements = nullptr;
static PFNGLPOINTPARAMETERFPROC sglPointParameterf = nullptr;
static PFNGLPOINTPARAMETERFVPROC sglPointParameterfv = nullptr;
static PFNGLPOINTPARAMETERIPROC sglPointParameteri = nullptr;
static PFNGLPOINTPARAMETERIVPROC sglPointParameteriv = nullptr;
static PFNGLBLENDCOLORPROC sglBlendColor = nullptr;
static PFNGLBLENDEQUATIONPROC sglBlendEquation = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
    if (sglBlendFuncSeparate)
    {
        sglBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
        ReportGLError("glBlendFuncSeparate");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glMultiDrawArrays(GLenum mode, const GLint *first, const GLsizei *count, GLsizei drawcount)
{
    if (sglMultiDrawArrays)
    {
        sglMultiDrawArrays(mode, first, count, drawcount);
        ReportGLError("glMultiDrawArrays");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glMultiDrawElements(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount)
{
    if (sglMultiDrawElements)
    {
        sglMultiDrawElements(mode, count, type, indices, drawcount);
        ReportGLError("glMultiDrawElements");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPointParameterf(GLenum pname, GLfloat param)
{
    if (sglPointParameterf)
    {
        sglPointParameterf(pname, param);
        ReportGLError("glPointParameterf");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPointParameterfv(GLenum pname, const GLfloat *params)
{
    if (sglPointParameterfv)
    {
        sglPointParameterfv(pname, params);
        ReportGLError("glPointParameterfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPointParameteri(GLenum pname, GLint param)
{
    if (sglPointParameteri)
    {
        sglPointParameteri(pname, param);
        ReportGLError("glPointParameteri");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPointParameteriv(GLenum pname, const GLint *params)
{
    if (sglPointParameteriv)
    {
        sglPointParameteriv(pname, params);
        ReportGLError("glPointParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    if (sglBlendColor)
    {
        sglBlendColor(red, green, blue, alpha);
        ReportGLError("glBlendColor");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlendEquation(GLenum mode)
{
    if (sglBlendEquation)
    {
        sglBlendEquation(mode);
        ReportGLError("glBlendEquation");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_1_4()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_1_4)
    {
        GetOpenGLFunction("glBlendFuncSeparate", sglBlendFuncSeparate);
        GetOpenGLFunction("glMultiDrawArrays", sglMultiDrawArrays);
        GetOpenGLFunction("glMultiDrawElements", sglMultiDrawElements);
        GetOpenGLFunction("glPointParameterf", sglPointParameterf);
        GetOpenGLFunction("glPointParameterfv", sglPointParameterfv);
        GetOpenGLFunction("glPointParameteri", sglPointParameteri);
        GetOpenGLFunction("glPointParameteriv", sglPointParameteriv);
        GetOpenGLFunction("glBlendColor", sglBlendColor);
        GetOpenGLFunction("glBlendEquation", sglBlendEquation);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_1_5
//----------------------------------------------------------------------------
static PFNGLGENQUERIESPROC sglGenQueries = nullptr;
static PFNGLDELETEQUERIESPROC sglDeleteQueries = nullptr;
static PFNGLISQUERYPROC sglIsQuery = nullptr;
static PFNGLBEGINQUERYPROC sglBeginQuery = nullptr;
static PFNGLENDQUERYPROC sglEndQuery = nullptr;
static PFNGLGETQUERYIVPROC sglGetQueryiv = nullptr;
static PFNGLGETQUERYOBJECTIVPROC sglGetQueryObjectiv = nullptr;
static PFNGLGETQUERYOBJECTUIVPROC sglGetQueryObjectuiv = nullptr;
static PFNGLBINDBUFFERPROC sglBindBuffer = nullptr;
static PFNGLDELETEBUFFERSPROC sglDeleteBuffers = nullptr;
static PFNGLGENBUFFERSPROC sglGenBuffers = nullptr;
static PFNGLISBUFFERPROC sglIsBuffer = nullptr;
static PFNGLBUFFERDATAPROC sglBufferData = nullptr;
static PFNGLBUFFERSUBDATAPROC sglBufferSubData = nullptr;
static PFNGLGETBUFFERSUBDATAPROC sglGetBufferSubData = nullptr;
static PFNGLMAPBUFFERPROC sglMapBuffer = nullptr;
static PFNGLUNMAPBUFFERPROC sglUnmapBuffer = nullptr;
static PFNGLGETBUFFERPARAMETERIVPROC sglGetBufferParameteriv = nullptr;
static PFNGLGETBUFFERPOINTERVPROC sglGetBufferPointerv = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glGenQueries(GLsizei n, GLuint *ids)
{
    if (sglGenQueries)
    {
        sglGenQueries(n, ids);
        ReportGLError("glGenQueries");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteQueries(GLsizei n, const GLuint *ids)
{
    if (sglDeleteQueries)
    {
        sglDeleteQueries(n, ids);
        ReportGLError("glDeleteQueries");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsQuery(GLuint id)
{
    GLboolean result;
    if (sglIsQuery)
    {
        result = sglIsQuery(id);
        ReportGLError("glIsQuery");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glBeginQuery(GLenum target, GLuint id)
{
    if (sglBeginQuery)
    {
        sglBeginQuery(target, id);
        ReportGLError("glBeginQuery");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glEndQuery(GLenum target)
{
    if (sglEndQuery)
    {
        sglEndQuery(target);
        ReportGLError("glEndQuery");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetQueryiv(GLenum target, GLenum pname, GLint *params)
{
    if (sglGetQueryiv)
    {
        sglGetQueryiv(target, pname, params);
        ReportGLError("glGetQueryiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetQueryObjectiv(GLuint id, GLenum pname, GLint *params)
{
    if (sglGetQueryObjectiv)
    {
        sglGetQueryObjectiv(id, pname, params);
        ReportGLError("glGetQueryObjectiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint *params)
{
    if (sglGetQueryObjectuiv)
    {
        sglGetQueryObjectuiv(id, pname, params);
        ReportGLError("glGetQueryObjectuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindBuffer(GLenum target, GLuint buffer)
{
    if (sglBindBuffer)
    {
        sglBindBuffer(target, buffer);
        ReportGLError("glBindBuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
    if (sglDeleteBuffers)
    {
        sglDeleteBuffers(n, buffers);
        ReportGLError("glDeleteBuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenBuffers(GLsizei n, GLuint *buffers)
{
    if (sglGenBuffers)
    {
        sglGenBuffers(n, buffers);
        ReportGLError("glGenBuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsBuffer(GLuint buffer)
{
    GLboolean result;
    if (sglIsBuffer)
    {
        result = sglIsBuffer(buffer);
        ReportGLError("glIsBuffer");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage)
{
    if (sglBufferData)
    {
        sglBufferData(target, size, data, usage);
        ReportGLError("glBufferData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
{
    if (sglBufferSubData)
    {
        sglBufferSubData(target, offset, size, data);
        ReportGLError("glBufferSubData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void *data)
{
    if (sglGetBufferSubData)
    {
        sglGetBufferSubData(target, offset, size, data);
        ReportGLError("glGetBufferSubData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void * APIENTRY glMapBuffer(GLenum target, GLenum access)
{
    void * result;
    if (sglMapBuffer)
    {
        result = sglMapBuffer(target, access);
        ReportGLError("glMapBuffer");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glUnmapBuffer(GLenum target)
{
    GLboolean result;
    if (sglUnmapBuffer)
    {
        result = sglUnmapBuffer(target);
        ReportGLError("glUnmapBuffer");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetBufferParameteriv(GLenum target, GLenum pname, GLint *params)
{
    if (sglGetBufferParameteriv)
    {
        sglGetBufferParameteriv(target, pname, params);
        ReportGLError("glGetBufferParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetBufferPointerv(GLenum target, GLenum pname, void **params)
{
    if (sglGetBufferPointerv)
    {
        sglGetBufferPointerv(target, pname, params);
        ReportGLError("glGetBufferPointerv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_1_5()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_1_5)
    {
        GetOpenGLFunction("glGenQueries", sglGenQueries);
        GetOpenGLFunction("glDeleteQueries", sglDeleteQueries);
        GetOpenGLFunction("glIsQuery", sglIsQuery);
        GetOpenGLFunction("glBeginQuery", sglBeginQuery);
        GetOpenGLFunction("glEndQuery", sglEndQuery);
        GetOpenGLFunction("glGetQueryiv", sglGetQueryiv);
        GetOpenGLFunction("glGetQueryObjectiv", sglGetQueryObjectiv);
        GetOpenGLFunction("glGetQueryObjectuiv", sglGetQueryObjectuiv);
        GetOpenGLFunction("glBindBuffer", sglBindBuffer);
        GetOpenGLFunction("glDeleteBuffers", sglDeleteBuffers);
        GetOpenGLFunction("glGenBuffers", sglGenBuffers);
        GetOpenGLFunction("glIsBuffer", sglIsBuffer);
        GetOpenGLFunction("glBufferData", sglBufferData);
        GetOpenGLFunction("glBufferSubData", sglBufferSubData);
        GetOpenGLFunction("glGetBufferSubData", sglGetBufferSubData);
        GetOpenGLFunction("glMapBuffer", sglMapBuffer);
        GetOpenGLFunction("glUnmapBuffer", sglUnmapBuffer);
        GetOpenGLFunction("glGetBufferParameteriv", sglGetBufferParameteriv);
        GetOpenGLFunction("glGetBufferPointerv", sglGetBufferPointerv);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_2_0
//----------------------------------------------------------------------------
static PFNGLBLENDEQUATIONSEPARATEPROC sglBlendEquationSeparate = nullptr;
static PFNGLDRAWBUFFERSPROC sglDrawBuffers = nullptr;
static PFNGLSTENCILOPSEPARATEPROC sglStencilOpSeparate = nullptr;
static PFNGLSTENCILFUNCSEPARATEPROC sglStencilFuncSeparate = nullptr;
static PFNGLSTENCILMASKSEPARATEPROC sglStencilMaskSeparate = nullptr;
static PFNGLATTACHSHADERPROC sglAttachShader = nullptr;
static PFNGLBINDATTRIBLOCATIONPROC sglBindAttribLocation = nullptr;
static PFNGLCOMPILESHADERPROC sglCompileShader = nullptr;
static PFNGLCREATEPROGRAMPROC sglCreateProgram = nullptr;
static PFNGLCREATESHADERPROC sglCreateShader = nullptr;
static PFNGLDELETEPROGRAMPROC sglDeleteProgram = nullptr;
static PFNGLDELETESHADERPROC sglDeleteShader = nullptr;
static PFNGLDETACHSHADERPROC sglDetachShader = nullptr;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC sglDisableVertexAttribArray = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC sglEnableVertexAttribArray = nullptr;
static PFNGLGETACTIVEATTRIBPROC sglGetActiveAttrib = nullptr;
static PFNGLGETACTIVEUNIFORMPROC sglGetActiveUniform = nullptr;
static PFNGLGETATTACHEDSHADERSPROC sglGetAttachedShaders = nullptr;
static PFNGLGETATTRIBLOCATIONPROC sglGetAttribLocation = nullptr;
static PFNGLGETPROGRAMIVPROC sglGetProgramiv = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC sglGetProgramInfoLog = nullptr;
static PFNGLGETSHADERIVPROC sglGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC sglGetShaderInfoLog = nullptr;
static PFNGLGETSHADERSOURCEPROC sglGetShaderSource = nullptr;
static PFNGLGETUNIFORMLOCATIONPROC sglGetUniformLocation = nullptr;
static PFNGLGETUNIFORMFVPROC sglGetUniformfv = nullptr;
static PFNGLGETUNIFORMIVPROC sglGetUniformiv = nullptr;
static PFNGLGETVERTEXATTRIBDVPROC sglGetVertexAttribdv = nullptr;
static PFNGLGETVERTEXATTRIBFVPROC sglGetVertexAttribfv = nullptr;
static PFNGLGETVERTEXATTRIBIVPROC sglGetVertexAttribiv = nullptr;
static PFNGLGETVERTEXATTRIBPOINTERVPROC sglGetVertexAttribPointerv = nullptr;
static PFNGLISPROGRAMPROC sglIsProgram = nullptr;
static PFNGLISSHADERPROC sglIsShader = nullptr;
static PFNGLLINKPROGRAMPROC sglLinkProgram = nullptr;
static PFNGLSHADERSOURCEPROC sglShaderSource = nullptr;
static PFNGLUSEPROGRAMPROC sglUseProgram = nullptr;
static PFNGLUNIFORM1FPROC sglUniform1f = nullptr;
static PFNGLUNIFORM2FPROC sglUniform2f = nullptr;
static PFNGLUNIFORM3FPROC sglUniform3f = nullptr;
static PFNGLUNIFORM4FPROC sglUniform4f = nullptr;
static PFNGLUNIFORM1IPROC sglUniform1i = nullptr;
static PFNGLUNIFORM2IPROC sglUniform2i = nullptr;
static PFNGLUNIFORM3IPROC sglUniform3i = nullptr;
static PFNGLUNIFORM4IPROC sglUniform4i = nullptr;
static PFNGLUNIFORM1FVPROC sglUniform1fv = nullptr;
static PFNGLUNIFORM2FVPROC sglUniform2fv = nullptr;
static PFNGLUNIFORM3FVPROC sglUniform3fv = nullptr;
static PFNGLUNIFORM4FVPROC sglUniform4fv = nullptr;
static PFNGLUNIFORM1IVPROC sglUniform1iv = nullptr;
static PFNGLUNIFORM2IVPROC sglUniform2iv = nullptr;
static PFNGLUNIFORM3IVPROC sglUniform3iv = nullptr;
static PFNGLUNIFORM4IVPROC sglUniform4iv = nullptr;
static PFNGLUNIFORMMATRIX2FVPROC sglUniformMatrix2fv = nullptr;
static PFNGLUNIFORMMATRIX3FVPROC sglUniformMatrix3fv = nullptr;
static PFNGLUNIFORMMATRIX4FVPROC sglUniformMatrix4fv = nullptr;
static PFNGLVALIDATEPROGRAMPROC sglValidateProgram = nullptr;
static PFNGLVERTEXATTRIB1DPROC sglVertexAttrib1d = nullptr;
static PFNGLVERTEXATTRIB1DVPROC sglVertexAttrib1dv = nullptr;
static PFNGLVERTEXATTRIB1FPROC sglVertexAttrib1f = nullptr;
static PFNGLVERTEXATTRIB1FVPROC sglVertexAttrib1fv = nullptr;
static PFNGLVERTEXATTRIB1SPROC sglVertexAttrib1s = nullptr;
static PFNGLVERTEXATTRIB1SVPROC sglVertexAttrib1sv = nullptr;
static PFNGLVERTEXATTRIB2DPROC sglVertexAttrib2d = nullptr;
static PFNGLVERTEXATTRIB2DVPROC sglVertexAttrib2dv = nullptr;
static PFNGLVERTEXATTRIB2FPROC sglVertexAttrib2f = nullptr;
static PFNGLVERTEXATTRIB2FVPROC sglVertexAttrib2fv = nullptr;
static PFNGLVERTEXATTRIB2SPROC sglVertexAttrib2s = nullptr;
static PFNGLVERTEXATTRIB2SVPROC sglVertexAttrib2sv = nullptr;
static PFNGLVERTEXATTRIB3DPROC sglVertexAttrib3d = nullptr;
static PFNGLVERTEXATTRIB3DVPROC sglVertexAttrib3dv = nullptr;
static PFNGLVERTEXATTRIB3FPROC sglVertexAttrib3f = nullptr;
static PFNGLVERTEXATTRIB3FVPROC sglVertexAttrib3fv = nullptr;
static PFNGLVERTEXATTRIB3SPROC sglVertexAttrib3s = nullptr;
static PFNGLVERTEXATTRIB3SVPROC sglVertexAttrib3sv = nullptr;
static PFNGLVERTEXATTRIB4NBVPROC sglVertexAttrib4Nbv = nullptr;
static PFNGLVERTEXATTRIB4NIVPROC sglVertexAttrib4Niv = nullptr;
static PFNGLVERTEXATTRIB4NSVPROC sglVertexAttrib4Nsv = nullptr;
static PFNGLVERTEXATTRIB4NUBPROC sglVertexAttrib4Nub = nullptr;
static PFNGLVERTEXATTRIB4NUBVPROC sglVertexAttrib4Nubv = nullptr;
static PFNGLVERTEXATTRIB4NUIVPROC sglVertexAttrib4Nuiv = nullptr;
static PFNGLVERTEXATTRIB4NUSVPROC sglVertexAttrib4Nusv = nullptr;
static PFNGLVERTEXATTRIB4BVPROC sglVertexAttrib4bv = nullptr;
static PFNGLVERTEXATTRIB4DPROC sglVertexAttrib4d = nullptr;
static PFNGLVERTEXATTRIB4DVPROC sglVertexAttrib4dv = nullptr;
static PFNGLVERTEXATTRIB4FPROC sglVertexAttrib4f = nullptr;
static PFNGLVERTEXATTRIB4FVPROC sglVertexAttrib4fv = nullptr;
static PFNGLVERTEXATTRIB4IVPROC sglVertexAttrib4iv = nullptr;
static PFNGLVERTEXATTRIB4SPROC sglVertexAttrib4s = nullptr;
static PFNGLVERTEXATTRIB4SVPROC sglVertexAttrib4sv = nullptr;
static PFNGLVERTEXATTRIB4UBVPROC sglVertexAttrib4ubv = nullptr;
static PFNGLVERTEXATTRIB4UIVPROC sglVertexAttrib4uiv = nullptr;
static PFNGLVERTEXATTRIB4USVPROC sglVertexAttrib4usv = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC sglVertexAttribPointer = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
    if (sglBlendEquationSeparate)
    {
        sglBlendEquationSeparate(modeRGB, modeAlpha);
        ReportGLError("glBlendEquationSeparate");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawBuffers(GLsizei n, const GLenum *bufs)
{
    if (sglDrawBuffers)
    {
        sglDrawBuffers(n, bufs);
        ReportGLError("glDrawBuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
    if (sglStencilOpSeparate)
    {
        sglStencilOpSeparate(face, sfail, dpfail, dppass);
        ReportGLError("glStencilOpSeparate");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
    if (sglStencilFuncSeparate)
    {
        sglStencilFuncSeparate(face, func, ref, mask);
        ReportGLError("glStencilFuncSeparate");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glStencilMaskSeparate(GLenum face, GLuint mask)
{
    if (sglStencilMaskSeparate)
    {
        sglStencilMaskSeparate(face, mask);
        ReportGLError("glStencilMaskSeparate");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glAttachShader(GLuint program, GLuint shader)
{
    if (sglAttachShader)
    {
        sglAttachShader(program, shader);
        ReportGLError("glAttachShader");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindAttribLocation(GLuint program, GLuint index, const GLchar *name)
{
    if (sglBindAttribLocation)
    {
        sglBindAttribLocation(program, index, name);
        ReportGLError("glBindAttribLocation");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCompileShader(GLuint shader)
{
    if (sglCompileShader)
    {
        sglCompileShader(shader);
        ReportGLError("glCompileShader");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLuint APIENTRY glCreateProgram()
{
    GLuint result;
    if (sglCreateProgram)
    {
        result = sglCreateProgram();
        ReportGLError("glCreateProgram");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
GLuint APIENTRY glCreateShader(GLenum type)
{
    GLuint result;
    if (sglCreateShader)
    {
        result = sglCreateShader(type);
        ReportGLError("glCreateShader");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteProgram(GLuint program)
{
    if (sglDeleteProgram)
    {
        sglDeleteProgram(program);
        ReportGLError("glDeleteProgram");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteShader(GLuint shader)
{
    if (sglDeleteShader)
    {
        sglDeleteShader(shader);
        ReportGLError("glDeleteShader");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDetachShader(GLuint program, GLuint shader)
{
    if (sglDetachShader)
    {
        sglDetachShader(program, shader);
        ReportGLError("glDetachShader");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDisableVertexAttribArray(GLuint index)
{
    if (sglDisableVertexAttribArray)
    {
        sglDisableVertexAttribArray(index);
        ReportGLError("glDisableVertexAttribArray");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glEnableVertexAttribArray(GLuint index)
{
    if (sglEnableVertexAttribArray)
    {
        sglEnableVertexAttribArray(index);
        ReportGLError("glEnableVertexAttribArray");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
{
    if (sglGetActiveAttrib)
    {
        sglGetActiveAttrib(program, index, bufSize, length, size, type, name);
        ReportGLError("glGetActiveAttrib");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name)
{
    if (sglGetActiveUniform)
    {
        sglGetActiveUniform(program, index, bufSize, length, size, type, name);
        ReportGLError("glGetActiveUniform");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders)
{
    if (sglGetAttachedShaders)
    {
        sglGetAttachedShaders(program, maxCount, count, shaders);
        ReportGLError("glGetAttachedShaders");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLint APIENTRY glGetAttribLocation(GLuint program, const GLchar *name)
{
    GLint result;
    if (sglGetAttribLocation)
    {
        result = sglGetAttribLocation(program, name);
        ReportGLError("glGetAttribLocation");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramiv(GLuint program, GLenum pname, GLint *params)
{
    if (sglGetProgramiv)
    {
        sglGetProgramiv(program, pname, params);
        ReportGLError("glGetProgramiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    if (sglGetProgramInfoLog)
    {
        sglGetProgramInfoLog(program, bufSize, length, infoLog);
        ReportGLError("glGetProgramInfoLog");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetShaderiv(GLuint shader, GLenum pname, GLint *params)
{
    if (sglGetShaderiv)
    {
        sglGetShaderiv(shader, pname, params);
        ReportGLError("glGetShaderiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    if (sglGetShaderInfoLog)
    {
        sglGetShaderInfoLog(shader, bufSize, length, infoLog);
        ReportGLError("glGetShaderInfoLog");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source)
{
    if (sglGetShaderSource)
    {
        sglGetShaderSource(shader, bufSize, length, source);
        ReportGLError("glGetShaderSource");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLint APIENTRY glGetUniformLocation(GLuint program, const GLchar *name)
{
    GLint result;
    if (sglGetUniformLocation)
    {
        result = sglGetUniformLocation(program, name);
        ReportGLError("glGetUniformLocation");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetUniformfv(GLuint program, GLint location, GLfloat *params)
{
    if (sglGetUniformfv)
    {
        sglGetUniformfv(program, location, params);
        ReportGLError("glGetUniformfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetUniformiv(GLuint program, GLint location, GLint *params)
{
    if (sglGetUniformiv)
    {
        sglGetUniformiv(program, location, params);
        ReportGLError("glGetUniformiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble *params)
{
    if (sglGetVertexAttribdv)
    {
        sglGetVertexAttribdv(index, pname, params);
        ReportGLError("glGetVertexAttribdv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params)
{
    if (sglGetVertexAttribfv)
    {
        sglGetVertexAttribfv(index, pname, params);
        ReportGLError("glGetVertexAttribfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetVertexAttribiv(GLuint index, GLenum pname, GLint *params)
{
    if (sglGetVertexAttribiv)
    {
        sglGetVertexAttribiv(index, pname, params);
        ReportGLError("glGetVertexAttribiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetVertexAttribPointerv(GLuint index, GLenum pname, void **pointer)
{
    if (sglGetVertexAttribPointerv)
    {
        sglGetVertexAttribPointerv(index, pname, pointer);
        ReportGLError("glGetVertexAttribPointerv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsProgram(GLuint program)
{
    GLboolean result;
    if (sglIsProgram)
    {
        result = sglIsProgram(program);
        ReportGLError("glIsProgram");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsShader(GLuint shader)
{
    GLboolean result;
    if (sglIsShader)
    {
        result = sglIsShader(shader);
        ReportGLError("glIsShader");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glLinkProgram(GLuint program)
{
    if (sglLinkProgram)
    {
        sglLinkProgram(program);
        ReportGLError("glLinkProgram");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glShaderSource(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length)
{
    if (sglShaderSource)
    {
        sglShaderSource(shader, count, string, length);
        ReportGLError("glShaderSource");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUseProgram(GLuint program)
{
    if (sglUseProgram)
    {
        sglUseProgram(program);
        ReportGLError("glUseProgram");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1f(GLint location, GLfloat v0)
{
    if (sglUniform1f)
    {
        sglUniform1f(location, v0);
        ReportGLError("glUniform1f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2f(GLint location, GLfloat v0, GLfloat v1)
{
    if (sglUniform2f)
    {
        sglUniform2f(location, v0, v1);
        ReportGLError("glUniform2f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    if (sglUniform3f)
    {
        sglUniform3f(location, v0, v1, v2);
        ReportGLError("glUniform3f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    if (sglUniform4f)
    {
        sglUniform4f(location, v0, v1, v2, v3);
        ReportGLError("glUniform4f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1i(GLint location, GLint v0)
{
    if (sglUniform1i)
    {
        sglUniform1i(location, v0);
        ReportGLError("glUniform1i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2i(GLint location, GLint v0, GLint v1)
{
    if (sglUniform2i)
    {
        sglUniform2i(location, v0, v1);
        ReportGLError("glUniform2i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
    if (sglUniform3i)
    {
        sglUniform3i(location, v0, v1, v2);
        ReportGLError("glUniform3i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    if (sglUniform4i)
    {
        sglUniform4i(location, v0, v1, v2, v3);
        ReportGLError("glUniform4i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1fv(GLint location, GLsizei count, const GLfloat *value)
{
    if (sglUniform1fv)
    {
        sglUniform1fv(location, count, value);
        ReportGLError("glUniform1fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2fv(GLint location, GLsizei count, const GLfloat *value)
{
    if (sglUniform2fv)
    {
        sglUniform2fv(location, count, value);
        ReportGLError("glUniform2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3fv(GLint location, GLsizei count, const GLfloat *value)
{
    if (sglUniform3fv)
    {
        sglUniform3fv(location, count, value);
        ReportGLError("glUniform3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4fv(GLint location, GLsizei count, const GLfloat *value)
{
    if (sglUniform4fv)
    {
        sglUniform4fv(location, count, value);
        ReportGLError("glUniform4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1iv(GLint location, GLsizei count, const GLint *value)
{
    if (sglUniform1iv)
    {
        sglUniform1iv(location, count, value);
        ReportGLError("glUniform1iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2iv(GLint location, GLsizei count, const GLint *value)
{
    if (sglUniform2iv)
    {
        sglUniform2iv(location, count, value);
        ReportGLError("glUniform2iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3iv(GLint location, GLsizei count, const GLint *value)
{
    if (sglUniform3iv)
    {
        sglUniform3iv(location, count, value);
        ReportGLError("glUniform3iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4iv(GLint location, GLsizei count, const GLint *value)
{
    if (sglUniform4iv)
    {
        sglUniform4iv(location, count, value);
        ReportGLError("glUniform4iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix2fv)
    {
        sglUniformMatrix2fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix3fv)
    {
        sglUniformMatrix3fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix4fv)
    {
        sglUniformMatrix4fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glValidateProgram(GLuint program)
{
    if (sglValidateProgram)
    {
        sglValidateProgram(program);
        ReportGLError("glValidateProgram");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib1d(GLuint index, GLdouble x)
{
    if (sglVertexAttrib1d)
    {
        sglVertexAttrib1d(index, x);
        ReportGLError("glVertexAttrib1d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib1dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttrib1dv)
    {
        sglVertexAttrib1dv(index, v);
        ReportGLError("glVertexAttrib1dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib1f(GLuint index, GLfloat x)
{
    if (sglVertexAttrib1f)
    {
        sglVertexAttrib1f(index, x);
        ReportGLError("glVertexAttrib1f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib1fv(GLuint index, const GLfloat *v)
{
    if (sglVertexAttrib1fv)
    {
        sglVertexAttrib1fv(index, v);
        ReportGLError("glVertexAttrib1fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib1s(GLuint index, GLshort x)
{
    if (sglVertexAttrib1s)
    {
        sglVertexAttrib1s(index, x);
        ReportGLError("glVertexAttrib1s");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib1sv(GLuint index, const GLshort *v)
{
    if (sglVertexAttrib1sv)
    {
        sglVertexAttrib1sv(index, v);
        ReportGLError("glVertexAttrib1sv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y)
{
    if (sglVertexAttrib2d)
    {
        sglVertexAttrib2d(index, x, y);
        ReportGLError("glVertexAttrib2d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib2dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttrib2dv)
    {
        sglVertexAttrib2dv(index, v);
        ReportGLError("glVertexAttrib2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y)
{
    if (sglVertexAttrib2f)
    {
        sglVertexAttrib2f(index, x, y);
        ReportGLError("glVertexAttrib2f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib2fv(GLuint index, const GLfloat *v)
{
    if (sglVertexAttrib2fv)
    {
        sglVertexAttrib2fv(index, v);
        ReportGLError("glVertexAttrib2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib2s(GLuint index, GLshort x, GLshort y)
{
    if (sglVertexAttrib2s)
    {
        sglVertexAttrib2s(index, x, y);
        ReportGLError("glVertexAttrib2s");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib2sv(GLuint index, const GLshort *v)
{
    if (sglVertexAttrib2sv)
    {
        sglVertexAttrib2sv(index, v);
        ReportGLError("glVertexAttrib2sv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    if (sglVertexAttrib3d)
    {
        sglVertexAttrib3d(index, x, y, z);
        ReportGLError("glVertexAttrib3d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib3dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttrib3dv)
    {
        sglVertexAttrib3dv(index, v);
        ReportGLError("glVertexAttrib3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    if (sglVertexAttrib3f)
    {
        sglVertexAttrib3f(index, x, y, z);
        ReportGLError("glVertexAttrib3f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib3fv(GLuint index, const GLfloat *v)
{
    if (sglVertexAttrib3fv)
    {
        sglVertexAttrib3fv(index, v);
        ReportGLError("glVertexAttrib3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z)
{
    if (sglVertexAttrib3s)
    {
        sglVertexAttrib3s(index, x, y, z);
        ReportGLError("glVertexAttrib3s");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib3sv(GLuint index, const GLshort *v)
{
    if (sglVertexAttrib3sv)
    {
        sglVertexAttrib3sv(index, v);
        ReportGLError("glVertexAttrib3sv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4Nbv(GLuint index, const GLbyte *v)
{
    if (sglVertexAttrib4Nbv)
    {
        sglVertexAttrib4Nbv(index, v);
        ReportGLError("glVertexAttrib4Nbv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4Niv(GLuint index, const GLint *v)
{
    if (sglVertexAttrib4Niv)
    {
        sglVertexAttrib4Niv(index, v);
        ReportGLError("glVertexAttrib4Niv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4Nsv(GLuint index, const GLshort *v)
{
    if (sglVertexAttrib4Nsv)
    {
        sglVertexAttrib4Nsv(index, v);
        ReportGLError("glVertexAttrib4Nsv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
    if (sglVertexAttrib4Nub)
    {
        sglVertexAttrib4Nub(index, x, y, z, w);
        ReportGLError("glVertexAttrib4Nub");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4Nubv(GLuint index, const GLubyte *v)
{
    if (sglVertexAttrib4Nubv)
    {
        sglVertexAttrib4Nubv(index, v);
        ReportGLError("glVertexAttrib4Nubv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4Nuiv(GLuint index, const GLuint *v)
{
    if (sglVertexAttrib4Nuiv)
    {
        sglVertexAttrib4Nuiv(index, v);
        ReportGLError("glVertexAttrib4Nuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4Nusv(GLuint index, const GLushort *v)
{
    if (sglVertexAttrib4Nusv)
    {
        sglVertexAttrib4Nusv(index, v);
        ReportGLError("glVertexAttrib4Nusv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4bv(GLuint index, const GLbyte *v)
{
    if (sglVertexAttrib4bv)
    {
        sglVertexAttrib4bv(index, v);
        ReportGLError("glVertexAttrib4bv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    if (sglVertexAttrib4d)
    {
        sglVertexAttrib4d(index, x, y, z, w);
        ReportGLError("glVertexAttrib4d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttrib4dv)
    {
        sglVertexAttrib4dv(index, v);
        ReportGLError("glVertexAttrib4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    if (sglVertexAttrib4f)
    {
        sglVertexAttrib4f(index, x, y, z, w);
        ReportGLError("glVertexAttrib4f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4fv(GLuint index, const GLfloat *v)
{
    if (sglVertexAttrib4fv)
    {
        sglVertexAttrib4fv(index, v);
        ReportGLError("glVertexAttrib4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4iv(GLuint index, const GLint *v)
{
    if (sglVertexAttrib4iv)
    {
        sglVertexAttrib4iv(index, v);
        ReportGLError("glVertexAttrib4iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
    if (sglVertexAttrib4s)
    {
        sglVertexAttrib4s(index, x, y, z, w);
        ReportGLError("glVertexAttrib4s");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4sv(GLuint index, const GLshort *v)
{
    if (sglVertexAttrib4sv)
    {
        sglVertexAttrib4sv(index, v);
        ReportGLError("glVertexAttrib4sv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4ubv(GLuint index, const GLubyte *v)
{
    if (sglVertexAttrib4ubv)
    {
        sglVertexAttrib4ubv(index, v);
        ReportGLError("glVertexAttrib4ubv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4uiv(GLuint index, const GLuint *v)
{
    if (sglVertexAttrib4uiv)
    {
        sglVertexAttrib4uiv(index, v);
        ReportGLError("glVertexAttrib4uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttrib4usv(GLuint index, const GLushort *v)
{
    if (sglVertexAttrib4usv)
    {
        sglVertexAttrib4usv(index, v);
        ReportGLError("glVertexAttrib4usv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
    if (sglVertexAttribPointer)
    {
        sglVertexAttribPointer(index, size, type, normalized, stride, pointer);
        ReportGLError("glVertexAttribPointer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_2_0()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_2_0)
    {
        GetOpenGLFunction("glBlendEquationSeparate", sglBlendEquationSeparate);
        GetOpenGLFunction("glDrawBuffers", sglDrawBuffers);
        GetOpenGLFunction("glStencilOpSeparate", sglStencilOpSeparate);
        GetOpenGLFunction("glStencilFuncSeparate", sglStencilFuncSeparate);
        GetOpenGLFunction("glStencilMaskSeparate", sglStencilMaskSeparate);
        GetOpenGLFunction("glAttachShader", sglAttachShader);
        GetOpenGLFunction("glBindAttribLocation", sglBindAttribLocation);
        GetOpenGLFunction("glCompileShader", sglCompileShader);
        GetOpenGLFunction("glCreateProgram", sglCreateProgram);
        GetOpenGLFunction("glCreateShader", sglCreateShader);
        GetOpenGLFunction("glDeleteProgram", sglDeleteProgram);
        GetOpenGLFunction("glDeleteShader", sglDeleteShader);
        GetOpenGLFunction("glDetachShader", sglDetachShader);
        GetOpenGLFunction("glDisableVertexAttribArray", sglDisableVertexAttribArray);
        GetOpenGLFunction("glEnableVertexAttribArray", sglEnableVertexAttribArray);
        GetOpenGLFunction("glGetActiveAttrib", sglGetActiveAttrib);
        GetOpenGLFunction("glGetActiveUniform", sglGetActiveUniform);
        GetOpenGLFunction("glGetAttachedShaders", sglGetAttachedShaders);
        GetOpenGLFunction("glGetAttribLocation", sglGetAttribLocation);
        GetOpenGLFunction("glGetProgramiv", sglGetProgramiv);
        GetOpenGLFunction("glGetProgramInfoLog", sglGetProgramInfoLog);
        GetOpenGLFunction("glGetShaderiv", sglGetShaderiv);
        GetOpenGLFunction("glGetShaderInfoLog", sglGetShaderInfoLog);
        GetOpenGLFunction("glGetShaderSource", sglGetShaderSource);
        GetOpenGLFunction("glGetUniformLocation", sglGetUniformLocation);
        GetOpenGLFunction("glGetUniformfv", sglGetUniformfv);
        GetOpenGLFunction("glGetUniformiv", sglGetUniformiv);
        GetOpenGLFunction("glGetVertexAttribdv", sglGetVertexAttribdv);
        GetOpenGLFunction("glGetVertexAttribfv", sglGetVertexAttribfv);
        GetOpenGLFunction("glGetVertexAttribiv", sglGetVertexAttribiv);
        GetOpenGLFunction("glGetVertexAttribPointerv", sglGetVertexAttribPointerv);
        GetOpenGLFunction("glIsProgram", sglIsProgram);
        GetOpenGLFunction("glIsShader", sglIsShader);
        GetOpenGLFunction("glLinkProgram", sglLinkProgram);
        GetOpenGLFunction("glShaderSource", sglShaderSource);
        GetOpenGLFunction("glUseProgram", sglUseProgram);
        GetOpenGLFunction("glUniform1f", sglUniform1f);
        GetOpenGLFunction("glUniform2f", sglUniform2f);
        GetOpenGLFunction("glUniform3f", sglUniform3f);
        GetOpenGLFunction("glUniform4f", sglUniform4f);
        GetOpenGLFunction("glUniform1i", sglUniform1i);
        GetOpenGLFunction("glUniform2i", sglUniform2i);
        GetOpenGLFunction("glUniform3i", sglUniform3i);
        GetOpenGLFunction("glUniform4i", sglUniform4i);
        GetOpenGLFunction("glUniform1fv", sglUniform1fv);
        GetOpenGLFunction("glUniform2fv", sglUniform2fv);
        GetOpenGLFunction("glUniform3fv", sglUniform3fv);
        GetOpenGLFunction("glUniform4fv", sglUniform4fv);
        GetOpenGLFunction("glUniform1iv", sglUniform1iv);
        GetOpenGLFunction("glUniform2iv", sglUniform2iv);
        GetOpenGLFunction("glUniform3iv", sglUniform3iv);
        GetOpenGLFunction("glUniform4iv", sglUniform4iv);
        GetOpenGLFunction("glUniformMatrix2fv", sglUniformMatrix2fv);
        GetOpenGLFunction("glUniformMatrix3fv", sglUniformMatrix3fv);
        GetOpenGLFunction("glUniformMatrix4fv", sglUniformMatrix4fv);
        GetOpenGLFunction("glValidateProgram", sglValidateProgram);
        GetOpenGLFunction("glVertexAttrib1d", sglVertexAttrib1d);
        GetOpenGLFunction("glVertexAttrib1dv", sglVertexAttrib1dv);
        GetOpenGLFunction("glVertexAttrib1f", sglVertexAttrib1f);
        GetOpenGLFunction("glVertexAttrib1fv", sglVertexAttrib1fv);
        GetOpenGLFunction("glVertexAttrib1s", sglVertexAttrib1s);
        GetOpenGLFunction("glVertexAttrib1sv", sglVertexAttrib1sv);
        GetOpenGLFunction("glVertexAttrib2d", sglVertexAttrib2d);
        GetOpenGLFunction("glVertexAttrib2dv", sglVertexAttrib2dv);
        GetOpenGLFunction("glVertexAttrib2f", sglVertexAttrib2f);
        GetOpenGLFunction("glVertexAttrib2fv", sglVertexAttrib2fv);
        GetOpenGLFunction("glVertexAttrib2s", sglVertexAttrib2s);
        GetOpenGLFunction("glVertexAttrib2sv", sglVertexAttrib2sv);
        GetOpenGLFunction("glVertexAttrib3d", sglVertexAttrib3d);
        GetOpenGLFunction("glVertexAttrib3dv", sglVertexAttrib3dv);
        GetOpenGLFunction("glVertexAttrib3f", sglVertexAttrib3f);
        GetOpenGLFunction("glVertexAttrib3fv", sglVertexAttrib3fv);
        GetOpenGLFunction("glVertexAttrib3s", sglVertexAttrib3s);
        GetOpenGLFunction("glVertexAttrib3sv", sglVertexAttrib3sv);
        GetOpenGLFunction("glVertexAttrib4Nbv", sglVertexAttrib4Nbv);
        GetOpenGLFunction("glVertexAttrib4Niv", sglVertexAttrib4Niv);
        GetOpenGLFunction("glVertexAttrib4Nsv", sglVertexAttrib4Nsv);
        GetOpenGLFunction("glVertexAttrib4Nub", sglVertexAttrib4Nub);
        GetOpenGLFunction("glVertexAttrib4Nubv", sglVertexAttrib4Nubv);
        GetOpenGLFunction("glVertexAttrib4Nuiv", sglVertexAttrib4Nuiv);
        GetOpenGLFunction("glVertexAttrib4Nusv", sglVertexAttrib4Nusv);
        GetOpenGLFunction("glVertexAttrib4bv", sglVertexAttrib4bv);
        GetOpenGLFunction("glVertexAttrib4d", sglVertexAttrib4d);
        GetOpenGLFunction("glVertexAttrib4dv", sglVertexAttrib4dv);
        GetOpenGLFunction("glVertexAttrib4f", sglVertexAttrib4f);
        GetOpenGLFunction("glVertexAttrib4fv", sglVertexAttrib4fv);
        GetOpenGLFunction("glVertexAttrib4iv", sglVertexAttrib4iv);
        GetOpenGLFunction("glVertexAttrib4s", sglVertexAttrib4s);
        GetOpenGLFunction("glVertexAttrib4sv", sglVertexAttrib4sv);
        GetOpenGLFunction("glVertexAttrib4ubv", sglVertexAttrib4ubv);
        GetOpenGLFunction("glVertexAttrib4uiv", sglVertexAttrib4uiv);
        GetOpenGLFunction("glVertexAttrib4usv", sglVertexAttrib4usv);
        GetOpenGLFunction("glVertexAttribPointer", sglVertexAttribPointer);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_2_1
//----------------------------------------------------------------------------
static PFNGLUNIFORMMATRIX2X3FVPROC sglUniformMatrix2x3fv = nullptr;
static PFNGLUNIFORMMATRIX3X2FVPROC sglUniformMatrix3x2fv = nullptr;
static PFNGLUNIFORMMATRIX2X4FVPROC sglUniformMatrix2x4fv = nullptr;
static PFNGLUNIFORMMATRIX4X2FVPROC sglUniformMatrix4x2fv = nullptr;
static PFNGLUNIFORMMATRIX3X4FVPROC sglUniformMatrix3x4fv = nullptr;
static PFNGLUNIFORMMATRIX4X3FVPROC sglUniformMatrix4x3fv = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix2x3fv)
    {
        sglUniformMatrix2x3fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix2x3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix3x2fv)
    {
        sglUniformMatrix3x2fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix3x2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix2x4fv)
    {
        sglUniformMatrix2x4fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix2x4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix4x2fv)
    {
        sglUniformMatrix4x2fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix4x2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix3x4fv)
    {
        sglUniformMatrix3x4fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix3x4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglUniformMatrix4x3fv)
    {
        sglUniformMatrix4x3fv(location, count, transpose, value);
        ReportGLError("glUniformMatrix4x3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_2_1()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_2_1)
    {
        GetOpenGLFunction("glUniformMatrix2x3fv", sglUniformMatrix2x3fv);
        GetOpenGLFunction("glUniformMatrix3x2fv", sglUniformMatrix3x2fv);
        GetOpenGLFunction("glUniformMatrix2x4fv", sglUniformMatrix2x4fv);
        GetOpenGLFunction("glUniformMatrix4x2fv", sglUniformMatrix4x2fv);
        GetOpenGLFunction("glUniformMatrix3x4fv", sglUniformMatrix3x4fv);
        GetOpenGLFunction("glUniformMatrix4x3fv", sglUniformMatrix4x3fv);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_3_0
//----------------------------------------------------------------------------
static PFNGLCOLORMASKIPROC sglColorMaski = nullptr;
static PFNGLGETBOOLEANI_VPROC sglGetBooleani_v = nullptr;
static PFNGLGETINTEGERI_VPROC sglGetIntegeri_v = nullptr;
static PFNGLENABLEIPROC sglEnablei = nullptr;
static PFNGLDISABLEIPROC sglDisablei = nullptr;
static PFNGLISENABLEDIPROC sglIsEnabledi = nullptr;
static PFNGLBEGINTRANSFORMFEEDBACKPROC sglBeginTransformFeedback = nullptr;
static PFNGLENDTRANSFORMFEEDBACKPROC sglEndTransformFeedback = nullptr;
static PFNGLBINDBUFFERRANGEPROC sglBindBufferRange = nullptr;
static PFNGLBINDBUFFERBASEPROC sglBindBufferBase = nullptr;
static PFNGLTRANSFORMFEEDBACKVARYINGSPROC sglTransformFeedbackVaryings = nullptr;
static PFNGLGETTRANSFORMFEEDBACKVARYINGPROC sglGetTransformFeedbackVarying = nullptr;
static PFNGLCLAMPCOLORPROC sglClampColor = nullptr;
static PFNGLBEGINCONDITIONALRENDERPROC sglBeginConditionalRender = nullptr;
static PFNGLENDCONDITIONALRENDERPROC sglEndConditionalRender = nullptr;
static PFNGLVERTEXATTRIBIPOINTERPROC sglVertexAttribIPointer = nullptr;
static PFNGLGETVERTEXATTRIBIIVPROC sglGetVertexAttribIiv = nullptr;
static PFNGLGETVERTEXATTRIBIUIVPROC sglGetVertexAttribIuiv = nullptr;
static PFNGLVERTEXATTRIBI1IPROC sglVertexAttribI1i = nullptr;
static PFNGLVERTEXATTRIBI2IPROC sglVertexAttribI2i = nullptr;
static PFNGLVERTEXATTRIBI3IPROC sglVertexAttribI3i = nullptr;
static PFNGLVERTEXATTRIBI4IPROC sglVertexAttribI4i = nullptr;
static PFNGLVERTEXATTRIBI1UIPROC sglVertexAttribI1ui = nullptr;
static PFNGLVERTEXATTRIBI2UIPROC sglVertexAttribI2ui = nullptr;
static PFNGLVERTEXATTRIBI3UIPROC sglVertexAttribI3ui = nullptr;
static PFNGLVERTEXATTRIBI4UIPROC sglVertexAttribI4ui = nullptr;
static PFNGLVERTEXATTRIBI1IVPROC sglVertexAttribI1iv = nullptr;
static PFNGLVERTEXATTRIBI2IVPROC sglVertexAttribI2iv = nullptr;
static PFNGLVERTEXATTRIBI3IVPROC sglVertexAttribI3iv = nullptr;
static PFNGLVERTEXATTRIBI4IVPROC sglVertexAttribI4iv = nullptr;
static PFNGLVERTEXATTRIBI1UIVPROC sglVertexAttribI1uiv = nullptr;
static PFNGLVERTEXATTRIBI2UIVPROC sglVertexAttribI2uiv = nullptr;
static PFNGLVERTEXATTRIBI3UIVPROC sglVertexAttribI3uiv = nullptr;
static PFNGLVERTEXATTRIBI4UIVPROC sglVertexAttribI4uiv = nullptr;
static PFNGLVERTEXATTRIBI4BVPROC sglVertexAttribI4bv = nullptr;
static PFNGLVERTEXATTRIBI4SVPROC sglVertexAttribI4sv = nullptr;
static PFNGLVERTEXATTRIBI4UBVPROC sglVertexAttribI4ubv = nullptr;
static PFNGLVERTEXATTRIBI4USVPROC sglVertexAttribI4usv = nullptr;
static PFNGLGETUNIFORMUIVPROC sglGetUniformuiv = nullptr;
static PFNGLBINDFRAGDATALOCATIONPROC sglBindFragDataLocation = nullptr;
static PFNGLGETFRAGDATALOCATIONPROC sglGetFragDataLocation = nullptr;
static PFNGLUNIFORM1UIPROC sglUniform1ui = nullptr;
static PFNGLUNIFORM2UIPROC sglUniform2ui = nullptr;
static PFNGLUNIFORM3UIPROC sglUniform3ui = nullptr;
static PFNGLUNIFORM4UIPROC sglUniform4ui = nullptr;
static PFNGLUNIFORM1UIVPROC sglUniform1uiv = nullptr;
static PFNGLUNIFORM2UIVPROC sglUniform2uiv = nullptr;
static PFNGLUNIFORM3UIVPROC sglUniform3uiv = nullptr;
static PFNGLUNIFORM4UIVPROC sglUniform4uiv = nullptr;
static PFNGLTEXPARAMETERIIVPROC sglTexParameterIiv = nullptr;
static PFNGLTEXPARAMETERIUIVPROC sglTexParameterIuiv = nullptr;
static PFNGLGETTEXPARAMETERIIVPROC sglGetTexParameterIiv = nullptr;
static PFNGLGETTEXPARAMETERIUIVPROC sglGetTexParameterIuiv = nullptr;
static PFNGLCLEARBUFFERIVPROC sglClearBufferiv = nullptr;
static PFNGLCLEARBUFFERUIVPROC sglClearBufferuiv = nullptr;
static PFNGLCLEARBUFFERFVPROC sglClearBufferfv = nullptr;
static PFNGLCLEARBUFFERFIPROC sglClearBufferfi = nullptr;
static PFNGLGETSTRINGIPROC sglGetStringi = nullptr;
static PFNGLISRENDERBUFFERPROC sglIsRenderbuffer = nullptr;
static PFNGLBINDRENDERBUFFERPROC sglBindRenderbuffer = nullptr;
static PFNGLDELETERENDERBUFFERSPROC sglDeleteRenderbuffers = nullptr;
static PFNGLGENRENDERBUFFERSPROC sglGenRenderbuffers = nullptr;
static PFNGLRENDERBUFFERSTORAGEPROC sglRenderbufferStorage = nullptr;
static PFNGLGETRENDERBUFFERPARAMETERIVPROC sglGetRenderbufferParameteriv = nullptr;
static PFNGLISFRAMEBUFFERPROC sglIsFramebuffer = nullptr;
static PFNGLBINDFRAMEBUFFERPROC sglBindFramebuffer = nullptr;
static PFNGLDELETEFRAMEBUFFERSPROC sglDeleteFramebuffers = nullptr;
static PFNGLGENFRAMEBUFFERSPROC sglGenFramebuffers = nullptr;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC sglCheckFramebufferStatus = nullptr;
static PFNGLFRAMEBUFFERTEXTURE1DPROC sglFramebufferTexture1D = nullptr;
static PFNGLFRAMEBUFFERTEXTURE2DPROC sglFramebufferTexture2D = nullptr;
static PFNGLFRAMEBUFFERTEXTURE3DPROC sglFramebufferTexture3D = nullptr;
static PFNGLFRAMEBUFFERRENDERBUFFERPROC sglFramebufferRenderbuffer = nullptr;
static PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC sglGetFramebufferAttachmentParameteriv = nullptr;
static PFNGLGENERATEMIPMAPPROC sglGenerateMipmap = nullptr;
static PFNGLBLITFRAMEBUFFERPROC sglBlitFramebuffer = nullptr;
static PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC sglRenderbufferStorageMultisample = nullptr;
static PFNGLFRAMEBUFFERTEXTURELAYERPROC sglFramebufferTextureLayer = nullptr;
static PFNGLMAPBUFFERRANGEPROC sglMapBufferRange = nullptr;
static PFNGLFLUSHMAPPEDBUFFERRANGEPROC sglFlushMappedBufferRange = nullptr;
static PFNGLBINDVERTEXARRAYPROC sglBindVertexArray = nullptr;
static PFNGLDELETEVERTEXARRAYSPROC sglDeleteVertexArrays = nullptr;
static PFNGLGENVERTEXARRAYSPROC sglGenVertexArrays = nullptr;
static PFNGLISVERTEXARRAYPROC sglIsVertexArray = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
    if (sglColorMaski)
    {
        sglColorMaski(index, r, g, b, a);
        ReportGLError("glColorMaski");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetBooleani_v(GLenum target, GLuint index, GLboolean *data)
{
    if (sglGetBooleani_v)
    {
        sglGetBooleani_v(target, index, data);
        ReportGLError("glGetBooleani_v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetIntegeri_v(GLenum target, GLuint index, GLint *data)
{
    if (sglGetIntegeri_v)
    {
        sglGetIntegeri_v(target, index, data);
        ReportGLError("glGetIntegeri_v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glEnablei(GLenum target, GLuint index)
{
    if (sglEnablei)
    {
        sglEnablei(target, index);
        ReportGLError("glEnablei");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDisablei(GLenum target, GLuint index)
{
    if (sglDisablei)
    {
        sglDisablei(target, index);
        ReportGLError("glDisablei");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsEnabledi(GLenum target, GLuint index)
{
    GLboolean result;
    if (sglIsEnabledi)
    {
        result = sglIsEnabledi(target, index);
        ReportGLError("glIsEnabledi");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glBeginTransformFeedback(GLenum primitiveMode)
{
    if (sglBeginTransformFeedback)
    {
        sglBeginTransformFeedback(primitiveMode);
        ReportGLError("glBeginTransformFeedback");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glEndTransformFeedback()
{
    if (sglEndTransformFeedback)
    {
        sglEndTransformFeedback();
        ReportGLError("glEndTransformFeedback");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
    if (sglBindBufferRange)
    {
        sglBindBufferRange(target, index, buffer, offset, size);
        ReportGLError("glBindBufferRange");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindBufferBase(GLenum target, GLuint index, GLuint buffer)
{
    if (sglBindBufferBase)
    {
        sglBindBufferBase(target, index, buffer);
        ReportGLError("glBindBufferBase");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode)
{
    if (sglTransformFeedbackVaryings)
    {
        sglTransformFeedbackVaryings(program, count, varyings, bufferMode);
        ReportGLError("glTransformFeedbackVaryings");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name)
{
    if (sglGetTransformFeedbackVarying)
    {
        sglGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
        ReportGLError("glGetTransformFeedbackVarying");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClampColor(GLenum target, GLenum clamp)
{
    if (sglClampColor)
    {
        sglClampColor(target, clamp);
        ReportGLError("glClampColor");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBeginConditionalRender(GLuint id, GLenum mode)
{
    if (sglBeginConditionalRender)
    {
        sglBeginConditionalRender(id, mode);
        ReportGLError("glBeginConditionalRender");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glEndConditionalRender()
{
    if (sglEndConditionalRender)
    {
        sglEndConditionalRender();
        ReportGLError("glEndConditionalRender");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)
{
    if (sglVertexAttribIPointer)
    {
        sglVertexAttribIPointer(index, size, type, stride, pointer);
        ReportGLError("glVertexAttribIPointer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetVertexAttribIiv(GLuint index, GLenum pname, GLint *params)
{
    if (sglGetVertexAttribIiv)
    {
        sglGetVertexAttribIiv(index, pname, params);
        ReportGLError("glGetVertexAttribIiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint *params)
{
    if (sglGetVertexAttribIuiv)
    {
        sglGetVertexAttribIuiv(index, pname, params);
        ReportGLError("glGetVertexAttribIuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI1i(GLuint index, GLint x)
{
    if (sglVertexAttribI1i)
    {
        sglVertexAttribI1i(index, x);
        ReportGLError("glVertexAttribI1i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI2i(GLuint index, GLint x, GLint y)
{
    if (sglVertexAttribI2i)
    {
        sglVertexAttribI2i(index, x, y);
        ReportGLError("glVertexAttribI2i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z)
{
    if (sglVertexAttribI3i)
    {
        sglVertexAttribI3i(index, x, y, z);
        ReportGLError("glVertexAttribI3i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
    if (sglVertexAttribI4i)
    {
        sglVertexAttribI4i(index, x, y, z, w);
        ReportGLError("glVertexAttribI4i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI1ui(GLuint index, GLuint x)
{
    if (sglVertexAttribI1ui)
    {
        sglVertexAttribI1ui(index, x);
        ReportGLError("glVertexAttribI1ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI2ui(GLuint index, GLuint x, GLuint y)
{
    if (sglVertexAttribI2ui)
    {
        sglVertexAttribI2ui(index, x, y);
        ReportGLError("glVertexAttribI2ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z)
{
    if (sglVertexAttribI3ui)
    {
        sglVertexAttribI3ui(index, x, y, z);
        ReportGLError("glVertexAttribI3ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
    if (sglVertexAttribI4ui)
    {
        sglVertexAttribI4ui(index, x, y, z, w);
        ReportGLError("glVertexAttribI4ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI1iv(GLuint index, const GLint *v)
{
    if (sglVertexAttribI1iv)
    {
        sglVertexAttribI1iv(index, v);
        ReportGLError("glVertexAttribI1iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI2iv(GLuint index, const GLint *v)
{
    if (sglVertexAttribI2iv)
    {
        sglVertexAttribI2iv(index, v);
        ReportGLError("glVertexAttribI2iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI3iv(GLuint index, const GLint *v)
{
    if (sglVertexAttribI3iv)
    {
        sglVertexAttribI3iv(index, v);
        ReportGLError("glVertexAttribI3iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4iv(GLuint index, const GLint *v)
{
    if (sglVertexAttribI4iv)
    {
        sglVertexAttribI4iv(index, v);
        ReportGLError("glVertexAttribI4iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI1uiv(GLuint index, const GLuint *v)
{
    if (sglVertexAttribI1uiv)
    {
        sglVertexAttribI1uiv(index, v);
        ReportGLError("glVertexAttribI1uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI2uiv(GLuint index, const GLuint *v)
{
    if (sglVertexAttribI2uiv)
    {
        sglVertexAttribI2uiv(index, v);
        ReportGLError("glVertexAttribI2uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI3uiv(GLuint index, const GLuint *v)
{
    if (sglVertexAttribI3uiv)
    {
        sglVertexAttribI3uiv(index, v);
        ReportGLError("glVertexAttribI3uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4uiv(GLuint index, const GLuint *v)
{
    if (sglVertexAttribI4uiv)
    {
        sglVertexAttribI4uiv(index, v);
        ReportGLError("glVertexAttribI4uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4bv(GLuint index, const GLbyte *v)
{
    if (sglVertexAttribI4bv)
    {
        sglVertexAttribI4bv(index, v);
        ReportGLError("glVertexAttribI4bv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4sv(GLuint index, const GLshort *v)
{
    if (sglVertexAttribI4sv)
    {
        sglVertexAttribI4sv(index, v);
        ReportGLError("glVertexAttribI4sv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4ubv(GLuint index, const GLubyte *v)
{
    if (sglVertexAttribI4ubv)
    {
        sglVertexAttribI4ubv(index, v);
        ReportGLError("glVertexAttribI4ubv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribI4usv(GLuint index, const GLushort *v)
{
    if (sglVertexAttribI4usv)
    {
        sglVertexAttribI4usv(index, v);
        ReportGLError("glVertexAttribI4usv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetUniformuiv(GLuint program, GLint location, GLuint *params)
{
    if (sglGetUniformuiv)
    {
        sglGetUniformuiv(program, location, params);
        ReportGLError("glGetUniformuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name)
{
    if (sglBindFragDataLocation)
    {
        sglBindFragDataLocation(program, color, name);
        ReportGLError("glBindFragDataLocation");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLint APIENTRY glGetFragDataLocation(GLuint program, const GLchar *name)
{
    GLint result;
    if (sglGetFragDataLocation)
    {
        result = sglGetFragDataLocation(program, name);
        ReportGLError("glGetFragDataLocation");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1ui(GLint location, GLuint v0)
{
    if (sglUniform1ui)
    {
        sglUniform1ui(location, v0);
        ReportGLError("glUniform1ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2ui(GLint location, GLuint v0, GLuint v1)
{
    if (sglUniform2ui)
    {
        sglUniform2ui(location, v0, v1);
        ReportGLError("glUniform2ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
    if (sglUniform3ui)
    {
        sglUniform3ui(location, v0, v1, v2);
        ReportGLError("glUniform3ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    if (sglUniform4ui)
    {
        sglUniform4ui(location, v0, v1, v2, v3);
        ReportGLError("glUniform4ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1uiv(GLint location, GLsizei count, const GLuint *value)
{
    if (sglUniform1uiv)
    {
        sglUniform1uiv(location, count, value);
        ReportGLError("glUniform1uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2uiv(GLint location, GLsizei count, const GLuint *value)
{
    if (sglUniform2uiv)
    {
        sglUniform2uiv(location, count, value);
        ReportGLError("glUniform2uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3uiv(GLint location, GLsizei count, const GLuint *value)
{
    if (sglUniform3uiv)
    {
        sglUniform3uiv(location, count, value);
        ReportGLError("glUniform3uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4uiv(GLint location, GLsizei count, const GLuint *value)
{
    if (sglUniform4uiv)
    {
        sglUniform4uiv(location, count, value);
        ReportGLError("glUniform4uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexParameterIiv(GLenum target, GLenum pname, const GLint *params)
{
    if (sglTexParameterIiv)
    {
        sglTexParameterIiv(target, pname, params);
        ReportGLError("glTexParameterIiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexParameterIuiv(GLenum target, GLenum pname, const GLuint *params)
{
    if (sglTexParameterIuiv)
    {
        sglTexParameterIuiv(target, pname, params);
        ReportGLError("glTexParameterIuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetTexParameterIiv(GLenum target, GLenum pname, GLint *params)
{
    if (sglGetTexParameterIiv)
    {
        sglGetTexParameterIiv(target, pname, params);
        ReportGLError("glGetTexParameterIiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint *params)
{
    if (sglGetTexParameterIuiv)
    {
        sglGetTexParameterIuiv(target, pname, params);
        ReportGLError("glGetTexParameterIuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint *value)
{
    if (sglClearBufferiv)
    {
        sglClearBufferiv(buffer, drawbuffer, value);
        ReportGLError("glClearBufferiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint *value)
{
    if (sglClearBufferuiv)
    {
        sglClearBufferuiv(buffer, drawbuffer, value);
        ReportGLError("glClearBufferuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat *value)
{
    if (sglClearBufferfv)
    {
        sglClearBufferfv(buffer, drawbuffer, value);
        ReportGLError("glClearBufferfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)
{
    if (sglClearBufferfi)
    {
        sglClearBufferfi(buffer, drawbuffer, depth, stencil);
        ReportGLError("glClearBufferfi");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
const GLubyte * APIENTRY glGetStringi(GLenum name, GLuint index)
{
    const GLubyte * result;
    if (sglGetStringi)
    {
        result = sglGetStringi(name, index);
        ReportGLError("glGetStringi");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsRenderbuffer(GLuint renderbuffer)
{
    GLboolean result;
    if (sglIsRenderbuffer)
    {
        result = sglIsRenderbuffer(renderbuffer);
        ReportGLError("glIsRenderbuffer");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
    if (sglBindRenderbuffer)
    {
        sglBindRenderbuffer(target, renderbuffer);
        ReportGLError("glBindRenderbuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteRenderbuffers(GLsizei n, const GLuint *renderbuffers)
{
    if (sglDeleteRenderbuffers)
    {
        sglDeleteRenderbuffers(n, renderbuffers);
        ReportGLError("glDeleteRenderbuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenRenderbuffers(GLsizei n, GLuint *renderbuffers)
{
    if (sglGenRenderbuffers)
    {
        sglGenRenderbuffers(n, renderbuffers);
        ReportGLError("glGenRenderbuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    if (sglRenderbufferStorage)
    {
        sglRenderbufferStorage(target, internalformat, width, height);
        ReportGLError("glRenderbufferStorage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint *params)
{
    if (sglGetRenderbufferParameteriv)
    {
        sglGetRenderbufferParameteriv(target, pname, params);
        ReportGLError("glGetRenderbufferParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsFramebuffer(GLuint framebuffer)
{
    GLboolean result;
    if (sglIsFramebuffer)
    {
        result = sglIsFramebuffer(framebuffer);
        ReportGLError("glIsFramebuffer");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glBindFramebuffer(GLenum target, GLuint framebuffer)
{
    if (sglBindFramebuffer)
    {
        sglBindFramebuffer(target, framebuffer);
        ReportGLError("glBindFramebuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteFramebuffers(GLsizei n, const GLuint *framebuffers)
{
    if (sglDeleteFramebuffers)
    {
        sglDeleteFramebuffers(n, framebuffers);
        ReportGLError("glDeleteFramebuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenFramebuffers(GLsizei n, GLuint *framebuffers)
{
    if (sglGenFramebuffers)
    {
        sglGenFramebuffers(n, framebuffers);
        ReportGLError("glGenFramebuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLenum APIENTRY glCheckFramebufferStatus(GLenum target)
{
    GLenum result;
    if (sglCheckFramebufferStatus)
    {
        result = sglCheckFramebufferStatus(target);
        ReportGLError("glCheckFramebufferStatus");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    if (sglFramebufferTexture1D)
    {
        sglFramebufferTexture1D(target, attachment, textarget, texture, level);
        ReportGLError("glFramebufferTexture1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    if (sglFramebufferTexture2D)
    {
        sglFramebufferTexture2D(target, attachment, textarget, texture, level);
        ReportGLError("glFramebufferTexture2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
    if (sglFramebufferTexture3D)
    {
        sglFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
        ReportGLError("glFramebufferTexture3D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    if (sglFramebufferRenderbuffer)
    {
        sglFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
        ReportGLError("glFramebufferRenderbuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint *params)
{
    if (sglGetFramebufferAttachmentParameteriv)
    {
        sglGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
        ReportGLError("glGetFramebufferAttachmentParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenerateMipmap(GLenum target)
{
    if (sglGenerateMipmap)
    {
        sglGenerateMipmap(target);
        ReportGLError("glGenerateMipmap");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
    if (sglBlitFramebuffer)
    {
        sglBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
        ReportGLError("glBlitFramebuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
    if (sglRenderbufferStorageMultisample)
    {
        sglRenderbufferStorageMultisample(target, samples, internalformat, width, height);
        ReportGLError("glRenderbufferStorageMultisample");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
    if (sglFramebufferTextureLayer)
    {
        sglFramebufferTextureLayer(target, attachment, texture, level, layer);
        ReportGLError("glFramebufferTextureLayer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void * APIENTRY glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access)
{
    void * result;
    if (sglMapBufferRange)
    {
        result = sglMapBufferRange(target, offset, length, access);
        ReportGLError("glMapBufferRange");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
    if (sglFlushMappedBufferRange)
    {
        sglFlushMappedBufferRange(target, offset, length);
        ReportGLError("glFlushMappedBufferRange");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindVertexArray(GLuint array)
{
    if (sglBindVertexArray)
    {
        sglBindVertexArray(array);
        ReportGLError("glBindVertexArray");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
    if (sglDeleteVertexArrays)
    {
        sglDeleteVertexArrays(n, arrays);
        ReportGLError("glDeleteVertexArrays");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    if (sglGenVertexArrays)
    {
        sglGenVertexArrays(n, arrays);
        ReportGLError("glGenVertexArrays");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsVertexArray(GLuint array)
{
    GLboolean result;
    if (sglIsVertexArray)
    {
        result = sglIsVertexArray(array);
        ReportGLError("glIsVertexArray");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_3_0()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_3_0)
    {
        GetOpenGLFunction("glColorMaski", sglColorMaski);
        GetOpenGLFunction("glGetBooleani_v", sglGetBooleani_v);
        GetOpenGLFunction("glGetIntegeri_v", sglGetIntegeri_v);
        GetOpenGLFunction("glEnablei", sglEnablei);
        GetOpenGLFunction("glDisablei", sglDisablei);
        GetOpenGLFunction("glIsEnabledi", sglIsEnabledi);
        GetOpenGLFunction("glBeginTransformFeedback", sglBeginTransformFeedback);
        GetOpenGLFunction("glEndTransformFeedback", sglEndTransformFeedback);
        GetOpenGLFunction("glBindBufferRange", sglBindBufferRange);
        GetOpenGLFunction("glBindBufferBase", sglBindBufferBase);
        GetOpenGLFunction("glTransformFeedbackVaryings", sglTransformFeedbackVaryings);
        GetOpenGLFunction("glGetTransformFeedbackVarying", sglGetTransformFeedbackVarying);
        GetOpenGLFunction("glClampColor", sglClampColor);
        GetOpenGLFunction("glBeginConditionalRender", sglBeginConditionalRender);
        GetOpenGLFunction("glEndConditionalRender", sglEndConditionalRender);
        GetOpenGLFunction("glVertexAttribIPointer", sglVertexAttribIPointer);
        GetOpenGLFunction("glGetVertexAttribIiv", sglGetVertexAttribIiv);
        GetOpenGLFunction("glGetVertexAttribIuiv", sglGetVertexAttribIuiv);
        GetOpenGLFunction("glVertexAttribI1i", sglVertexAttribI1i);
        GetOpenGLFunction("glVertexAttribI2i", sglVertexAttribI2i);
        GetOpenGLFunction("glVertexAttribI3i", sglVertexAttribI3i);
        GetOpenGLFunction("glVertexAttribI4i", sglVertexAttribI4i);
        GetOpenGLFunction("glVertexAttribI1ui", sglVertexAttribI1ui);
        GetOpenGLFunction("glVertexAttribI2ui", sglVertexAttribI2ui);
        GetOpenGLFunction("glVertexAttribI3ui", sglVertexAttribI3ui);
        GetOpenGLFunction("glVertexAttribI4ui", sglVertexAttribI4ui);
        GetOpenGLFunction("glVertexAttribI1iv", sglVertexAttribI1iv);
        GetOpenGLFunction("glVertexAttribI2iv", sglVertexAttribI2iv);
        GetOpenGLFunction("glVertexAttribI3iv", sglVertexAttribI3iv);
        GetOpenGLFunction("glVertexAttribI4iv", sglVertexAttribI4iv);
        GetOpenGLFunction("glVertexAttribI1uiv", sglVertexAttribI1uiv);
        GetOpenGLFunction("glVertexAttribI2uiv", sglVertexAttribI2uiv);
        GetOpenGLFunction("glVertexAttribI3uiv", sglVertexAttribI3uiv);
        GetOpenGLFunction("glVertexAttribI4uiv", sglVertexAttribI4uiv);
        GetOpenGLFunction("glVertexAttribI4bv", sglVertexAttribI4bv);
        GetOpenGLFunction("glVertexAttribI4sv", sglVertexAttribI4sv);
        GetOpenGLFunction("glVertexAttribI4ubv", sglVertexAttribI4ubv);
        GetOpenGLFunction("glVertexAttribI4usv", sglVertexAttribI4usv);
        GetOpenGLFunction("glGetUniformuiv", sglGetUniformuiv);
        GetOpenGLFunction("glBindFragDataLocation", sglBindFragDataLocation);
        GetOpenGLFunction("glGetFragDataLocation", sglGetFragDataLocation);
        GetOpenGLFunction("glUniform1ui", sglUniform1ui);
        GetOpenGLFunction("glUniform2ui", sglUniform2ui);
        GetOpenGLFunction("glUniform3ui", sglUniform3ui);
        GetOpenGLFunction("glUniform4ui", sglUniform4ui);
        GetOpenGLFunction("glUniform1uiv", sglUniform1uiv);
        GetOpenGLFunction("glUniform2uiv", sglUniform2uiv);
        GetOpenGLFunction("glUniform3uiv", sglUniform3uiv);
        GetOpenGLFunction("glUniform4uiv", sglUniform4uiv);
        GetOpenGLFunction("glTexParameterIiv", sglTexParameterIiv);
        GetOpenGLFunction("glTexParameterIuiv", sglTexParameterIuiv);
        GetOpenGLFunction("glGetTexParameterIiv", sglGetTexParameterIiv);
        GetOpenGLFunction("glGetTexParameterIuiv", sglGetTexParameterIuiv);
        GetOpenGLFunction("glClearBufferiv", sglClearBufferiv);
        GetOpenGLFunction("glClearBufferuiv", sglClearBufferuiv);
        GetOpenGLFunction("glClearBufferfv", sglClearBufferfv);
        GetOpenGLFunction("glClearBufferfi", sglClearBufferfi);
        GetOpenGLFunction("glGetStringi", sglGetStringi);
        GetOpenGLFunction("glIsRenderbuffer", sglIsRenderbuffer);
        GetOpenGLFunction("glBindRenderbuffer", sglBindRenderbuffer);
        GetOpenGLFunction("glDeleteRenderbuffers", sglDeleteRenderbuffers);
        GetOpenGLFunction("glGenRenderbuffers", sglGenRenderbuffers);
        GetOpenGLFunction("glRenderbufferStorage", sglRenderbufferStorage);
        GetOpenGLFunction("glGetRenderbufferParameteriv", sglGetRenderbufferParameteriv);
        GetOpenGLFunction("glIsFramebuffer", sglIsFramebuffer);
        GetOpenGLFunction("glBindFramebuffer", sglBindFramebuffer);
        GetOpenGLFunction("glDeleteFramebuffers", sglDeleteFramebuffers);
        GetOpenGLFunction("glGenFramebuffers", sglGenFramebuffers);
        GetOpenGLFunction("glCheckFramebufferStatus", sglCheckFramebufferStatus);
        GetOpenGLFunction("glFramebufferTexture1D", sglFramebufferTexture1D);
        GetOpenGLFunction("glFramebufferTexture2D", sglFramebufferTexture2D);
        GetOpenGLFunction("glFramebufferTexture3D", sglFramebufferTexture3D);
        GetOpenGLFunction("glFramebufferRenderbuffer", sglFramebufferRenderbuffer);
        GetOpenGLFunction("glGetFramebufferAttachmentParameteriv", sglGetFramebufferAttachmentParameteriv);
        GetOpenGLFunction("glGenerateMipmap", sglGenerateMipmap);
        GetOpenGLFunction("glBlitFramebuffer", sglBlitFramebuffer);
        GetOpenGLFunction("glRenderbufferStorageMultisample", sglRenderbufferStorageMultisample);
        GetOpenGLFunction("glFramebufferTextureLayer", sglFramebufferTextureLayer);
        GetOpenGLFunction("glMapBufferRange", sglMapBufferRange);
        GetOpenGLFunction("glFlushMappedBufferRange", sglFlushMappedBufferRange);
        GetOpenGLFunction("glBindVertexArray", sglBindVertexArray);
        GetOpenGLFunction("glDeleteVertexArrays", sglDeleteVertexArrays);
        GetOpenGLFunction("glGenVertexArrays", sglGenVertexArrays);
        GetOpenGLFunction("glIsVertexArray", sglIsVertexArray);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_3_1
//----------------------------------------------------------------------------
static PFNGLDRAWARRAYSINSTANCEDPROC sglDrawArraysInstanced = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDPROC sglDrawElementsInstanced = nullptr;
static PFNGLTEXBUFFERPROC sglTexBuffer = nullptr;
static PFNGLPRIMITIVERESTARTINDEXPROC sglPrimitiveRestartIndex = nullptr;
static PFNGLCOPYBUFFERSUBDATAPROC sglCopyBufferSubData = nullptr;
static PFNGLGETUNIFORMINDICESPROC sglGetUniformIndices = nullptr;
static PFNGLGETACTIVEUNIFORMSIVPROC sglGetActiveUniformsiv = nullptr;
static PFNGLGETACTIVEUNIFORMNAMEPROC sglGetActiveUniformName = nullptr;
static PFNGLGETUNIFORMBLOCKINDEXPROC sglGetUniformBlockIndex = nullptr;
static PFNGLGETACTIVEUNIFORMBLOCKIVPROC sglGetActiveUniformBlockiv = nullptr;
static PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC sglGetActiveUniformBlockName = nullptr;
static PFNGLUNIFORMBLOCKBINDINGPROC sglUniformBlockBinding = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount)
{
    if (sglDrawArraysInstanced)
    {
        sglDrawArraysInstanced(mode, first, count, instancecount);
        ReportGLError("glDrawArraysInstanced");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount)
{
    if (sglDrawElementsInstanced)
    {
        sglDrawElementsInstanced(mode, count, type, indices, instancecount);
        ReportGLError("glDrawElementsInstanced");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer)
{
    if (sglTexBuffer)
    {
        sglTexBuffer(target, internalformat, buffer);
        ReportGLError("glTexBuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPrimitiveRestartIndex(GLuint index)
{
    if (sglPrimitiveRestartIndex)
    {
        sglPrimitiveRestartIndex(index);
        ReportGLError("glPrimitiveRestartIndex");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
    if (sglCopyBufferSubData)
    {
        sglCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
        ReportGLError("glCopyBufferSubData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar *const*uniformNames, GLuint *uniformIndices)
{
    if (sglGetUniformIndices)
    {
        sglGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
        ReportGLError("glGetUniformIndices");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint *uniformIndices, GLenum pname, GLint *params)
{
    if (sglGetActiveUniformsiv)
    {
        sglGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
        ReportGLError("glGetActiveUniformsiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformName)
{
    if (sglGetActiveUniformName)
    {
        sglGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
        ReportGLError("glGetActiveUniformName");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLuint APIENTRY glGetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName)
{
    GLuint result;
    if (sglGetUniformBlockIndex)
    {
        result = sglGetUniformBlockIndex(program, uniformBlockName);
        ReportGLError("glGetUniformBlockIndex");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint *params)
{
    if (sglGetActiveUniformBlockiv)
    {
        sglGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
        ReportGLError("glGetActiveUniformBlockiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei *length, GLchar *uniformBlockName)
{
    if (sglGetActiveUniformBlockName)
    {
        sglGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
        ReportGLError("glGetActiveUniformBlockName");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
{
    if (sglUniformBlockBinding)
    {
        sglUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
        ReportGLError("glUniformBlockBinding");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_3_1()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_3_1)
    {
        GetOpenGLFunction("glDrawArraysInstanced", sglDrawArraysInstanced);
        GetOpenGLFunction("glDrawElementsInstanced", sglDrawElementsInstanced);
        GetOpenGLFunction("glTexBuffer", sglTexBuffer);
        GetOpenGLFunction("glPrimitiveRestartIndex", sglPrimitiveRestartIndex);
        GetOpenGLFunction("glCopyBufferSubData", sglCopyBufferSubData);
        GetOpenGLFunction("glGetUniformIndices", sglGetUniformIndices);
        GetOpenGLFunction("glGetActiveUniformsiv", sglGetActiveUniformsiv);
        GetOpenGLFunction("glGetActiveUniformName", sglGetActiveUniformName);
        GetOpenGLFunction("glGetUniformBlockIndex", sglGetUniformBlockIndex);
        GetOpenGLFunction("glGetActiveUniformBlockiv", sglGetActiveUniformBlockiv);
        GetOpenGLFunction("glGetActiveUniformBlockName", sglGetActiveUniformBlockName);
        GetOpenGLFunction("glUniformBlockBinding", sglUniformBlockBinding);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_3_2
//----------------------------------------------------------------------------
static PFNGLDRAWELEMENTSBASEVERTEXPROC sglDrawElementsBaseVertex = nullptr;
static PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC sglDrawRangeElementsBaseVertex = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC sglDrawElementsInstancedBaseVertex = nullptr;
static PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC sglMultiDrawElementsBaseVertex = nullptr;
static PFNGLPROVOKINGVERTEXPROC sglProvokingVertex = nullptr;
static PFNGLFENCESYNCPROC sglFenceSync = nullptr;
static PFNGLISSYNCPROC sglIsSync = nullptr;
static PFNGLDELETESYNCPROC sglDeleteSync = nullptr;
static PFNGLCLIENTWAITSYNCPROC sglClientWaitSync = nullptr;
static PFNGLWAITSYNCPROC sglWaitSync = nullptr;
static PFNGLGETINTEGER64VPROC sglGetInteger64v = nullptr;
static PFNGLGETSYNCIVPROC sglGetSynciv = nullptr;
static PFNGLGETINTEGER64I_VPROC sglGetInteger64i_v = nullptr;
static PFNGLGETBUFFERPARAMETERI64VPROC sglGetBufferParameteri64v = nullptr;
static PFNGLFRAMEBUFFERTEXTUREPROC sglFramebufferTexture = nullptr;
static PFNGLTEXIMAGE2DMULTISAMPLEPROC sglTexImage2DMultisample = nullptr;
static PFNGLTEXIMAGE3DMULTISAMPLEPROC sglTexImage3DMultisample = nullptr;
static PFNGLGETMULTISAMPLEFVPROC sglGetMultisamplefv = nullptr;
static PFNGLSAMPLEMASKIPROC sglSampleMaski = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex)
{
    if (sglDrawElementsBaseVertex)
    {
        sglDrawElementsBaseVertex(mode, count, type, indices, basevertex);
        ReportGLError("glDrawElementsBaseVertex");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex)
{
    if (sglDrawRangeElementsBaseVertex)
    {
        sglDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
        ReportGLError("glDrawRangeElementsBaseVertex");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex)
{
    if (sglDrawElementsInstancedBaseVertex)
    {
        sglDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
        ReportGLError("glDrawElementsInstancedBaseVertex");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei *count, GLenum type, const void *const*indices, GLsizei drawcount, const GLint *basevertex)
{
    if (sglMultiDrawElementsBaseVertex)
    {
        sglMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
        ReportGLError("glMultiDrawElementsBaseVertex");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProvokingVertex(GLenum mode)
{
    if (sglProvokingVertex)
    {
        sglProvokingVertex(mode);
        ReportGLError("glProvokingVertex");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLsync APIENTRY glFenceSync(GLenum condition, GLbitfield flags)
{
    GLsync result;
    if (sglFenceSync)
    {
        result = sglFenceSync(condition, flags);
        ReportGLError("glFenceSync");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsSync(GLsync sync)
{
    GLboolean result;
    if (sglIsSync)
    {
        result = sglIsSync(sync);
        ReportGLError("glIsSync");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteSync(GLsync sync)
{
    if (sglDeleteSync)
    {
        sglDeleteSync(sync);
        ReportGLError("glDeleteSync");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLenum APIENTRY glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    GLenum result;
    if (sglClientWaitSync)
    {
        result = sglClientWaitSync(sync, flags, timeout);
        ReportGLError("glClientWaitSync");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout)
{
    if (sglWaitSync)
    {
        sglWaitSync(sync, flags, timeout);
        ReportGLError("glWaitSync");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetInteger64v(GLenum pname, GLint64 *data)
{
    if (sglGetInteger64v)
    {
        sglGetInteger64v(pname, data);
        ReportGLError("glGetInteger64v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values)
{
    if (sglGetSynciv)
    {
        sglGetSynciv(sync, pname, bufSize, length, values);
        ReportGLError("glGetSynciv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetInteger64i_v(GLenum target, GLuint index, GLint64 *data)
{
    if (sglGetInteger64i_v)
    {
        sglGetInteger64i_v(target, index, data);
        ReportGLError("glGetInteger64i_v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 *params)
{
    if (sglGetBufferParameteri64v)
    {
        sglGetBufferParameteri64v(target, pname, params);
        ReportGLError("glGetBufferParameteri64v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
    if (sglFramebufferTexture)
    {
        sglFramebufferTexture(target, attachment, texture, level);
        ReportGLError("glFramebufferTexture");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    if (sglTexImage2DMultisample)
    {
        sglTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
        ReportGLError("glTexImage2DMultisample");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
    if (sglTexImage3DMultisample)
    {
        sglTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
        ReportGLError("glTexImage3DMultisample");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetMultisamplefv(GLenum pname, GLuint index, GLfloat *val)
{
    if (sglGetMultisamplefv)
    {
        sglGetMultisamplefv(pname, index, val);
        ReportGLError("glGetMultisamplefv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSampleMaski(GLuint maskNumber, GLbitfield mask)
{
    if (sglSampleMaski)
    {
        sglSampleMaski(maskNumber, mask);
        ReportGLError("glSampleMaski");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_3_2()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_3_2)
    {
        GetOpenGLFunction("glDrawElementsBaseVertex", sglDrawElementsBaseVertex);
        GetOpenGLFunction("glDrawRangeElementsBaseVertex", sglDrawRangeElementsBaseVertex);
        GetOpenGLFunction("glDrawElementsInstancedBaseVertex", sglDrawElementsInstancedBaseVertex);
        GetOpenGLFunction("glMultiDrawElementsBaseVertex", sglMultiDrawElementsBaseVertex);
        GetOpenGLFunction("glProvokingVertex", sglProvokingVertex);
        GetOpenGLFunction("glFenceSync", sglFenceSync);
        GetOpenGLFunction("glIsSync", sglIsSync);
        GetOpenGLFunction("glDeleteSync", sglDeleteSync);
        GetOpenGLFunction("glClientWaitSync", sglClientWaitSync);
        GetOpenGLFunction("glWaitSync", sglWaitSync);
        GetOpenGLFunction("glGetInteger64v", sglGetInteger64v);
        GetOpenGLFunction("glGetSynciv", sglGetSynciv);
        GetOpenGLFunction("glGetInteger64i_v", sglGetInteger64i_v);
        GetOpenGLFunction("glGetBufferParameteri64v", sglGetBufferParameteri64v);
        GetOpenGLFunction("glFramebufferTexture", sglFramebufferTexture);
        GetOpenGLFunction("glTexImage2DMultisample", sglTexImage2DMultisample);
        GetOpenGLFunction("glTexImage3DMultisample", sglTexImage3DMultisample);
        GetOpenGLFunction("glGetMultisamplefv", sglGetMultisamplefv);
        GetOpenGLFunction("glSampleMaski", sglSampleMaski);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_3_3
//----------------------------------------------------------------------------
static PFNGLBINDFRAGDATALOCATIONINDEXEDPROC sglBindFragDataLocationIndexed = nullptr;
static PFNGLGETFRAGDATAINDEXPROC sglGetFragDataIndex = nullptr;
static PFNGLGENSAMPLERSPROC sglGenSamplers = nullptr;
static PFNGLDELETESAMPLERSPROC sglDeleteSamplers = nullptr;
static PFNGLISSAMPLERPROC sglIsSampler = nullptr;
static PFNGLBINDSAMPLERPROC sglBindSampler = nullptr;
static PFNGLSAMPLERPARAMETERIPROC sglSamplerParameteri = nullptr;
static PFNGLSAMPLERPARAMETERIVPROC sglSamplerParameteriv = nullptr;
static PFNGLSAMPLERPARAMETERFPROC sglSamplerParameterf = nullptr;
static PFNGLSAMPLERPARAMETERFVPROC sglSamplerParameterfv = nullptr;
static PFNGLSAMPLERPARAMETERIIVPROC sglSamplerParameterIiv = nullptr;
static PFNGLSAMPLERPARAMETERIUIVPROC sglSamplerParameterIuiv = nullptr;
static PFNGLGETSAMPLERPARAMETERIVPROC sglGetSamplerParameteriv = nullptr;
static PFNGLGETSAMPLERPARAMETERIIVPROC sglGetSamplerParameterIiv = nullptr;
static PFNGLGETSAMPLERPARAMETERFVPROC sglGetSamplerParameterfv = nullptr;
static PFNGLGETSAMPLERPARAMETERIUIVPROC sglGetSamplerParameterIuiv = nullptr;
static PFNGLQUERYCOUNTERPROC sglQueryCounter = nullptr;
static PFNGLGETQUERYOBJECTI64VPROC sglGetQueryObjecti64v = nullptr;
static PFNGLGETQUERYOBJECTUI64VPROC sglGetQueryObjectui64v = nullptr;
static PFNGLVERTEXATTRIBDIVISORPROC sglVertexAttribDivisor = nullptr;
static PFNGLVERTEXATTRIBP1UIPROC sglVertexAttribP1ui = nullptr;
static PFNGLVERTEXATTRIBP1UIVPROC sglVertexAttribP1uiv = nullptr;
static PFNGLVERTEXATTRIBP2UIPROC sglVertexAttribP2ui = nullptr;
static PFNGLVERTEXATTRIBP2UIVPROC sglVertexAttribP2uiv = nullptr;
static PFNGLVERTEXATTRIBP3UIPROC sglVertexAttribP3ui = nullptr;
static PFNGLVERTEXATTRIBP3UIVPROC sglVertexAttribP3uiv = nullptr;
static PFNGLVERTEXATTRIBP4UIPROC sglVertexAttribP4ui = nullptr;
static PFNGLVERTEXATTRIBP4UIVPROC sglVertexAttribP4uiv = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar *name)
{
    if (sglBindFragDataLocationIndexed)
    {
        sglBindFragDataLocationIndexed(program, colorNumber, index, name);
        ReportGLError("glBindFragDataLocationIndexed");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLint APIENTRY glGetFragDataIndex(GLuint program, const GLchar *name)
{
    GLint result;
    if (sglGetFragDataIndex)
    {
        result = sglGetFragDataIndex(program, name);
        ReportGLError("glGetFragDataIndex");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGenSamplers(GLsizei count, GLuint *samplers)
{
    if (sglGenSamplers)
    {
        sglGenSamplers(count, samplers);
        ReportGLError("glGenSamplers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteSamplers(GLsizei count, const GLuint *samplers)
{
    if (sglDeleteSamplers)
    {
        sglDeleteSamplers(count, samplers);
        ReportGLError("glDeleteSamplers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsSampler(GLuint sampler)
{
    GLboolean result;
    if (sglIsSampler)
    {
        result = sglIsSampler(sampler);
        ReportGLError("glIsSampler");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glBindSampler(GLuint unit, GLuint sampler)
{
    if (sglBindSampler)
    {
        sglBindSampler(unit, sampler);
        ReportGLError("glBindSampler");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSamplerParameteri(GLuint sampler, GLenum pname, GLint param)
{
    if (sglSamplerParameteri)
    {
        sglSamplerParameteri(sampler, pname, param);
        ReportGLError("glSamplerParameteri");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint *param)
{
    if (sglSamplerParameteriv)
    {
        sglSamplerParameteriv(sampler, pname, param);
        ReportGLError("glSamplerParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param)
{
    if (sglSamplerParameterf)
    {
        sglSamplerParameterf(sampler, pname, param);
        ReportGLError("glSamplerParameterf");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat *param)
{
    if (sglSamplerParameterfv)
    {
        sglSamplerParameterfv(sampler, pname, param);
        ReportGLError("glSamplerParameterfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint *param)
{
    if (sglSamplerParameterIiv)
    {
        sglSamplerParameterIiv(sampler, pname, param);
        ReportGLError("glSamplerParameterIiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint *param)
{
    if (sglSamplerParameterIuiv)
    {
        sglSamplerParameterIuiv(sampler, pname, param);
        ReportGLError("glSamplerParameterIuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint *params)
{
    if (sglGetSamplerParameteriv)
    {
        sglGetSamplerParameteriv(sampler, pname, params);
        ReportGLError("glGetSamplerParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint *params)
{
    if (sglGetSamplerParameterIiv)
    {
        sglGetSamplerParameterIiv(sampler, pname, params);
        ReportGLError("glGetSamplerParameterIiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat *params)
{
    if (sglGetSamplerParameterfv)
    {
        sglGetSamplerParameterfv(sampler, pname, params);
        ReportGLError("glGetSamplerParameterfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint *params)
{
    if (sglGetSamplerParameterIuiv)
    {
        sglGetSamplerParameterIuiv(sampler, pname, params);
        ReportGLError("glGetSamplerParameterIuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glQueryCounter(GLuint id, GLenum target)
{
    if (sglQueryCounter)
    {
        sglQueryCounter(id, target);
        ReportGLError("glQueryCounter");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 *params)
{
    if (sglGetQueryObjecti64v)
    {
        sglGetQueryObjecti64v(id, pname, params);
        ReportGLError("glGetQueryObjecti64v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 *params)
{
    if (sglGetQueryObjectui64v)
    {
        sglGetQueryObjectui64v(id, pname, params);
        ReportGLError("glGetQueryObjectui64v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribDivisor(GLuint index, GLuint divisor)
{
    if (sglVertexAttribDivisor)
    {
        sglVertexAttribDivisor(index, divisor);
        ReportGLError("glVertexAttribDivisor");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
    if (sglVertexAttribP1ui)
    {
        sglVertexAttribP1ui(index, type, normalized, value);
        ReportGLError("glVertexAttribP1ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
{
    if (sglVertexAttribP1uiv)
    {
        sglVertexAttribP1uiv(index, type, normalized, value);
        ReportGLError("glVertexAttribP1uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
    if (sglVertexAttribP2ui)
    {
        sglVertexAttribP2ui(index, type, normalized, value);
        ReportGLError("glVertexAttribP2ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
{
    if (sglVertexAttribP2uiv)
    {
        sglVertexAttribP2uiv(index, type, normalized, value);
        ReportGLError("glVertexAttribP2uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
    if (sglVertexAttribP3ui)
    {
        sglVertexAttribP3ui(index, type, normalized, value);
        ReportGLError("glVertexAttribP3ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
{
    if (sglVertexAttribP3uiv)
    {
        sglVertexAttribP3uiv(index, type, normalized, value);
        ReportGLError("glVertexAttribP3uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value)
{
    if (sglVertexAttribP4ui)
    {
        sglVertexAttribP4ui(index, type, normalized, value);
        ReportGLError("glVertexAttribP4ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint *value)
{
    if (sglVertexAttribP4uiv)
    {
        sglVertexAttribP4uiv(index, type, normalized, value);
        ReportGLError("glVertexAttribP4uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_3_3()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_3_3)
    {
        GetOpenGLFunction("glBindFragDataLocationIndexed", sglBindFragDataLocationIndexed);
        GetOpenGLFunction("glGetFragDataIndex", sglGetFragDataIndex);
        GetOpenGLFunction("glGenSamplers", sglGenSamplers);
        GetOpenGLFunction("glDeleteSamplers", sglDeleteSamplers);
        GetOpenGLFunction("glIsSampler", sglIsSampler);
        GetOpenGLFunction("glBindSampler", sglBindSampler);
        GetOpenGLFunction("glSamplerParameteri", sglSamplerParameteri);
        GetOpenGLFunction("glSamplerParameteriv", sglSamplerParameteriv);
        GetOpenGLFunction("glSamplerParameterf", sglSamplerParameterf);
        GetOpenGLFunction("glSamplerParameterfv", sglSamplerParameterfv);
        GetOpenGLFunction("glSamplerParameterIiv", sglSamplerParameterIiv);
        GetOpenGLFunction("glSamplerParameterIuiv", sglSamplerParameterIuiv);
        GetOpenGLFunction("glGetSamplerParameteriv", sglGetSamplerParameteriv);
        GetOpenGLFunction("glGetSamplerParameterIiv", sglGetSamplerParameterIiv);
        GetOpenGLFunction("glGetSamplerParameterfv", sglGetSamplerParameterfv);
        GetOpenGLFunction("glGetSamplerParameterIuiv", sglGetSamplerParameterIuiv);
        GetOpenGLFunction("glQueryCounter", sglQueryCounter);
        GetOpenGLFunction("glGetQueryObjecti64v", sglGetQueryObjecti64v);
        GetOpenGLFunction("glGetQueryObjectui64v", sglGetQueryObjectui64v);
        GetOpenGLFunction("glVertexAttribDivisor", sglVertexAttribDivisor);
        GetOpenGLFunction("glVertexAttribP1ui", sglVertexAttribP1ui);
        GetOpenGLFunction("glVertexAttribP1uiv", sglVertexAttribP1uiv);
        GetOpenGLFunction("glVertexAttribP2ui", sglVertexAttribP2ui);
        GetOpenGLFunction("glVertexAttribP2uiv", sglVertexAttribP2uiv);
        GetOpenGLFunction("glVertexAttribP3ui", sglVertexAttribP3ui);
        GetOpenGLFunction("glVertexAttribP3uiv", sglVertexAttribP3uiv);
        GetOpenGLFunction("glVertexAttribP4ui", sglVertexAttribP4ui);
        GetOpenGLFunction("glVertexAttribP4uiv", sglVertexAttribP4uiv);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_4_0
//----------------------------------------------------------------------------
static PFNGLMINSAMPLESHADINGPROC sglMinSampleShading = nullptr;
static PFNGLBLENDEQUATIONIPROC sglBlendEquationi = nullptr;
static PFNGLBLENDEQUATIONSEPARATEIPROC sglBlendEquationSeparatei = nullptr;
static PFNGLBLENDFUNCIPROC sglBlendFunci = nullptr;
static PFNGLBLENDFUNCSEPARATEIPROC sglBlendFuncSeparatei = nullptr;
static PFNGLDRAWARRAYSINDIRECTPROC sglDrawArraysIndirect = nullptr;
static PFNGLDRAWELEMENTSINDIRECTPROC sglDrawElementsIndirect = nullptr;
static PFNGLUNIFORM1DPROC sglUniform1d = nullptr;
static PFNGLUNIFORM2DPROC sglUniform2d = nullptr;
static PFNGLUNIFORM3DPROC sglUniform3d = nullptr;
static PFNGLUNIFORM4DPROC sglUniform4d = nullptr;
static PFNGLUNIFORM1DVPROC sglUniform1dv = nullptr;
static PFNGLUNIFORM2DVPROC sglUniform2dv = nullptr;
static PFNGLUNIFORM3DVPROC sglUniform3dv = nullptr;
static PFNGLUNIFORM4DVPROC sglUniform4dv = nullptr;
static PFNGLUNIFORMMATRIX2DVPROC sglUniformMatrix2dv = nullptr;
static PFNGLUNIFORMMATRIX3DVPROC sglUniformMatrix3dv = nullptr;
static PFNGLUNIFORMMATRIX4DVPROC sglUniformMatrix4dv = nullptr;
static PFNGLUNIFORMMATRIX2X3DVPROC sglUniformMatrix2x3dv = nullptr;
static PFNGLUNIFORMMATRIX2X4DVPROC sglUniformMatrix2x4dv = nullptr;
static PFNGLUNIFORMMATRIX3X2DVPROC sglUniformMatrix3x2dv = nullptr;
static PFNGLUNIFORMMATRIX3X4DVPROC sglUniformMatrix3x4dv = nullptr;
static PFNGLUNIFORMMATRIX4X2DVPROC sglUniformMatrix4x2dv = nullptr;
static PFNGLUNIFORMMATRIX4X3DVPROC sglUniformMatrix4x3dv = nullptr;
static PFNGLGETUNIFORMDVPROC sglGetUniformdv = nullptr;
static PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC sglGetSubroutineUniformLocation = nullptr;
static PFNGLGETSUBROUTINEINDEXPROC sglGetSubroutineIndex = nullptr;
static PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC sglGetActiveSubroutineUniformiv = nullptr;
static PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC sglGetActiveSubroutineUniformName = nullptr;
static PFNGLGETACTIVESUBROUTINENAMEPROC sglGetActiveSubroutineName = nullptr;
static PFNGLUNIFORMSUBROUTINESUIVPROC sglUniformSubroutinesuiv = nullptr;
static PFNGLGETUNIFORMSUBROUTINEUIVPROC sglGetUniformSubroutineuiv = nullptr;
static PFNGLGETPROGRAMSTAGEIVPROC sglGetProgramStageiv = nullptr;
static PFNGLPATCHPARAMETERIPROC sglPatchParameteri = nullptr;
static PFNGLPATCHPARAMETERFVPROC sglPatchParameterfv = nullptr;
static PFNGLBINDTRANSFORMFEEDBACKPROC sglBindTransformFeedback = nullptr;
static PFNGLDELETETRANSFORMFEEDBACKSPROC sglDeleteTransformFeedbacks = nullptr;
static PFNGLGENTRANSFORMFEEDBACKSPROC sglGenTransformFeedbacks = nullptr;
static PFNGLISTRANSFORMFEEDBACKPROC sglIsTransformFeedback = nullptr;
static PFNGLPAUSETRANSFORMFEEDBACKPROC sglPauseTransformFeedback = nullptr;
static PFNGLRESUMETRANSFORMFEEDBACKPROC sglResumeTransformFeedback = nullptr;
static PFNGLDRAWTRANSFORMFEEDBACKPROC sglDrawTransformFeedback = nullptr;
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC sglDrawTransformFeedbackStream = nullptr;
static PFNGLBEGINQUERYINDEXEDPROC sglBeginQueryIndexed = nullptr;
static PFNGLENDQUERYINDEXEDPROC sglEndQueryIndexed = nullptr;
static PFNGLGETQUERYINDEXEDIVPROC sglGetQueryIndexediv = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glMinSampleShading(GLfloat value)
{
    if (sglMinSampleShading)
    {
        sglMinSampleShading(value);
        ReportGLError("glMinSampleShading");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlendEquationi(GLuint buf, GLenum mode)
{
    if (sglBlendEquationi)
    {
        sglBlendEquationi(buf, mode);
        ReportGLError("glBlendEquationi");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
    if (sglBlendEquationSeparatei)
    {
        sglBlendEquationSeparatei(buf, modeRGB, modeAlpha);
        ReportGLError("glBlendEquationSeparatei");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlendFunci(GLuint buf, GLenum src, GLenum dst)
{
    if (sglBlendFunci)
    {
        sglBlendFunci(buf, src, dst);
        ReportGLError("glBlendFunci");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
    if (sglBlendFuncSeparatei)
    {
        sglBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
        ReportGLError("glBlendFuncSeparatei");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawArraysIndirect(GLenum mode, const void *indirect)
{
    if (sglDrawArraysIndirect)
    {
        sglDrawArraysIndirect(mode, indirect);
        ReportGLError("glDrawArraysIndirect");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect)
{
    if (sglDrawElementsIndirect)
    {
        sglDrawElementsIndirect(mode, type, indirect);
        ReportGLError("glDrawElementsIndirect");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1d(GLint location, GLdouble x)
{
    if (sglUniform1d)
    {
        sglUniform1d(location, x);
        ReportGLError("glUniform1d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2d(GLint location, GLdouble x, GLdouble y)
{
    if (sglUniform2d)
    {
        sglUniform2d(location, x, y);
        ReportGLError("glUniform2d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z)
{
    if (sglUniform3d)
    {
        sglUniform3d(location, x, y, z);
        ReportGLError("glUniform3d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    if (sglUniform4d)
    {
        sglUniform4d(location, x, y, z, w);
        ReportGLError("glUniform4d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform1dv(GLint location, GLsizei count, const GLdouble *value)
{
    if (sglUniform1dv)
    {
        sglUniform1dv(location, count, value);
        ReportGLError("glUniform1dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform2dv(GLint location, GLsizei count, const GLdouble *value)
{
    if (sglUniform2dv)
    {
        sglUniform2dv(location, count, value);
        ReportGLError("glUniform2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform3dv(GLint location, GLsizei count, const GLdouble *value)
{
    if (sglUniform3dv)
    {
        sglUniform3dv(location, count, value);
        ReportGLError("glUniform3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniform4dv(GLint location, GLsizei count, const GLdouble *value)
{
    if (sglUniform4dv)
    {
        sglUniform4dv(location, count, value);
        ReportGLError("glUniform4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix2dv)
    {
        sglUniformMatrix2dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix3dv)
    {
        sglUniformMatrix3dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix4dv)
    {
        sglUniformMatrix4dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix2x3dv)
    {
        sglUniformMatrix2x3dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix2x3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix2x4dv)
    {
        sglUniformMatrix2x4dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix2x4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix3x2dv)
    {
        sglUniformMatrix3x2dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix3x2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix3x4dv)
    {
        sglUniformMatrix3x4dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix3x4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix4x2dv)
    {
        sglUniformMatrix4x2dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix4x2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglUniformMatrix4x3dv)
    {
        sglUniformMatrix4x3dv(location, count, transpose, value);
        ReportGLError("glUniformMatrix4x3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetUniformdv(GLuint program, GLint location, GLdouble *params)
{
    if (sglGetUniformdv)
    {
        sglGetUniformdv(program, location, params);
        ReportGLError("glGetUniformdv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLint APIENTRY glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar *name)
{
    GLint result;
    if (sglGetSubroutineUniformLocation)
    {
        result = sglGetSubroutineUniformLocation(program, shadertype, name);
        ReportGLError("glGetSubroutineUniformLocation");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
GLuint APIENTRY glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar *name)
{
    GLuint result;
    if (sglGetSubroutineIndex)
    {
        result = sglGetSubroutineIndex(program, shadertype, name);
        ReportGLError("glGetSubroutineIndex");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint *values)
{
    if (sglGetActiveSubroutineUniformiv)
    {
        sglGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
        ReportGLError("glGetActiveSubroutineUniformiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name)
{
    if (sglGetActiveSubroutineUniformName)
    {
        sglGetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
        ReportGLError("glGetActiveSubroutineUniformName");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei *length, GLchar *name)
{
    if (sglGetActiveSubroutineName)
    {
        sglGetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
        ReportGLError("glGetActiveSubroutineName");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint *indices)
{
    if (sglUniformSubroutinesuiv)
    {
        sglUniformSubroutinesuiv(shadertype, count, indices);
        ReportGLError("glUniformSubroutinesuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint *params)
{
    if (sglGetUniformSubroutineuiv)
    {
        sglGetUniformSubroutineuiv(shadertype, location, params);
        ReportGLError("glGetUniformSubroutineuiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint *values)
{
    if (sglGetProgramStageiv)
    {
        sglGetProgramStageiv(program, shadertype, pname, values);
        ReportGLError("glGetProgramStageiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPatchParameteri(GLenum pname, GLint value)
{
    if (sglPatchParameteri)
    {
        sglPatchParameteri(pname, value);
        ReportGLError("glPatchParameteri");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPatchParameterfv(GLenum pname, const GLfloat *values)
{
    if (sglPatchParameterfv)
    {
        sglPatchParameterfv(pname, values);
        ReportGLError("glPatchParameterfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindTransformFeedback(GLenum target, GLuint id)
{
    if (sglBindTransformFeedback)
    {
        sglBindTransformFeedback(target, id);
        ReportGLError("glBindTransformFeedback");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteTransformFeedbacks(GLsizei n, const GLuint *ids)
{
    if (sglDeleteTransformFeedbacks)
    {
        sglDeleteTransformFeedbacks(n, ids);
        ReportGLError("glDeleteTransformFeedbacks");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenTransformFeedbacks(GLsizei n, GLuint *ids)
{
    if (sglGenTransformFeedbacks)
    {
        sglGenTransformFeedbacks(n, ids);
        ReportGLError("glGenTransformFeedbacks");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsTransformFeedback(GLuint id)
{
    GLboolean result;
    if (sglIsTransformFeedback)
    {
        result = sglIsTransformFeedback(id);
        ReportGLError("glIsTransformFeedback");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glPauseTransformFeedback()
{
    if (sglPauseTransformFeedback)
    {
        sglPauseTransformFeedback();
        ReportGLError("glPauseTransformFeedback");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glResumeTransformFeedback()
{
    if (sglResumeTransformFeedback)
    {
        sglResumeTransformFeedback();
        ReportGLError("glResumeTransformFeedback");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawTransformFeedback(GLenum mode, GLuint id)
{
    if (sglDrawTransformFeedback)
    {
        sglDrawTransformFeedback(mode, id);
        ReportGLError("glDrawTransformFeedback");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream)
{
    if (sglDrawTransformFeedbackStream)
    {
        sglDrawTransformFeedbackStream(mode, id, stream);
        ReportGLError("glDrawTransformFeedbackStream");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBeginQueryIndexed(GLenum target, GLuint index, GLuint id)
{
    if (sglBeginQueryIndexed)
    {
        sglBeginQueryIndexed(target, index, id);
        ReportGLError("glBeginQueryIndexed");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glEndQueryIndexed(GLenum target, GLuint index)
{
    if (sglEndQueryIndexed)
    {
        sglEndQueryIndexed(target, index);
        ReportGLError("glEndQueryIndexed");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint *params)
{
    if (sglGetQueryIndexediv)
    {
        sglGetQueryIndexediv(target, index, pname, params);
        ReportGLError("glGetQueryIndexediv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_4_0()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_4_0)
    {
        GetOpenGLFunction("glMinSampleShading", sglMinSampleShading);
        GetOpenGLFunction("glBlendEquationi", sglBlendEquationi);
        GetOpenGLFunction("glBlendEquationSeparatei", sglBlendEquationSeparatei);
        GetOpenGLFunction("glBlendFunci", sglBlendFunci);
        GetOpenGLFunction("glBlendFuncSeparatei", sglBlendFuncSeparatei);
        GetOpenGLFunction("glDrawArraysIndirect", sglDrawArraysIndirect);
        GetOpenGLFunction("glDrawElementsIndirect", sglDrawElementsIndirect);
        GetOpenGLFunction("glUniform1d", sglUniform1d);
        GetOpenGLFunction("glUniform2d", sglUniform2d);
        GetOpenGLFunction("glUniform3d", sglUniform3d);
        GetOpenGLFunction("glUniform4d", sglUniform4d);
        GetOpenGLFunction("glUniform1dv", sglUniform1dv);
        GetOpenGLFunction("glUniform2dv", sglUniform2dv);
        GetOpenGLFunction("glUniform3dv", sglUniform3dv);
        GetOpenGLFunction("glUniform4dv", sglUniform4dv);
        GetOpenGLFunction("glUniformMatrix2dv", sglUniformMatrix2dv);
        GetOpenGLFunction("glUniformMatrix3dv", sglUniformMatrix3dv);
        GetOpenGLFunction("glUniformMatrix4dv", sglUniformMatrix4dv);
        GetOpenGLFunction("glUniformMatrix2x3dv", sglUniformMatrix2x3dv);
        GetOpenGLFunction("glUniformMatrix2x4dv", sglUniformMatrix2x4dv);
        GetOpenGLFunction("glUniformMatrix3x2dv", sglUniformMatrix3x2dv);
        GetOpenGLFunction("glUniformMatrix3x4dv", sglUniformMatrix3x4dv);
        GetOpenGLFunction("glUniformMatrix4x2dv", sglUniformMatrix4x2dv);
        GetOpenGLFunction("glUniformMatrix4x3dv", sglUniformMatrix4x3dv);
        GetOpenGLFunction("glGetUniformdv", sglGetUniformdv);
        GetOpenGLFunction("glGetSubroutineUniformLocation", sglGetSubroutineUniformLocation);
        GetOpenGLFunction("glGetSubroutineIndex", sglGetSubroutineIndex);
        GetOpenGLFunction("glGetActiveSubroutineUniformiv", sglGetActiveSubroutineUniformiv);
        GetOpenGLFunction("glGetActiveSubroutineUniformName", sglGetActiveSubroutineUniformName);
        GetOpenGLFunction("glGetActiveSubroutineName", sglGetActiveSubroutineName);
        GetOpenGLFunction("glUniformSubroutinesuiv", sglUniformSubroutinesuiv);
        GetOpenGLFunction("glGetUniformSubroutineuiv", sglGetUniformSubroutineuiv);
        GetOpenGLFunction("glGetProgramStageiv", sglGetProgramStageiv);
        GetOpenGLFunction("glPatchParameteri", sglPatchParameteri);
        GetOpenGLFunction("glPatchParameterfv", sglPatchParameterfv);
        GetOpenGLFunction("glBindTransformFeedback", sglBindTransformFeedback);
        GetOpenGLFunction("glDeleteTransformFeedbacks", sglDeleteTransformFeedbacks);
        GetOpenGLFunction("glGenTransformFeedbacks", sglGenTransformFeedbacks);
        GetOpenGLFunction("glIsTransformFeedback", sglIsTransformFeedback);
        GetOpenGLFunction("glPauseTransformFeedback", sglPauseTransformFeedback);
        GetOpenGLFunction("glResumeTransformFeedback", sglResumeTransformFeedback);
        GetOpenGLFunction("glDrawTransformFeedback", sglDrawTransformFeedback);
        GetOpenGLFunction("glDrawTransformFeedbackStream", sglDrawTransformFeedbackStream);
        GetOpenGLFunction("glBeginQueryIndexed", sglBeginQueryIndexed);
        GetOpenGLFunction("glEndQueryIndexed", sglEndQueryIndexed);
        GetOpenGLFunction("glGetQueryIndexediv", sglGetQueryIndexediv);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_4_1
//----------------------------------------------------------------------------
static PFNGLRELEASESHADERCOMPILERPROC sglReleaseShaderCompiler = nullptr;
static PFNGLSHADERBINARYPROC sglShaderBinary = nullptr;
static PFNGLGETSHADERPRECISIONFORMATPROC sglGetShaderPrecisionFormat = nullptr;
static PFNGLDEPTHRANGEFPROC sglDepthRangef = nullptr;
static PFNGLCLEARDEPTHFPROC sglClearDepthf = nullptr;
static PFNGLGETPROGRAMBINARYPROC sglGetProgramBinary = nullptr;
static PFNGLPROGRAMBINARYPROC sglProgramBinary = nullptr;
static PFNGLPROGRAMPARAMETERIPROC sglProgramParameteri = nullptr;
static PFNGLUSEPROGRAMSTAGESPROC sglUseProgramStages = nullptr;
static PFNGLACTIVESHADERPROGRAMPROC sglActiveShaderProgram = nullptr;
static PFNGLCREATESHADERPROGRAMVPROC sglCreateShaderProgramv = nullptr;
static PFNGLBINDPROGRAMPIPELINEPROC sglBindProgramPipeline = nullptr;
static PFNGLDELETEPROGRAMPIPELINESPROC sglDeleteProgramPipelines = nullptr;
static PFNGLGENPROGRAMPIPELINESPROC sglGenProgramPipelines = nullptr;
static PFNGLISPROGRAMPIPELINEPROC sglIsProgramPipeline = nullptr;
static PFNGLGETPROGRAMPIPELINEIVPROC sglGetProgramPipelineiv = nullptr;
static PFNGLPROGRAMUNIFORM1IPROC sglProgramUniform1i = nullptr;
static PFNGLPROGRAMUNIFORM1IVPROC sglProgramUniform1iv = nullptr;
static PFNGLPROGRAMUNIFORM1FPROC sglProgramUniform1f = nullptr;
static PFNGLPROGRAMUNIFORM1FVPROC sglProgramUniform1fv = nullptr;
static PFNGLPROGRAMUNIFORM1DPROC sglProgramUniform1d = nullptr;
static PFNGLPROGRAMUNIFORM1DVPROC sglProgramUniform1dv = nullptr;
static PFNGLPROGRAMUNIFORM1UIPROC sglProgramUniform1ui = nullptr;
static PFNGLPROGRAMUNIFORM1UIVPROC sglProgramUniform1uiv = nullptr;
static PFNGLPROGRAMUNIFORM2IPROC sglProgramUniform2i = nullptr;
static PFNGLPROGRAMUNIFORM2IVPROC sglProgramUniform2iv = nullptr;
static PFNGLPROGRAMUNIFORM2FPROC sglProgramUniform2f = nullptr;
static PFNGLPROGRAMUNIFORM2FVPROC sglProgramUniform2fv = nullptr;
static PFNGLPROGRAMUNIFORM2DPROC sglProgramUniform2d = nullptr;
static PFNGLPROGRAMUNIFORM2DVPROC sglProgramUniform2dv = nullptr;
static PFNGLPROGRAMUNIFORM2UIPROC sglProgramUniform2ui = nullptr;
static PFNGLPROGRAMUNIFORM2UIVPROC sglProgramUniform2uiv = nullptr;
static PFNGLPROGRAMUNIFORM3IPROC sglProgramUniform3i = nullptr;
static PFNGLPROGRAMUNIFORM3IVPROC sglProgramUniform3iv = nullptr;
static PFNGLPROGRAMUNIFORM3FPROC sglProgramUniform3f = nullptr;
static PFNGLPROGRAMUNIFORM3FVPROC sglProgramUniform3fv = nullptr;
static PFNGLPROGRAMUNIFORM3DPROC sglProgramUniform3d = nullptr;
static PFNGLPROGRAMUNIFORM3DVPROC sglProgramUniform3dv = nullptr;
static PFNGLPROGRAMUNIFORM3UIPROC sglProgramUniform3ui = nullptr;
static PFNGLPROGRAMUNIFORM3UIVPROC sglProgramUniform3uiv = nullptr;
static PFNGLPROGRAMUNIFORM4IPROC sglProgramUniform4i = nullptr;
static PFNGLPROGRAMUNIFORM4IVPROC sglProgramUniform4iv = nullptr;
static PFNGLPROGRAMUNIFORM4FPROC sglProgramUniform4f = nullptr;
static PFNGLPROGRAMUNIFORM4FVPROC sglProgramUniform4fv = nullptr;
static PFNGLPROGRAMUNIFORM4DPROC sglProgramUniform4d = nullptr;
static PFNGLPROGRAMUNIFORM4DVPROC sglProgramUniform4dv = nullptr;
static PFNGLPROGRAMUNIFORM4UIPROC sglProgramUniform4ui = nullptr;
static PFNGLPROGRAMUNIFORM4UIVPROC sglProgramUniform4uiv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2FVPROC sglProgramUniformMatrix2fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3FVPROC sglProgramUniformMatrix3fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4FVPROC sglProgramUniformMatrix4fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2DVPROC sglProgramUniformMatrix2dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3DVPROC sglProgramUniformMatrix3dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4DVPROC sglProgramUniformMatrix4dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC sglProgramUniformMatrix2x3fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC sglProgramUniformMatrix3x2fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC sglProgramUniformMatrix2x4fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC sglProgramUniformMatrix4x2fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC sglProgramUniformMatrix3x4fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC sglProgramUniformMatrix4x3fv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC sglProgramUniformMatrix2x3dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC sglProgramUniformMatrix3x2dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC sglProgramUniformMatrix2x4dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC sglProgramUniformMatrix4x2dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC sglProgramUniformMatrix3x4dv = nullptr;
static PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC sglProgramUniformMatrix4x3dv = nullptr;
static PFNGLVALIDATEPROGRAMPIPELINEPROC sglValidateProgramPipeline = nullptr;
static PFNGLGETPROGRAMPIPELINEINFOLOGPROC sglGetProgramPipelineInfoLog = nullptr;
static PFNGLVERTEXATTRIBL1DPROC sglVertexAttribL1d = nullptr;
static PFNGLVERTEXATTRIBL2DPROC sglVertexAttribL2d = nullptr;
static PFNGLVERTEXATTRIBL3DPROC sglVertexAttribL3d = nullptr;
static PFNGLVERTEXATTRIBL4DPROC sglVertexAttribL4d = nullptr;
static PFNGLVERTEXATTRIBL1DVPROC sglVertexAttribL1dv = nullptr;
static PFNGLVERTEXATTRIBL2DVPROC sglVertexAttribL2dv = nullptr;
static PFNGLVERTEXATTRIBL3DVPROC sglVertexAttribL3dv = nullptr;
static PFNGLVERTEXATTRIBL4DVPROC sglVertexAttribL4dv = nullptr;
static PFNGLVERTEXATTRIBLPOINTERPROC sglVertexAttribLPointer = nullptr;
static PFNGLGETVERTEXATTRIBLDVPROC sglGetVertexAttribLdv = nullptr;
static PFNGLVIEWPORTARRAYVPROC sglViewportArrayv = nullptr;
static PFNGLVIEWPORTINDEXEDFPROC sglViewportIndexedf = nullptr;
static PFNGLVIEWPORTINDEXEDFVPROC sglViewportIndexedfv = nullptr;
static PFNGLSCISSORARRAYVPROC sglScissorArrayv = nullptr;
static PFNGLSCISSORINDEXEDPROC sglScissorIndexed = nullptr;
static PFNGLSCISSORINDEXEDVPROC sglScissorIndexedv = nullptr;
static PFNGLDEPTHRANGEARRAYVPROC sglDepthRangeArrayv = nullptr;
static PFNGLDEPTHRANGEINDEXEDPROC sglDepthRangeIndexed = nullptr;
static PFNGLGETFLOATI_VPROC sglGetFloati_v = nullptr;
static PFNGLGETDOUBLEI_VPROC sglGetDoublei_v = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glReleaseShaderCompiler()
{
    if (sglReleaseShaderCompiler)
    {
        sglReleaseShaderCompiler();
        ReportGLError("glReleaseShaderCompiler");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glShaderBinary(GLsizei count, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length)
{
    if (sglShaderBinary)
    {
        sglShaderBinary(count, shaders, binaryformat, binary, length);
        ReportGLError("glShaderBinary");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision)
{
    if (sglGetShaderPrecisionFormat)
    {
        sglGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
        ReportGLError("glGetShaderPrecisionFormat");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDepthRangef(GLfloat n, GLfloat f)
{
    if (sglDepthRangef)
    {
        sglDepthRangef(n, f);
        ReportGLError("glDepthRangef");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearDepthf(GLfloat d)
{
    if (sglClearDepthf)
    {
        sglClearDepthf(d);
        ReportGLError("glClearDepthf");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei *length, GLenum *binaryFormat, void *binary)
{
    if (sglGetProgramBinary)
    {
        sglGetProgramBinary(program, bufSize, length, binaryFormat, binary);
        ReportGLError("glGetProgramBinary");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramBinary(GLuint program, GLenum binaryFormat, const void *binary, GLsizei length)
{
    if (sglProgramBinary)
    {
        sglProgramBinary(program, binaryFormat, binary, length);
        ReportGLError("glProgramBinary");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramParameteri(GLuint program, GLenum pname, GLint value)
{
    if (sglProgramParameteri)
    {
        sglProgramParameteri(program, pname, value);
        ReportGLError("glProgramParameteri");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program)
{
    if (sglUseProgramStages)
    {
        sglUseProgramStages(pipeline, stages, program);
        ReportGLError("glUseProgramStages");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glActiveShaderProgram(GLuint pipeline, GLuint program)
{
    if (sglActiveShaderProgram)
    {
        sglActiveShaderProgram(pipeline, program);
        ReportGLError("glActiveShaderProgram");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLuint APIENTRY glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar *const*strings)
{
    GLuint result;
    if (sglCreateShaderProgramv)
    {
        result = sglCreateShaderProgramv(type, count, strings);
        ReportGLError("glCreateShaderProgramv");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glBindProgramPipeline(GLuint pipeline)
{
    if (sglBindProgramPipeline)
    {
        sglBindProgramPipeline(pipeline);
        ReportGLError("glBindProgramPipeline");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDeleteProgramPipelines(GLsizei n, const GLuint *pipelines)
{
    if (sglDeleteProgramPipelines)
    {
        sglDeleteProgramPipelines(n, pipelines);
        ReportGLError("glDeleteProgramPipelines");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGenProgramPipelines(GLsizei n, GLuint *pipelines)
{
    if (sglGenProgramPipelines)
    {
        sglGenProgramPipelines(n, pipelines);
        ReportGLError("glGenProgramPipelines");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLboolean APIENTRY glIsProgramPipeline(GLuint pipeline)
{
    GLboolean result;
    if (sglIsProgramPipeline)
    {
        result = sglIsProgramPipeline(pipeline);
        ReportGLError("glIsProgramPipeline");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint *params)
{
    if (sglGetProgramPipelineiv)
    {
        sglGetProgramPipelineiv(pipeline, pname, params);
        ReportGLError("glGetProgramPipelineiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1i(GLuint program, GLint location, GLint v0)
{
    if (sglProgramUniform1i)
    {
        sglProgramUniform1i(program, location, v0);
        ReportGLError("glProgramUniform1i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    if (sglProgramUniform1iv)
    {
        sglProgramUniform1iv(program, location, count, value);
        ReportGLError("glProgramUniform1iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1f(GLuint program, GLint location, GLfloat v0)
{
    if (sglProgramUniform1f)
    {
        sglProgramUniform1f(program, location, v0);
        ReportGLError("glProgramUniform1f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    if (sglProgramUniform1fv)
    {
        sglProgramUniform1fv(program, location, count, value);
        ReportGLError("glProgramUniform1fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1d(GLuint program, GLint location, GLdouble v0)
{
    if (sglProgramUniform1d)
    {
        sglProgramUniform1d(program, location, v0);
        ReportGLError("glProgramUniform1d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
{
    if (sglProgramUniform1dv)
    {
        sglProgramUniform1dv(program, location, count, value);
        ReportGLError("glProgramUniform1dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1ui(GLuint program, GLint location, GLuint v0)
{
    if (sglProgramUniform1ui)
    {
        sglProgramUniform1ui(program, location, v0);
        ReportGLError("glProgramUniform1ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
{
    if (sglProgramUniform1uiv)
    {
        sglProgramUniform1uiv(program, location, count, value);
        ReportGLError("glProgramUniform1uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1)
{
    if (sglProgramUniform2i)
    {
        sglProgramUniform2i(program, location, v0, v1);
        ReportGLError("glProgramUniform2i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    if (sglProgramUniform2iv)
    {
        sglProgramUniform2iv(program, location, count, value);
        ReportGLError("glProgramUniform2iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
    if (sglProgramUniform2f)
    {
        sglProgramUniform2f(program, location, v0, v1);
        ReportGLError("glProgramUniform2f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    if (sglProgramUniform2fv)
    {
        sglProgramUniform2fv(program, location, count, value);
        ReportGLError("glProgramUniform2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1)
{
    if (sglProgramUniform2d)
    {
        sglProgramUniform2d(program, location, v0, v1);
        ReportGLError("glProgramUniform2d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
{
    if (sglProgramUniform2dv)
    {
        sglProgramUniform2dv(program, location, count, value);
        ReportGLError("glProgramUniform2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1)
{
    if (sglProgramUniform2ui)
    {
        sglProgramUniform2ui(program, location, v0, v1);
        ReportGLError("glProgramUniform2ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
{
    if (sglProgramUniform2uiv)
    {
        sglProgramUniform2uiv(program, location, count, value);
        ReportGLError("glProgramUniform2uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
    if (sglProgramUniform3i)
    {
        sglProgramUniform3i(program, location, v0, v1, v2);
        ReportGLError("glProgramUniform3i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    if (sglProgramUniform3iv)
    {
        sglProgramUniform3iv(program, location, count, value);
        ReportGLError("glProgramUniform3iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    if (sglProgramUniform3f)
    {
        sglProgramUniform3f(program, location, v0, v1, v2);
        ReportGLError("glProgramUniform3f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    if (sglProgramUniform3fv)
    {
        sglProgramUniform3fv(program, location, count, value);
        ReportGLError("glProgramUniform3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2)
{
    if (sglProgramUniform3d)
    {
        sglProgramUniform3d(program, location, v0, v1, v2);
        ReportGLError("glProgramUniform3d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
{
    if (sglProgramUniform3dv)
    {
        sglProgramUniform3dv(program, location, count, value);
        ReportGLError("glProgramUniform3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
    if (sglProgramUniform3ui)
    {
        sglProgramUniform3ui(program, location, v0, v1, v2);
        ReportGLError("glProgramUniform3ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
{
    if (sglProgramUniform3uiv)
    {
        sglProgramUniform3uiv(program, location, count, value);
        ReportGLError("glProgramUniform3uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    if (sglProgramUniform4i)
    {
        sglProgramUniform4i(program, location, v0, v1, v2, v3);
        ReportGLError("glProgramUniform4i");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint *value)
{
    if (sglProgramUniform4iv)
    {
        sglProgramUniform4iv(program, location, count, value);
        ReportGLError("glProgramUniform4iv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    if (sglProgramUniform4f)
    {
        sglProgramUniform4f(program, location, v0, v1, v2, v3);
        ReportGLError("glProgramUniform4f");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat *value)
{
    if (sglProgramUniform4fv)
    {
        sglProgramUniform4fv(program, location, count, value);
        ReportGLError("glProgramUniform4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3)
{
    if (sglProgramUniform4d)
    {
        sglProgramUniform4d(program, location, v0, v1, v2, v3);
        ReportGLError("glProgramUniform4d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble *value)
{
    if (sglProgramUniform4dv)
    {
        sglProgramUniform4dv(program, location, count, value);
        ReportGLError("glProgramUniform4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    if (sglProgramUniform4ui)
    {
        sglProgramUniform4ui(program, location, v0, v1, v2, v3);
        ReportGLError("glProgramUniform4ui");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint *value)
{
    if (sglProgramUniform4uiv)
    {
        sglProgramUniform4uiv(program, location, count, value);
        ReportGLError("glProgramUniform4uiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix2fv)
    {
        sglProgramUniformMatrix2fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix3fv)
    {
        sglProgramUniformMatrix3fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix4fv)
    {
        sglProgramUniformMatrix4fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix2dv)
    {
        sglProgramUniformMatrix2dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix3dv)
    {
        sglProgramUniformMatrix3dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix4dv)
    {
        sglProgramUniformMatrix4dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix2x3fv)
    {
        sglProgramUniformMatrix2x3fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix2x3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix3x2fv)
    {
        sglProgramUniformMatrix3x2fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix3x2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix2x4fv)
    {
        sglProgramUniformMatrix2x4fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix2x4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix4x2fv)
    {
        sglProgramUniformMatrix4x2fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix4x2fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix3x4fv)
    {
        sglProgramUniformMatrix3x4fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix3x4fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    if (sglProgramUniformMatrix4x3fv)
    {
        sglProgramUniformMatrix4x3fv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix4x3fv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix2x3dv)
    {
        sglProgramUniformMatrix2x3dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix2x3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix3x2dv)
    {
        sglProgramUniformMatrix3x2dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix3x2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix2x4dv)
    {
        sglProgramUniformMatrix2x4dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix2x4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix4x2dv)
    {
        sglProgramUniformMatrix4x2dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix4x2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix3x4dv)
    {
        sglProgramUniformMatrix3x4dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix3x4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble *value)
{
    if (sglProgramUniformMatrix4x3dv)
    {
        sglProgramUniformMatrix4x3dv(program, location, count, transpose, value);
        ReportGLError("glProgramUniformMatrix4x3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glValidateProgramPipeline(GLuint pipeline)
{
    if (sglValidateProgramPipeline)
    {
        sglValidateProgramPipeline(pipeline);
        ReportGLError("glValidateProgramPipeline");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei *length, GLchar *infoLog)
{
    if (sglGetProgramPipelineInfoLog)
    {
        sglGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
        ReportGLError("glGetProgramPipelineInfoLog");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL1d(GLuint index, GLdouble x)
{
    if (sglVertexAttribL1d)
    {
        sglVertexAttribL1d(index, x);
        ReportGLError("glVertexAttribL1d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y)
{
    if (sglVertexAttribL2d)
    {
        sglVertexAttribL2d(index, x, y);
        ReportGLError("glVertexAttribL2d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    if (sglVertexAttribL3d)
    {
        sglVertexAttribL3d(index, x, y, z);
        ReportGLError("glVertexAttribL3d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    if (sglVertexAttribL4d)
    {
        sglVertexAttribL4d(index, x, y, z, w);
        ReportGLError("glVertexAttribL4d");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL1dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttribL1dv)
    {
        sglVertexAttribL1dv(index, v);
        ReportGLError("glVertexAttribL1dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL2dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttribL2dv)
    {
        sglVertexAttribL2dv(index, v);
        ReportGLError("glVertexAttribL2dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL3dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttribL3dv)
    {
        sglVertexAttribL3dv(index, v);
        ReportGLError("glVertexAttribL3dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribL4dv(GLuint index, const GLdouble *v)
{
    if (sglVertexAttribL4dv)
    {
        sglVertexAttribL4dv(index, v);
        ReportGLError("glVertexAttribL4dv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)
{
    if (sglVertexAttribLPointer)
    {
        sglVertexAttribLPointer(index, size, type, stride, pointer);
        ReportGLError("glVertexAttribLPointer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble *params)
{
    if (sglGetVertexAttribLdv)
    {
        sglGetVertexAttribLdv(index, pname, params);
        ReportGLError("glGetVertexAttribLdv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glViewportArrayv(GLuint first, GLsizei count, const GLfloat *v)
{
    if (sglViewportArrayv)
    {
        sglViewportArrayv(first, count, v);
        ReportGLError("glViewportArrayv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
    if (sglViewportIndexedf)
    {
        sglViewportIndexedf(index, x, y, w, h);
        ReportGLError("glViewportIndexedf");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glViewportIndexedfv(GLuint index, const GLfloat *v)
{
    if (sglViewportIndexedfv)
    {
        sglViewportIndexedfv(index, v);
        ReportGLError("glViewportIndexedfv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glScissorArrayv(GLuint first, GLsizei count, const GLint *v)
{
    if (sglScissorArrayv)
    {
        sglScissorArrayv(first, count, v);
        ReportGLError("glScissorArrayv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height)
{
    if (sglScissorIndexed)
    {
        sglScissorIndexed(index, left, bottom, width, height);
        ReportGLError("glScissorIndexed");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glScissorIndexedv(GLuint index, const GLint *v)
{
    if (sglScissorIndexedv)
    {
        sglScissorIndexedv(index, v);
        ReportGLError("glScissorIndexedv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble *v)
{
    if (sglDepthRangeArrayv)
    {
        sglDepthRangeArrayv(first, count, v);
        ReportGLError("glDepthRangeArrayv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f)
{
    if (sglDepthRangeIndexed)
    {
        sglDepthRangeIndexed(index, n, f);
        ReportGLError("glDepthRangeIndexed");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetFloati_v(GLenum target, GLuint index, GLfloat *data)
{
    if (sglGetFloati_v)
    {
        sglGetFloati_v(target, index, data);
        ReportGLError("glGetFloati_v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetDoublei_v(GLenum target, GLuint index, GLdouble *data)
{
    if (sglGetDoublei_v)
    {
        sglGetDoublei_v(target, index, data);
        ReportGLError("glGetDoublei_v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_4_1()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_4_1)
    {
        GetOpenGLFunction("glReleaseShaderCompiler", sglReleaseShaderCompiler);
        GetOpenGLFunction("glShaderBinary", sglShaderBinary);
        GetOpenGLFunction("glGetShaderPrecisionFormat", sglGetShaderPrecisionFormat);
        GetOpenGLFunction("glDepthRangef", sglDepthRangef);
        GetOpenGLFunction("glClearDepthf", sglClearDepthf);
        GetOpenGLFunction("glGetProgramBinary", sglGetProgramBinary);
        GetOpenGLFunction("glProgramBinary", sglProgramBinary);
        GetOpenGLFunction("glProgramParameteri", sglProgramParameteri);
        GetOpenGLFunction("glUseProgramStages", sglUseProgramStages);
        GetOpenGLFunction("glActiveShaderProgram", sglActiveShaderProgram);
        GetOpenGLFunction("glCreateShaderProgramv", sglCreateShaderProgramv);
        GetOpenGLFunction("glBindProgramPipeline", sglBindProgramPipeline);
        GetOpenGLFunction("glDeleteProgramPipelines", sglDeleteProgramPipelines);
        GetOpenGLFunction("glGenProgramPipelines", sglGenProgramPipelines);
        GetOpenGLFunction("glIsProgramPipeline", sglIsProgramPipeline);
        GetOpenGLFunction("glGetProgramPipelineiv", sglGetProgramPipelineiv);
        GetOpenGLFunction("glProgramUniform1i", sglProgramUniform1i);
        GetOpenGLFunction("glProgramUniform1iv", sglProgramUniform1iv);
        GetOpenGLFunction("glProgramUniform1f", sglProgramUniform1f);
        GetOpenGLFunction("glProgramUniform1fv", sglProgramUniform1fv);
        GetOpenGLFunction("glProgramUniform1d", sglProgramUniform1d);
        GetOpenGLFunction("glProgramUniform1dv", sglProgramUniform1dv);
        GetOpenGLFunction("glProgramUniform1ui", sglProgramUniform1ui);
        GetOpenGLFunction("glProgramUniform1uiv", sglProgramUniform1uiv);
        GetOpenGLFunction("glProgramUniform2i", sglProgramUniform2i);
        GetOpenGLFunction("glProgramUniform2iv", sglProgramUniform2iv);
        GetOpenGLFunction("glProgramUniform2f", sglProgramUniform2f);
        GetOpenGLFunction("glProgramUniform2fv", sglProgramUniform2fv);
        GetOpenGLFunction("glProgramUniform2d", sglProgramUniform2d);
        GetOpenGLFunction("glProgramUniform2dv", sglProgramUniform2dv);
        GetOpenGLFunction("glProgramUniform2ui", sglProgramUniform2ui);
        GetOpenGLFunction("glProgramUniform2uiv", sglProgramUniform2uiv);
        GetOpenGLFunction("glProgramUniform3i", sglProgramUniform3i);
        GetOpenGLFunction("glProgramUniform3iv", sglProgramUniform3iv);
        GetOpenGLFunction("glProgramUniform3f", sglProgramUniform3f);
        GetOpenGLFunction("glProgramUniform3fv", sglProgramUniform3fv);
        GetOpenGLFunction("glProgramUniform3d", sglProgramUniform3d);
        GetOpenGLFunction("glProgramUniform3dv", sglProgramUniform3dv);
        GetOpenGLFunction("glProgramUniform3ui", sglProgramUniform3ui);
        GetOpenGLFunction("glProgramUniform3uiv", sglProgramUniform3uiv);
        GetOpenGLFunction("glProgramUniform4i", sglProgramUniform4i);
        GetOpenGLFunction("glProgramUniform4iv", sglProgramUniform4iv);
        GetOpenGLFunction("glProgramUniform4f", sglProgramUniform4f);
        GetOpenGLFunction("glProgramUniform4fv", sglProgramUniform4fv);
        GetOpenGLFunction("glProgramUniform4d", sglProgramUniform4d);
        GetOpenGLFunction("glProgramUniform4dv", sglProgramUniform4dv);
        GetOpenGLFunction("glProgramUniform4ui", sglProgramUniform4ui);
        GetOpenGLFunction("glProgramUniform4uiv", sglProgramUniform4uiv);
        GetOpenGLFunction("glProgramUniformMatrix2fv", sglProgramUniformMatrix2fv);
        GetOpenGLFunction("glProgramUniformMatrix3fv", sglProgramUniformMatrix3fv);
        GetOpenGLFunction("glProgramUniformMatrix4fv", sglProgramUniformMatrix4fv);
        GetOpenGLFunction("glProgramUniformMatrix2dv", sglProgramUniformMatrix2dv);
        GetOpenGLFunction("glProgramUniformMatrix3dv", sglProgramUniformMatrix3dv);
        GetOpenGLFunction("glProgramUniformMatrix4dv", sglProgramUniformMatrix4dv);
        GetOpenGLFunction("glProgramUniformMatrix2x3fv", sglProgramUniformMatrix2x3fv);
        GetOpenGLFunction("glProgramUniformMatrix3x2fv", sglProgramUniformMatrix3x2fv);
        GetOpenGLFunction("glProgramUniformMatrix2x4fv", sglProgramUniformMatrix2x4fv);
        GetOpenGLFunction("glProgramUniformMatrix4x2fv", sglProgramUniformMatrix4x2fv);
        GetOpenGLFunction("glProgramUniformMatrix3x4fv", sglProgramUniformMatrix3x4fv);
        GetOpenGLFunction("glProgramUniformMatrix4x3fv", sglProgramUniformMatrix4x3fv);
        GetOpenGLFunction("glProgramUniformMatrix2x3dv", sglProgramUniformMatrix2x3dv);
        GetOpenGLFunction("glProgramUniformMatrix3x2dv", sglProgramUniformMatrix3x2dv);
        GetOpenGLFunction("glProgramUniformMatrix2x4dv", sglProgramUniformMatrix2x4dv);
        GetOpenGLFunction("glProgramUniformMatrix4x2dv", sglProgramUniformMatrix4x2dv);
        GetOpenGLFunction("glProgramUniformMatrix3x4dv", sglProgramUniformMatrix3x4dv);
        GetOpenGLFunction("glProgramUniformMatrix4x3dv", sglProgramUniformMatrix4x3dv);
        GetOpenGLFunction("glValidateProgramPipeline", sglValidateProgramPipeline);
        GetOpenGLFunction("glGetProgramPipelineInfoLog", sglGetProgramPipelineInfoLog);
        GetOpenGLFunction("glVertexAttribL1d", sglVertexAttribL1d);
        GetOpenGLFunction("glVertexAttribL2d", sglVertexAttribL2d);
        GetOpenGLFunction("glVertexAttribL3d", sglVertexAttribL3d);
        GetOpenGLFunction("glVertexAttribL4d", sglVertexAttribL4d);
        GetOpenGLFunction("glVertexAttribL1dv", sglVertexAttribL1dv);
        GetOpenGLFunction("glVertexAttribL2dv", sglVertexAttribL2dv);
        GetOpenGLFunction("glVertexAttribL3dv", sglVertexAttribL3dv);
        GetOpenGLFunction("glVertexAttribL4dv", sglVertexAttribL4dv);
        GetOpenGLFunction("glVertexAttribLPointer", sglVertexAttribLPointer);
        GetOpenGLFunction("glGetVertexAttribLdv", sglGetVertexAttribLdv);
        GetOpenGLFunction("glViewportArrayv", sglViewportArrayv);
        GetOpenGLFunction("glViewportIndexedf", sglViewportIndexedf);
        GetOpenGLFunction("glViewportIndexedfv", sglViewportIndexedfv);
        GetOpenGLFunction("glScissorArrayv", sglScissorArrayv);
        GetOpenGLFunction("glScissorIndexed", sglScissorIndexed);
        GetOpenGLFunction("glScissorIndexedv", sglScissorIndexedv);
        GetOpenGLFunction("glDepthRangeArrayv", sglDepthRangeArrayv);
        GetOpenGLFunction("glDepthRangeIndexed", sglDepthRangeIndexed);
        GetOpenGLFunction("glGetFloati_v", sglGetFloati_v);
        GetOpenGLFunction("glGetDoublei_v", sglGetDoublei_v);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_4_2
//----------------------------------------------------------------------------
static PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC sglDrawArraysInstancedBaseInstance = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC sglDrawElementsInstancedBaseInstance = nullptr;
static PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC sglDrawElementsInstancedBaseVertexBaseInstance = nullptr;
static PFNGLGETINTERNALFORMATIVPROC sglGetInternalformativ = nullptr;
static PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC sglGetActiveAtomicCounterBufferiv = nullptr;
static PFNGLBINDIMAGETEXTUREPROC sglBindImageTexture = nullptr;
static PFNGLMEMORYBARRIERPROC sglMemoryBarrier = nullptr;
static PFNGLTEXSTORAGE1DPROC sglTexStorage1D = nullptr;
static PFNGLTEXSTORAGE2DPROC sglTexStorage2D = nullptr;
static PFNGLTEXSTORAGE3DPROC sglTexStorage3D = nullptr;
static PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC sglDrawTransformFeedbackInstanced = nullptr;
static PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC sglDrawTransformFeedbackStreamInstanced = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance)
{
    if (sglDrawArraysInstancedBaseInstance)
    {
        sglDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
        ReportGLError("glDrawArraysInstancedBaseInstance");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLuint baseinstance)
{
    if (sglDrawElementsInstancedBaseInstance)
    {
        sglDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
        ReportGLError("glDrawElementsInstancedBaseInstance");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance)
{
    if (sglDrawElementsInstancedBaseVertexBaseInstance)
    {
        sglDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
        ReportGLError("glDrawElementsInstancedBaseVertexBaseInstance");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint *params)
{
    if (sglGetInternalformativ)
    {
        sglGetInternalformativ(target, internalformat, pname, bufSize, params);
        ReportGLError("glGetInternalformativ");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint *params)
{
    if (sglGetActiveAtomicCounterBufferiv)
    {
        sglGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
        ReportGLError("glGetActiveAtomicCounterBufferiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format)
{
    if (sglBindImageTexture)
    {
        sglBindImageTexture(unit, texture, level, layered, layer, access, format);
        ReportGLError("glBindImageTexture");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glMemoryBarrier(GLbitfield barriers)
{
    if (sglMemoryBarrier)
    {
        sglMemoryBarrier(barriers);
        ReportGLError("glMemoryBarrier");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
    if (sglTexStorage1D)
    {
        sglTexStorage1D(target, levels, internalformat, width);
        ReportGLError("glTexStorage1D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
    if (sglTexStorage2D)
    {
        sglTexStorage2D(target, levels, internalformat, width, height);
        ReportGLError("glTexStorage2D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
    if (sglTexStorage3D)
    {
        sglTexStorage3D(target, levels, internalformat, width, height, depth);
        ReportGLError("glTexStorage3D");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount)
{
    if (sglDrawTransformFeedbackInstanced)
    {
        sglDrawTransformFeedbackInstanced(mode, id, instancecount);
        ReportGLError("glDrawTransformFeedbackInstanced");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount)
{
    if (sglDrawTransformFeedbackStreamInstanced)
    {
        sglDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
        ReportGLError("glDrawTransformFeedbackStreamInstanced");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_4_2()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_4_2)
    {
        GetOpenGLFunction("glDrawArraysInstancedBaseInstance", sglDrawArraysInstancedBaseInstance);
        GetOpenGLFunction("glDrawElementsInstancedBaseInstance", sglDrawElementsInstancedBaseInstance);
        GetOpenGLFunction("glDrawElementsInstancedBaseVertexBaseInstance", sglDrawElementsInstancedBaseVertexBaseInstance);
        GetOpenGLFunction("glGetInternalformativ", sglGetInternalformativ);
        GetOpenGLFunction("glGetActiveAtomicCounterBufferiv", sglGetActiveAtomicCounterBufferiv);
        GetOpenGLFunction("glBindImageTexture", sglBindImageTexture);
        GetOpenGLFunction("glMemoryBarrier", sglMemoryBarrier);
        GetOpenGLFunction("glTexStorage1D", sglTexStorage1D);
        GetOpenGLFunction("glTexStorage2D", sglTexStorage2D);
        GetOpenGLFunction("glTexStorage3D", sglTexStorage3D);
        GetOpenGLFunction("glDrawTransformFeedbackInstanced", sglDrawTransformFeedbackInstanced);
        GetOpenGLFunction("glDrawTransformFeedbackStreamInstanced", sglDrawTransformFeedbackStreamInstanced);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_4_3
//----------------------------------------------------------------------------
static PFNGLCLEARBUFFERDATAPROC sglClearBufferData = nullptr;
static PFNGLCLEARBUFFERSUBDATAPROC sglClearBufferSubData = nullptr;
static PFNGLDISPATCHCOMPUTEPROC sglDispatchCompute = nullptr;
static PFNGLDISPATCHCOMPUTEINDIRECTPROC sglDispatchComputeIndirect = nullptr;
static PFNGLCOPYIMAGESUBDATAPROC sglCopyImageSubData = nullptr;
static PFNGLFRAMEBUFFERPARAMETERIPROC sglFramebufferParameteri = nullptr;
static PFNGLGETFRAMEBUFFERPARAMETERIVPROC sglGetFramebufferParameteriv = nullptr;
static PFNGLGETINTERNALFORMATI64VPROC sglGetInternalformati64v = nullptr;
static PFNGLINVALIDATETEXSUBIMAGEPROC sglInvalidateTexSubImage = nullptr;
static PFNGLINVALIDATETEXIMAGEPROC sglInvalidateTexImage = nullptr;
static PFNGLINVALIDATEBUFFERSUBDATAPROC sglInvalidateBufferSubData = nullptr;
static PFNGLINVALIDATEBUFFERDATAPROC sglInvalidateBufferData = nullptr;
static PFNGLINVALIDATEFRAMEBUFFERPROC sglInvalidateFramebuffer = nullptr;
static PFNGLINVALIDATESUBFRAMEBUFFERPROC sglInvalidateSubFramebuffer = nullptr;
static PFNGLMULTIDRAWARRAYSINDIRECTPROC sglMultiDrawArraysIndirect = nullptr;
static PFNGLMULTIDRAWELEMENTSINDIRECTPROC sglMultiDrawElementsIndirect = nullptr;
static PFNGLGETPROGRAMINTERFACEIVPROC sglGetProgramInterfaceiv = nullptr;
static PFNGLGETPROGRAMRESOURCEINDEXPROC sglGetProgramResourceIndex = nullptr;
static PFNGLGETPROGRAMRESOURCENAMEPROC sglGetProgramResourceName = nullptr;
static PFNGLGETPROGRAMRESOURCEIVPROC sglGetProgramResourceiv = nullptr;
static PFNGLGETPROGRAMRESOURCELOCATIONPROC sglGetProgramResourceLocation = nullptr;
static PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC sglGetProgramResourceLocationIndex = nullptr;
static PFNGLSHADERSTORAGEBLOCKBINDINGPROC sglShaderStorageBlockBinding = nullptr;
static PFNGLTEXBUFFERRANGEPROC sglTexBufferRange = nullptr;
static PFNGLTEXSTORAGE2DMULTISAMPLEPROC sglTexStorage2DMultisample = nullptr;
static PFNGLTEXSTORAGE3DMULTISAMPLEPROC sglTexStorage3DMultisample = nullptr;
static PFNGLTEXTUREVIEWPROC sglTextureView = nullptr;
static PFNGLBINDVERTEXBUFFERPROC sglBindVertexBuffer = nullptr;
static PFNGLVERTEXATTRIBFORMATPROC sglVertexAttribFormat = nullptr;
static PFNGLVERTEXATTRIBIFORMATPROC sglVertexAttribIFormat = nullptr;
static PFNGLVERTEXATTRIBLFORMATPROC sglVertexAttribLFormat = nullptr;
static PFNGLVERTEXATTRIBBINDINGPROC sglVertexAttribBinding = nullptr;
static PFNGLVERTEXBINDINGDIVISORPROC sglVertexBindingDivisor = nullptr;
static PFNGLDEBUGMESSAGECONTROLPROC sglDebugMessageControl = nullptr;
static PFNGLDEBUGMESSAGEINSERTPROC sglDebugMessageInsert = nullptr;
static PFNGLDEBUGMESSAGECALLBACKPROC sglDebugMessageCallback = nullptr;
static PFNGLGETDEBUGMESSAGELOGPROC sglGetDebugMessageLog = nullptr;
static PFNGLPUSHDEBUGGROUPPROC sglPushDebugGroup = nullptr;
static PFNGLPOPDEBUGGROUPPROC sglPopDebugGroup = nullptr;
static PFNGLOBJECTLABELPROC sglObjectLabel = nullptr;
static PFNGLGETOBJECTLABELPROC sglGetObjectLabel = nullptr;
static PFNGLOBJECTPTRLABELPROC sglObjectPtrLabel = nullptr;
static PFNGLGETOBJECTPTRLABELPROC sglGetObjectPtrLabel = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void *data)
{
    if (sglClearBufferData)
    {
        sglClearBufferData(target, internalformat, format, type, data);
        ReportGLError("glClearBufferData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void *data)
{
    if (sglClearBufferSubData)
    {
        sglClearBufferSubData(target, internalformat, offset, size, format, type, data);
        ReportGLError("glClearBufferSubData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
{
    if (sglDispatchCompute)
    {
        sglDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
        ReportGLError("glDispatchCompute");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDispatchComputeIndirect(GLintptr indirect)
{
    if (sglDispatchComputeIndirect)
    {
        sglDispatchComputeIndirect(indirect);
        ReportGLError("glDispatchComputeIndirect");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
    if (sglCopyImageSubData)
    {
        sglCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
        ReportGLError("glCopyImageSubData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glFramebufferParameteri(GLenum target, GLenum pname, GLint param)
{
    if (sglFramebufferParameteri)
    {
        sglFramebufferParameteri(target, pname, param);
        ReportGLError("glFramebufferParameteri");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint *params)
{
    if (sglGetFramebufferParameteriv)
    {
        sglGetFramebufferParameteriv(target, pname, params);
        ReportGLError("glGetFramebufferParameteriv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 *params)
{
    if (sglGetInternalformati64v)
    {
        sglGetInternalformati64v(target, internalformat, pname, bufSize, params);
        ReportGLError("glGetInternalformati64v");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
{
    if (sglInvalidateTexSubImage)
    {
        sglInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
        ReportGLError("glInvalidateTexSubImage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glInvalidateTexImage(GLuint texture, GLint level)
{
    if (sglInvalidateTexImage)
    {
        sglInvalidateTexImage(texture, level);
        ReportGLError("glInvalidateTexImage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
    if (sglInvalidateBufferSubData)
    {
        sglInvalidateBufferSubData(buffer, offset, length);
        ReportGLError("glInvalidateBufferSubData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glInvalidateBufferData(GLuint buffer)
{
    if (sglInvalidateBufferData)
    {
        sglInvalidateBufferData(buffer);
        ReportGLError("glInvalidateBufferData");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments)
{
    if (sglInvalidateFramebuffer)
    {
        sglInvalidateFramebuffer(target, numAttachments, attachments);
        ReportGLError("glInvalidateFramebuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum *attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
    if (sglInvalidateSubFramebuffer)
    {
        sglInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
        ReportGLError("glInvalidateSubFramebuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glMultiDrawArraysIndirect(GLenum mode, const void *indirect, GLsizei drawcount, GLsizei stride)
{
    if (sglMultiDrawArraysIndirect)
    {
        sglMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
        ReportGLError("glMultiDrawArraysIndirect");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void *indirect, GLsizei drawcount, GLsizei stride)
{
    if (sglMultiDrawElementsIndirect)
    {
        sglMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
        ReportGLError("glMultiDrawElementsIndirect");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint *params)
{
    if (sglGetProgramInterfaceiv)
    {
        sglGetProgramInterfaceiv(program, programInterface, pname, params);
        ReportGLError("glGetProgramInterfaceiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLuint APIENTRY glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar *name)
{
    GLuint result;
    if (sglGetProgramResourceIndex)
    {
        result = sglGetProgramResourceIndex(program, programInterface, name);
        ReportGLError("glGetProgramResourceIndex");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei *length, GLchar *name)
{
    if (sglGetProgramResourceName)
    {
        sglGetProgramResourceName(program, programInterface, index, bufSize, length, name);
        ReportGLError("glGetProgramResourceName");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum *props, GLsizei bufSize, GLsizei *length, GLint *params)
{
    if (sglGetProgramResourceiv)
    {
        sglGetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
        ReportGLError("glGetProgramResourceiv");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLint APIENTRY glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar *name)
{
    GLint result;
    if (sglGetProgramResourceLocation)
    {
        result = sglGetProgramResourceLocation(program, programInterface, name);
        ReportGLError("glGetProgramResourceLocation");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
GLint APIENTRY glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar *name)
{
    GLint result;
    if (sglGetProgramResourceLocationIndex)
    {
        result = sglGetProgramResourceLocationIndex(program, programInterface, name);
        ReportGLError("glGetProgramResourceLocationIndex");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
{
    if (sglShaderStorageBlockBinding)
    {
        sglShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
        ReportGLError("glShaderStorageBlockBinding");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
    if (sglTexBufferRange)
    {
        sglTexBufferRange(target, internalformat, buffer, offset, size);
        ReportGLError("glTexBufferRange");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    if (sglTexStorage2DMultisample)
    {
        sglTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
        ReportGLError("glTexStorage2DMultisample");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
    if (sglTexStorage3DMultisample)
    {
        sglTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
        ReportGLError("glTexStorage3DMultisample");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
{
    if (sglTextureView)
    {
        sglTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
        ReportGLError("glTextureView");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
    if (sglBindVertexBuffer)
    {
        sglBindVertexBuffer(bindingindex, buffer, offset, stride);
        ReportGLError("glBindVertexBuffer");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
    if (sglVertexAttribFormat)
    {
        sglVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
        ReportGLError("glVertexAttribFormat");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    if (sglVertexAttribIFormat)
    {
        sglVertexAttribIFormat(attribindex, size, type, relativeoffset);
        ReportGLError("glVertexAttribIFormat");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    if (sglVertexAttribLFormat)
    {
        sglVertexAttribLFormat(attribindex, size, type, relativeoffset);
        ReportGLError("glVertexAttribLFormat");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
{
    if (sglVertexAttribBinding)
    {
        sglVertexAttribBinding(attribindex, bindingindex);
        ReportGLError("glVertexAttribBinding");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
{
    if (sglVertexBindingDivisor)
    {
        sglVertexBindingDivisor(bindingindex, divisor);
        ReportGLError("glVertexBindingDivisor");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled)
{
    if (sglDebugMessageControl)
    {
        sglDebugMessageControl(source, type, severity, count, ids, enabled);
        ReportGLError("glDebugMessageControl");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf)
{
    if (sglDebugMessageInsert)
    {
        sglDebugMessageInsert(source, type, id, severity, length, buf);
        ReportGLError("glDebugMessageInsert");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glDebugMessageCallback(GLDEBUGPROC callback, const void *userParam)
{
    if (sglDebugMessageCallback)
    {
        sglDebugMessageCallback(callback, userParam);
        ReportGLError("glDebugMessageCallback");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
GLuint APIENTRY glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog)
{
    GLuint result;
    if (sglGetDebugMessageLog)
    {
        result = sglGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
        ReportGLError("glGetDebugMessageLog");
    }
    else
    {
        assert(false);
        result = 0;
    }
    return result;
}
//----------------------------------------------------------------------------
void APIENTRY glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar *message)
{
    if (sglPushDebugGroup)
    {
        sglPushDebugGroup(source, id, length, message);
        ReportGLError("glPushDebugGroup");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glPopDebugGroup()
{
    if (sglPopDebugGroup)
    {
        sglPopDebugGroup();
        ReportGLError("glPopDebugGroup");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar *label)
{
    if (sglObjectLabel)
    {
        sglObjectLabel(identifier, name, length, label);
        ReportGLError("glObjectLabel");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label)
{
    if (sglGetObjectLabel)
    {
        sglGetObjectLabel(identifier, name, bufSize, length, label);
        ReportGLError("glGetObjectLabel");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glObjectPtrLabel(const void *ptr, GLsizei length, const GLchar *label)
{
    if (sglObjectPtrLabel)
    {
        sglObjectPtrLabel(ptr, length, label);
        ReportGLError("glObjectPtrLabel");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glGetObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label)
{
    if (sglGetObjectPtrLabel)
    {
        sglGetObjectPtrLabel(ptr, bufSize, length, label);
        ReportGLError("glGetObjectPtrLabel");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_4_3()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_4_3)
    {
        GetOpenGLFunction("glClearBufferData", sglClearBufferData);
        GetOpenGLFunction("glClearBufferSubData", sglClearBufferSubData);
        GetOpenGLFunction("glDispatchCompute", sglDispatchCompute);
        GetOpenGLFunction("glDispatchComputeIndirect", sglDispatchComputeIndirect);
        GetOpenGLFunction("glCopyImageSubData", sglCopyImageSubData);
        GetOpenGLFunction("glFramebufferParameteri", sglFramebufferParameteri);
        GetOpenGLFunction("glGetFramebufferParameteriv", sglGetFramebufferParameteriv);
        GetOpenGLFunction("glGetInternalformati64v", sglGetInternalformati64v);
        GetOpenGLFunction("glInvalidateTexSubImage", sglInvalidateTexSubImage);
        GetOpenGLFunction("glInvalidateTexImage", sglInvalidateTexImage);
        GetOpenGLFunction("glInvalidateBufferSubData", sglInvalidateBufferSubData);
        GetOpenGLFunction("glInvalidateBufferData", sglInvalidateBufferData);
        GetOpenGLFunction("glInvalidateFramebuffer", sglInvalidateFramebuffer);
        GetOpenGLFunction("glInvalidateSubFramebuffer", sglInvalidateSubFramebuffer);
        GetOpenGLFunction("glMultiDrawArraysIndirect", sglMultiDrawArraysIndirect);
        GetOpenGLFunction("glMultiDrawElementsIndirect", sglMultiDrawElementsIndirect);
        GetOpenGLFunction("glGetProgramInterfaceiv", sglGetProgramInterfaceiv);
        GetOpenGLFunction("glGetProgramResourceIndex", sglGetProgramResourceIndex);
        GetOpenGLFunction("glGetProgramResourceName", sglGetProgramResourceName);
        GetOpenGLFunction("glGetProgramResourceiv", sglGetProgramResourceiv);
        GetOpenGLFunction("glGetProgramResourceLocation", sglGetProgramResourceLocation);
        GetOpenGLFunction("glGetProgramResourceLocationIndex", sglGetProgramResourceLocationIndex);
        GetOpenGLFunction("glShaderStorageBlockBinding", sglShaderStorageBlockBinding);
        GetOpenGLFunction("glTexBufferRange", sglTexBufferRange);
        GetOpenGLFunction("glTexStorage2DMultisample", sglTexStorage2DMultisample);
        GetOpenGLFunction("glTexStorage3DMultisample", sglTexStorage3DMultisample);
        GetOpenGLFunction("glTextureView", sglTextureView);
        GetOpenGLFunction("glBindVertexBuffer", sglBindVertexBuffer);
        GetOpenGLFunction("glVertexAttribFormat", sglVertexAttribFormat);
        GetOpenGLFunction("glVertexAttribIFormat", sglVertexAttribIFormat);
        GetOpenGLFunction("glVertexAttribLFormat", sglVertexAttribLFormat);
        GetOpenGLFunction("glVertexAttribBinding", sglVertexAttribBinding);
        GetOpenGLFunction("glVertexBindingDivisor", sglVertexBindingDivisor);
        GetOpenGLFunction("glDebugMessageControl", sglDebugMessageControl);
        GetOpenGLFunction("glDebugMessageInsert", sglDebugMessageInsert);
        GetOpenGLFunction("glDebugMessageCallback", sglDebugMessageCallback);
        GetOpenGLFunction("glGetDebugMessageLog", sglGetDebugMessageLog);
        GetOpenGLFunction("glPushDebugGroup", sglPushDebugGroup);
        GetOpenGLFunction("glPopDebugGroup", sglPopDebugGroup);
        GetOpenGLFunction("glObjectLabel", sglObjectLabel);
        GetOpenGLFunction("glGetObjectLabel", sglGetObjectLabel);
        GetOpenGLFunction("glObjectPtrLabel", sglObjectPtrLabel);
        GetOpenGLFunction("glGetObjectPtrLabel", sglGetObjectPtrLabel);
    }
}
//----------------------------------------------------------------------------
// GL_VERSION_4_4
//----------------------------------------------------------------------------
static PFNGLBUFFERSTORAGEPROC sglBufferStorage = nullptr;
static PFNGLCLEARTEXIMAGEPROC sglClearTexImage = nullptr;
static PFNGLCLEARTEXSUBIMAGEPROC sglClearTexSubImage = nullptr;
static PFNGLBINDBUFFERSBASEPROC sglBindBuffersBase = nullptr;
static PFNGLBINDBUFFERSRANGEPROC sglBindBuffersRange = nullptr;
static PFNGLBINDTEXTURESPROC sglBindTextures = nullptr;
static PFNGLBINDSAMPLERSPROC sglBindSamplers = nullptr;
static PFNGLBINDIMAGETEXTURESPROC sglBindImageTextures = nullptr;
static PFNGLBINDVERTEXBUFFERSPROC sglBindVertexBuffers = nullptr;
//----------------------------------------------------------------------------
void APIENTRY glBufferStorage(GLenum target, GLsizeiptr size, const void *data, GLbitfield flags)
{
    if (sglBufferStorage)
    {
        sglBufferStorage(target, size, data, flags);
        ReportGLError("glBufferStorage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void *data)
{
    if (sglClearTexImage)
    {
        sglClearTexImage(texture, level, format, type, data);
        ReportGLError("glClearTexImage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data)
{
    if (sglClearTexSubImage)
    {
        sglClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
        ReportGLError("glClearTexSubImage");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint *buffers)
{
    if (sglBindBuffersBase)
    {
        sglBindBuffersBase(target, first, count, buffers);
        ReportGLError("glBindBuffersBase");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizeiptr *sizes)
{
    if (sglBindBuffersRange)
    {
        sglBindBuffersRange(target, first, count, buffers, offsets, sizes);
        ReportGLError("glBindBuffersRange");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindTextures(GLuint first, GLsizei count, const GLuint *textures)
{
    if (sglBindTextures)
    {
        sglBindTextures(first, count, textures);
        ReportGLError("glBindTextures");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindSamplers(GLuint first, GLsizei count, const GLuint *samplers)
{
    if (sglBindSamplers)
    {
        sglBindSamplers(first, count, samplers);
        ReportGLError("glBindSamplers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindImageTextures(GLuint first, GLsizei count, const GLuint *textures)
{
    if (sglBindImageTextures)
    {
        sglBindImageTextures(first, count, textures);
        ReportGLError("glBindImageTextures");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
void APIENTRY glBindVertexBuffers(GLuint first, GLsizei count, const GLuint *buffers, const GLintptr *offsets, const GLsizei *strides)
{
    if (sglBindVertexBuffers)
    {
        sglBindVertexBuffers(first, count, buffers, offsets, strides);
        ReportGLError("glBindVertexBuffers");
    }
    else
    {
        assert(false);
    }
}
//----------------------------------------------------------------------------
static void Initialize_OPENGL_VERSION_4_4()
{
    if (GetOpenGLVersion() >= OPENGL_VERSION_4_4)
    {
        GetOpenGLFunction("glBufferStorage", sglBufferStorage);
        GetOpenGLFunction("glClearTexImage", sglClearTexImage);
        GetOpenGLFunction("glClearTexSubImage", sglClearTexSubImage);
        GetOpenGLFunction("glBindBuffersBase", sglBindBuffersBase);
        GetOpenGLFunction("glBindBuffersRange", sglBindBuffersRange);
        GetOpenGLFunction("glBindTextures", sglBindTextures);
        GetOpenGLFunction("glBindSamplers", sglBindSamplers);
        GetOpenGLFunction("glBindImageTextures", sglBindImageTextures);
        GetOpenGLFunction("glBindVertexBuffers", sglBindVertexBuffers);
    }
}
//----------------------------------------------------------------------------
void InitializeOpenGL(char const* infofile)
{
#if !defined(WIN32)
    Initialize_OPENGL_VERSION_1_0();
    Initialize_OPENGL_VERSION_1_1();
#endif

    Initialize_OPENGL_VERSION_1_2();
    Initialize_OPENGL_VERSION_1_3();
    Initialize_OPENGL_VERSION_1_4();
    Initialize_OPENGL_VERSION_1_5();
    Initialize_OPENGL_VERSION_2_0();
    Initialize_OPENGL_VERSION_2_1();
    Initialize_OPENGL_VERSION_3_0();
    Initialize_OPENGL_VERSION_3_1();
    Initialize_OPENGL_VERSION_3_2();
    Initialize_OPENGL_VERSION_3_3();
    Initialize_OPENGL_VERSION_4_0();
    Initialize_OPENGL_VERSION_4_1();
    Initialize_OPENGL_VERSION_4_2();
    Initialize_OPENGL_VERSION_4_3();
    Initialize_OPENGL_VERSION_4_4();

    if (infofile)
    {
        std::ofstream output(infofile);
        if (output)
        {
            char const* vendor = (char const*)glGetString(GL_VENDOR);
            if (vendor)
            {
                output << "vendor = " << vendor;
            }
            else
            {
                output << "vendor = <null>";
            }
            output << std::endl;

            char const* renderer = (char const*)glGetString(GL_RENDERER);
            if (vendor)
            {
                output << "renderer = " << renderer;
            }
            else
            {
                output << "renderer = <null>";
            }
            output << std::endl;

            char const* version = (char const*)glGetString(GL_VERSION);
            if (version)
            {
                output << "version = " << version;
            }
            else
            {
                output << "version = <null>";
            }
            output << std::endl;

            if (GetOpenGLVersion() >= OPENGL_VERSION_3_0)
            {
                GLint numExtensions;
                glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
                for (int i = 0; i < numExtensions; ++i)
                {
                    output << glGetStringi(GL_EXTENSIONS, i) << std::endl;
                }
            }
            else
            {
                char const* extensions =
                    (char const*)glGetString(GL_EXTENSIONS);
                if (extensions)
                {
                    output << "extensions =" << std::endl;
                    size_t numBytes = strlen(extensions) + 1;
                    char* extension = new char[numBytes];
                    strcpy_s(extension, numBytes, extensions);
                    char* nextToken = nullptr;
                    char* token = strtok_s(extension, " \t\n", &nextToken);
                    while (token)
                    {
                        output << "    " << token << std::endl;
                        token = strtok_s(nullptr, " \t\n", &nextToken);
                    }
                    delete[] extension;
                }
                else
                {
                    output << "extensions = <null>" << std::endl;
                }
            }

            output.close();
        }
    }
}
//----------------------------------------------------------------------------
