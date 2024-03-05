#include <gl/freeglut.h>

void drawRed() {
	glLoadIdentity();

	glColor3f(1.0, 0.0, 0.0);		
	glutSolidCube(0.3);
}

void drawGreen() {
	glLoadIdentity();

	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(0.6, 0.0, 0.0);   

	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(0.3);
}

void drawBlue() {
	glLoadIdentity();

	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);

	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(0.3);
}

void drawYellow() {
	glLoadIdentity();

	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glTranslatef(0.6, 0.0, 0.0);

	glColor3f(2.5, 2.3, 0.0);
	glutSolidCube(0.3);
}

void drawGray() {
	glLoadIdentity();

	glRotatef(-45.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.6, 0.0, 0.0);

	glColor3f(0.9, 0.9, 0.9);
	glutSolidCube(0.3);
}

void drawPink() {
	glLoadIdentity();

	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(-0.6, 0.0, 0.0);

	glColor3f(2.5, 0.0, 2.2);
	glutSolidCube(0.3);
}

void drawSkyblue() {
	glLoadIdentity();

	glTranslatef(0.0, -0.85, 0.0);
	glTranslatef(0.85, 0.0, 0.0);

	glColor3f(0.0, 2.1, 2.5);
	glutSolidCube(0.3);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawRed();
	drawGreen();
	drawBlue();
	drawYellow();
	drawGray();
	drawPink();
	drawSkyblue();


	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutCreateWindow("Transformation");

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}