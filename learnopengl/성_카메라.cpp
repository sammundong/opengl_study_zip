#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

GLint xValue = 0; GLint yValue = 0; GLint zValue = 0;

GLint clickDown = 0;
GLint fixX = 0; GLint fixY = 0;

GLfloat lookatX = 0.0; GLfloat lookatY = 0.0; GLfloat lookatZ = 1.0;

GLfloat radius = 1.0; GLfloat theta = 0.0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(lookatX, lookatY, lookatZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(xValue, 1.0, 0.0, 0.0);
	glRotatef(yValue, 0.0, 1.0, 0.0);
	glRotatef(zValue, 0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0); //X
	glVertex3f(-1, 0, 0); glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0); //Y
	glVertex3f(0, -1, 0); glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1); //Z
	glVertex3f(0, 0, -1); glVertex3f(0, 0, 1);
	glEnd();

	//Using Push-Pop Matrix
	glColor3f(1.0, 0.0, 0.0);

	//middle
	glPushMatrix();
	glScalef(2.0, 1.0, 1.0);
	glutSolidCube(0.4);
	glPopMatrix();

	//left 
	glPushMatrix();
	glTranslatef(-0.6, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(0.4);
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.3, 36, 10);
	glPopMatrix();
	glPopMatrix();

	//right 
	glPushMatrix();
	glTranslatef(+0.6, 0.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(0.4);
	glPushMatrix();
	glTranslatef(0.0, 0.2, 0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.3, 36, 10);
	glPopMatrix();
	glPopMatrix();

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
	case 'q': exit(0); break;
	case 32: //SPACE
		xValue = 0; yValue = 0; zValue = 0; break;
	case 27: //ESC
		exit(0); break;
	case 3: //CTRL + C
		exit(0); break;
	}
	glutPostRedisplay();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		fixX = X; fixY = Y;
		clickDown = 1;
	}
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {
		clickDown = 0;
	}
}

void MyMouseMove(GLint X, GLint Y) {
	if (clickDown == 1) {
		yValue = yValue + (fixX - X);
		xValue = xValue + (fixY - Y);
		fixX = X; fixY = Y;
	}
	glutPostRedisplay();
}

void MyTimer(int Value)
{
	lookatX = radius * cos(theta * 3.14 / 180.0);
	lookatZ = radius * sin(theta * 3.14 / 180.0);
	lookatY = 0.8;
	theta += 1;

	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("OpenGL Example");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0); //시점과 거리설정 

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutTimerFunc(40, MyTimer, 1);

	glutMainLoop();
	return 0;
}