//���� ���� - gluLookAt(3,3,3,0,0,0,0,1,0);
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "math.h"

double time = 0; //time ���� 

GLfloat headAngle = 0.0f;
GLfloat armAngleL = 0.0f;
GLfloat armAngleR = 0.0f;
GLfloat legAngleL = 0.0f;
GLfloat legAngleR = 0.0f;

void drawLeftArm();
void drawRightArm();
void drawLeftLeg();
void drawRightLeg();
void drawHead();
void drawBody();
void MyDisplay();
void timerFunction(int);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Open Example");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -20.0, 20.0);

	glClearColor(0.5, 0.5, 0.5, 0.0);

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(22, timerFunction, 1); //timer set
	glutMainLoop();
	return 0;
}

void timerFunction(int value)
{
	time = time + 0.1; //�ð� ���� 

	headAngle += 5;
	if (headAngle >= 360) headAngle -= 360;

	armAngleL = sin(time) * 20;
	armAngleR = -armAngleL;

	legAngleR = sin(time) * 20;
	legAngleL = -legAngleR;

	glutPostRedisplay();
	glutTimerFunc(22, timerFunction, 1); //Ÿ�̸� ���� 
}


void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Test Enable or Disable
	//Camera Setting (�������� ���� ������ Ÿ����)
	gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);

	glBegin(GL_LINES); //Axis
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(5.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 5.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 5.0f);
	glEnd();

	//Body
	drawBody();

	//Head
	drawHead();

	//Arm
	drawLeftArm();
	drawRightArm();

	//Leg
	drawLeftLeg();
	drawRightLeg();
	glFlush();
}

void drawHead()
{
	glPushMatrix();
	glColor3f(1, 0, 0);

	//Transform 
	glRotatef(headAngle, 0.0f, 1.0f, 0.0f);

	//Modeling 
	glTranslatef(0, 2.8, 0);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);

	/*glutSolidTeapot(0.8);*/
	glutSolidSphere(0.8, 18, 18);
	glPopMatrix();
}

void drawBody()
{
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(0, 1, 0); //���� 1/2��ŭ ���� �̵� 
	glScalef(2, 2, 1);

	glutSolidCube(1);
	glPopMatrix();
}

void drawLeftArm()
{
	glPushMatrix();
	glColor3f(0, 1, 0);

	//Transform 
	//Cube�� �߽���ǥ ��ġ�� ���ؼ� ǥ����� ���� 
	glTranslatef(0.0, 2.0, 0.0);
	glRotatef(armAngleL, 1, 0, 0); //�� ���� 

	//Modeling 
	glTranslatef(1.3, -1, 0);

	glPushMatrix();
	glScalef(0.5, 2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix(); //hand
	glTranslatef(0.0, -1.3, 0.0); //���� ���̴� 2
	glColor3f(0, 0, 0);
	glutSolidSphere(0.3, 18, 18);
	glPopMatrix();
	glPopMatrix();
}

void drawRightArm()
{
	glPushMatrix();
	glColor3f(1, 1, 0); //����

	//Transform 
	// Cube�� �߽���ǥ ��ġ�� ���ؼ� ǥ����� ���� 
	glTranslatef(0.0, 2.0, 0.0);
	glRotatef(armAngleR, 1, 0, 0);

	//Modeling 
	glTranslatef(-1.3, -1, 0);

	glPushMatrix();
	glScalef(0.5, 2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix(); //hand
	glTranslatef(0.0, -1.3, 0.0); //���� ���̴� 2
	glColor3f(0, 0, 0);
	glutSolidSphere(0.3, 18, 18);
	glPopMatrix();
	glPopMatrix();
}

void drawLeftLeg()
{
	glPushMatrix();
	glColor3f(0, 1, 1); //���� 
	//Transform 
	glRotatef(legAngleL, 1, 0, 0);

	//Modeling 
	glTranslatef(0.5, -2.0, 0);
	glPushMatrix();
	glScalef(0.6, 4, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //foot 
	glTranslatef(0.0, -2.2, 0.3); //���� ���̴� 2
	glScalef(0.6, 0.4, 1.2);
	glColor3f(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

}

void drawRightLeg()
{
	glPushMatrix();
	glColor3f(0, 1, 1); //���� 

	//Transform 
	glRotatef(legAngleR, 1, 0, 0); //�� ���� 

	//Modeling 
	glTranslatef(-0.5, -2.0, 0);
	glPushMatrix();
	glScalef(0.6, 4, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //foot 
	glTranslatef(0.0, -2.2, 0.3); //���� ���̴� 2
	glScalef(0.6, 0.4, 1.2);
	glColor3f(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}