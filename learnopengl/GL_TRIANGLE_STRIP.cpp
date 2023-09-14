#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLE_STRIP);
	GLfloat x = -0.8;
	GLfloat y = 0.4;
	for (int i = 0; i < 6; i++)
	{
		if (i % 2 == 0)
			glColor3f(1.0, 0.0, 0.0);
		else
			glColor3f(0.0, 1.0, 0.0);
		glVertex3f(x, y, 0);
		x += 0.3;
		y *= -1;
	}
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