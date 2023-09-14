#include <glut.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <stdio.h>

GLint winWidth = 0;
GLint winHeight = 0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(0.5); //or glutSolidTeapot(0.5);
	glPopMatrix();

	glViewport(winWidth / 2, 0, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glutWireTeapot(0.5); //or glutSolidTeapot(0.5);
	glPopMatrix();

	glViewport(0, winHeight / 2, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glutWireTeapot(0.5); //or glutSolidTeapot(0.5);
	glPopMatrix();

	glViewport(winWidth / 2, winHeight / 2, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	glutWireTeapot(0.5); //or glutSolidTeapot(0.5);
	glPopMatrix();
	glFlush();
}

void MyReshape(int width, int height)
{
	winWidth = width;
	winHeight = height;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("OpenGL Example");

	//Projection Setting
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 30.0);

	//Resize 함수 기능 정의 
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}