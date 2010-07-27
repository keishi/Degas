//
//  Face.h
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef Face_h
#define Face_h

#include "Vertex.h"
#include "Surface.h"

namespace Degas {
    class Face {
    public:
        Face(Mesh* mesh, int vertexIndex1, int vertexIndex2, int vertexIndex3);
        ~Face();
        
        bool hasVertex(Vertex* v) { return (v == m_v1 || v == m_v2 || v == m_v3); }
        void calculateNormal();
        
        Surface* createSurface(Material* material=NULL);
        
        void changeVertex(Vertex* from, Vertex* to);
        
        const Vector3& normal() const { return m_normal; }
        
    private:
        Vertex* m_v1;
        Vertex* m_v2;
        Vertex* m_v3;
        Vector3 m_normal;
        Mesh* m_mesh;
    };
    
    std::ostream& operator<<(std::ostream& out, const Face& f);
}


#endif // Face_h