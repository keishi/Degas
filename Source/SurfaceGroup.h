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
        SurfaceGroup()
        {
        }
        
        std::vector<Surface*>& surfaces() { return m_surfaces; };
        void addSurface(Surface* s)
        {
            m_surfaces.push_back(s);
        }
        
        bool hit(const Ray& ray, HitInfo* hitInfo);
        void drawGL();
        void applyTransformation(const Matrix4& t);
        
    private:
        std::vector<Surface*> m_surfaces;
    };
    
    typedef SurfaceGroup* SurfaceGroupRef;
}

#endif
