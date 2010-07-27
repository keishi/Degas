//
//  StructuredMesh.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/27/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "StructuredMesh.h"

namespace Degas {
    StructuredMesh::StructuredMesh(char* filename, int width, int height) {
        m_mesh = new Mesh(filename);
        m_width = width;
        m_height = height;
        int i, j;
        for (j = 0; j < m_height - 1; j++) {
            for (i = 0; i < m_width; i++) {
                Edge* e = m_mesh->getEdge(getVertex(i, j), getVertex(i, j + 1));
                m_verticalEdges.push_back(e);
            }
        }
        for (j = 0; j < m_height; j++) {
            for (i = 0; i < m_width - 1; i++) {
                Edge* e = m_mesh->getEdge(getVertex(i, j), getVertex(i + 1, j));
                m_horizontalEdges.push_back(e);
            }
        }
    }
    
    Vertex* StructuredMesh::getVertex(int x, int y)
    {
        return m_mesh->getVertex(x + y * m_width);
    }
    
    void StructuredMesh::calculateAllCollapseCosts()
    {
        m_mesh->calculateAllCollapseCosts();
    }
    
    bool collapseCostPredicate(Edge* d1, Edge* d2)
    {
        return d1->collapseCost() < d2->collapseCost();
    }
    
    void StructuredMesh::collapse(int n)
    {
        std::vector<Edge*> edges(m_verticalEdges.begin(), m_verticalEdges.end());
        edges.insert(edges.end(), m_horizontalEdges.begin(), m_horizontalEdges.end());
        std::sort(edges.begin(), edges.end(), collapseCostPredicate);
        for (int i = 0; i < n; i++) {
            m_mesh->collapse(edges[i]);
        }
    }
}
