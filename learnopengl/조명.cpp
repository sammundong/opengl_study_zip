#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

//위치 지정
GLfloat light_position[] = { 0.0,0.0,3.0,0.0 }; //1 정면
//GLfloat light_position[] = { 3.0,0.0,0.0,0.0 }; //1 오른쪽
//GLfloat light_position[] = { 0.0,3.0,0.0,0.0 }; //1 왼쪽

//조명 색상 지정
GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };//4  흰
//GLfloat light_diffuse[] = { 1.0,0.0,0.0,1.0 };//5 빨
//GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };//6 노
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutSolidTeapot(0.5);
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutCreateWindow("조명함수");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 30.0);
	//조명 기능 활성화 
	glEnable(GL_LIGHTING);
	//개별 조명 활성화
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}