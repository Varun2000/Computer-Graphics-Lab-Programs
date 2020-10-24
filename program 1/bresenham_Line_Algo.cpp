#include<gl/glut.h>
#include<stdio.h>

void setPixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
int x1, y1, x2, y2;

void draw_line()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int dx, dy, i, p;
	int incx=1, incy=1, inc1, inc2;
	int x, y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0)
	{
		dx = -dx;
		incx = -1;
	}

	if (dy < 0)
	{
		dy = -dy;
		incy = -1;
	}


	x = x1;
	y = y1;

	if (dx > dy)
	{

		setPixel(x, y);

		p = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++)
		{
			if (p >= 0)
			{
				y += incy;
				p += inc1;
			}
			else
				p += inc2;
			x += incx;

			setPixel(x, y);

		}
	}

	else
	{

		setPixel(x, y);
		p = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++)
		{
			if (p >= 0)
			{
				x += incx;
				p += inc1;
			}
			else
				p += inc2;
			y += incy;

			setPixel(x, y);

		}
	}
	glFlush();
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	gluOrtho2D(10, 500, 10, 500);
}


void main(int argc, char* argv[])
{
	printf("Enter the start(x1,y1) and end points(x2,y2)\n");
	scanf_s("%d%d%d%d", &x1, &y1, &x2, &y2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Line Algo");
	glutDisplayFunc(draw_line);
	init();
	glutMainLoop();
}
