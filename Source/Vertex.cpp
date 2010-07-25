//
//  Vertex.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "Vertex.h"

namespace Degas {
    Vertex::Vertex(int index, double x, double y, double z) {
        m_index = index;
        m_position = Vector3(x, y, z);
    }
    
    void Vertex::addAdjacentVertex(Vertex* v)
    {
        m_adjacentVertices.push_back(v);
    }
    
    void Vertex::addAdjacentFace(Face* f)
    {
        m_adjacentFaces.push_back(f);
    }
    
}
