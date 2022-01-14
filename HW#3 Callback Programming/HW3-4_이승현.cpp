/*******************************************************************************************************/
/*                                     HW#3-4. Menu Callback ����                                      */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 10�� 6�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* Menu Callback�� �̿��Ͽ� �޴��� ����ϰ�, 3D Primitive�� ���� ������ �ϵ��� �Ѵ�.                   */
/* ��� :                                                                                              */
/* 1. ���콺 ��Ŭ������ Draw Sphere, Draw Torus, Draw Teapot, Change Color, Exit�� �޴��� �����Ѵ�.    */
/* 2. �޴��� ���� Sphere, Torus, Teapot�� 3D�� �׸���.                                                 */
/* 3. �޴��� ���� �� Primitive�� ���� ������, �ʷϻ�, �Ķ��� �� �ϳ��� �ٲ� �� �ֵ��� �Ѵ�.            */
/* 4. �޴��� ���� �� Primitive�� ũ�⸦ Small, Large �� ���� �� �ֵ��� �Ѵ�.                           */
/*******************************************************************************************************/


#include <gl/glut.h>

GLboolean IsSphere = true, IsTorus = false, IsTeapot = false; // ��� 3D Primitive�� �׸� �������� ���� ����
GLboolean IsSmall = true, IsLarge = false; // ��� ũ��� Primitive�� �׸� �������� ���� ����
GLfloat red = 0.5, green = 0.5, blue = 0.5; // ��� ������ Primitive�� ������ �������� ���� ����

// Display Event�� ó���ϴ� �Լ�
void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT); // �� ���۸� �����Ͽ� ȭ�鿡�� �׸� �����
    glColor3f(red, green, blue); // �ʱ� ������ ȸ������ ����

    if ((IsSphere) && (IsSmall))
        glutWireSphere(0.5, 30, 30); // ���� ũ���� ���̾� ������ ���� �׸�
    else if ((IsSphere) && (IsLarge))
        glutWireSphere(0.7, 30, 30); // ū ũ���� ���̾� ������ ���� �׸�
    else if ((IsTorus) && (IsSmall))
        glutWireTorus(0.1, 0.3, 40, 20); // ���� ũ���� ���̾� ������ �䷯���� �׸�
    else if ((IsTorus) && (IsLarge))
        glutWireTorus(0.2, 0.5, 40, 20); // ū ũ���� ���̾� ������ �䷯���� �׸�
    else if ((IsTeapot) && (IsSmall))
        glutWireTeapot(0.3); // ���� ũ���� ���̾� ������ �����ڸ� �׸�
    else if ((IsTeapot) && (IsLarge))
        glutWireTeapot(0.6); // ū ũ���� ���̾� ������ �����ڸ� �׸�
    glFlush();
}

// ���� �޴��� ������
void MyMainMenu(int entryID) {
    switch (entryID)
    {
    case 1: // ù ��°('Draw Sphere')�� �����ϸ� ���� �׸�
        IsSphere = true;
        IsTorus = false;
        IsTeapot = false;
        break;
    case 2: // �� ��°('Draw Torus')�� �����ϸ� �䷯���� �׸�
        IsSphere = false;
        IsTorus = true;
        IsTeapot = false;
        break;
    case 3: // �� ��°('Draw Teapot')�� �����ϸ� �����ڸ� �׸�
        IsSphere = false;
        IsTorus = false;
        IsTeapot = true;
        break;
    case 4: // ������('Exit')�� �����ϸ� ���α׷� ����
        exit(0);
    }

    glutPostRedisplay(); // Display Event ������ �߻���Ű��
}

// ����� ���õ� �޴��� ������
void MySizeMenu(int entryID) {
    switch (entryID)
    {
    case 1: // ù ��°("Small")�� �����ϸ� 3D Primitive�� �۰� �׸�
        IsSmall = true;
        IsLarge = false;
        break;
    case 2: // �� ��°("Large")�� �����ϸ� 3D Primitive�� ũ�� �׸�
        IsSmall = false;
        IsLarge = true;
        break;
    }

    glutPostRedisplay(); // Display Event ������ �߻���Ű��
}

// ���� ���� �޴��� ������
void MyColorMenu(int entryID)
{
    switch (entryID)
    {
    case 1: // ù ��°("Red")�� �����ϸ� 3D Primitive�� ���������� ����
        red = 1.0;
        green = 0.0;
        blue = 0.0;
        break;
    case 2: // �� ��°("Green")�� �����ϸ� 3D Primitive�� �ʷϻ����� ����
        red = 0.0;
        green = 1.0;
        blue = 0.0;
        break;
    case 3: // �� ��°("Blue")�� �����ϸ� 3D Primitive�� �Ķ������� ����
        red = 0.0;
        green = 0.0;
        blue = 1.0;
        break;
    }

    glutPostRedisplay(); // Display Event ������ �߻���Ű��
}

// �ʱ� ����
void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // ȭ���� �Ͼ������ �����
    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ

    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ���� ������ ����

    GLint MySizeID = glutCreateMenu(MySizeMenu); // ũ�� ������ ���� �޴� �ݹ� �Լ��� ����Ͽ� �޴� ���̵� �� ����
    glutAddMenuEntry("Small", 1); // Primitive�� �۰� �׸��� �޴� ����
    glutAddMenuEntry("Large", 2); // Primitive�� ũ�� �׸��� �޴� ����

    GLint MyColorID = glutCreateMenu(MyColorMenu); // ���� ������ ���� �޴� �ݹ� �Լ��� ����Ͽ� �޴� ���̵� �� ����
    glutAddMenuEntry("Red", 1); // Primitive�� ���������� �׸��� �޴� ����
    glutAddMenuEntry("Green", 2); // Primitive�� �ʷϻ����� �׸��� �޴� ����
    glutAddMenuEntry("Blue", 3); // Primitive�� �Ķ������� �׸��� �޴� ����

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu); // �� �޴��� ���� �޴� �ݹ� �Լ��� ����Ͽ� �޴� ���̵� �� ����
    glutAddMenuEntry("Draw Sphere", 1); // Sphere�� �׸��� �޴� ����
    glutAddMenuEntry("Draw Torus", 2); // Torus�� �׸��� �޴� ����
    glutAddMenuEntry("Draw Teapot", 3); // Teapot�� �׸��� �޴� ����
    glutAddSubMenu("Size", MySizeID); // Size�� ���� ���� �޴� ����
    glutAddSubMenu("Color", MyColorID); // Color�� ���� ���� �޴� ����
    glutAddMenuEntry("Exit", 4); // ���α׷� ���� �޴� ����
    glutAttachMenu(GLUT_RIGHT_BUTTON); // ���콺�� ������ ��ư�� �޴� �Ҵ�
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // Window OS ���ǰ� �����ϰ� GLUT Library �ʱ�ȭ
    glutInitDisplayMode(GLUT_RGB); // Display Mode ����
    glutInitWindowSize(500, 500); // â ũ�� ����
    glutInitWindowPosition(0, 0); // â ��ġ ����
    glutCreateWindow("Menu Callback"); // â �̸� ������ �Բ� â ����
    MyInit(); // �ʱ� ���� ����
    glutDisplayFunc(MyDisplay); // Display Event�� �Ͼ ������ MyDisplay ȣ���ϵ��� ���

    glutMainLoop(); // GLUT Event ó�� Loop ����
    return 0;
}