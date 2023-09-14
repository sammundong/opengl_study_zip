#include <glut.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "BunnyModel.h"
#include <stdio.h>

GLuint g_standfordBunnyID = -1;

GLint xValue = 0;
GLint yValue = 0;
GLint zValue = 0;

GLint clickDown = 0;
GLint fixX = 0;
GLint fixY = 0;

GLint GenerateCallList()
{
	GLint lid = glGenLists(1);

	glNewList(lid, GL_COMPILE);
	glColor3f(1.0f, 0.0f, 0.0f);

	//bunny 그리는 코드 
	unsigned int i;
	for (i = 0; i < 16301; i++)
	{
		int vi;
		// Randomly generate a color.
		GLubyte r = rand() % 256;
		GLubyte g = rand() % 256;
		GLubyte b = rand() % 256;
		// Set the color to the randomly generated color.
		glColor3ub(r, g, b);

		glBegin(GL_LINE_LOOP); //GL_POLYGON, GL_TRIANGLES, GL_LINE_LOOP
		vi = face_indicies[i][0]; glVertex3fv(vertices[vi]);
		vi = face_indicies[i][1]; glVertex3fv(vertices[vi]);
		vi = face_indicies[i][2]; glVertex3fv(vertices[vi]);
		glEnd();
	}
	glEndList();

	return lid;
}

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	//glScalef(2.0f,2.0f,2.0f);
	//Axis
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	//위치에 따라서 좌표축도 회전함 
	glRotatef(xValue, 1.0, 0.0, 0.0);
	glRotatef(yValue, 0.0, 1.0, 0.0);
	glRotatef(zValue, 0.0, 0.0, 1.0);
	//display Call Lists
	glCallList(g_standfordBunnyID);
	glFlush();
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
	glutInitWindowSize(700, 700);
	glutCreateWindow("Open Example");

	g_standfordBunnyID = GenerateCallList();

	glutDisplayFunc(MyDisplay);

	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);

	glutMainLoop();
	return 0;
}