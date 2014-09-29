//
//  RAMesh.cpp
//  PAM2
//
//  Created by Rinat Abdrashitov on 2014-06-11.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#include "RAMesh.h"
#include <limits>

namespace RAEngine {

    using namespace gte;
    
#pragma mark - Public methods
    RAMesh::RAMesh()
    {
        viewMatrix.SetIdentity();
        projectionMatrix.SetIdentity();
        
        translationMatrix.SetIdentity();
        rotationMatrix.SetIdentity();
        scaleMatrix.SetIdentity();
        
        enabled = false;
        
        numVerticies = 0;
        numIndicies = 0;
        numWireframeIndicies = 0;
    }
    
    RAMesh::~RAMesh()
    {
        //Indexed vertex data
        delete positionDataBuffer;
        delete normalDataBuffer;
        delete colorDataBuffer;
        delete indexDataBuffer;

        //Interlieved vertex data
        delete vertexDataBuffer;
        
        //Indexed wireframe data
        delete wireframeColorBuffer;
        delete wireframeIndexBuffer;
        
        //Vertex array
        delete vertexArray;

        //Shaders
        delete drawShaderProgram;
        delete depthShaderProgram;
    }
    
    Mat4x4 RAMesh::getModelViewProjectionMatrix() const
    {
        return projectionMatrix * getModelViewMatrix();
    }
    
    Mat4x4 RAMesh::getModelViewMatrix() const
    {
        return viewMatrix * getModelMatrix();
    }
    
    Mat4x4 RAMesh::getModelMatrix() const
    {
        //TODO check the order!
        Mat4x4 modelMatrix = translationMatrix*rotationMatrix*scaleMatrix;
        return modelMatrix;
    }
    
    Mat3x3 RAMesh::getNormalMatrix() const
    {
        return Transpose(Inverse(GetMatrix3x3(getModelViewMatrix())));
    }
    
    void RAMesh::rotate(float radians, Vec3 axis, Vec3 toPivot)
    {
//        Mat4x4 toOrigin = translation_Mat4x4f(toPivot);
//        Mat4x4 fromOrigin = translation_Mat4x4f(-1 * toPivot);
//        Vec3f modelAxis = Vec3f(invert_ortho(getModelViewMatrix()) * Vec4f(axis, 0));
//        Mat4x4 rotMat = rotation_Mat4x4f(modelAxis, radians);
//        rotationMatrix = fromOrigin * rotMat * toOrigin * rotationMatrix;
    }
    
    void RAMesh::rotate(Mat4x4 mat)
    {
        rotationMatrix = mat * rotationMatrix;
    }
    
    void RAMesh::translate(Vec3 translation)
    {
        Transform<float> tr;
        tr.SetTranslation(translation);
        translationMatrix = tr * translationMatrix;
    }
    
    void RAMesh::scale(Vec3 scale, Vec3 toPivot)
    {
        Transform<float> scaleMat;
        scaleMat.MakeDiagonal(scale[0], scale[1], scale[2], 1.0);
        scaleMatrix = scaleMat;
    }
    
    int RAMesh::loadObjFile(const char* path)
    {
        return 0;
    }
}