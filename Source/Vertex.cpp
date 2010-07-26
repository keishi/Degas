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
    
    Vertex::~Vertex()
    {
        m_adjacentVertices.clear();
        m_adjacentFaces.clear();
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
            }
        }
        m_adjacentEdges.push_back(e);
    }
    
    void Vertex::addAdjacentFace(Face* f)
    {
        m_adjacentFaces.push_back(f);
    }
}
