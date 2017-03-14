

#include "stdafx.h"
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>

#else

#include <GL/glut.h>


#endif

// Pocztkowy rozmiar i pozycja prostokta
GLfloat srodek_x1 = 150.0f;
GLfloat srodek_y1 = 150.0f;
GLsizei rsize = 50;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

std::vector < GLint > vertex_x(7);
std::vector < GLint > vertex_y(7);
std::vector < GLboolean > edge_flags;


// Dane zmieniajcych si� rozmiar�w okna
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat M_PI = 3.14;
GLfloat alpha = 0;


void glutWspolrzedne() {


	for (size_t i = 0; i < 7; i++)
	{

		alpha = alpha + (360 / 7)*(M_PI / 180);
		vertex_x[i] = (rsize*cos(alpha) + srodek_x1);
		vertex_y[i] = (rsize*sin(alpha) + srodek_y1);
	}



}
///////////////////////////////////////////////////////////
// Wywo�ywana w celu przerysowania sceny
void RenderScene(void) {
	glutWspolrzedne();
	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym
	glClear(GL_COLOR_BUFFER_BIT);

	// Aktualny kolor rysuj�cy - czerwony
	//    R    G    B
	glColor3f(1.0f, 0.0f, 0.0f);

	// Narysowanie wielokata wype�nionego aktualnym kolorem


	glBegin(GL_POLYGON);

	for (size_t i = 0; i < 7; i++)
	{

		glVertex3f(vertex_x[i], vertex_y[i], 0);
	}

	glEnd();

	// Wys�anie polece� do wykonania - !!! dla animacji to jest inne polecenie


	glutSwapBuffers();

}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania

void SetupRC(void) {
	// Ustalenie br�zoweg koloru czyszcz�cego   

	glClearColor(99.0 / 255, 66.0 / 255, 33.0 / 255, 0);
}
///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT przy ka�dej zmianie wielko�ci okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;
	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);
	// Ustalenie uk�adu wsp�rz�dnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	// width and height for later use
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczaj�cej (lewo, prawo, d�, g�ra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void TimerFunction(int value) {
	glLoadIdentity();


	//glLoadIdentity();
	glLoadIdentity();
	// Odwr�cenie kierunku, je�eli osi�gni�to lew� lub praw� kraw�d�
	if (srodek_x1 > windowWidth - rsize || (srodek_x1 - rsize) < 0)
		xstep = -xstep;

	// Odwr�cenie kierunku, je�eli osi�gni�to doln� lub g�rn� kraw�d�
	if (srodek_y1 > windowHeight - rsize || srodek_y1 - rsize < 0)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy�o swoj wielko�� w czasie, gdy kwadrat odbija� si� od     
	// kraw�dzi, co mog�oby spowodowa�, �e znalaz� by si� poza      
	// przestrzeni� ograniczajc�.     


	if (srodek_x1 > windowWidth - rsize)
		srodek_x1 = windowWidth - rsize - 1;

	if (srodek_y1 > windowHeight - rsize)
		srodek_y1 = windowHeight - rsize - 1;

	// Wykonanie przesuni�cia kwadratu
	srodek_x1 += xstep;
	srodek_y1 += ystep;
	// Ponowne rysowanie sceny z nowymi wsp�rz�dnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// G��wny punkt wej�cia programu
void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("M�j pierwszy program w GLUT");


	glutDisplayFunc(RenderScene);
	glutPostRedisplay();

	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}
