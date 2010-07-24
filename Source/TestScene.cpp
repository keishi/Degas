//
//  TestScene.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "TestScene.h"

#include "Scene.h"
#include "Triangle.h"

using namespace Degas;

void testSceneRasterize(CuTest *tc)
{
    Scene* scene = new Scene();
    
    Material* redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    
    Vector3 v0(-1.0, -1.0, 4.0);
    Vector3 v1(1.5, -1.0, 4.0);
    Vector3 v2(0.0, 1.0, 4.0);
    Triangle* triangle = new Triangle(v0, v1, v2);
    triangle->setMaterial(redMaterial);
    scene->rootGroup()->addSurface(triangle);
    
    Camera* camera = new Camera();
    Image* image = new Image(64, 64);
    scene->rasterize(camera, image);
    
    image->writeBMPFile("testSceneRasterize.bmp");
    
    Image* referenceImage = new Image(64, 64);
    referenceImage->loadBMPFile("TestExpected/testSceneRasterize.bmp");
    
    if (!(image->equalsImage(referenceImage))) {
        image->writeBMPFile("testSceneRasterize.bmp");
        CuAssertTrue(tc, false);
    }
}

CuSuite* getSceneTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testSceneRasterize);
    return suite;
}
