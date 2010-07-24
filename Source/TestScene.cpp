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
    
    Vector3 v0(-1.0, -1.0, -4.0);
    Vector3 v1(1.5, -1.0, -4.0);
    Vector3 v2(0.0, 1.0, -4.0);
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

// glutCreateWindow needs to be called before glBindFramebufferEXT
void testSceneRenderGL(CuTest *tc)
{
    Scene* scene = new Scene();
    
    Material* redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    
    Vector3 v0(-1.0, -1.0, -4.0);
    Vector3 v1(1.5, -1.0, -4.0);
    Vector3 v2(0.0, 1.0, -4.0);
    Triangle* triangle = new Triangle(v0, v1, v2);
    triangle->setMaterial(redMaterial);
    scene->rootGroup()->addSurface(triangle);
    
    // create a valid handle for FBO
    GLuint fbo;
    glGenFramebuffersEXT(1, &fbo);
    
    // bind it so we can perform operations on it
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    // create a valid handle for depthbuffer
    GLuint depthbuffer;
    glGenRenderbuffersEXT(1, &depthbuffer);
    // bind it
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthbuffer);
    // associate storage space to depthbuffer
    int width = 64;
    int height = 64;
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
    // attatch it to FBO
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthbuffer);
    // bind FBO and start rendering to it
    // glPushAtrrib and glPopAttrib are used as a quick way to save the old viewport information
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(0,0,width, height);
    // render. The output goes to the FBO and it’s attached buffers
    Camera* camera = new Camera();
    scene->renderGL(camera);
    // read pixels
    Image* image = new Image(width, height);
    image->loadGLBuffer();
    // stop rendering
    glPopAttrib();
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    
    image->writeBMPFile("testSceneRenderGL.bmp");
    
    Image* referenceImage = new Image(64, 64);
    referenceImage->loadBMPFile("TestExpected/testSceneRenderGL.bmp");
    
    if (!(image->equalsImage(referenceImage))) {
        image->writeBMPFile("testSceneRenderGL.bmp");
        CuAssertTrue(tc, false);
    }
}

CuSuite* getSceneTestSuite()
{
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testSceneRasterize);
    //SUITE_ADD_TEST(suite, testSceneRenderGL);
    return suite;
}
