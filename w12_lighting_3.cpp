#include <iostream>
#include <gl/freeglut.h>
using namespace std;

#define WIDTH 600
#define HEIGHT 600
float spin = 0;
int ltype = 1;
float spotlightAngle = 10.0; 
float spotlightAttenuation = 1.0; 

void display()
{
    GLfloat position[] = { 0, 0, 1, 0 };

    // Orthographic View Volume
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 1, 30);

    // Camera Position, Direction, Up vector
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 3, 0, 0, 0, 0, 1, 0);

    // LIGHT
    switch (ltype) {
    case 1: // Point Light
        position[3] = 1;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0);
        break;
    case 2: // Directional Light
        position[3] = 0;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        break;
    case 3: // Spotlight
        position[3] = 1;
        glLightfv(GL_LIGHT0, GL_POSITION, position);
        GLfloat sd[] = { 0.3, 0.0, -1.0 };
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, sd);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotlightAngle);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0);
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, spotlightAttenuation);
        break;
    }
    // Draw Solid Torus
    glColor3f(1, 0, 1);
    glutSolidTorus(0.1, 0.3, 100, 100);

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case '1':
        ltype = 1;
        break;
    case '2':
        ltype = 2;
        break;
    case '3':
        ltype = 3;
        break;
    case 'a': 
        spotlightAngle += 5.0;
        break;
    case 'b': 
        spotlightAngle -= 5.0;
        break;
    case 'c': 
        spotlightAttenuation += 0.1;
        break;
    case 'd': 
        spotlightAttenuation -= 0.1;
        break;
    default:
        break;
    }
    spotlightAngle = max(1.0f, min(90.0f, spotlightAngle));
    spotlightAttenuation = max(0.1f, min(1.0f, spotlightAttenuation));

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("test");

    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}