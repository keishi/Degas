//
//  TestImage.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "TestImage.h"

#include "Image.h"
#include <iostream>

using namespace Degas;

void testImageWriteBMPFile(CuTest *tc)
{
    Image* image = new Image(64, 64);
    for (int y = 0; y < image->height(); y++) {
        for (int x = 0; x < image->width(); x++) {
            int m = ((x / 16) + ((y / 16) % 4)) % 4;
            Color color = (m == 0 ? kColorWhite : 
                           m == 1 ? kColorBlack :
                           m == 2 ? kColorRed : 
                           m == 3 ? kColorGreen : kColorBlue);
            image->setPixelColor(x, y, color);
        }
    }
    image->writeBMPFile("testImageWriteBMPFile.bmp");
    image->loadBMPFile("testImageWriteBMPFile.bmp");
    
    Image* referenceImage = new Image();
    referenceImage->loadBMPFile("TestExpected/testImageWriteBMPFile.bmp");
    CuAssertTrue(tc, image->equalsImage(referenceImage));
}

CuSuite* getImageTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testImageWriteBMPFile);
    return suite;
}
