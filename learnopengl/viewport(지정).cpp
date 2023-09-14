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
	//glViewport(0, 0, width / 2, height / 2); //설정 변경에 따른 출력 위치 확인 
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
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