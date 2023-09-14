#include <glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.0f, 0.0f); //point #1
	glVertex2f(0.25f, 0.25f);//point #2
	glVertex2f(0.5f, 0.0f);//point #3
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-0.5f, 0.0f);//point #4
	glVertex2f(-0.75f, 0.5f);//point #5
	glVertex2f(-0.25f, 0.0f);//point #6

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