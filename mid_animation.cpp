#include <iostream>
#include <GL/freeglut.h>
#include <math.h>

using namespace std;

#define PI 3.141592
static int gameStarted = 0; 

// 이름
static GLfloat shapeYPosition = 0.0f; 
static GLfloat nameSpeed = 0.05f;
static GLfloat nameScale = 1.5f;
static GLfloat wholeNameScale = 1.0f;
GLfloat vibrationAmount = 0.0;
float horizontalLineRotation = 0.0;
float rotationAngle = 0.0;

// 캐릭터
static GLfloat characterXPosition = 0.0f; 
int shoulder = 0, elbow = 0, leg = 0;

// 물방울 
GLfloat waterAngle = 0.0f;

// 티팟
GLfloat teapotAngleX = 0.0f;
float teapotAngleY = 0.0f;
GLfloat teapotAngleZ = 0.0f; 
GLfloat teapotSize = 0.1f;
GLfloat teapotX = 0.7f;
GLfloat teapotY = -0.7f;
GLfloat teapotTopY = 0.08f;
bool isTeapotEnlarged = false;

bool gKeyPressed = false;

void startGame() {
    gameStarted = 1;
    glutPostRedisplay();
}

// 버튼 그리기
void drawButton() {
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.5, 0.0); 
    glVertex2f(0.2, 0.2);
    glVertex2f(0.2, 0.3);
    glVertex2f(0.4, 0.3);
    glVertex2f(0.4, 0.2);
    glEnd();
}

// 큐브 그리기
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

// 캐릭터 그리기
void drawCharacter(float characterXPosition, float leg, float shoulder, float elbow) {
    glPushMatrix();
    // 몸
    glPushMatrix(); glTranslatef(-0.6 + characterXPosition, -0.6, 0.0);
    glScalef(0.1, 0.1, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    // 머리
    glTranslatef(-0.6 + characterXPosition, -0.52, 0.0);
    glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(0.03f, 100, 100);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // 오른쪽 위 팔
    glTranslatef(-0.55 + characterXPosition, -0.57, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.03, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // 오른쪽 아래 팔 
    glTranslatef(0.05, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(0.035, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.07, 0.03, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // 왼쪽 위 팔
    glTranslatef(-0.65 + characterXPosition, -0.57, 0.0);
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(-0.05, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.03, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // 왼쪽 아래 팔 
    glTranslatef(-0.05, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(-0.035, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.07, 0.03, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // 왼쪽 위 다리
    glTranslatef(-0.63 + characterXPosition, -0.65, 0.0);
    glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.05, 0.1, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // 왼쪽 아래 다리
    glTranslatef(0.0, -0.05, 0.0);
    glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.05, 0.1, 1.0);
    glColor3f(0.9, 0.0, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // 오른쪽 위 다리
    glTranslatef(-0.57 + characterXPosition, -0.65, 0.0);
    glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.05, 0.1, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // 오른쪽 아래 다리
    glTranslatef(0.0, -0.05, 0.0);
    glRotatef((GLfloat)leg, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.05, 0.0);
    glPushMatrix();
    glScalef(0.05, 0.1, 1.0);
    glColor3f(0.9, 0.0, 2.5);
    glutSolidCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}

// 물방울 보호막 그리기
void drawWaterShield(float characterXPosition, float waterAngle) {
    glPushMatrix();
    glTranslatef(-0.6f + characterXPosition, -0.7f, 0.0f);  // 캐릭터의 위치로 이동

    glPushMatrix();
    glRotatef(waterAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.25f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);	// 파란색
    glutSolidSphere(0.03f, 100, 100);

    glRotatef(waterAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.08f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.6f, 2.5f);	// 하늘색
    glutSolidSphere(0.02f, 100, 100);
    glPopMatrix();

    glPopMatrix();
}

// Y축과 평행한 축으로 회전하는 티팟 그리기
void drawTeapotY() {
    GLfloat scaleFactor = isTeapotEnlarged ? 2.0f : 1.0f;

    glPushMatrix();
    glTranslatef(teapotX, teapotY, 0.0f);

    // 티팟의 가장 높은 지점을 기준으로 확대
    glTranslatef(0.0f, teapotTopY, 0.0f);
    glScalef(scaleFactor, scaleFactor, scaleFactor);
    glTranslatef(0.0f, -teapotTopY, 0.0f);

    glRotatef(teapotAngleY, 0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutWireTeapot(teapotSize);
    glPopMatrix();
}

void updateShapePosition(float speed) {
    if (shapeYPosition > -1.0) {
        shapeYPosition -= speed;
    }
}

void updateCharacterPosition(int direction)
{
    // direction이 1이면 양의 방향, -1이면 음의 방향으로 이동
    characterXPosition += 0.05 * direction;
}

void rotateShapes(float angle)
{
    glRotatef(angle, 0.0, 1.0, 0.0); 
}

bool checkCollision() {
    float teapotXMin = teapotX - teapotSize;
    float characterXMax = characterXPosition - 0.5f; 

    if (teapotXMin <= characterXMax) {
        // 충돌이 감지되었을 경우
        return true;
    }
    return false;
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (!gameStarted) {
        glPushMatrix();
        glTranslatef(0.3, 0.1, 0.0);
        drawButton();
        glPopMatrix();
    }
    if (gameStarted) {
        if (shapeYPosition > -1.0) {
            // 이름이 화면 하단에 닿을 때까지 이동
            shapeYPosition -= 0.0001;
            drawCharacter(characterXPosition, leg, shoulder, elbow);
            drawWaterShield(characterXPosition, waterAngle);
        }
        else {
            if (gKeyPressed) {
                drawCharacter(characterXPosition, leg, shoulder, elbow);
                drawWaterShield(characterXPosition, waterAngle);
            }
        }
    }

    glPushMatrix();
    rotateShapes(rotationAngle);

    // 이름 쓰기
    glPushMatrix();
    glTranslatef(-0.8, 0.8 + shapeYPosition, 0.0); // ㅡ
    glRotatef(horizontalLineRotation, 1.0, 0.0, 0.0);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.15, 0.05, 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7, 0.75 + shapeYPosition, 0.0); //  ㅣ
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.15, 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, 0.73 + shapeYPosition+ vibrationAmount, 0.0); //  ㅣ
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.25, 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.75, 0.51 + shapeYPosition, 0.0); //  ㅣ
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.17, 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.68, 0.57 + shapeYPosition, 0.0); // ㅡ
    glRotatef(horizontalLineRotation, 1.0, 0.0, 0.0);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.13, 0.05, 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, 0.51 + shapeYPosition, 0.0); //  ㅣ
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.17, 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.68, 0.45 + shapeYPosition, 0.0); // ㅡ
    glRotatef(horizontalLineRotation, 1.0, 0.0, 0.0);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.13, 0.05, 0.05, 1.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.38, 0.8 + shapeYPosition, 0.0); // .(cone)
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    glColor3f(1.0, 1.0, 0.0);
    glutWireCone(0.03, 0.07, 20, 10); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.38, 0.78 + shapeYPosition, 0.0); //  ㅡ
    glRotatef(horizontalLineRotation, 1.0, 0.0, 0.0);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.2, 0.05, 0.05, 1.0, 1.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.38, 0.68 + shapeYPosition, 0.0); // ㅇ(sphere)
    glScalef(nameScale, nameScale, nameScale);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(0.07, 20, 20); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2, 0.73 + shapeYPosition+ vibrationAmount, 0.0); //  ㅣ
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.25, 0.05, 1.0, 1.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.15, 0.73 + shapeYPosition, 0.0); //  .
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.05, 0.05, 1.0, 1.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.8 + shapeYPosition, 0.0); //  ㅡ
    glRotatef(horizontalLineRotation, 1.0, 0.0, 0.0);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.2, 0.05, 0.05, 0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.015, 0.75 + shapeYPosition, 0.0); //  /
    glRotatef(45.0, 0.0, 0.0, 1.0); 
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.15, 0.05, 0.05, 0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.015, 0.75 + shapeYPosition, 0.0); //  ↘
    glRotatef(-45.0, 0.0, 0.0, 1.0);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.15, 0.05, 0.05, 0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15, 0.75 + shapeYPosition, 0.0); //  .
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.05, 0.05, 0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 0.75 + shapeYPosition+ vibrationAmount, 0.0); //  ㅣ
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    drawBox(0.05, 0.25, 0.05, 0.0, 0.0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.12, 0.55 + shapeYPosition, 0.0); // ㅇ(torus)
    glColor3f(0.0, 0.0, 1.0);
    glScalef(nameScale, nameScale, nameScale);
    glScalef(wholeNameScale, wholeNameScale, wholeNameScale);
    glutWireTorus(0.035, 0.085, 50, 50);
    glPopMatrix();

    glPopMatrix();
    
    if (!checkCollision()) {
        drawTeapotY();
    }

    // 티팟2: x축 평행하게 회전
    glPushMatrix();
    glTranslatef(teapotX, teapotY + 0.3f, 0.0f);
    glRotatef(teapotAngleX, 1.0f, 0.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutWireTeapot(teapotSize);
    glPopMatrix();

    // 티팟3: z축 평행하게 회전
    glPushMatrix();
    glTranslatef(teapotX, teapotY + 0.6f, 0.0f);
    glRotatef(teapotAngleZ, 0.0f, 0.0f, 1.0f); 
    glColor3f(0.5f, 0.5f, 0.5f); 
    glutWireTeapot(teapotSize);
    glPopMatrix();

    glFlush();

    glutSwapBuffers();
}

void idle(void)
{
    if (gameStarted && shapeYPosition > -1.0) {
        updateShapePosition(0.00001);
    }
    // 물방울이 회전하는 각속도 설정
    if (gKeyPressed) {
        waterAngle += 0.03f;
        if (waterAngle > 360.0f) {
            waterAngle -= 360.0f;
        }
    }

    // 티팟Y 회전 각속도 설정
    teapotAngleY += 0.05f;
    if (teapotAngleY > 360.0f) {
        teapotAngleY -= 360.0f;
    }

    // 티팟X 회전 각속도 설정
    teapotAngleX += 0.03f;
    if (teapotAngleX > 360.0f) {
        teapotAngleX -= 360.0f;
    }

    // 티팟Z 회전 각속도 설정
    teapotAngleZ += 0.1f;
    if (teapotAngleZ > 360.0f) {
        teapotAngleZ -= 360.0f;
    }

    // ㅡ획이 x축을 기준으로 회전
    horizontalLineRotation += 0.2f;
    if (horizontalLineRotation > 360.0f) {
        horizontalLineRotation -= 360.0f;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
        // 'r' 키 누르면 이름이 시계방향으로 회전
        rotationAngle += 5.0;
        break;
    case 'g':
        // 'g' 키를 누르면 물방울 그래픽 요소 회전 활성화
        gKeyPressed = true;
        glutPostRedisplay();
        break;
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
    case 'l': leg = (leg + 5) % 360;
        glutPostRedisplay();
        break;
    case 'L': leg = (leg - 5) % 360;
        glutPostRedisplay();
        break;
    case 'b':
        // 'b' 키를 누를 때마다 티팟 확대/축소
        isTeapotEnlarged = !isTeapotEnlarged;
        glutPostRedisplay();
        break;
    case 'n':
        wholeNameScale = 0.8;
        break;
    case 'N':
        wholeNameScale = 1.0;
        break;
    default: break;
    }

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        updateCharacterPosition(1);
        break;
    case GLUT_KEY_LEFT:
        updateCharacterPosition(-1);
        break;
    default:
        break;
    }
}

void convertDeviceXYOpenGLXY(int x, int y, float* ox, float* oy)
{
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    *ox = (float)(x - (float)w / 2.0) * (1.0 / (float)(w / 2.0));
    *oy = -(float)(y - (float)h / 2.0) * (1.0 / (float)(h / 2.0));
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float mouseX, mouseY;
        convertDeviceXYOpenGLXY(x, y, &mouseX, &mouseY);

        // 버튼의 OpenGL 좌표 범위 설정
        float buttonX1 = 0.5f;
        float buttonX2 = 0.6f;
        float buttonY1 = 0.3f;
        float buttonY2 = 0.4f;

        // 마우스 클릭한 위치(mouseX, mouseY)를 버튼 영역과 비교
        if (mouseX >= buttonX1 && mouseX <= buttonX2 && mouseY >= buttonY1 && mouseY <= buttonY2) {
            startGame();  // 게임 시작 버튼 클릭
        }
    }
}

void update(int value) {
    vibrationAmount = 0.1 * sin(2 * glutGet(GLUT_ELAPSED_TIME) * 0.001); // 진동 속도 및 크기 조절
    nameScale = 1.0 + 0.5 * sin(glutGet(GLUT_ELAPSED_TIME) * 0.001);
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("20221346");

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 0;
}