#include <iostream>
#include <gl/freeglut.h>
using namespace std;

#define WIDTH 600
#define HEIGHT 600

GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 }; 
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat ambient1[] = { 0.1, 0.1, 0.1, 0.1 };
GLfloat diffuse1[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat specular1[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess1[] = { 0.0 };
GLfloat emission1[] = { 0, 0, 0.1, 1.0 };

GLfloat ambient2[] = { 0.7, 0.7, 0.7, 0.1 };
GLfloat diffuse2[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat specular2[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess2[] = { 0.0 };
GLfloat emission2[] = { 0, 0, 0.1, 0.2 };

GLfloat ambient3[] = { 0.2, 0.2, 0.2, 0.1 };
GLfloat diffuse3[] = { 0.0, 0.3, 1.0, 1.0 }; 
GLfloat specular3[] = { 0.5, 0.5, 0.7, 1.0 };
GLfloat shininess3[] = { 0.0 };
GLfloat emission3[] = { 0.1, 0.1, 0.1, 1 };

GLfloat ambient4[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat diffuse4[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat specular4[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess4[] = { 5.0 };
GLfloat emission4[] = { 0, 0, 0.1, 1.0 };

GLfloat ambient5[] = { 0.7, 0.7, 0.7, 0.1 };
GLfloat diffuse5[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat specular5[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess5[] = { 5.0 };
GLfloat emission5[] = { 0, 0, 0.1, 1.0 };

GLfloat ambient6[] = { 0.2, 0.2, 0.2, 0.1 };
GLfloat diffuse6[] = { 0.5, 0.5, 1.0, 1.0 };
GLfloat specular6[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess6[] = { 5.0 };
GLfloat emission6[] = { 0.2, 0.2, 0, 1 };

GLfloat ambient7[] = { 0.1, 0.1, 0.1, 0.1 };
GLfloat diffuse7[] = { 0.0, 0.0, 0.5, 1.0 }; 
GLfloat specular7[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess7[] = { 50.0 };
GLfloat emission7[] = { 0, 0, 0.1, 1.0 };

GLfloat ambient8[] = { 0.7, 0.7, 0.7, 0.1 };
GLfloat diffuse8[] = { 0.0, 0.3, 1.0, 1.0 };
GLfloat specular8[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess8[] = { 50.0 };
GLfloat emission8[] = { 0,0,0.1, 1 };

GLfloat ambient9[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat diffuse9[] = { 0.0, 0.1, 1.0, 1.0 };
GLfloat specular9[] = { 0.7, 1.0, 1.0, 1.0 };
GLfloat shininess9[] = { 50.0 };
GLfloat emission9[] = { 0.3, 0.3, 0, 1 };

GLfloat ambient10[] = { 0.2, 0.2, 0.2, 0.1 };
GLfloat diffuse10[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat specular10[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess10[] = { 0.0 };
GLfloat emission10[] = { 0,0, 0.1, 1 };

GLfloat ambient11[] = { 0.2, 0.2, 0.2, 0.1 };
GLfloat diffuse11[] = { 0.0, 0.0, 1.0, 1.0 }; // 파란색
GLfloat specular11[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess11[] = { 0.0 };
GLfloat emission11[] = { 0.2, 0.2, 0.5, 1 };

GLfloat ambient12[] = { 0.2, 0.2, 0.2, 0.1 };
GLfloat diffuse12[] = { 0.0, 0.0,0.5, 1.0 }; // 파란색
GLfloat specular12[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess12[] = { 0.0 };
GLfloat emission12[] = { 0.3, 0.3, 0, 1 };

GLfloat position[] = { 0, 0, 2, 1 };
bool dir = true;

void drawSphere(float x, float y, float z, float radius, GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess[], GLfloat emission[])
{
    glPushMatrix();
    glTranslatef(x, y, z);

    // Set material properties for the current sphere
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

    glutSolidSphere(radius, 40, 40); // Increased sphere resolution for smoother appearance

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // View Volume
    glOrtho(-1, 1, -1, 1, 1, 30);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Light Position
    if (dir) position[0] += 0.005;
    else position[0] -= 0.005;
    if (position[0] >= 5.0) dir = false;
    if (position[0] <= -5.0) dir = true;
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    // Camera
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

    // Light
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    // Draw 12 spheres with different material properties
    float offset = 0.0; // Adjust this offset for centering

    drawSphere(-0.6 + offset, 0.4+offset, 0, 0.15, ambient1, diffuse1, specular1, shininess1, emission1);
    drawSphere(-0.6 + offset,  offset, 0, 0.15, ambient2, diffuse2, specular2, shininess2, emission2);
    drawSphere(-0.6 + offset, -0.4 + offset, 0, 0.15, ambient3, diffuse3, specular3, shininess3, emission3);
    drawSphere(-0.2 + offset, 0.4 + offset, 0, 0.15, ambient4, diffuse4, specular4, shininess4, emission4);
    drawSphere(-0.2 + offset,  offset, 0, 0.15, ambient5, diffuse5, specular5, shininess5, emission5);
    drawSphere(-0.2 + offset, -0.4 + offset, 0, 0.15, ambient6, diffuse6, specular6, shininess6, emission6);
    drawSphere(0.2 + offset, 0.4 + offset, 0, 0.15, ambient7, diffuse7, specular7, shininess7, emission7);
    drawSphere(0.2 + offset,  offset, 0, 0.15, ambient8, diffuse8, specular8, shininess8, emission8);
    drawSphere(0.2 + offset, -0.4 + offset, 0, 0.15, ambient9, diffuse9, specular9, shininess9, emission9);
    drawSphere(0.6 + offset, 0.4 + offset, 0, 0.15, ambient10, diffuse10, specular10, shininess10, emission10);
    drawSphere(0.6 + offset,  offset, 0, 0.15, ambient11, diffuse11, specular11, shininess11, emission11);
    drawSphere(0.6+ offset, -0.4 + offset, 0, 0.15, ambient12, diffuse12, specular12, shininess12, emission12);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("test");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
