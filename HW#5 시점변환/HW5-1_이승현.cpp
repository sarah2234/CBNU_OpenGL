/*******************************************************************************************************/
/*                                 HW#5-1 : gluLookAt()�� �ǽð� ����(1)                               */
/*  �ۼ��� : �̽���                                                            ��¥ : 2021�� 10�� 31�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. ���� ��ǥ�踦 Keyboard Callback �Լ��� �ǽð� ��� �����ϵ��� �����Ѵ�.                        */
/* ��� :                                                                                              */
/* 1. �� Ű�� ������ Camera�� Y�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 2. �� Ű�� ������ Camera�� Y�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 3. �� Ű�� ������ Camera�� X�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 4. �� Ű�� ������ Camera�� X�� ��ǥ�� 0.01�� ���������� ����                                        */
/* 5. a �Ǵ� A Ű�� ������ ����(Focus)�� X�� ��ǥ�� 0.01�� ���������� ����                             */
/* 6. f �Ǵ� F Ű�� ������ ����(Focus)�� X�� ��ǥ�� 0.01�� ���������� ����                             */
/* 7. r �Ǵ� R Ű�� ������ ����(Focus)�� Y�� ��ǥ�� 0.01�� ���������� ����                             */
/* 8. v �Ǵ� V Ű�� ������ ����(Focus)�� Y�� ��ǥ�� 0.01�� ���������� ����                             */
/* 9. z �Ǵ� Z Ű�� ������ ����(Focus)�� Z�� ��ǥ�� 0.01�� ���������� ����                             */
/* 10. t �Ǵ� T Ű�� ������ ����(Focus)�� Z�� ��ǥ�� 0.01�� ���������� ����                            */
/* 11: s �Ǵ� S Ű�� ������ �ʱ� ��ȯ ���·� �ǵ��ư�                                                  */
/*******************************************************************************************************/

// 0.1�� �� �ӵ��� �ʹ� ���� 0.01�� �����Ͽ����ϴ�.

#include <GL/glut.h>

bool moveCameraX[2], moveCameraY[2], moveFocusX[2], moveFocusY[2], moveFocusZ[2]; // ī�޶� �� ������ ��ġ�� �����ϴ� ������
GLdouble cameraX, cameraY, focusX, focusY, focusZ; // ī�޶� �� ������ ��ġ�� �����ϴ� ������

// �ʱ� ����
void MyInit()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // ȭ���� ���������� �����

    // �ʱ� ȭ�鿡�� ī�޶�� ������ �������� �ʵ��� ����
    // '������[0] = true'�� �� ��ǥ�迡�� ��� ������, '������[1] = true'�� �� ���� ������ �̵�
    for (int i = 0; i < 2; i++)
    {
        moveCameraX[i] = false;
        moveCameraY[i] = false;
        moveFocusX[i] = false;
        moveFocusY[i] = false;
        moveFocusZ[i] = false;
    }
    
    // �ʱ� ȭ�鿡���� ī�޶� �� ���� ��ġ ����
    cameraX = 0.0;
    cameraY = 3.5;
    focusX = 0.0;
    focusY = 0.0;
    focusZ = 0.0;
}

// ��ü �׸���
void DrawGround() {
    glColor3f(0.5, 0.5, 0.5); // Teapot�� ��ġ�� ���� ���� ����
    glBegin(GL_POLYGON); // �ٰ��� �׸��� ����(�� �׸���)
    glVertex3f(-2.0, -0.71, 2.0); // ��(�簢��)�� �̷�� 4���� �������� ��ġ ����
    glVertex3f(2.0, -0.71, 2.0);
    glVertex3f(2.0, -0.71, -2.0);
    glVertex3f(-2.0, -0.71, -2.0);
    glEnd(); // �ٰ��� �׸��� ������

    glColor3f(0.3, 0.3, 0.3); // �� ���� ���ڹ����� ���� ����
    glBegin(GL_LINES); // �� �׸��� ����
    for (float x = -2.0; x <= 2.2; x += 0.2) { // �� ��ü�� ���μ� ����
        glVertex3f(x, -0.7, -2.0); // ���� �̷�� 2���� �������� ��ġ ����
        glVertex3f(x, -0.7, 2.0);
    }
    
    for (float z = -2.0; z <= 2.2; z += 0.2) { // �� ��ü�� ���μ� ����
        glVertex3f(-2.0, -0.7, z); // ���� �̷�� 2���� �������� ��ġ ����
        glVertex3f(2.0, -0.7, z);
    }
    glEnd(); // �� �׸��� ������
}

// Display Event �߻� �� ȣ��Ǵ� callback �Լ�
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �� ���ۿ� ���� ���۸� �����Ͽ� ȭ�鿡�� �׸� �����
    glMatrixMode(GL_MODELVIEW); // �𵨺� ��� ����
    glLoadIdentity(); // �𵨺� ����� �׵� ��ķ� �ʱ�ȭ

    gluLookAt(cameraX, cameraY, 3.5, focusX, focusY, focusZ, 0.0, 1.0, 0.0); // ���� ��ǥ�� ���� (ī�޶��� ��ġ�� ���� ����)
    
    DrawGround(); // Teapot�� ��ġ�� �� �׸���

    glColor3f(1.0, 1.0, 0.0); // Teapot ���� ����
    glutWireTeapot(1.0); // Teapot �׸���

    glFlush(); // ���� ���� ������ �������� ���������� ���μ��� ����
}

// Keyboard Event �߻� �� ȣ��Ǵ� callback �Լ� (�Ϲ�Ű ó��)
void MyKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A': // 'a'�� 'A'�� �Է����� ��
        moveFocusX[0] = true; // ������ ���������� �����ؼ� ������
        moveFocusX[1] = false;
        break;
    case 'f':
    case 'F': // 'f'�� 'F'�� �Է����� ��
        moveFocusX[0] = false;
        moveFocusX[1] = true; // ������ �������� �����ؼ� ������
        break;
    case 'r':
    case 'R': // 'r'�̳� 'R'�� �Է����� ��
        moveFocusY[0] = true; // ������ �������� �����ؼ� ������
        moveFocusY[1] = false;
        break;
    case 'v':
    case 'V': // 'v'�� 'V'�� �Է����� ��
        moveFocusY[0] = false;
        moveFocusY[1] = true; // ������ �Ʒ������� �����ؼ� ������
        break;
    case 'z':
    case 'Z': // 'z'�� 'Z'�� �Է����� ��
        moveFocusZ[0] = true; // ������ ������ �����ؼ� ������
        moveFocusZ[1] = false;
        break;
    case 't':
    case 'T': // 't'�� 'T'�� �Է����� ��
        moveFocusZ[0] = false;
        moveFocusZ[1] = true; // ������ �ڷ� �����ؼ� ������
        break;
    case 's':
    case 'S': // 's'�� 'S'�� �Է����� ��
        MyInit(); // �ʱ� ȭ������ ���ư�
        break;
    }
}

// Keyboard Event �߻� �� ȣ��Ǵ� callback �Լ� (Ư��Ű ó��)
void MySpecialKey(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: // �踦 �Է����� ��
        moveCameraY[0] = true; // ī�޶��� ��ġ�� ���� �����ؼ� ������
        moveCameraY[1] = false;
        break;
    case GLUT_KEY_DOWN: // �鸦 �Է����� ��
        moveCameraY[0] = false; 
        moveCameraY[1] = true; // ī�޶��� ��ġ�� ������ �����ؼ� ������
        break;
    case GLUT_KEY_LEFT: // �縦 �Է����� ��
        moveCameraX[0] = false;
        moveCameraX[1] = true; // ī�޶��� ��ġ�� �������� �����ؼ� ������
        break;
    case GLUT_KEY_RIGHT: // �渦 �Է����� ��
        moveCameraX[0] = true; // ī�޶��� ��ġ�� ���������� �����ؼ� ������
        moveCameraX[1] = false;
        break;
    }
}

// ó���� Event�� ���� �� ȣ��Ǵ� callback �Լ�
void MyIdle()
{
    // '������[0] = true'�� �� ��ǥ�迡�� ��� ������, '������[1] = true'�� �� ���� ������ �̵�
    if (moveCameraY[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        cameraY += 0.01; // ī�޶� ���� �����ؼ� ������
    }
    else if (moveCameraY[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        cameraY -= 0.01; // ī�޶� �Ʒ��� �����ؼ� ������
    }

    if (moveCameraX[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        cameraX += 0.01; // ī�޶� ���������� �����ؼ� ������
    }
    else if (moveCameraX[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        cameraX -= 0.01; // ī�޶� �������� �����ؼ� ������
    }

    if (moveFocusX[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        focusX += 0.01; // ������ ���������� �����ؼ� ������
    }
    else if (moveFocusX[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        focusX -= 0.01; // ������ �������� �����ؼ� ������
    }

    if (moveFocusY[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        focusY += 0.01; // ������ �������� �����ؼ� ������
    }
    else if (moveFocusY[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        focusY -= 0.01; // ������ �Ʒ��� �����ؼ� ������
    }

    if (moveFocusZ[0]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        focusZ += 0.01; // ������ ������ �����ؼ� ������
    }
    else if (moveFocusZ[1]) // Keyboard Event�� �ش� ������ true�� �ٲ���� ��
    {
        focusZ -= 0.01; // ������ �ڷ� �����ؼ� ������
    }

    glutPostRedisplay(); // Display Event�� ������ �߻����� ȭ�鿡 �׸��� �ٽ� �׸����� ��
}

// ȭ���� �ٽ� �׷��� �� �� ȣ��Ǵ� callback �Լ�
void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // ���� ��Ⱦ�� ����
    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
    gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.0, 100); // ���� ���� ���� (�������� ��Ⱦ�� ��ġ���� �ְ� ���� ����)
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Window OS�� ���� ���� & GLUT Library �ʱ�ȭ
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // Display Mode ���� (Ʈ���÷� ��� & 1���� ���� ���)
    glutInitWindowSize(500, 500); // �������� ũ�� ����
    glutInitWindowPosition(0, 0); // �������� ��ġ ����
    glutCreateWindow("VCS (View Coordinate System)"); // ������ ���� �� �̸� ����
    MyInit(); // �ʱ� ���� ����
    glutDisplayFunc(MyDisplay); // Display Event�� �߻��� ������ MyDisplay�� ȣ���ϵ��� ���
    glutReshapeFunc(MyReshape); // ȭ���� ���� �׷��� �� ������ MyReshape�� ȣ���ϵ��� ���
    glutKeyboardFunc(MyKeyboard); // �Ϲ�Ű�� ���� Keyboard Event�� �߻��� ������ MyKeyboard�� ȣ���ϵ��� ���
    glutSpecialFunc(MySpecialKey); // Ư��Ű�� ���� Keyboard Event�� �߻��� ������ MySpecialKey�� ȣ���ϵ��� ���
    glutIdleFunc(MyIdle); // ó���� Event�� ���� �� MyIdle�� ȣ���ϵ��� ���
    glutMainLoop(); // GLUT Event ó�� Main Loop ����
    return 0;
}