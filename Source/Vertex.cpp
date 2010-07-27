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
        m_weight = 1;
    }
    
    void Vertex::addAdjacentVertex(Vertex* v)
    {
        m_adjacentVertices.push_back(v);
    }
    
    void Vertex::addAdjacentEdge(Edge* e)
    {
        m_adjacentEdges.push_back(e);
    }
    
    void Vertex::removeAdjacentEdge(Edge* e)
    {
        std::vector<Edge*>::iterator i;
        for (i = m_adjacentEdges.begin(); i != m_adjacentEdges.end(); ++i){
            if ((*i) == e) {
                m_adjacentEdges.erase(i);
                return;
            }
        }
    }
    
    void Vertex::addAdjacentFace(Face* f)
    {
        m_adjacentFaces.push_back(f);
    }
    
    void Vertex::removeAdjacentFace(Face* f)
    {
        std::vector<Face*>::iterator i;
        for (i = m_adjacentFaces.begin(); i != m_adjacentFaces.end(); ++i){
            if ((*i) == f) {
                m_adjacentFaces.erase(i);
                return;
            }
        }
    }
}
