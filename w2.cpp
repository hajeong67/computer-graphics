#include <gl/freeglut.h>

void drawStar() {
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.72f, 0.96f, 0.0f);
    glVertex3f(-0.66f, 0.78f, 0.0f);
    glVertex3f(-0.48f, 0.78f, 0.0f);
    glVertex3f(-0.63f, 0.66f, 0.0f);
    glVertex3f(-0.57f, 0.51f, 0.0f);
    glVertex3f(-0.74f, 0.60f, 0.0f);
    glVertex3f(-0.87f, 0.51f, 0.0f);
    glVertex3f(-0.81f, 0.66f, 0.0f);
    glVertex3f(-0.96f, 0.78f, 0.0f);
    glVertex3f(-0.78f, 0.78f, 0.0f);
    glEnd();
}

void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex3f(0.74f, 0.94f, 0.0f);
    glVertex3f(0.94f, 0.59f, 0.0f);
    glVertex3f(0.54f, 0.59f, 0.0f);
    glEnd();
}

void drawPentagon() {
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.05f, 0.35f, 0.0f);
    glVertex3f(0.25f, 0.2f, 0.0f);
    glVertex3f(0.15f, -0.05f, 0.0f);
    glVertex3f(-0.05f, -0.05f, 0.0f);
    glVertex3f(-0.15f, 0.2f, 0.0f);
    glEnd();
}

void drawLineTop() {
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.9f, -0.55f, 0.0f);
    glVertex3f(-0.1f, -0.55f, 0.0f);
    glEnd();
}

void drawLineBottom() {
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.9f, -0.85f, 0.0f);
    glVertex3f(-0.1f, -0.85f, 0.0f);
    glEnd();
}

void drawStrip() {
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.15f, -0.5f, 0.0f);
    glVertex3f(0.85f, -0.5f, 0.0f);
    glVertex3f(0.85f, -0.8f, 0.0f);
    glVertex3f(0.15f, -0.8f, 0.0f);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawStar();
    drawTriangle();
    drawPentagon();
    drawLineTop();
    drawLineBottom();
    drawStrip();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
    glutCreateWindow("<±èÇÏÁ¤>");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
