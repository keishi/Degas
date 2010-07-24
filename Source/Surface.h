//
//  Surface.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Surface_h
#define Surface_h

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "Matrix4.h"
#include "Ray.h"

namespace Degas {
    class Surface;
    
    typedef struct {
        Vector3 position;
        Vector3 normal;
        double distance;
        Surface* surface;
        Ray ray;
        //Vector2 uv;
    } HitInfo;
    
    class Surface {
    public:
        Surface()
        {
        }
        
        virtual bool hit(const Ray& ray, HitInfo* hitInfo) = 0;
        virtual void drawGL() = 0;
        virtual void applyTransformation(const Matrix4& t) = 0;
    };
}

#endif
