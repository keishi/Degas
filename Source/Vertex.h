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
        Vertex(int index, double x, double y, double z);
        
        int index() { return m_index; }
        void setIndex(int index) { m_index = index; }
        
    private:
        int m_index;
        Vector3 m_position;
        std::vector<Vertex*> m_adjacentVertices;
        std::vector<Face*> m_adjacentFaces;
    };
}

#endif // Vertex_h
