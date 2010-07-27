//
//  StructuredMesh.h
//  Degas
//
//  Created by Keishi Hattori on 7/27/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef StructuredMesh_h
#define StructuredMesh_h

#include "Mesh.h"

namespace Degas {
    class StructuredMesh {
    public:
        StructuredMesh(char* filename, int width, int height);
        
        Vertex* getVertex(int x, int y);
        void calculateAllCollapseCosts();
        void collapse(int n);
        
        Mesh* mesh() { return m_mesh; }
        
    private:
        Mesh* m_mesh;
        int m_width;
        int m_height;
        std::vector<Edge*> m_horizontalEdges;
        std::vector<Edge*> m_verticalEdges;
    };
}

#endif // StructuredMesh_h
