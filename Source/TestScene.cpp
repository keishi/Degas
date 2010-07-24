//
//  TestScene.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//

#include "TestScene.h"

void testSceneRasterize(CuTest *tc)
{
    SceneRef scene = new Scene();
    /*
    Vector3 v0(-1.0, -1.0, 2.0);
    Vector3 v1(1.0, -1.0, 2.0);
    Vector3 v2(0.0, 1.0, 2.5);
    TriangleRef triangle = new Triangle(v0, v1, v2);
    triangle->setMaterial(redMaterial);
    scene->addSurface(triangle);
    
    CameraRef camera = new Camera();
    camera->setWidth(64);
    camera->setHeight(64);
    ImageRef image = scene->rasterize(camera);
    ImageRef referenceImage = new Image();
    referenceImage->loadBMPFile("testSceneRasterize.bmp");
    if (!(image->equalToImage(referenceImage))) {
        image->writeBMPFile("testSceneRasterize.bmp");
        CuAssertTrue(tc, false);
    }*/
}
