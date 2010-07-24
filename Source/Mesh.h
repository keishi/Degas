//
//  Mesh.h
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <vector>

#include "Vertex.h"
#include "Face.h"

namespace Degas {
    class Mesh {
    public:
        
    private:
        std::vector<Vertex*> m_vertexList;
        std::vector<Face*> m_faceList;
    };
}

#endif // Mesh_h