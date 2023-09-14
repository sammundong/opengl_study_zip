#include <glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glScalef(1.2, 1.2, 1.2);
	glRotatef(135, 0.0, 1.0, 0.0);
	glTranslatef(0.5, 0.0, 0.0);


	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.2, -0.2, 0.0);
	glVertex3f(0.2, -0.2, 0.0);
	glVertex3f(0.2, 0.2, 0.0);
	glVertex3f(-0.2, 0.2, 0.0);
	glEnd();
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