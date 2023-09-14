#include <glut.h>
#include <GL/gl.h>
#include <gl/glu.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f); //point1
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.5f, 0.0f, 0.0f); //point2
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0f, 0.5f, 0.0f); //point3
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutCreateWindow("OpenGL Example");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}