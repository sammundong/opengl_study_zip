#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "BunnyModel.h"

int zRotate = 0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); //���� ��ȯ ��� �ʱ�ȭ 
	//glRotatef(-90, 1.0, 0.0, 0.0); // Z�� ȸ�� (���� ����)
	glutSolidSphere(0.5, 24, 6);
	
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