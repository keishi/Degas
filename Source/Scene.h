//
//  Scene.h
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#ifndef Scene_h
#define Scene_h

#include "SurfaceGroup.h"
#include "Camera.h"
#include "Image.h"

namespace Degas {
    class Scene {
    public:
        Scene()
        {
            m_rootGroup = new SurfaceGroup();
        }
        
        void renderGL(Camera* camera);
        void rasterize(Camera* camera, Image* image);
        
        SurfaceGroup* rootGroup() { return m_rootGroup; }
        
    private:
        SurfaceGroup* m_rootGroup;
    };
}

#endif // Scene_h