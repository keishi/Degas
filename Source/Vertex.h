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
    class Edge;
    class Mesh;
    
    class Vertex {
    public:
        Vertex(int index, double x, double y, double z);
        virtual ~Vertex();
        
        int index() { return m_index; }
        void setIndex(int index) { m_index = index; }
        const Vector3& position() { return m_position; }
        void setPosition(Vector3 position) { m_position = position; }
        std::vector<Vertex*>& adjacentVertices() { return m_adjacentVertices; }
        std::vector<Edge*>& adjacentEdges() { return m_adjacentEdges; }
        std::vector<Face*>& adjacentFaces() { return m_adjacentFaces; }
        int weight() { return m_weight; }
        void setWeight(int weight) { m_weight = weight; }
        
        void addAdjacentVertex(Vertex* v);
        void addAdjacentEdge(Edge* e);
        void addAdjacentFace(Face* f);
        void removeAdjacentEdge(Edge* e);
        
    private:
        int m_index;
        Vector3 m_position;
        std::vector<Vertex*> m_adjacentVertices;
        std::vector<Edge*> m_adjacentEdges;
        std::vector<Face*> m_adjacentFaces;
        int m_weight;
    };
}

#endif // Vertex_h
