//
//  SurfaceGroup.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "SurfaceGroup.h"

namespace Degas {
    bool SurfaceGroup::hit(const Ray& ray, HitInfo* hitInfo)
    {
        //if (!m_boundingBox.doesHit(ray)) {
        //    return false;
        //}
        
        double hitDistance = INFINITY;
        HitInfo intersectionInfo;
        
        // find nearest intersection
        for (unsigned int i = 0; i < m_surfaces.size(); i++) {
            Surface* s = m_surfaces[i];
            if (s->hit(ray, &intersectionInfo)) {
                if (intersectionInfo.distance < hitDistance) {
                    hitDistance = intersectionInfo.distance;
                    *hitInfo = intersectionInfo;
                }
            }
        }
        return hitDistance != INFINITY;
    }
    
    void SurfaceGroup::drawGL()
    {
        for (unsigned int i = 0; i < m_surfaces.size(); i++) {
            m_surfaces[i]->drawGL();
        }
    }
    
    void SurfaceGroup::applyTransformation(const Matrix4& t)
    {
        for (unsigned int i = 0; i < m_surfaces.size(); i++) {
            Surface *s = m_surfaces[i];
            s->applyTransformation(t);
        }
        //updateBoudingBox();
    }
}
