//
//  Mesh.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/25/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "Mesh.h"

#include <cassert>

namespace Degas {
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
                if (strncmp(tmp, "vertex", 6)) {
                    break;
                } else {
                    didFindElement = false;
                }
            } else {
                if (strncmp(tmp, "element", 7)) {
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
    
    bool Mesh::readPlyFaceCount(FILE *&inFile, int& vertexCount)
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
                if (strncmp(tmp, "face", 6)) {
                    break;
                } else {
                    didFindElement = false;
                }
            } else {
                if (strncmp(tmp, "element", 7)) {
                    didFindElement = true;
                }
            }
        }
        fscanf(inFile, "%d", &vertexCount); 
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
            int v1, v2, v3;
            int ngon;
            
            fscanf(inFile, "%d", &ngon);
            if (ngon != 3) {
                std::cerr << "Ply file contains polygons which are not triangles.";
                return false;
            }
            
            fscanf(inFile, "%d", &v1);
            fscanf(inFile, "%d", &v2);
            fscanf(inFile, "%d", &v3);
            
            assert(v1 < m_vertexCount && v2 < m_vertexCount && v3 < m_vertexCount);
            
            Face* f = new Face(this, v1, v2, v3);
            m_faceList.push_back(f);
            
            if (feof(inFile)) {
                std::cerr << "Reached EOF before all vertices found.";
                return false;
            }
            
            // read until end of line
            while (fgetc(inFile) != '\n');
        }
        
        return true;
    }
}
