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
    
    bool Vertex::isAdjactentTo(Vertex* v)
    {
        std::vector<Vertex*>::iterator i;
        for (i = m_adjacentVertices.begin(); i != m_adjacentVertices.end(); ++i){
            if ((*i) == v) {
                return true;
            }
        }
    }
    
    void Vertex::addAdjacentVertex(Vertex* v)
    {
        if (!isAdjactentTo(v)) {
            m_adjacentVertices.push_back(v);
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
    
    void Vertex::removeAdjacentVertex(Vertex* v)
    {
        std::vector<Vertex*>::iterator i;
        for (i = m_adjacentVertices.begin(); i != m_adjacentVertices.end(); ++i){
            if ((*i) == v) {
                m_adjacentVertices.erase(i);
                return;
            }
        }
    }
}
