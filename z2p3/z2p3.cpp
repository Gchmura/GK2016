// z2p3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "math.h"
#include <GL/glut.h>

#define GL_PI 3.1415f
// Wielkoœæ obrotów
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
GLuint texture;
char pixels[256 * 256];

static GLboolean iCull, iDepth, iOutline;
// Funkcja wykonuje wszystkie konieczne inicjalizacje kontekstu renderowania
void SetupRC()
{

	glShadeModel(GL_FLAT);

	glFrontFace(GL_CW);

	GLuint texture;
	int x, y;
	char pixels[256 * 256];
	GLint iWidth = 256;
	GLint iHeight = 256;
	GLint iComponents = GL_RGB;
	GLenum eFormat = {
		GL_RGBA
	};

	GLfloat whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.5f, 0.35f, 0.05f, 1.0f);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);


	for (y = 0; y < 256; y++)
	{
		for (x = 0; x < 256; x++)
			pixels[y * 256 + x] = rand() % 256;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 256, 256, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}
// Wywo³ywana w celu przerysowania scen
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat x, y, angle;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_BACK, GL_FILL);

	glPushMatrix();

	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);

	for (angle = 0.0f; angle < (3.0f*GL_PI);)
	{
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		glVertex3f(x, y, 0.0f);
		glTexCoord2f(0.0f, 0.0f);

		
		angle += (GL_PI / 3.0f);
		glVertex3f(0.0f, 0.0f, 75.0f);
		glTexCoord2f(0.5f, 1.0f);
		
		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);
		glVertex3f(x, y, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for (angle = 0.0f; angle < (3.0f*GL_PI);)
	{
		x = 50.0f*sin(angle);		
		y = 50.0f*cos(angle);
		
		angle += (GL_PI / 3.0f);
		
		glVertex3f(x, y, 0.0f);
		glTexCoord2f(0.0f, 0.0f);

		
		
		x = 50.0f*sin(angle); 
		y = 50.0f*cos(angle);
		
		glVertex3f(x, y, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		
		glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.5f, 1.0f);
		
	}
	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	// Odœwie¿enie zawartoœci okna
	glutPostRedisplay();
}
void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;
	// Ustalenie wymiarów widoku na zgodnych z wymiarami okna
	glViewport(0, 0, w, h);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Utworzenie przestrzeni ograniczaj¹cej (lewo, prawo, dó³, góra, blisko, daleko)

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
	// Ponowne ustawienie stosu macierzy rzutowania
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Textured Pyramid");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);

	SetupRC();

	glutMainLoop();

	return 0;
}