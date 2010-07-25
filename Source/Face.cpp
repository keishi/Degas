//
//  Face.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "Face.h"

#include "Mesh.h"

namespace Degas {
    Face::Face(Mesh* mesh, int vertexIndex1, int vertexIndex2, int vertexIndex3)
    {
        m_mesh = mesh;
        m_v1 = m_mesh->getVertex(vertexIndex1);
        m_v2 = m_mesh->getVertex(vertexIndex2);
        m_v3 = m_mesh->getVertex(vertexIndex3);
    }
}
