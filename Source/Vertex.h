//
//  Vertex.h
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

#include <vector>

#include "Vector3.h"

namespace Degas {
    class Face;
    class Mesh;
    
    class Vertex {
    public:
        
    private:
        Vector3 m_position;
        std::vector<Vertex*> m_adjacentVertices;
        std::vector<Face*> m_adjacentFaces;
    };
}

#endif // Vertex_h
