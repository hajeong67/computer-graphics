#include <iostream>
#include <gl/freeglut.h>
#include <math.h> //sin(),cos()
using namespace std;

int shoulder = 0, elbow = 0, leg = 0, neck=0;
float zTranslation = 0.0;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0, 0.0, zTranslation);
	// Body
	glPushMatrix();
		glScalef(0.5, 0.5, 1.0);
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube(1.0);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();
		// Left Upper Arm 
		glTranslatef(0.25, 0.2, 0.0);
		glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
		glTranslatef(0.2, 0.0, 0.0);
		glPushMatrix();
			glScalef(0.4, 0.1, 1.0);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		// Left Lower Arm 
		glTranslatef(0.2, 0.0, 0.0);
		glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
		glTranslatef(0.15, 0.0, 0.0);
		glPushMatrix();
		glScalef(0.3, 0.1, 1.0);
		glColor3f(1.0, 1.0, 0.0);
		glutSolidCube(1.0);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		// Right Upper Arm 
		glTranslatef(-0.25, 0.2, 0.0);
		glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
		glTranslatef(-0.2, 0.0, 0.0);
		glPushMatrix();
			glScalef(0.4, 0.1, 1.0);
			glColor3f(1.0, 0.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		// Right Lower Arm 
		glTranslatef(-0.2, 0.0, 0.0);
		glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
		glTranslatef(-0.15, 0.0, 0.0);
		glPushMatrix();
			glScalef(0.3, 0.1, 1.0);
			glColor3f(1.0, 1.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	// Left Upper Leg
		glTranslatef(0.2,-0.25,0.0);
		glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
		glTranslatef(0.0,-0.2,0.0);
		glPushMatrix();
			glScalef(0.13,0.4,1.0);
			glColor3f(0.0, 1.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		// Left Lower Leg
		glTranslatef(0.0, -0.2, 0.0);
		glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
		glTranslatef(0.0, -0.15, 0.0);
		glPushMatrix();
			glScalef(0.13, 0.3, 1.0);
			glColor3f(0.9, 0.0, 2.5);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		// Right Upper Leg
		glTranslatef(-0.2, -0.25, 0.0);
		glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
		glTranslatef(0.0, -0.2, 0.0);
		glPushMatrix();
			glScalef(0.13, 0.4, 1.0);
			glColor3f(0.0, 1.0, 0.0);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();

		// Right Lower Leg
		glTranslatef(0.0, -0.2, 0.0);
		glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
		glTranslatef(0.0, -0.15, 0.0);
		glPushMatrix();
			glScalef(0.13, 0.3, 1.0);
			glColor3f(0.9, 0.0, 2.5);
			glutSolidCube(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glutWireCube(1.0);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		//head
		glTranslatef(0.0, 0.4, 0.0);
		glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
		glTranslatef(0.0, 0.0, 0.0);
		glPushMatrix();
			glColor3f(1.0, 1.0, 0.0);
			glutSolidSphere(0.15f, 100, 100);
		glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's': shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S': shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e': elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E': elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 'n': neck = (neck + 5) % 360;
		glutPostRedisplay();
		break;
	case 'N': neck = (neck - 5) % 360;
		glutPostRedisplay();
		break;
	case 't':
		zTranslation += 0.2;
		glutPostRedisplay();
		break;
	case 'T':
		zTranslation -= 0.2;
		glutPostRedisplay();
		break;
	case 'l': leg = (leg + 5) % 360;
		glutPostRedisplay();
		break;
	case 'L': leg = (leg - 5) % 360;
		glutPostRedisplay();
		break;
	default: break;
	}
	glutPostRedisplay();
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