#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "BunnyModel.h"

int zRotate = 0;

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity(); //���� ��ȯ ��� �ʱ�ȭ 
	glRotatef(zRotate, 0.0, 0.0, 1.0); // Z�� ȸ�� (���� ����)

		//Bunney �׸��� �ڵ� 
	unsigned int i;
	for (i = 0; i < BUNNY_NUM_INDICES; i += 3)
	{
		int vi;
		glBegin(GL_LINES);
		vi = face_indicies[i][0]; glVertex3fv(bunny_vertices[vi]);
		vi = face_indicies[i][1]; glVertex3fv(bunny_vertices[vi]);
		vi = face_indicies[i][1]; glVertex3fv(bunny_vertices[vi]);
		vi = face_indicies[i][2]; glVertex3fv(bunny_vertices[vi]);
		vi = face_indicies[i][2]; glVertex3fv(bunny_vertices[vi]);
		vi = face_indicies[i][0]; glVertex3fv(bunny_vertices[vi]);
		glEnd();
	}
	glFlush();
}

void MyTimer(int Value)
{
	zRotate += 5;
	glutPostRedisplay();
	glutTimerFunc(100, MyTimer, 1);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // ���� ���۸� �� Z�� ȸ�� �ڵ�

	glutCreateWindow("OpenGL Example");
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(100, MyTimer, 1);
	glutMainLoop();
	return 0;
}