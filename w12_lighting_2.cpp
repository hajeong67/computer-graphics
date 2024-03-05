#include <iostream>
#include <gl/freeglut.h>
using namespace std;

#define WIDTH 600
#define HEIGHT 600

float spin = 0;
bool rotationEnabled = true;

GLfloat initialLightPosition[] = { 0, 0, 1, 0 };
GLfloat currentLightPosition[] = { 0, 0, 1, 0 };

void toggleRotation()
{
    rotationEnabled = !rotationEnabled;
}

void resetLightPosition()
{
    for (int i = 0; i < 4; ++i)
        currentLightPosition[i] = initialLightPosition[i];
}

void display()
{
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
    glPushMatrix();
    if (rotationEnabled)
    {
        glRotatef(spin, 0.0, 1.0, 0.0);
        spin += 0.3; // 회전 속도 조절
    }
    else
    {
        resetLightPosition();
    }

    glLightfv(GL_LIGHT0, GL_POSITION, currentLightPosition);
    glTranslatef(currentLightPosition[0], currentLightPosition[1], currentLightPosition[2]);
    glDisable(GL_LIGHTING);
    glColor3f(1, 0, 0);
    glutWireCube(0.1);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    // Draw Solid Torus
    glColor3f(1, 0, 1);
    glutSolidTorus(0.1, 0.3, 100, 100);

    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 's' || key == 'S')
        toggleRotation();
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

    glutIdleFunc(display);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
