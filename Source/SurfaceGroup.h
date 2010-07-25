//
//  SurfaceGroup.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef SurfaceGroup_h
#define SurfaceGroup_h

#include <vector>

#include "Surface.h"

namespace Degas {
    class SurfaceGroup : public Surface {
    public:
        std::vector<Surface*>& surfaces() { return m_surfaces; }
        void addSurface(Surface* s)
        {
            m_surfaces.push_back(s);
        }
        void removeSurface(Surface* s)
        {
            std::vector<Surface*>::iterator i;
            for (i = m_surfaces.begin(); i != m_surfaces.end(); ++i){
                if (s == *i) {
                    m_surfaces.erase(i);
                    return;
                }
            }
        }
        
        bool hit(const Ray& ray, HitInfo* hitInfo);
        void drawGL();
        void applyTransformation(const Matrix4& t);
        
    private:
        std::vector<Surface*> m_surfaces;
    };
}

#endif
