#include <gl/freeglut.h>

GLfloat blueAngle = 0.0f;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glColor3f(1.0f, 0.0f, 0.0f);	// red
	glutSolidSphere(0.1f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.7f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);	// blue
	glutSolidSphere(0.05f, 100, 100);

	glPushMatrix();
	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);	// green
	glutSolidSphere(0.05f, 100, 100);

	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.1f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.6f, 2.5f);	// skyblue
	glutSolidSphere(0.03f, 100, 100);
	glPopMatrix();

	glRotatef(blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.12f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);	// black
	glutSolidSphere(0.03f, 100, 100);
	glPopMatrix();

	glRotatef(-blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.3f, 0.0f, 0.0f);
	glColor3f(2.5f, 2.3f, 0.0f);	// yellow
	glutSolidSphere(0.05f, 100, 100);

	glRotatef(-blueAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.1f, 0.0f, 0.0f);
	glColor3f(2.5f, 0.0f, 2.2f);	// pink
	glutSolidSphere(0.03f, 100, 100);

	blueAngle += 0.04f;

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}