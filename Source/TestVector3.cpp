//
//  TestVector3.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "TestVector3.h"

#include "Vector3.h"

using namespace Degas;

void testVector3Equality(CuTest *tc)
{
    Vector3 a = Vector3(1, 2, 3);
    Vector3 b = Vector3(1, 2, 3);
    Vector3 c = Vector3(4, 5, 6);
    
    CuAssertTrue(tc, a == b);
    CuAssertTrue(tc, !(a != b));
    CuAssertTrue(tc, !(a == c));
    CuAssertTrue(tc, a != c);
}

void testVector3Arithmetic(CuTest *tc)
{
    Vector3 a = Vector3(1, 2, 3);
    Vector3 b = Vector3(4, 5, 6);
    
    CuAssertTrue(tc, a + b == Vector3(5, 7, 9));
    CuAssertTrue(tc, a - b == Vector3(-3, -3, -3));
    CuAssertTrue(tc, a * b == Vector3(4, 10, 18));
    CuAssertTrue(tc, b / a == Vector3(4, 2.5, 2));
}

CuSuite* getVector3TestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testVector3Equality);
    SUITE_ADD_TEST(suite, testVector3Arithmetic);
    return suite;
}
