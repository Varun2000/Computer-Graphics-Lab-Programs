#include<gl/glut.h>
#include<stdio.h>
int xc, yc, r,rx,ry;

inline int round(const float a) { return int(a + 0.5); }

void draw_circle(int xc, int yc, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);

	glVertex2i(xc + y, yc + x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc + y, yc - x);
	glVertex2i(xc - y, yc - x);
	glEnd();
}

void circlebres()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int x = 0, y = r;
	int d = 3 - 2 * r;
	while (x <= y)
	{
		draw_circle(xc, yc, x, y);
		x++;
		if (d < 0)
			d = d + 4 * x + 6;

		else
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		draw_circle(xc, yc, x, y);
	}
	glFlush();
}

void ellipsePoints(int xc, int yc, int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc - x, yc + y);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);
	glEnd();
}

void ellipsebres()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int rx2 = rx * rx,ry2=ry*ry,trx2=2*rx2,try2=2*ry2;
	int p, x = 0, y = ry, px = 0, py = trx2 * y;
	ellipsePoints(xc, yc, x, y);

	p = round(ry2 - (rx2 * ry) + 0.25 * rx2);
	while (px < py)
	{
		x++;
		px += try2;
		if (p < 0)
			p += ry2 + px;
		else
		{
			y--;
			py -= trx2;
			p += ry2 + px - py;
		}
		ellipsePoints(xc, yc, x, y);
	}

	p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
	while (y > 0)
	{
		y--;
		py -= trx2;
		if (p > 0)
			p += rx2 - py;
		else
		{
			x++;
			px += try2;
			p += rx2 - py + px;
		}
		ellipsePoints(xc, yc, x, y);
	}

	glFlush();
}

void minit()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	gluOrtho2D(10, 500, 10, 500);
}


void main(int argc, char* argv[])
{
	
	printf("Enter the coordinates of the center and the radius\n");
	scanf_s("%d%d%d", &xc, &yc, &r);
	printf("Enter the semimajor and semiminor axis length\n");
	scanf_s("%d%d", &rx,&ry);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 100);
	
	glutCreateWindow("Circle Diagram");
	glutDisplayFunc(circlebres);
	minit();
	glutCreateWindow("Ellipse");
	glutPositionWindow(540, 40);
	glutDisplayFunc(ellipsebres);

	minit();
	glutMainLoop();
}
