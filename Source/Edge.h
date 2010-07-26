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
        
    private:
        Vertex* m_v1;
        Vertex* m_v2;
        double m_collapseCost;
    };
}

#endif // Edge_h
