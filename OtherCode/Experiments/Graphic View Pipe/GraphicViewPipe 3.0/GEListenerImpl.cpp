#include "GEListenerImpl.h"

#include <cmath>
#include <windows.h>

GEListenerImpl::GEListenerImpl()
{
    gCamera = new GCamera();

    gGrid = new GCubeGrid();

    gSphere = new GSphere();
    gSphere->SetRadius(0.2);
    gSphere->SetMeasure(30, 30);

    gCylinder = new GCylinder();
    gCylinder->SetRadius(0.025, 0.025);
    gCylinder->SetMeasure(30, 1);

    for (int i = 0; i < 256; ++i)
        keyDown[i] = false;
}

GEListenerImpl::~GEListenerImpl()
{
    delete gGrid;
    delete gCamera;
}

void GEListenerImpl::Initialize(void)
{
    glClearColor(0.603921568627451, 0.7529411764705882, 0.803921568627451, 0.0);
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);

    // Read File Begin
    ifstream fin ("input.txt");
    fin >> n;

    points.resize(n);
    gridSize = 0.0f;

    for (int i = 0; i < n; ++i)
    {
        fin >> points[i].x >> points[i].y >> points[i].z;

        gridSize = max(gridSize, fabs( points[i].x ));
        gridSize = max(gridSize, fabs( points[i].y ));
        gridSize = max(gridSize, fabs( points[i].z ));
    }

    // Set Grid Settings
    gGrid->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    gGrid->SetMeasure(20.0f);
    gGrid->SetSize(gridSize);

    // Graphic Settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);

    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);

    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_NORMALIZE);

    float light0_diffuse[] = {1, 1, 1};
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    glLineWidth(1.5f);
}

void GEListenerImpl::DisplayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set Camera
    gCamera->UpdatePosition(keyDown);
    gCamera->SetView();

    // Graphic Settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    // Draw Grid
    gGrid->Draw();

    // Material Settings
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float amb_color[] = {0.2, 0.0, 0.0, 1.0};
    float dif_color[] = {0.8, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, amb_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dif_color);

    // Draw Sphere
    gSphere->rotation = gGrid->rotation;
    gSphere->position = gGrid->position;

    for (int i = 0; i < points.size(); ++ i)
    {
        gSphere->SetCenter(points[i].x, points[i].y, points[i].z);
        gSphere->Draw();
    }

    // Draw Cylinder
    gCylinder->rotation = gGrid->rotation;
    gCylinder->position = gGrid->position;


    gCylinder->SetRadius(0.025f, 0.025f);
    for(int i = 1; i < points.size(); ++ i)
    {
        gCylinder->SetFromTo(points[i - 1].x, points[i - 1].y, points[i - 1].z, points[i].x, points[i].y, points[i].z);
        gCylinder->Draw();
    }

    // Material Settings
    float amc_color[] = {0.0, 0.0, 0.0, 0.5};
    float dfc_color[] = {0.0, 0.0, 0.3, 0.5};
    glMaterialfv(GL_FRONT, GL_AMBIENT, amc_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, dfc_color);

    // Draw Transparent Cylinder
    gCylinder->SetRadius(0.07f, 0.07f);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    for(int i = 1; i < points.size(); i = i + 2)
    {
        gCylinder->SetFromTo(points[i - 1].x, points[i - 1].y, points[i - 1].z, points[i].x, points[i].y, points[i].z);
        gCylinder->Draw();
    }

    glutSwapBuffers();
    glutPostRedisplay();

}

void GEListenerImpl::KeyboardFunc(unsigned char key, int x, int y)
{
    keyDown[key] = true;

    if (key == 27)
    {
        exit(0);
    }
}

void GEListenerImpl::KeyboardUpFunc(unsigned char key, int x, int y)
{
    keyDown[key] = false;
}

void GEListenerImpl::MotionFunc(int x, int y)
{
    mousePX = mouseX, mousePY = mouseY;
    mouseX = x, mouseY = y;

    GLfloat DeltaMouse;

	if(mouseX < mousePX)
	{
		DeltaMouse = GLfloat(mousePX - mouseX);

		if(!rightMouseClick)
            gCamera->RotateX(0.1f * DeltaMouse); else
            gGrid->RotateX(0.1f * DeltaMouse);

	}
	else if(mouseX > mousePX)
	{
		DeltaMouse = GLfloat(mouseX - mousePX);

		if(!rightMouseClick)
            gCamera->RotateX(-0.1f * DeltaMouse); else
            gGrid->RotateX(-0.1f * DeltaMouse);
	}

	if(mouseY < mousePY)
	{
		DeltaMouse = GLfloat(mousePY - mouseY);

		if(!rightMouseClick)
            gCamera->RotateY(0.1f * DeltaMouse); else
            gGrid->RotateY(0.1f * DeltaMouse);
	}
	else if(mouseY > mousePY)
	{
		DeltaMouse = GLfloat(mouseY - mousePY);

		if(!rightMouseClick)
            gCamera->RotateY(-0.1f * DeltaMouse); else
            gGrid->RotateY(-0.1f * DeltaMouse);
	}
}

void GEListenerImpl::MouseFunc(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        mousePX = x;
        mousePY = y;
        mouseX = x;
        mouseY = y;
    }
    if(button == GLUT_RIGHT_BUTTON)
        rightMouseClick = true; else
        rightMouseClick = false;
}

void GEListenerImpl::ReshapeFunc(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.001f, 10000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
