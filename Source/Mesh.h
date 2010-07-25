//
//  Mesh.h
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <vector>

#include "Vertex.h"
#include "Face.h"

namespace Degas {
    class Mesh {
    public:
        bool loadFromPlyFile(char* filename);
        
        bool readPlyHeader(FILE *&inFile);
        bool readPlyVertexList(FILE *&inFile);
        bool readPlyFaceList(FILE *&inFile);
        bool readPlyMagicNumber(FILE *&inFile);
        bool readPlyVertexCount(FILE *&inFile, int& vertexCount);
        bool readPlyFaceCount(FILE *&inFile, int& faceCount);
        bool readPlyHeaderTerminator(FILE *&inFile);
        
        Vertex* getVertex(int index) {return m_vertexList[index];};
        
    private:
        std::vector<Vertex*> m_vertexList;
        std::vector<Face*> m_faceList;
        
        int m_vertexCount;
        int m_faceCount;
        
    };
}

#endif // Mesh_h