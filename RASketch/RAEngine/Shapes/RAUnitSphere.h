//
//  RAUnitSphere.h
//  PAM2
//
//  Created by Rinat Abdrashitov on 2014-06-28.
//  Copyright (c) 2014 Rinat Abdrashitov. All rights reserved.
//

#ifndef __PAM2__RAUnitSphere__
#define __PAM2__RAUnitSphere__

#include <iostream>
#include "RAMesh.h"
#include "GteVector3.h"

namespace RAEngine {
    class RAUnitSphere : public RAMesh
    {
    public:
        RAUnitSphere();
        RAUnitSphere(const gte::Vector3f& point);
        void setCenter(const gte::Vector3f& point);

        void setupShaders(const std::string vertexShader, const std::string fragmentShader);
        void resetTranslation();
        int  loadObjFile(const char* path, const char* file) override;
        Bounds getBoundingBox() const override;
        void draw() const;
    private:
        gte::Vector3f center;
    };
}

#endif /* defined(__PAM2__RAUnitSphere__) */
