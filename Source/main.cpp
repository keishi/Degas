//
//  main.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//


#include <iostream>

#include "CuTest.h"
#include "TestVector3.h"
#include "TestImage.h"
#include "TestScene.h"

int main (int argc, const char * argv[]) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    CuSuiteAddSuite(suite, getVector3TestSuite());
    CuSuiteAddSuite(suite, getImageTestSuite());
    CuSuiteAddSuite(suite, getSceneTestSuite());
    
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    std::cout << output->buffer;
    
    return 0;
}

