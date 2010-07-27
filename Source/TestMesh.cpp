//
//  TestMesh.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/26/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "TestMesh.h"

#include "Mesh.h"
#include "StructuredMesh.h"

using namespace Degas;

void testMeshLoadPlyFile(CuTest *tc)
{
    char filename[] = "TestResource/testMeshLoadPlyFile.ply";
    Mesh *m = new Mesh(filename);
    CuAssertIntEquals(tc, 8, m->vertexCount());
    CuAssertIntEquals(tc, 12, m->faceCount());
    
    m->calculateAllCollapseCosts();
    //std::cout << m->getEdge(0)->collapseCost();
}

void testStructuredMeshLoadPlyFile(CuTest *tc)
{
    char filename[] = "TestResource/testStructuredMesh.ply";
    StructuredMesh *m = new StructuredMesh(filename, 4, 4);
    CuAssertIntEquals(tc, 16, m->mesh()->vertexCount());
    CuAssertIntEquals(tc, 18, m->mesh()->faceCount());
    Vertex* v1 = m->mesh()->getVertex(13);
    Vertex* v2 = m->mesh()->getVertex(9);
    CuAssertTrue(tc, m->mesh()->getEdge(v1, v2) != NULL);
    CuAssertTrue(tc, m->mesh()->getEdge(v2, v1) != NULL);
    
    m->calculateAllCollapseCosts();
    m->collapse(4);
}

CuSuite* getMeshTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testMeshLoadPlyFile);
    SUITE_ADD_TEST(suite, testStructuredMeshLoadPlyFile);
    return suite;
}
