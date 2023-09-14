#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // x 
	glVertex3f(-1, 0, 0); glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0); // y
	glVertex3f(0, -1, 0); glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1); // z 
	glVertex3f(0, 0, -1); glVertex3f(0, 0, 1);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glutWireTeapot(0.3);

	glPushMatrix();
	glTranslatef(2.0, 2.0, 2.0);
	glutWireTeapot(0.3);

	glPushMatrix();
	glTranslatef(3.0, -1.0, 0.0);
	glRotatef(45, 0.0, 0.0, 1.0);
	glScalef(2.0, 2.0, 2.0);
	glutWireTeapot(0.3);
	glPopMatrix();

	glPopMatrix();

	glTranslatef(0.0, -2.0, 0.0);
	glutWireTeapot(0.3);

	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowSize(700, 700);

	glutCreateWindow("Open Example");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION); //차후 설명 
	glLoadIdentity();
	glOrtho(-6.0, 6.0, -6.0, 6.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}