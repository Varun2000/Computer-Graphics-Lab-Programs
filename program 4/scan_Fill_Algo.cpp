#include<iostream>
#include<algorithm>
#include<gl/glut.h>
using namespace std;

//float x[] = { 100, 150, 200, 250, 300,10,10 }, y[] = { 200,100,200,50,300,300 };
//float x[] = { 110, 200, 250, 100, 10, 10 }, y[] = { 100, 220, 110, 200, 0, 300 };
float x[] = { 350,255,291,409,445 },y[] = { 250, 319, 431, 431, 319 };
int n = 5, m;
int wx = 500, wy = 500;
static float intx[10] = { 0 };

void draw_line(float x1, float y1, float x2, float y2)
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void edgedetect(float x1, float y1, float x2, float y2, int scanline)
{
	float temp;
	if (y2 < y1)
	{
		temp = x1; x1 = x2; x2 = temp;
		temp = y1; y1 = y2; y2 = temp;
	}
	if (scanline > y1 && scanline < y2)
		intx[m++] = x1 + (scanline - y1) * (x2 - x1) / (y2 - y1);
}

void scanfill(float x[], float y[])
{
	for (int sl = 0; sl <= wy; sl++)
	{
		m = 0;
		for (int i = 0; i < n; i++)
		{
			edgedetect(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n], sl);
		}
		//asort(intx);
		sort(intx, (intx + m));
		if (m >= 2)
			for (int i = 0; i < m; i += 2)
				draw_line(intx[i], sl, intx[i + 1], sl);
	}
}

void display_filled_polygon()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
		glVertex2f(x[i], y[i]);
	glEnd();
	scanfill(x, y);
	glFlush();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i++)
		glVertex2f(x[i], y[i]);
	glEnd();
	glFlush();
}
void myinit()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(0, 0, 1);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, wx, 0, wy);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Original Polygon");
	glutDisplayFunc(display);
	myinit();
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 0);
	glutCreateWindow("Scan Filled Polygon");
	glutDisplayFunc(display_filled_polygon);
	myinit();
	glutMainLoop();
}
