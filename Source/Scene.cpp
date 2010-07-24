//
//  Scene.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "Scene.h"
#include "utils.h"

namespace Degas {
    void Scene::renderGL(Camera* camera)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glLoadIdentity();
        gluPerspective(rad2deg(camera->FOV()), camera->aspect(), 0.1, 1000.0);
        gluLookAt(camera->eye().x(), camera->eye().y(), camera->eye().z(), 
                  camera->lookat().x(), camera->lookat().y(), camera->lookat().z(), 
                  camera->up().x(), camera->up().y(), camera->up().z());
        
        glEnable( GL_DEPTH_TEST );
        
        glCullFace(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        
        //glEnable(GL_LIGHTING);
        //glEnable(GL_LIGHT0);
        //for (unsigned int i = 0; i < m_lights.size(); i++) {
        //    LightRef light = m_lights[i];
        //    light->drawGL();
        //}
        
        m_rootGroup->drawGL();
        
        glDisable(GL_DEPTH_TEST);
        
        glFlush();
    }
    
    void Scene::rasterize(Camera* camera, Image* image) {
        for (unsigned int y = 0; y < image->height(); y++) {
            for (unsigned int x = 0; x < image->width(); x++) {
                double xPos = 2.0 * (double)x / (double) image->width() - 1.0;
                double yPos = 2.0 * (double)y / (double) image->height() - 1.0;
                Ray viewRay = camera->viewRay(xPos, yPos);
                HitInfo hitInfo;
                if (m_rootGroup->hit(viewRay, &hitInfo)) {
                    image->setPixelColor(x, y, hitInfo.material->color());
                }
            }
        }
    }
}