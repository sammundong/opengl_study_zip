#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-1, 0, 0); glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, -1, 0); glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1);
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
	glTranslatef(0.6, 0.0, 0.0);
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(700, 700);
	glutCreateWindow("OpenGL Example");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}