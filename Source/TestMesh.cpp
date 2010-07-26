//
//  TestMesh.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/26/10.
//  Copyright (c) 2010 Me. All rights reserved.
//

#include "TestMesh.h"

#include "Mesh.h"

using namespace Degas;

void testMeshLoadPlyFile(CuTest *tc)
{
    char filename[] = "TestResource/testMeshLoadPlyFile.ply";
    Mesh *m = new Mesh(filename);
    CuAssertIntEquals(tc, 8, m->vertexCount());
    CuAssertIntEquals(tc, 12, m->faceCount());
}

CuSuite* getMeshTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testMeshLoadPlyFile);
    return suite;
}
