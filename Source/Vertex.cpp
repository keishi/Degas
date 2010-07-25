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
    }
}
