#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "BunnyModel.h"

int zRotate = 0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); //현재 변환 행렬 초기화 
	//glRotatef(-90, 1.0, 0.0, 0.0); // Z축 회전 (차후 설명)
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