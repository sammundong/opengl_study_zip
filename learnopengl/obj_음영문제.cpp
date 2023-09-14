#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include <string>
#include <sstream> // istringstream iss(s);
#include <fstream>
#include <iostream>
using namespace std;

//GLdouble forValue = 0.0;

GLint xValue = 0; GLint yValue = 0; GLint zValue = 0;
GLint clickDown = 0; GLint fixX = 0; GLint fixY = 0;

// 0번 광원 특성
GLfloat lightOpos[] = { 0.0,0.0,1.0,1.0 }; // 위치
GLfloat lightOambient[] = { 0.2,0.2,0.2,1.0 };// 주변광
GLfloat lightOdiffuse[] = { 0.4,0.4,0.4,1.0 };// 확산광
GLfloat lightOspecular[] = { 0.4,0.4,0.4,1.0 };// 경면광

void MyLightInit() {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 0번 광원 특성 할당
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightOambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightOdiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightOspecular);
}

class obj3dmodel {
    //정점
    struct vertex {
        double x; double y; double z;
    };
    //법선 벡터
    struct normal {
        double nx; double ny; double nz;
    };
    //면
    struct face {
        unsigned int v1, v2, v3;
        unsigned int n1, n2, n3;
    };
    vector<vertex> vertices;
    vector<normal> normals;
    vector<face> faces;

public:
    void readfile(const char* filename);
    void draw(); // 3D 렌더링
};

obj3dmodel model;

void obj3dmodel::readfile(const char* filename) {
    string s;
    ifstream fin(filename);    // 파일을 읽기 위해 ifstream 사용

    if (!fin) { cerr << "Error opening file: " << filename << endl; return; }

    while (getline(fin, s)) {
        if (s.empty() || s[0] == '#')  continue; //s가 비어있거나, 주석(#로 시작하는 문자열)이면 무시

        istringstream iss(s); // 문자열을 읽기 위해, iss 객체 생성 (파싱을 위해)
        string type;
        iss >> type;

        if (type == "v") {    // 정점
            vertex v;
            iss >> v.x >> v.y >> v.z;
            this->vertices.push_back(v);
        }
        else if (type == "vn") {  // 법선 벡터
            normal n;
            iss >> n.nx >> n.ny >> n.nz;
            this->normals.push_back(n);
        }
        else if (type == "f") {   // 면
            face f;
            char dummy; // 사용하지 않을 문자를 저장
            iss >> f.v1 >> dummy >> dummy >> f.n1 >> f.v2 >> dummy >> dummy >> f.n2 >> f.v3 >> dummy >> dummy >> f.n3;
            f.v1--; f.v2--; f.v3--; // 1을 빼서 0부터 시작하도록 변환
            f.n1--; f.n2--; f.n3--;
            faces.push_back(f);
        }
    }
}

void obj3dmodel::draw() {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < faces.size(); i++) {
        face f = faces[i];
        vertex v1 = vertices[f.v1]; vertex v2 = vertices[f.v2]; vertex v3 = vertices[f.v3];
        normal n1 = normals[f.n1]; normal n2 = normals[f.n2]; normal n3 = normals[f.n3];

        glNormal3d(n1.nx, n1.ny, n1.nz); glVertex3d(v1.x, v1.y, v1.z);
        glNormal3d(n2.nx, n2.ny, n2.nz); glVertex3d(v2.x, v2.y, v2.z);
        glNormal3d(n3.nx, n3.ny, n3.nz); glVertex3d(v3.x, v3.y, v3.z);
    }
    glEnd();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 위치에 따라서 좌표축도 회전
    glRotatef(xValue, 1.0, 0.0, 0.0);
    glRotatef(yValue, 0.0, 1.0, 0.0);
    glRotatef(zValue, 0.0, 0.0, 1.0);

    ////axis
    //glLineWidth(2.0);
    //glBegin(GL_LINES);
    //glColor3f(1.0, 0.0, 0.0);
    //    glVertex3f(-2.0, 0.0, 0.0); glVertex3f(2.0, 0.0, 0.0);
    //    glColor3f(0.0, 1.0, 0.0);
    //    glVertex3f(0.0, -2.0, 0.0); glVertex3f(0.0, 2.0, 0.0);
    //    glColor3f(0.0, 0.0, 1.0);
    //    glVertex3f(0.0, 0.0, -2.0); glVertex3f(0.0, 0.0, 2.0);
    //glEnd();

    // 시야 설정
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0); // 모델의 색상 (흰색)
    glScalef(2.0f, 2.0f, 2.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, lightOpos); // 위치성 광원

    // obj3dmodel 클래스의 draw 함수 호출하여 모델 렌더링
    model.draw();
    glutPostRedisplay();
    glFlush();
}

void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
    switch (KeyPressed) {
    case 'X': case 'x':
        xValue += 1;
        if (xValue > 360) xValue -= 360;
        break;
    case 'Y': case 'y':
        yValue += 1;
        if (yValue > 360) yValue -= 360;
        break;
    case 'Z': case 'z':
        zValue += 1;
        if (zValue > 360) zValue -= 360;
        break;
    case 'Q': case 'q': case 27:/*esc*/ case 3: /*ctrl+c*/
        exit(0); break;
    case 32: // SPACE Key
        xValue = 0; yValue = 0; zValue = 0; break;
        //case 91: // [
        //    forValue += 1;
        //    break;
        //case 93: // ]
        //    forValue -= 1;
        //    break;
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
        xValue += (fixY - Y);
        yValue += (fixX - X);
        fixX = X; fixY = Y;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    const char* filename = "rocker.obj";
    model.readfile(filename);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 700);
    glutCreateWindow("Rocker OBJ");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -3.0, 3.0);
    glClearColor(0.8, 0.8, 0.8, 1.0);

    MyLightInit();

    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMouseFunc(MyMouseClick);
    glutMotionFunc(MyMouseMove);

    glutMainLoop();
    return 0;
}