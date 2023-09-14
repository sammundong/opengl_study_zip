#include <glut.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include <stdio.h>
#include "BunnyModel.h"

GLuint g_standfordBunnyID = -1;

GLint xValue = 0;
GLint yValue = 0;
GLint zValue = 0;

GLint clickDown = 0;
GLint fixX = 0;
GLint fixY = 0;

GLint winWidth = 700;
GLint winHeight = 700;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	//좌하단
	glLoadIdentity();
	glViewport(0, 0, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//위치에 따라서 좌표축도 회전함 
	glRotatef(xValue, 1.0, 0.0, 0.0);
	glRotatef(yValue, 0.0, 1.0, 0.0);
	glRotatef(zValue, 0.0, 0.0, 1.0);

	//display Call Lists
	glCallList(g_standfordBunnyID);

	//우하단
	glLoadIdentity();
	glViewport(winWidth / 2, 0, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//위치에 따라서 좌표축도 회전함 
	glRotatef(xValue, 1.0, 0.0, 0.0);
	glRotatef(yValue, 0.0, 1.0, 0.0);
	glRotatef(zValue, 0.0, 0.0, 1.0);

	//display Call Lists
	glCallList(g_standfordBunnyID);

	//좌상단
	glLoadIdentity();
	glViewport(0, winHeight / 2, winWidth / 2, winHeight / 2);
	glPushMatrix();
	gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

	//위치에 따라서 좌표축도 회전함 
	glRotatef(xValue, 1.0, 0.0, 0.0);
	glRotatef(yValue, 0.0, 1.0, 0.0);
	glRotatef(zValue, 0.0, 0.0, 1.0);

	//display Call Lists
	glCallList(g_standfordBunnyID);

	//우상단
	glLoadIdentity();
	glViewport(winWidth / 2, winHeight / 2, winWidth / 2, winHeight / 2);
	gluLookAt(1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//위치에 따라서 좌표축도 회전함 
	glRotatef(xValue, 1.0, 0.0, 0.0);
	glRotatef(yValue, 0.0, 1.0, 0.0);
	glRotatef(zValue, 0.0, 0.0, 1.0);

	//display Call Lists
	glCallList(g_standfordBunnyID);

	glFlush();
}

void MyReshape(int width, int height)
{
	winWidth = width;
	winHeight = height;
}

GLint GenerateCallList()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	//Axis 
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();

	//bunny 그리는 코드 
	unsigned int i;
	glColor3f(1.0f, 0.0f, 0.0f);
	for (i = 0; i < 16301; i++)
	{
		int vi;
		glBegin(GL_LINES); //GL_POLYGON, GL_TRIANGLES, GL_LINE_LOOP
		vi = face_indicies[i][0]; glVertex3fv(vertices[vi]);
		vi = face_indicies[i][1]; glVertex3fv(vertices[vi]);
		vi = face_indicies[i][2]; glVertex3fv(vertices[vi]);
		glEnd();
	}
	glEndList();
	return lid;
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y)
{
	switch (KeyPressed) {
	case 'X':
	case 'x': xValue += 1;
		if (xValue > 360) xValue -= 360;
		break;
	case 'Y':
	case 'y': yValue += 1;
		if (yValue > 360) yValue -= 360;
		break;
	case 'Z':
	case 'z': zValue += 1;
		if (zValue > 360) zValue -= 360;
		break;
	case 'Q':
	case 'q':
		exit(0);
		break;
	case 32: //SPACE Key
		xValue = 0;
		yValue = 0;
		zValue = 0;
		break;
	case 27: //ESC Key
		exit(0);
		break;
	case 3: //CTRL + C
		exit(0);
		break;
	}
	printf("%d\n", KeyPressed);
	glutPostRedisplay();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y)
{
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN)
	{
		fixX = X;
		fixY = Y;
		clickDown = 1;
	}
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP)
	{
		clickDown = 0;
	}
}

void MyMouseMove(GLint X, GLint Y)
{
	if (clickDown == 1)
	{
		xValue += (fixX - X);
		yValue += (fixY - Y);
		fixX = X;
		fixY = Y;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Open Example");

	//Projection Setting
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 30.0);

	g_standfordBunnyID = GenerateCallList();

	glutDisplayFunc(MyDisplay);

	//Resize 함수 기능 정의 
	glutReshapeFunc(MyReshape);

	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);

	glutMainLoop();
	return 0;

}