#include <iostream>
#include <gl/freeglut.h>
#include <math.h> //sin(),cos()
using namespace std;

#define PI 3.141592

void drawBox()
{
	// Red rectangle
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();

	// Green rectangle
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	// Blue lines
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(45.0, 1.0, 1.0, 1.0);    // rotation w.r.t v=(1,1,1)
	glScalef(0.1, 0.2, 0.1); // drawBox()가 스케일링 안된 상태라 필요
	drawBox();
	glPopMatrix();
	glFlush();
}

void xyzRotate(char mode)
{
	GLfloat center[3] = { 0, 0, 0 };
	float angle = 45.0;

	switch (mode)
	{
	case 'x':
		glRotatef(angle, 1.0, 0.0, 0.0);
		break;
	case 'y':
		glRotatef(angle, 0.0, 1.0, 0.0);
		break;
	case 'z':
		glRotatef(angle, 0.0, 0.0, 1.0);
		break;
	case 'u':
		glPushMatrix();
		glTranslatef(0.0, -0.6, 0.0);
		glRotatef(45.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.6, 0.0);
		glPopMatrix();
		break;
	case 'v':
		glPushMatrix();
		glTranslatef(-0.6, 0.0, 0.0);
		glRotatef(45.0, 0.0, 1.0, 0.0);
		glTranslatef(0.6, 0.0, 0.0);
		glPopMatrix();
		break;
	case 'w':
		glPushMatrix();
		glTranslatef(-0.6, 0.0, 0.0);
		glRotatef(45.0, 0.0, 0.0, 1.0);
		glTranslatef(0.6, 0.0, 0.0);
		glPopMatrix();
		break;
	default: break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x': xyzRotate('x'); glutPostRedisplay(); break;
	case 'y': xyzRotate('y'); glutPostRedisplay(); break;
	case 'z': xyzRotate('z'); glutPostRedisplay(); break;
	case 'u': xyzRotate('u'); glutPostRedisplay(); break;
	case 'v': xyzRotate('v'); glutPostRedisplay(); break;
	case 'w': xyzRotate('w'); glutPostRedisplay(); break;
	default: break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}