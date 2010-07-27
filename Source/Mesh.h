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
#include "Edge.h"
#include "Face.h"

namespace Degas {
    class Mesh {
    public:
        Mesh(char* filename);
        
        bool loadFromPlyFile(char* filename);
        
        bool readPlyHeader(FILE *&inFile);
        bool readPlyVertexList(FILE *&inFile);
        bool readPlyFaceList(FILE *&inFile);
        bool readPlyMagicNumber(FILE *&inFile);
        bool readPlyVertexCount(FILE *&inFile, int& vertexCount);
        bool readPlyFaceCount(FILE *&inFile, int& faceCount);
        bool readPlyHeaderTerminator(FILE *&inFile);
        
        Vertex* getVertex(int index) { return m_vertexList[index]; };
        Edge* getEdge(int index) { return m_edgeList[index]; };
        Edge* getEdge(Vertex* v1, Vertex* v2)
        {
            std::vector<Edge*>::iterator i;
            for (i = m_edgeList.begin(); i != m_edgeList.end(); ++i){
                Edge* e = *i;
                if (e->hasVertex(v1) && e->hasVertex(v2)) {
                    return e;
                }
            }
            return NULL;
        };
        Face* getFace(int index) { return m_faceList[index]; };
        
        int vertexCount() { return m_vertexCount; };
        int faceCount() { return m_faceCount; };
        Material* material() { return m_material; };
        
        Surface* createSurface(Material* material=NULL);
        
        void collapse(Vertex* v1, Vertex* v2);
        void collapse(Edge* edge);
        double calculateCollapseCost(Edge* edge);
        
        void removeFace(Face* f);
        
    private:
        std::vector<Vertex*> m_vertexList;
        std::vector<Edge*> m_edgeList;
        std::vector<Face*> m_faceList;
        int m_vertexCount;
        int m_faceCount;
        Material* m_material;
    };
}

#endif // Mesh_h