//
//  Edge.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/26/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "Edge.h"

namespace Degas {
    Edge::Edge(Vertex* v1, Vertex* v2)
    {
        m_v1 = v1;
        m_v1->addAdjacentEdge(this);
        m_v2 = v2;
        m_v2->addAdjacentEdge(this);
    }
    
    Edge::~Edge()
    {
        m_v1->removeAdjacentEdge(this);
        m_v2->removeAdjacentEdge(this);
    }
}
