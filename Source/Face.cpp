//
//  Face.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "Face.h"

#include "Mesh.h"
#include "utils.h"
#include "Triangle.h"

namespace Degas {
    Face::Face(Mesh* mesh, int vertexIndex1, int vertexIndex2, int vertexIndex3)
    {
        m_mesh = mesh;
        m_v1 = m_mesh->getVertex(vertexIndex1);
        m_v2 = m_mesh->getVertex(vertexIndex2);
        m_v3 = m_mesh->getVertex(vertexIndex3);
        calculateNormal();
    }
    
    void Face::calculateNormal()
    {
        Vector3 p1 = m_v1->position();
        Vector3 p2 = m_v2->position();
        Vector3 p3 = m_v3->position();
        
        Vector3 v12 = p2 - p1;
        Vector3 v13 = p3 - p1;
        
        m_normal = v12.cross(v13).normalized();
    }
    
    Surface* Face::createSurface(Material* material)
    {
        Triangle* t = new Triangle(m_v1->position(), m_v2->position(), m_v3->position());
        if (material) {
            t->setMaterial(material);
        }
        return (Surface*)t;
    }
    
    void Face::changeVertex(Vertex* from, Vertex* to)
    {
        if (from == m_v1) {
            m_v1 = to;
        } else if (from == m_v2) {
            m_v2 = to;
        } else if (from == m_v3) {
            m_v3 = to;
        }
    }
}
