//
//  main.cpp
//  Degas
//
//  Created by Keishi Hattori on 7/24/10.
//  Copyright (c) 2010 __MyCompanyName__. All rights reserved.
//


#include <iostream>

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#include "CuTest.h"
#include "TestVector3.h"
#include "TestImage.h"
#include "TestScene.h"


#include "Scene.h"
#include "Triangle.h"

using namespace Degas;

Scene* reScene;
Camera* camera;

void display(void)
{
    reScene->renderGL(camera);
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    
    glutPostRedisplay();
}

void runTests()
{
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    CuSuiteAddSuite(suite, getVector3TestSuite());
    CuSuiteAddSuite(suite, getImageTestSuite());
    CuSuiteAddSuite(suite, getSceneTestSuite());
    
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    std::cout << output->buffer;
}

int main (int argc, char * argv[]) {
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    /*
    reScene = new Scene();
    
    Material* redMaterial = new Material();
    redMaterial->setColor(kColorRed);
    
    Vector3 v0(-1.0, -1.0, -4.0);
    Vector3 v1(1.5, -1.0, -4.0);
    Vector3 v2(0.0, 1.0, -4.0);
    Triangle* triangle = new Triangle(v0, v1, v2);
    triangle->setMaterial(redMaterial);
    reScene->rootGroup()->addSurface(triangle);
    
    camera = new Camera();
    */
    
    runTests();
    //glutMainLoop();
    
    return 0;
}

