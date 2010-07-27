//
//  Edge.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/26/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "Edge.h"

#include <cassert>

namespace Degas {
    Edge::Edge(Vertex* v1, Vertex* v2)
    {
        assert(v1 != v2);
        m_v1 = v1;
        m_v2 = v2;
        m_collapseCost = 10000000.0;
    }
    
    void Edge::addSide(Face* side)
    {
        m_sides.push_back(side); 
    }
    
    void Edge::changeVertex(Vertex* from, Vertex* to)
    {
        if (from == m_v1) {
            m_v1 = to;
        } else if (from == m_v2) {
            m_v2 = to;
        }
    }
}
