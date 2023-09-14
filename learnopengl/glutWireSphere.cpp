#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(-90, 1.0, 0.0, 0.0);
	glutWireSphere(0.5, 24, 6);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutCreateWindow("Open Example");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}
