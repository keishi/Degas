//
//  Face.h
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef Face_h
#define Face_h

#include "Vertex.h"

namespace Degas {
    class Face {
    public:
        Face(Vertex* v0, Vertex* v1, Vertex* v2);
        
        bool hasVertex(Vertex* v);
        
    private:
        Vertex* m_v1;
        Vertex* m_v2;
        Vertex* m_v3;
        Vector3 m_normal;
        Mesh* m_mesh;
    };
}


#endif // Face_h