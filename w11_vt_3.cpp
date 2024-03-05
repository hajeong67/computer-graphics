#include <iostream>
#include <GL/freeglut.h>
using namespace std;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glutWireTeapot(6.0);

    glTranslatef(18.0, 0.0, -5.0);
    glColor3f(0.0, 1.0, 0.0);
    glutWireTeapot(6.0);

    glTranslatef(-36.0, 0.0, -5.0);
    glColor3f(1.0, 0.0, 0.0);
    glutWireTeapot(6.0);
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, 5.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '4':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-60.0, 30.0, -40.0, 10.0, 5.0, 30.0);
        glMatrixMode(GL_MODELVIEW);
        glutPostRedisplay();
        break;
    case '5':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-35.0, 35.0, -10.0, 10.0, 5.0, 30.0);
        glMatrixMode(GL_MODELVIEW);
        glutPostRedisplay();
        break;
    case '6':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-18.0, 0.0, 0.0, 12.0,5.0, 30.0);
        glMatrixMode(GL_MODELVIEW);
        glutPostRedisplay();
        break;
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
