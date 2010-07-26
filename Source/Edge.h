//
//  Edge.h
//  Degas
//
//  Created by Keishi Hattori on 7/26/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef Edge_h
#define Edge_h

#include "Vertex.h"

namespace Degas {
    class Edge {
    public:
        Edge(Vertex* v1, Vertex* v2);
        ~Edge();
        
        double length() { return (m_v1->position() - m_v2->position()).norm(); }
        
        void addSide(Face* side);
        void removeSide(Face* side);
        
        bool hasVertex(Vertex* v) { return m_v1 == v || m_v2 == v;}
        
        Vertex* v1() { return m_v1; }
        Vertex* v2() { return m_v2; }
        double collapseCost() { return m_collapseCost; }
        void setCollapseCost(double cost) { m_collapseCost = cost; }
        std::vector<Face*>& sides() { return m_sides; }
        
    private:
        Vertex* m_v1;
        Vertex* m_v2;
        std::vector<Face*> m_sides;
        double m_collapseCost;
    };
}

#endif // Edge_h
