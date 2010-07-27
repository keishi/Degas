//
//  Mesh.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "Mesh.h"

#include <cassert>

#include "SurfaceGroup.h"
#include "utils.h"

namespace Degas {
    Mesh::Mesh(char* filename)
    {
        m_vertexCount = 0;
        m_faceCount = 0;
        loadFromPlyFile(filename);
    }
    
    bool Mesh::loadFromPlyFile(char *filename)
    {
        FILE* inFile = fopen(filename, "rt");
        if (inFile == NULL) {
            std::cerr << filename << " does not exist." << std::endl;
            return false;
        }
        
        if (!readPlyHeader(inFile)) { return false;}
        if (!readPlyVertexList(inFile)) { return false; }
        if (!readPlyFaceList(inFile)) {return false; }
        
        fclose(inFile); // close the file
        
        return true;
    }
    
    bool Mesh::readPlyHeader(FILE *&inFile)
    {
        if (!readPlyMagicNumber(inFile)) { return false; }
        if (!readPlyVertexCount(inFile, m_vertexCount)) { return false; }
        if (!readPlyFaceCount(inFile, m_faceCount)) { return false; }
        if (!readPlyHeaderTerminator(inFile)) { return false; }
        
        return true;
    }
    
    void cstringToLower(char* str)
	{
		for (char* pc = str; pc < str + strlen(str); pc++) {
			*pc = (char)tolower(*pc);
		}
	}
    
    bool Mesh::readPlyMagicNumber(FILE *&inFile)
    {
        char tmp[1024];
        do {
            fscanf(inFile, "%s", tmp);
            if (feof(inFile)) {
                std::cerr << "Reached EOF and \"ply\" not found.";
                return false;
            }
            cstringToLower(tmp);
        } while(strncmp(tmp, "ply", 3));
        return true;
    }
    
    bool Mesh::readPlyVertexCount(FILE *&inFile, int& vertexCount)
    {
        char tmp[1024];
        bool didFindElement = false;
        while(1) {
            fscanf(inFile, "%s", tmp);
            if (feof(inFile)) {
                std::cerr << "Reached EOF and \"element vertex\" not found.";
                return false;
            }
            cstringToLower(tmp);
            if (didFindElement) {
                if (!strncmp(tmp, "vertex", 6)) {
                    break;
                } else {
                    didFindElement = false;
                }
            } else {
                if (!strncmp(tmp, "element", 7)) {
                    didFindElement = true;
                }
            }
        }
        fscanf(inFile, "%d", &vertexCount);
        if (feof(inFile)) {
            std::cerr << "Reached EOF and \"element face\" not found.";
            return false;
        }
        return true;
    }
    
    bool Mesh::readPlyFaceCount(FILE *&inFile, int& faceCount)
    {
        char tmp[1024];
        bool didFindElement = false;
        while(1) {
            fscanf(inFile, "%s", tmp);
            if (feof(inFile)) {
                std::cerr << "Reached EOF and \"element face\" not found.";
                return false;
            }
            cstringToLower(tmp);
            if (didFindElement) {
                if (!strncmp(tmp, "face", 4)) {
                    break;
                } else {
                    didFindElement = false;
                }
            } else {
                if (!strncmp(tmp, "element", 7)) {
                    didFindElement = true;
                }
            }
        }
        fscanf(inFile, "%d", &faceCount); 
        if (feof(inFile)) {
            std::cerr << "Reached EOF and vertex list not found.";
            return false;
        }
        return true;
    }
    
    bool Mesh::readPlyHeaderTerminator(FILE *&inFile)
    {
        char tmp[1024];
        do {
            fscanf(inFile, "%s", tmp);
            if (feof(inFile)) {
                std::cerr << "Reached EOF and \"end_header\" not found.";
                return false;
            }
            cstringToLower(tmp);
        } while(strncmp(tmp, "end_header", 10));
        return true;
    }
    
    bool Mesh::readPlyVertexList(FILE *&inFile)
    {
        int i;
        for (i = 0; i < m_vertexCount; i++) {
            char tmp[1024];
            
            fscanf(inFile, "%s", tmp);
            float x = atof(tmp);
            fscanf(inFile, "%s", tmp);
            float y = atof(tmp);
            fscanf(inFile, "%s", tmp);
            float z = atof(tmp);
            
            Vertex* v = new Vertex(i, x, y, z);
            m_vertexList.push_back(v);
            
            if (feof(inFile)) {
                std::cerr << "Reached EOF before all vertices found.";
                return false;
            }
            
            // read until end of line
            while (fgetc(inFile) != '\n');
        }
        return true;
    }
    
    bool Mesh::readPlyFaceList(FILE *&inFile) {
        int i;
        for (i = 0; i < m_faceCount; i++) {
            int vertexIndex1, vertexIndex2, vertexIndex3;
            int ngon;
            
            fscanf(inFile, "%d", &ngon);
            if (ngon != 3) {
                std::cerr << "Ply file contains polygons which are not triangles.";
                return false;
            }
            
            fscanf(inFile, "%d", &vertexIndex1);
            fscanf(inFile, "%d", &vertexIndex2);
            fscanf(inFile, "%d", &vertexIndex3);
            
            assert(vertexIndex1 < m_vertexCount);
            assert(vertexIndex2 < m_vertexCount);
            assert(vertexIndex3 < m_vertexCount);
            
            Edge* e12 = new Edge(getVertex(vertexIndex1), getVertex(vertexIndex2));
            m_edgeList.push_back(e12);
            Edge* e23 = new Edge(getVertex(vertexIndex2), getVertex(vertexIndex3));
            m_edgeList.push_back(e23);
            Edge* e31 = new Edge(getVertex(vertexIndex3), getVertex(vertexIndex1));
            m_edgeList.push_back(e31);
            
            Face* f = new Face(this, vertexIndex1, vertexIndex2, vertexIndex3);
            m_faceList.push_back(f);
            
            if (feof(inFile)) {
                std::cerr << "Reached EOF before all faces found.";
                return false;
            }
            
            // read until end of line
            while (fgetc(inFile) != '\n');
        }
        
        return true;
    }
    
    Surface* Mesh::createSurface(Material* material)
    {
        SurfaceGroup* sg = new SurfaceGroup();
        std::vector<Face*>::iterator i;
        for (i = m_faceList.begin(); i != m_faceList.end(); ++i){
            Face* f = *i;
            sg->addSurface(f->createSurface(material));
        }
        return (Surface*)sg;
    }
    
    void Mesh::collapse(Vertex* v1, Vertex* v2)
    {
        std::vector<Face*>::iterator i;
        for (i = v1->adjacentFaces().begin(); i != v1->adjacentFaces().end(); ++i){
            Face* f = *i;
            if (f->hasVertex(v2)) {
                removeFace(f);
                delete f;
            }
        }
        
        Vector3 position1 = v1->position();
        int weight1 = v1->weight();
        Vector3 position2 = v2->position();
        int weight2 = v2->weight();
        
        Vector3 newPosition = (position1 * weight1 + position2 * weight2) / (weight1 + weight2);
        
        v2->setPosition(newPosition);
        v2->setWeight(v1->weight() + v2->weight());
        
        for (i = v1->adjacentFaces().begin(); i != v1->adjacentFaces().end(); ++i){
            Face* f = *i;
            f->changeVertex(v1, v2);
            f->calculateNormal();
        }
    }
    
    void Mesh::collapse(Edge* edge)
    {
        collapse(edge->v1(), edge->v2());
    }
    
    double Mesh::calculateCollapseCost(Edge* edge)
    {
        double curvature = 0.0;
        
        std::vector<Face*>::iterator i;
        for (i = edge->v1()->adjacentFaces().begin(); i != edge->v1()->adjacentFaces().end(); ++i){
            double minCurvature = 1.0;
            std::vector<Face*>::iterator j;
            for (j = edge->sides().begin(); j != edge->sides().end(); ++j){
                double dotProduct = (*i)->normal().dot((*j)->normal());
                minCurvature = min(minCurvature, (1.0 - dotProduct) / 2.0);
            }
            curvature = max(curvature, minCurvature);
        }
        
        return edge->length() * curvature;
    }
    
    void Mesh::removeFace(Face* f)
    {
        std::vector<Face*>::iterator i;
        for (i = m_faceList.begin(); i != m_faceList.end(); ++i){
            if ((*i) == f) {
                m_faceList.erase(i);
                return;
            }
        }
    }
}
