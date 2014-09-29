//
//  RAMesh.h
//  PAM2
//
//  Created by Rinat Abdrashitov on 2014-06-11.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#ifndef __PAM2__RAMesh__
#define __PAM2__RAMesh__

#include <iostream>

#include <GteTransform.h>
#include <GteMatrix3x3.h>

#include <GteVector2.h>
#include <GteVector4.h>
#include "RAES2VertexBuffer.h"
#include "RAES2ShaderProgram.h"
#include "RAES2VertexArray.h"
#include "RALogManager.h"

#include "RA_Types.h"
#if defined(RA_OS_IPHONE)
#import <OpenGLES/ES2/gl.h>
#elif defined(RA_OS_MAC)
#import <OpenGL/gl.h>
#endif

namespace RAEngine
{
    typedef gte::Transform<float> Mat4x4;
    typedef gte::Matrix3x3<float> Mat3x3;
    typedef gte::Vector3<float> Vec3;
    typedef gte::Vector2<float> Vec2;
    
    struct Bounds {
        Vec3 minBound;
        Vec3 maxBound;
        Vec3 center;
        float radius;
    };
    
    class RAMesh
    {
    public:
        RAMesh();
        ~RAMesh();
        
        bool enabled;
        
        Mat4x4 viewMatrix;
        Mat4x4 projectionMatrix;

        GLsizei numVerticies;
        GLsizei numIndicies;
        GLsizei numWireframeIndicies;
        
        Mat4x4 getModelViewProjectionMatrix() const;
        Mat4x4 getModelViewMatrix() const;
        Mat4x4 getModelMatrix() const;
        Mat3x3 getNormalMatrix() const;
        
//        void rotate(float radians, Vec3 axis); //rotates around world origin
        void rotate(float radians, Vec3 axis, Vec3 toPivot);
        void rotate(Mat4x4 mat);
        void translate(Vec3 translation);
        void scale(Vec3 scale, Vec3 toPivot);

        ///override in the child
//        virtual void bufferVertexDataToGPU(bool deleteCPUdata);
        
        ///override in the child
        virtual Bounds getBoundingBox() const = 0;
        
        ///override in the child
        virtual int loadObjFile(const char* path);
        
        ///override in the child
        virtual void draw() const = 0;
        
        ///override in the child
//        virtual void drawToDepthBuffer();
        
        ///override in the child
//        virtual void drawWireframe() const = 0;
        
        // Test for intersection of linear component and bound (points of
        // intersection not computed).  The linear component is parameterized by
        // P + t*D, where P is a point on the component (the origin) and D is a
        // unit-length direction vector.  The interval [tmin,tmax] is
        //   line:     tmin = -Mathf::MAX_REAL, tmax = Mathf::MAX_REAL
        //   ray:      tmin = 0.0f, tmax = Mathf::MAX_REAL
        //   segment:  tmin >= 0.0f, tmax > tmin
//        virtual bool testBoundingBoxIntersection(const Vec3& origin, const Vec3& direction,
//                                                 float tmin, float tmax) const;


    private:
//        Vec3* positions;
//        Vec3* normals;
    protected:
        
        Mat4x4 translationMatrix;
        Mat4x4 rotationMatrix;
        Mat4x4 scaleMatrix;
        
        enum
        {
            UNIFORM_MODELVIEWPROJECTION_MATRIX,
            UNIFORM_MODELVIEW_MATRIX,
            UNIFORM_MODEL_MATRIX,
            UNIFORM_NORMAL_MATRIX,
            UNIFORM_TEXTURE,
            UNIFORM_LIGHT_POSITION,
            UNIFORM_LIGHT_DIRECTION,
            UNIFORM_LIGHT_COLOR,
            UNIFORM_POINT_SIZE,
            NUM_UNIFORMS
        };
        
        enum
        {
            ATTRIB_COLOR,
            ATTRIB_POSITION,
            ATTRIB_TEXT,
            ATTRIB_NORMAL,
            NUM_ATTRIB
        };
      
        //Display Shader Variables
        GLint attrib[NUM_ATTRIB];
        GLint uniforms[NUM_UNIFORMS];
        
        //Off Screen Depth Shader Variables
        GLint attribDepth[NUM_ATTRIB];
        GLint uniformsDepth[NUM_UNIFORMS];
        
        //Indexed vertex data
        RAES2VertexBuffer* positionDataBuffer = nullptr;
        RAES2VertexBuffer* normalDataBuffer = nullptr;
        RAES2VertexBuffer* colorDataBuffer = nullptr;
        RAES2VertexBuffer* indexDataBuffer = nullptr;

        //Interlieved vertex data
        RAES2VertexBuffer* vertexDataBuffer = nullptr;
        
        //Indexed wireframe data
        RAES2VertexBuffer* wireframeColorBuffer = nullptr;
        RAES2VertexBuffer* wireframeIndexBuffer = nullptr;

        //Vertex array
        RAES2VertexArray* vertexArray = nullptr;
        
        //Shaders
        RAES2ShaderProgram* drawShaderProgram = nullptr;
        RAES2ShaderProgram* depthShaderProgram = nullptr;
    };
}

#endif /* defined(__PAM2__RAMesh__) */
