#include <iostream>
#include <math.h>
#include <gl/freeglut.h>
#include <cmath>
#include <windows.h> 
using namespace std;

#define WIDTH 600
#define HEIGHT 600

#define PI 3.141592

//camera position
GLfloat cameraPositionX = 5.0f;
GLfloat cameraPositionY = 5.0f;
GLfloat cameraPositionZ = 2.0f;

GLfloat lookAtX = 0.0f;
GLfloat lookAtY = 0.0f;
GLfloat lookAtZ = 0.0f;

GLfloat upX = 0.0f;
GLfloat upY = 1.0f;
GLfloat upZ = 0.0f;

bool isUpView = false;

// name
static GLfloat shapeYPosition = 0.3f; 
static GLfloat shapeXPosition = 0.3f; 
GLfloat vibrationAmount = 0.0;

// light
GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat position[] = { 0, 0, 1, 1 };
GLfloat currentLightPosition[] = { 0, 0, 1, 1 };

bool dir = true;

int ltype = 1;
float spotlightAngle = 10.0; // spotlight angle
float spotlightAttenuation = 1.0; // spotlight attenuation

float spin = 0;
bool rotationEnabled = false;

// totus material
GLfloat mat_a[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat mat_d[] = { 0.3, 0.6, 0.2, 1.0 };
GLfloat mat_s[] = { 0, 1, 0, 1.0 };
GLfloat low_sh[] = { 50.0 };
GLfloat material_emission[] = { 0.3,0.3,0,1 };

// material
GLfloat ambient1[] = { 0.7, 0.7, 0.7, 0.1 };
GLfloat diffuse1[] = { 0.0, 0.0, 0.5, 1.0 };
GLfloat specular1[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess1[] = { 5.0 };
GLfloat emission1[] = { 0, 0, 0.1, 1.0 };

GLfloat ambient2[] = { 0.2, 0.2, 0.2, 0.1 };
GLfloat diffuse2[] = { 0.5, 0.5, 1.0, 1.0 };
GLfloat specular2[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess2[] = { 5.0 };
GLfloat emission2[] = { 0.2, 0.2, 0, 1 };

GLfloat ambient3[] = { 0.7, 0.7, 0.7, 0.1 };
GLfloat diffuse3[] = { 0.3, 0.2, 0.0, 1.0 };
GLfloat specular3[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat shininess3[] = { 50.0 };
GLfloat emission3[] = { 0.1,0.1,0,1 };

GLfloat ambient4[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat diffuse4[] = { 0.1, 0.0, 0.0, 1.0 };
GLfloat specular4[] = { 0.7, 1.0, 1.0, 1.0 };
GLfloat shininess4[] = { 50.0 };
GLfloat emission4[] = { 0.3, 0, 0, 1 };

// texture ID
GLuint texID1, texID2, texID3, texID4;
float rotationAngle = 0.0;
float rotationSpeed = 0.01f;

void drawBox(float width, float height, float depth, float red, float green, float blue)
{
	float halfWidth = width / 2.0;
	float halfHeight = height / 2.0;
	float halfDepth = depth / 2.0;

	glColor3f(red, green, blue);

	// 앞면
	glBegin(GL_LINE_LOOP);
	glVertex3f(-halfWidth, -halfHeight, -halfDepth);
	glVertex3f(halfWidth, -halfHeight, -halfDepth);
	glVertex3f(halfWidth, halfHeight, -halfDepth);
	glVertex3f(-halfWidth, halfHeight, -halfDepth);
	glEnd();

	// 뒷면
	glBegin(GL_LINE_LOOP);
	glVertex3f(-halfWidth, -halfHeight, halfDepth);
	glVertex3f(halfWidth, -halfHeight, halfDepth);
	glVertex3f(halfWidth, halfHeight, halfDepth);
	glVertex3f(-halfWidth, halfHeight, halfDepth);
	glEnd();

	// 연결하는 선분
	glBegin(GL_LINES);
	glVertex3f(-halfWidth, -halfHeight, -halfDepth);
	glVertex3f(-halfWidth, -halfHeight, halfDepth);
	glVertex3f(halfWidth, -halfHeight, -halfDepth);
	glVertex3f(halfWidth, -halfHeight, halfDepth);
	glVertex3f(halfWidth, halfHeight, -halfDepth);
	glVertex3f(halfWidth, halfHeight, halfDepth);
	glVertex3f(-halfWidth, halfHeight, -halfDepth);
	glVertex3f(-halfWidth, halfHeight, halfDepth);
	glEnd();
}

void drawSphere(float x, float y, float z, float radius, GLfloat ambient[], GLfloat diffuse[], GLfloat specular[], GLfloat shininess[], GLfloat emission[])
{
	glPushMatrix();
	glTranslatef(x, y, z);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

	glutSolidSphere(radius, 40, 40); 

	glPopMatrix();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void toggleRotation()
{
	rotationEnabled = !rotationEnabled;
}

void resetLightPosition()
{
	for (int i = 0; i < 4; ++i)
		currentLightPosition[i] = position[i];
}

void updateCamera() {
	GLfloat t = 0.003f; // 카메라 이동 속도 조절
	cameraPositionX = (1.0f - t) * cameraPositionX + t * 0.0f;
	cameraPositionY = (1.0f - t) * cameraPositionY + t * 0.0f;
	cameraPositionZ = (1.0f - t) * cameraPositionZ + t * 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35.0, 1.0, 1.0, 30.0); 

	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
		lookAtX, lookAtY, lookAtZ,
		upX, upY, upZ);
}

void animateCamera() {
	GLfloat t = 0.005f; 
	lookAtX = (1.0f - t) * lookAtX + t * -5.0f;
	cameraPositionY = (1.0f - t) * cameraPositionY + t * 5.0f;
	upX = (1.0f - t) * upX + t * 5.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35.0, 1.0, 1.0, 30.0);

	gluLookAt(cameraPositionX, cameraPositionY, cameraPositionZ,
		lookAtX, lookAtY, lookAtZ,
		upX, upY, upZ);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, 1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCamera();
	cameraPositionY += 0.0f;

	// Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	glPushMatrix();

	if (rotationEnabled)
	{
		glRotatef(spin, 0.0, 1.0, 0.0);
		spin += 0.3; // 회전 속도 조절

		// position[0]이 일정 값 이상이 되면 반대 방향으로 이동
		if (position[0] >= 5.0 || position[0] <= -5.0)
		{
			position[0] = (position[0] >= 5.0) ? 5.0 : -5.0;
			dir = !dir; // 방향 반전
		}

		if (dir) position[0] += 0.005;
		else position[0] -= 0.005;
	}
	else
	{
		resetLightPosition();
	}
	glPopMatrix();

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

	float offset = 0.0;

	glDisable(GL_TEXTURE_2D);
	drawSphere(-0.7 + offset, offset, -0.9, 0.06, ambient1, diffuse1, specular1, shininess1, emission1);
	drawSphere(-0.5 + offset, -0.4 + offset, -0.9, 0.05, ambient2, diffuse2, specular2, shininess2, emission2);
	drawSphere(-0.4 + offset, offset, -0.9, 0.05, ambient3, diffuse3, specular3, shininess3, emission3);
	drawSphere(-0.6 + offset, 0.5 + offset, -0.9, 0.04, ambient4, diffuse4, specular4, shininess4, emission4);
	glEnable(GL_TEXTURE_2D);

	// Teapot
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texID4);
	glTranslatef(-0.8, -0.8, 0);
	glutSolidTeapot(0.2);
	glPopMatrix();

	// Teapot2
	glBindTexture(GL_TEXTURE_2D, texID2);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glPushMatrix();
	glTranslatef(-0.6, 0.77, -0.8);
	glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.1);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	// christmas wreath-> Torus+sphere
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_sh);
	glMaterialfv(GL_FRONT_AND_BACK,
		GL_EMISSION, material_emission);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glTranslatef(0.5, 0.6, -0.8);
	glutSolidTorus(0.03, 0.09, 100, 100);
	drawSphere(-0.02, 0.05, 0.05, 0.03, ambient4, diffuse4, specular4, shininess4, emission4);
	drawSphere(0.02, 0.05, 0.05, 0.03, ambient4, diffuse4, specular4, shininess4, emission4);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	// 이름
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-0.8 + shapeXPosition, 0.8 + shapeYPosition, 0.0); // ㅡ
	drawBox(0.15, 0.05, 0.05, 1.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.7 + shapeXPosition, 0.75 + shapeYPosition, 0.0); //  ㅣ
	drawBox(0.05, 0.15, 0.05, 1.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.6 + shapeXPosition, 0.73 + shapeYPosition + vibrationAmount, 0.0); //  ㅣ
	drawBox(0.05, 0.25, 0.05, 1.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.75 + shapeXPosition, 0.51 + shapeYPosition, 0.0); //  ㅣ
	drawBox(0.05, 0.17, 0.05, 1.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.68 + shapeXPosition, 0.57 + shapeYPosition, 0.0); // ㅡ
	drawBox(0.13, 0.05, 0.05, 1.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.6 + shapeXPosition, 0.51 + shapeYPosition, 0.0); //  ㅣ
	drawBox(0.05, 0.17, 0.05, 1.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.68 + shapeXPosition, 0.45 + shapeYPosition, 0.0); // ㅡ
	drawBox(0.13, 0.05, 0.05, 1.0, 0.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.38 + shapeXPosition, 0.8 + shapeYPosition, 0.0); // .(cone)
	glRotatef(-90, 1.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glutWireCone(0.03, 0.07, 20, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.38 + shapeXPosition, 0.78 + shapeYPosition, 0.0); //  ㅡ
	drawBox(0.2, 0.05, 0.05, 1.0, 1.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.38 + shapeXPosition, 0.68 + shapeYPosition, 0.0); // ㅇ(sphere)
	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(0.07, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2 + shapeXPosition, 0.73 + shapeYPosition + vibrationAmount, 0.0); //  ㅣ
	drawBox(0.05, 0.25, 0.05, 1.0, 1.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.15 + shapeXPosition, 0.73 + shapeYPosition, 0.0); //  .
	drawBox(0.05, 0.05, 0.05, 1.0, 1.0, 0.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0 + shapeXPosition, 0.8 + shapeYPosition, 0.0); //  ㅡ
	drawBox(0.2, 0.05, 0.05, 0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.015 + shapeXPosition, 0.75 + shapeYPosition, 0.0); //  /
	glRotatef(45.0, 0.0, 0.0, 1.0); // 45도 회전
	drawBox(0.15, 0.05, 0.05, 0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.015 + shapeXPosition, 0.75 + shapeYPosition, 0.0); //  ↘
	glRotatef(-45.0, 0.0, 0.0, 1.0); // -45도 회전
	drawBox(0.15, 0.05, 0.05, 0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.15 + shapeXPosition, 0.75 + shapeYPosition, 0.0); //  .
	drawBox(0.05, 0.05, 0.05, 0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2 + shapeXPosition, 0.75 + shapeYPosition + vibrationAmount, 0.0); //  ㅣ
	drawBox(0.05, 0.25, 0.05, 0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.12 + shapeXPosition, 0.55 + shapeYPosition, 0.0); // ㅇ(torus)
	glColor3f(0.0, 0.0, 1.0);
	glutWireTorus(0.035, 0.085, 50, 50);
	glPopMatrix();

	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	// Rectangle(배경)
	glBindTexture(GL_TEXTURE_2D, texID1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, -1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, -1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, -1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, -1);
	glEnd();

	//cube1
	glBindTexture(GL_TEXTURE_2D, texID3);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE,
		GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE,
		GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	glTranslatef(-0.7, -0.7, -0.8);
	glutSolidCube(0.3);
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//cube2
	glBindTexture(GL_TEXTURE_2D, texID4);
	glPushMatrix();
	glTranslatef(-0.4, -0.7, -0.7);
	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.1, -0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, -0.1, 0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.1, 0.1, 0.1);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.1, 0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, 0.1, 0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, -0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.1, 0.1, -0.1);

	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.1, -0.1, 0.1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.1, -0.1, -0.1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.1, 0.1, -0.1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.1, 0.1, 0.1);
	glEnd();
	glPopMatrix();

	glFlush();
}

// Data read from the header of the BMP file// Each BMP file begins by a 54-bytes header
unsigned char header[54];
// Position in the file where the actual data begins
unsigned int dataPos;
// image width and height
unsigned int width, height;
// imageSize = width*height*3
unsigned int imageSize;

unsigned char* loadBMP(char* fname)
{
	FILE* file = fopen(fname, "rb");	 // file open
	if (!file) {
		cout << "Image file could not be opened "
			<< endl; return NULL;
	}
	if (fread(header, 1, 54, file) != 54) {
		// read header: if not 54 bytes read, problem
		cout << "Not a correct BMP file\n";
		return NULL;
	}
	if (header[0] != 'B' || header[1] != 'M') {  // 2 bytes
		cout << "Not a correct BMP file\n";
		return NULL;
	}
	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	imageSize = *(int*)&(header[0x22]);
	cout << "width = " << width << " height = " << height << endl;

	// Some BMP files are misformatted, guess missing information
	// 3 : one byte for each Red, Green and Blue component
	if (imageSize == 0)    imageSize = width * height * 3;

	// The BMP header is done that way
	if (dataPos == 0)      dataPos = 54;

	// Create a buffer
	unsigned char* bitmap = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(bitmap, 1, imageSize, file);

	// Everything is in memory now, the file can be closed
	fclose(file);

	return bitmap;
}
int initTexture()
{
	unsigned char* bitmap;

	glEnable(GL_TEXTURE_2D);

	// Texture ID1
	bitmap = loadBMP((char*)"christmas.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	cout << "width=" << width << " height=" << height << endl;

	glGenTextures(1, &texID1);
	glBindTexture(GL_TEXTURE_2D, texID1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Texture ID2
	bitmap = loadBMP((char*)"house.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	glGenTextures(2, &texID2);
	glBindTexture(GL_TEXTURE_2D, texID2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Texture ID3
	bitmap = loadBMP((char*)"pattern.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	glGenTextures(3, &texID3);
	glBindTexture(GL_TEXTURE_2D, texID3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture ID4
	bitmap = loadBMP((char*)"patterngreen.bmp");
	if (bitmap == NULL) {
		cout << "file open error" << endl;
		return -1;
	}
	glGenTextures(4, &texID4);
	glBindTexture(GL_TEXTURE_2D, texID4);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Environment Texture Parameter
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	return 0;

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'u':
		isUpView = !isUpView;

		if (isUpView) {
			lookAtY = 0.7f;
		}
		else {
			lookAtY = 0.0f;
		}
		break;
	case '1':
		ltype = 1;
		break;
	case '2':
		ltype = 2;
		break;
	case '3':
		ltype = 3;
		break;
	case 'a': // Increase spotlight angle
		spotlightAngle += 5.0;
		break;
	case 'b': // Decrease spotlight angle
		spotlightAngle -= 5.0;
		break;
	case 'c': // Increase spotlight attenuation
		spotlightAttenuation -= 0.1;
		break;
	case 't':
		upX = 1.0f - upX; 
		break;
	case 's':
		toggleRotation();
		break;
	case 'd':
		animateCamera();
		break;
	case 'y':
		ambient[0] = 0.2; 
		ambient[1] = 0.2;
		ambient[2] = 0.0;

		diffuse[0] = 1.0; 
		diffuse[1] = 1.0; 
		diffuse[2] = 0.0; 

		specular[0] = 1.0;
		specular[1] = 1.0; 
		specular[2] = 0.0; 
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void idle(void)
{
	rotationAngle += rotationSpeed;
	if (rotationAngle > 360.0f) {
		rotationAngle -= 360.0f;
	}
	vibrationAmount = 0.02 * sin(rotationAngle * PI / 180.0);

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("20221346김하정");
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);

	initTexture();
	glutKeyboardFunc(keyboard);

	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}