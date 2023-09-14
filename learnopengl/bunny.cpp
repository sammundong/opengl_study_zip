#include <glut.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include "BunnyModel.h"

GLint g_standforBunnyID = -1;

GLint xValue = 0; GLint yValue = 0; GLint zValue = 0;

GLint clickDown = 0;
GLint fixX = 0; GLint fixY = 0;

//Light Position 
GLfloat lightOpos[] = { 0.0f,0.0f,3.0f,0.0f }; // 위치
GLfloat lightOambient[] = { 1.0,0.0,0.0,1.0 }; // 주변광
GLfloat lightOdiffuse[] = { 1.0,1.0,0.0,1.0 }; // 확산광
GLfloat lightOspecular[] = { 0.0,0.0,1.0,1.0 }; // 경면광

GLint GenerateCallList() {
    GLint lid = glGenLists(1);
    glNewList(lid, GL_COMPILE);
    glColor3f(1.0, 1.0, 1.0);
    //bunny 
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < sizeof(face_indicies) / sizeof(face_indicies[0]); i++) {
        for (int j = 0; j < 3; j++) {
            int vi = face_indicies[i][j];
            int ni = face_indicies[i][j + 3]; // Normal index
            glNormal3fv(&normals[ni][0]);
            glVertex3fv(&vertices[vi][0]);
        }
    }
    glEnd();
    glEndList();
    return lid;
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y)
{
    switch (KeyPressed) {
    case 'X':
    case 'x': xValue += 1;
        if (xValue > 360) xValue -= 360;
        break;
    case 'Y':
    case 'y': yValue += 1;
        if (yValue > 360) yValue -= 360;
        break;
    case 'Z':
    case 'z': zValue += 1;
        if (zValue > 360) zValue -= 360;
        break;
    case 'Q':
    case 'q':
        exit(0); break;
    case 32: //SPACE Key
        xValue = 0; yValue = 0; zValue = 0;
        break;
    case 27: //ESC Key
        exit(0); break;
    case 3: //CTRL + C
        exit(0); break;
    }
    glutPostRedisplay();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
        fixX = X; fixY = Y;
        clickDown = 1;
    }
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_UP) {
        clickDown = 0;
    }
}

void MyMouseMove(GLint X, GLint Y) {
    if (clickDown == 1) {
        xValue += (fixX - X);
        yValue += (fixY - Y);
        fixX = X; fixY = Y;
    }
    glutPostRedisplay();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //LightO Position (조명 고정)
    //glLightfv(GL_LIGHT0, GL_POSITION, lightOpos);

    glRotatef(xValue, 1.0, 0.0, 0.0);
    glRotatef(yValue, 0.0, 1.0, 0.0);
    glRotatef(zValue, 0.0, 0.0, 1.0);

    //Axis
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();

    //Light Position 
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(lightOpos[0], lightOpos[1], lightOpos[2]);
    glutSolidSphere(0.1, 36, 36);
    glPopMatrix();

    //display Call Lists
    glLineWidth(1);
    glColor3f(1.0f, 1.0f, 1.0f);

    //Light0 Position 
    glLightfv(GL_LIGHT0, GL_POSITION, lightOpos);

    glEnable(GL_LIGHTING);
    glCallList(g_standforBunnyID);
    glDisable(GL_LIGHTING);

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("OpenGL Example");
    glClearColor(0.35, 0.53f, 0.7f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.0, 0.1, 30);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);

    //0번 광원 특성 할당 
    glLightfv(GL_LIGHT0, GL_POSITION, lightOpos); // 위치
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightOambient); // 주변광
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightOdiffuse); // 확산광
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightOspecular); // 경면광 

    g_standforBunnyID = GenerateCallList();

    glShadeModel(GL_SMOOTH);

    //glEnable(GL_COLOR_MATERIAL); // 물체의 색상이 나타나도록 지정 

    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);
    glutMainLoop();
    return 0;
}