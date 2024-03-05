#include <iostream>
#include <GL/freeglut.h>
using namespace std;

bool reverseView = false;
bool case2 = false;
bool case3 = false;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (reverseView) {
        gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0);
    }
    else if (case2) {
        gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, -2.0, -1.0, 0.0);
    }
    else if (case3) {
        gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, -2.0, 1.0, 0.0);
    }
    else {
        gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }

    glColor3f(1, 0, 0);
    glutWireTeapot(3);
    glColor3f(0, 1, 0);
    glTranslatef(5, 0, -5);
    glutWireTeapot(3);
    glColor3f(0, 0, 1);
    glTranslatef(-10, 0, -5);
    glutWireTeapot(3);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, 5.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == '1')
    {
        reverseView = true;
        glutPostRedisplay();
    }
    if (key == '2')
    {
        case2 = true;
        glutPostRedisplay();
    }
    if (key == '3')
    {
        case3 = true;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutCreateWindow("Viewing Transformation");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
