#include <glut.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <stdio.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutWireTeapot(0.5);
	glFlush();
}

void MyReshape(int width, int height)
{
	printf("Width %d, Height %d\n", width, height);
	glViewport(0, 0, width, height);
	//glViewport(0, 0, width / 2, height / 2); //���� ���濡 ���� ��� ��ġ Ȯ�� 
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("OpenGL Example");

	//Projection Setting
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 30.0);

	//Resize �Լ� ��� ���� 
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}