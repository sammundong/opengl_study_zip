//시점 조정 - gluLookAt(3,3,3,0,0,0,0,1,0);
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "math.h"

double time = 0; //time 변수 

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
	time = time + 0.1; //시간 증가 

	headAngle += 5;
	if (headAngle >= 360) headAngle -= 360;

	armAngleL = sin(time) * 20;
	armAngleR = -armAngleL;

	legAngleR = sin(time) * 20;
	legAngleL = -legAngleR;

	glutPostRedisplay();
	glutTimerFunc(22, timerFunction, 1); //타이머 설정 
}


void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Test Enable or Disable
	//Camera Setting (시점조절 관련 간단히 타이핑)
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
	glTranslatef(0, 1, 0); //몸의 1/2만큼 상향 이동 
	glScalef(2, 2, 1);

	glutSolidCube(1);
	glPopMatrix();
}

void drawLeftArm()
{
	glPushMatrix();
	glColor3f(0, 1, 0);

	//Transform 
	//Cube의 중심좌표 위치로 인해서 표현방법 변경 
	glTranslatef(0.0, 2.0, 0.0);
	glRotatef(armAngleL, 1, 0, 0); //팔 흔들기 

	//Modeling 
	glTranslatef(1.3, -1, 0);

	glPushMatrix();
	glScalef(0.5, 2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix(); //hand
	glTranslatef(0.0, -1.3, 0.0); //팔의 길이는 2
	glColor3f(0, 0, 0);
	glutSolidSphere(0.3, 18, 18);
	glPopMatrix();
	glPopMatrix();
}

void drawRightArm()
{
	glPushMatrix();
	glColor3f(1, 1, 0); //우측

	//Transform 
	// Cube의 중심좌표 위치로 인해서 표현방법 변경 
	glTranslatef(0.0, 2.0, 0.0);
	glRotatef(armAngleR, 1, 0, 0);

	//Modeling 
	glTranslatef(-1.3, -1, 0);

	glPushMatrix();
	glScalef(0.5, 2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix(); //hand
	glTranslatef(0.0, -1.3, 0.0); //팔의 길이는 2
	glColor3f(0, 0, 0);
	glutSolidSphere(0.3, 18, 18);
	glPopMatrix();
	glPopMatrix();
}

void drawLeftLeg()
{
	glPushMatrix();
	glColor3f(0, 1, 1); //좌측 
	//Transform 
	glRotatef(legAngleL, 1, 0, 0);

	//Modeling 
	glTranslatef(0.5, -2.0, 0);
	glPushMatrix();
	glScalef(0.6, 4, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //foot 
	glTranslatef(0.0, -2.2, 0.3); //발의 길이는 2
	glScalef(0.6, 0.4, 1.2);
	glColor3f(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

}

void drawRightLeg()
{
	glPushMatrix();
	glColor3f(0, 1, 1); //우측 

	//Transform 
	glRotatef(legAngleR, 1, 0, 0); //발 흔들기 

	//Modeling 
	glTranslatef(-0.5, -2.0, 0);
	glPushMatrix();
	glScalef(0.6, 4, 0.6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix(); //foot 
	glTranslatef(0.0, -2.2, 0.3); //발의 길이는 2
	glScalef(0.6, 0.4, 1.2);
	glColor3f(0, 0, 0);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}