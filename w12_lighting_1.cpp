#include <iostream>
#include <gl/freeglut.h>
using namespace std;

#define WIDTH 600
#define HEIGHT 600

GLfloat position[] = { 0, 0, 2, 0 }; // 초기 빛의 위치

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	// Light setup
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glutSolidTorus(0.1, 0.3, 100, 100);
	glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '+':
		position[2] += 1.0f; // z 위치를 양의 방향으로 증가
		break;
	case '-':
		position[2] -= 1.0f; // z 위치를 음의 방향으로 감소
		break;
	}

	glutPostRedisplay(); // 화면을 다시 그리도록 요청
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

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard); // 키보드 콜백 함수 등록
	glutMainLoop();
	return 0;
}
