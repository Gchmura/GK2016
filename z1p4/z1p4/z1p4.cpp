// z1p4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <GL/glut.h>
#include<iostream>
#include <stdlib.h>

using namespace std;

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	}
}
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0;
float _cameraangle = 30.0;

void drawScene()
{



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(_cameraangle, 0.0f, 1.0f, 0.0f); //rotate object by 30 degree with respect to y-axis
	glTranslatef(0.0f, 0.0f, -10.0f);

	glPushMatrix();
	glTranslatef(5.0f, -1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	glRotatef(_angle, 1.0f, 1.0f, 2.0f); //rotating object continuously by 2 degree
	glColor3f(.98f, 0.625f, 0.12f);
	// Narysowanie 6cio kata wype³nionego aktualnym kolorem  

	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 0.6f);
	glVertex2f(0.5f, 0.3f);
	glVertex2f(0.5f, -0.3f);
	glVertex2f(0.0f, -0.6f);
	glVertex2f(-0.5f, -0.3f);
	glVertex2f(-0.5f, 0.3f);


	glEnd();

	glPopMatrix();
	glutSwapBuffers();


}
void update(int value)
{
	_angle += 2.0f;
	if (_angle>360.f)
	{
		_angle -= 360;
	}
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);


	glutCreateWindow("rotate");
	initRendering();



	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);
	//this call the function update in every 25 millsecond
	//so value of angle of rotation change and object rotates continuously
	glutMainLoop();


	return 0;
}