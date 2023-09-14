#include <iostream>
#include <fstream>
#include <vector>

#include <glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>

struct Vector3f {
    float x, y, z;
};

std::vector<Vector3f> vertices;
std::vector<Vector3f> normals;
std::vector<std::vector<std::vector<int>>> faces; // [���� ����][���� ���� �ε���][���� �������� �ε���]

void ParseOBJ(const char* filename) {
    std::ifstream fin(filename);

    if (!fin) {
        std::cout << "������ �� �� �����ϴ�." << std::endl;
        exit(1);
    }

    char type[3];
    while (fin >> type) {
        if (strcmp(type, "v") == 0) {
            Vector3f vertex;
            fin >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        }
        else if (strcmp(type, "vn") == 0) {
            Vector3f normal;
            fin >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (strcmp(type, "f") == 0) {
            std::vector<std::vector<int>> face;
            for (int i = 0; i < 3; i++) {
                int vIndex, nIndex;
                fin >> vIndex;
                fin.ignore(2); // ����
                fin >> nIndex;
                face.push_back({ vIndex, nIndex });
            }
            faces.push_back(face);
        }
    }

    fin.close();
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �� �κп� �׸��� �ڵ带 �߰��ϸ� �˴ϴ�.
    // �Ľ��� �����͸� �̿��Ͽ� �׸��⸦ �������ּ���.

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OBJ Parser Example");
    glutDisplayFunc(Display);

    ParseOBJ("kitten.obj"); // example.obj ������ �Ľ��Ͽ� �����͸� ����

    glutMainLoop();
    return 0;
}