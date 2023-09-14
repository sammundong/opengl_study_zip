#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0.5f, 0.5f);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-0.5f, 0.5f);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.5f, -0.5f);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0.5f, -0.5f);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("OpenGL Example");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}