#include <glut.h>
#include <Gl/glu.h>
#include <Gl/gl.h>
//- ���� ���� Ȱ��ȭ : glEnable(GL_DEPTH_TEST);
//-���� ���� ��� �� �ʱ�ȭ : glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
GLfloat pA[3] = { 0.2,0.2,0.2 };
GLfloat pB[3] = { -0.2,0.2,0.2 };
GLfloat pC[3] = { -0.2,-0.2,0.2 };
GLfloat pD[3] = { 0.2,-0.2,0.2 };
GLfloat pE[3] = { 0.2,0.2,-0.2 };
GLfloat pF[3] = { -0.2,0.2,-0.2 };
GLfloat pG[3] = { -0.2,-0.2,-0.2 };
GLfloat pH[3] = { 0.2,-0.2,-0.2 };

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.5, 0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//Axis
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(5.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 5.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 5.0f);
	glEnd();

	//���� 
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0); //Red
	glVertex3f(pA[0], pA[1], pA[2]);
	glVertex3f(pB[0], pB[1], pB[2]);
	glVertex3f(pC[0], pC[1], pC[2]);
	glVertex3f(pD[0], pD[1], pD[2]);
	glEnd();

	//�ĸ�  - Counter Clockwise
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0); //Green
	glVertex3f(pF[0], pF[1], pF[2]);
	glVertex3f(pE[0], pE[1], pE[2]);
	glVertex3f(pH[0], pH[1], pH[2]);
	glVertex3f(pG[0], pG[1], pG[2]);
	glEnd();

	////�ĸ� - Clockwise
	//glBegin(GL_POLYGON);
	//glColor3f(0.0, 1.0, 0.0); //Green
	//glVertex3f(pE[0], pE[1], pE[2]);
	//glVertex3f(pF[0], pF[1], pF[2]);
	//glVertex3f(pG[0], pG[1], pG[2]);
	//glVertex3f(pH[0], pH[1], pH[2]);
	//glEnd();

	//���� 
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0); //Blue
	glVertex3f(pA[0], pA[1], pA[2]);
	glVertex3f(pE[0], pE[1], pE[2]);
	glVertex3f(pF[0], pF[1], pF[2]);
	glVertex3f(pB[0], pB[1], pB[2]);
	glEnd();

	//����
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 1.0); //Cyan
	glVertex3f(pD[0], pD[1], pD[2]);
	glVertex3f(pC[0], pC[1], pC[2]);
	glVertex3f(pG[0], pG[1], pG[2]);
	glVertex3f(pH[0], pH[1], pH[2]);
	glEnd();

	//����
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0); //Margenta
	glVertex3f(pA[0], pA[1], pA[2]);
	glVertex3f(pD[0], pD[1], pD[2]);
	glVertex3f(pH[0], pH[1], pH[2]);
	glVertex3f(pE[0], pE[1], pE[2]);
	glEnd();

	//����
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0); //Yellow
	glVertex3f(pB[0], pB[1], pB[2]);
	glVertex3f(pF[0], pF[1], pF[2]);
	glVertex3f(pG[0], pG[1], pG[2]);
	glVertex3f(pC[0], pC[1], pC[2]);
	glEnd();

	//glutSolidTeapot(0.5);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("OpenGL Example");

	//Projection Setting
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 30.0);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, 0.7, 30.0); //�κ�����(�ĸ�ǥ��)

	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW); //Counter Clockwise
	//glFrontFace(GL_CW); //Clockwise

	//Culling
	//glCullFace(GL_FRONT); // Frontface (��������)
	//glCullFace(GL_BACK); //Backface (�ĸ�����)

	//���� : ���� �׸� �� �ܰ��� ǥ��
	/*glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);*/

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;

}