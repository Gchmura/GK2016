// z1p2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

///////////////////////////////////////////////////////////
// Wywo�ywana w celu przerysowania sceny


void RenderScene(void) {
	// Wyczyszczenie okna aktualnym kolorem czyszczcym   
	glClear(GL_COLOR_BUFFER_BIT);
	// Aktualny kolor rysujcy - pomaranczowy 
	//           R     G     B  
	glColor3f(.98f, 0.625f, 0.12f);
	// Narysowanie 14 kata wype�nionego aktualnym kolorem  

	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 60.0f);
	glVertex2f(50.0f, 30.0f);
	glVertex2f(50.0f, -30.0f);
	glVertex2f(0.0f, -60.0f);
	glVertex2f(-50.0f, -30.0f);
	glVertex2f(-50.0f, 30.0f);

	glEnd();
	// Wys�anie polece do wykonania     
	glFlush();



}
///////////////////////////////////////////////////////////
// Konfiguracja stanu renderowania  
void SetupRC(void) {
	// Ustalenie niebieskiego koloru czyszczcego     
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT w przypadku zmiany rozmiaru okna
void ChangeSize(int w, int h) {
	GLfloat aspectRatio;
	// Zabezpieczenie przed dzieleniem przez zero  
	if (h == 0)   h = 1;
	// Ustawienie wielko�ci widoku na r�wn� wielko�ci okna     
	glViewport(0, 0, w, h);
	// Ustalenie uk�adu wsp�rz�dnych  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Wyznaczenie przestrzeni ograniczaj�cej (lewy, prawy, dolny, g�rny, bliski, odleg�y)  
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)    glOrtho(-200.0, 200.0, -200 / aspectRatio, 200.0 / aspectRatio, 2.0, -2.0);
	else    glOrtho(-200.0 * aspectRatio, 200.0 * aspectRatio, -200.0, 200.0, 2.0, -2.0);
	glMatrixMode(GL_MODELVIEW);  glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G��wny punkt wejcia programu
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GLRect");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	SetupRC();
	glutMainLoop();
	return 0;
}