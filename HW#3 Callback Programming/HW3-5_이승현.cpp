/*******************************************************************************************************/
/*                                       HW#3-5 : Idle Callback ����                                   */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 10�� 6�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. Special Keyboard Callback�� �̿��Ͽ� �簢���� ������ ������ �����Ѵ�.                            */
/* 2. Idle Callback�� �̿��Ͽ� �簢���� ���������� �����̵��� �Ѵ�.                                    */
/* 3. Display Callback�� �̿��Ͽ� �簢���� â ���� �������� �Ѿ�� �ʵ��� �Ѵ�.                      */
/* ��� :                                                                                              */
/* 1. �� : �簢���� �������� 0.01 �̵�                                                                 */
/* 2. �� : �簢���� �Ʒ������� 0.01 �̵�                                                               */
/* 3. �� : �簢���� �������� 0.01 �̵�                                                                 */
/* 4. �� : �簢���� ���������� 0.01 �̵�                                                               */
/* 5. â�� ũ�⸦ �ٲ��� �� �簢���� â �� �������� �Ѿ�� �ʵ��� �Ѵ�.                              */
/*******************************************************************************************************/

// �簢���� �����̴� �ӵ��� ���� 0.01�� ���߾����ϴ�.

#include <gl/glut.h>

GLfloat deltaX = 0.0, deltaY = 0.0; // �簢���� x��, y�� �������� �����̱� ���� ����
GLfloat windowWidth, windowHeight; // â�� ũ�⿡ ���� ������ �����ϴ� ����

// Display Event�� �Ͼ �� �簢���� �׸����� �ϴ� �Լ�
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT); // ȭ�鿡�� �׸� ����
    glColor3f(0.0, 0.5, 0.8); // �ش� ������ �簢�� ���� ����

    // �簢���� â�� �ٱ� ������ ��ġ�ϸ� �簢���� â�� ���ο� ��ġ�� �� �ֵ��� ����
    if (-0.5 + deltaX < -windowWidth / 2) // ���� �Ʒ� ���� x��ǥ�� �ٱ� ������ ���� �� ����
        deltaX = 0.5 - windowWidth / 2;
    if (-0.5 + deltaY < -windowHeight / 2) // ���� �Ʒ� ���� y ��ǥ�� �ٱ� ������ ���� �� ����
        deltaY = 0.5 - windowHeight / 2;
    if (0.5 + deltaX > windowWidth / 2) // ������ �� ���� x��ǥ�� �ٱ� ������ ���� �� ����
        deltaX = -0.5 + windowWidth / 2;
    if (0.5 + deltaY > windowHeight / 2) // ������ �� ���� y ��ǥ�� �ٱ� ������ ���� �� ����
        deltaY = -0.5 + windowHeight / 2;

	glBegin(GL_POLYGON); // �簢�� �׸���
    glVertex3f(-0.5 + deltaX, -0.5 + deltaY, 0.0); // �ش� �簢���� x�࿡�� deltaX��ŭ �̵�, y�࿡�� deltaY��ŭ �̵�
    glVertex3f(0.5 + deltaX, -0.5 + deltaY, 0.0);
    glVertex3f(0.5 + deltaX, 0.5 + deltaY, 0.0);
    glVertex3f(-0.5 + deltaX, 0.5 + deltaY, 0.0);
    glEnd(); // �׸��� ������
    glutSwapBuffers(); // ���� ���ۿ� �ĸ� ���۸� ��ü�Ͽ� �ĸ� ���ۿ� �غ��ص� �׸��� ��Ÿ��
}

// ȭ���� ���� �׷��� �� �� â�� ũ�⿡ ���� ������ �����ϰ�, �簢���� ������ ��ġ�� �������ϴ� �Լ�
void MyReshape(int w, int h)
{
    GLfloat widthFactor = (GLfloat)w / (GLfloat)300;
    GLfloat heightFactor = (GLfloat)h / (GLfloat)300;

    glViewport(0, 0, w, h); // ���� ����

    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
    glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1); // ���ú��Ǹ� ������ ��Ⱦ�� ���߱�

    windowWidth = 2 * widthFactor;
    windowHeight = 2 * heightFactor;
}

// �簢���� ���������� �������� �����̵��� �ϴ� �Լ�
void MoveToTheLeft()
{
    if (-0.5 + deltaX > -windowWidth / 2)
        deltaX -= 0.01; // �簢���� â ���� ������ �ֵ��� �簢�� �����̱�
    glutPostRedisplay(); // ������ Display Event�� �߻����� �ٲ� ��ġ�� ���� �簢���� �׸�
}

// �簢���� ���������� ���������� �����̵��� �ϴ� �Լ�
void MoveToTheRight()
{
    if (0.5 + deltaX < windowWidth / 2)
        deltaX += 0.01; // �簢���� â ���� ������ �ֵ��� �簢�� �����̱�
    glutPostRedisplay(); // ������ Display Event�� �߻����� �ٲ� ��ġ�� ���� �簢���� �׸�
}

// �簢���� ���������� ���� �����̵��� �ϴ� �Լ�
void MoveToTheTop()
{
    if (0.5 + deltaY < windowHeight / 2)
        deltaY += 0.01; // �簢���� â ���� ������ �ֵ��� �簢�� �����̱�
    glutPostRedisplay(); // ������ Display Event�� �߻����� �ٲ� ��ġ�� ���� �簢���� �׸�
}

// �簢���� ���������� �Ʒ��� �����̵��� �ϴ� �Լ�
void MoveToTheBottom()
{
    if (-0.5 + deltaY > -windowHeight / 2)
        deltaY -= 0.01; // �簢���� â ���� ������ �ֵ��� �簢�� �����̱�
    glutPostRedisplay(); // ������ Display Event�� �߻����� �ٲ� ��ġ�� ���� �簢���� �׸�
}

// Ű������ Ư��Ű�� �Է¹޾��� �� ȣ��Ǵ� �Լ�
void MySpecialKey(int key, int x, int y)
{
    // ����Ű�� �Է¹޾��� �� ť�� �̺�Ʈ�� ������ ������ ����Ű�� �´� callback �Լ� ȣ��
    switch (key)
    {
    case GLUT_KEY_LEFT: // ���� ����Ű �Է�
        glutIdleFunc(MoveToTheLeft); // �簢���� �������� ������
        break;
    case GLUT_KEY_RIGHT: // ������ ����Ű �Է�
        glutIdleFunc(MoveToTheRight); // �簢���� ���������� ������
        break;
    case GLUT_KEY_UP: // ���� ����Ű �Է�
        glutIdleFunc(MoveToTheTop); // �簢���� �������� ������
        break;
    case GLUT_KEY_DOWN: // �Ʒ��� ����Ű �Է�
        glutIdleFunc(MoveToTheBottom); // �簢���� �Ʒ������� ������
        break;
    }
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv); // Window OS ���ǰ� �����ϰ� GLUT Library �ʱ�ȭ
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Ʈ���÷� ���� ���� ���۸� ����ϵ��� Display Mode ����
    glutInitWindowPosition(0, 0); // â ��ġ ����
    glutInitWindowSize(300, 300); // â ũ�� ����
    glutCreateWindow("Idle Callback"); // â �̸� ������ �Բ� â ����
    glutDisplayFunc(MyDisplay); // Display Event�� �Ͼ ������ MyDisplay ȣ���ϵ��� ���
    glutReshapeFunc(MyReshape); // ȭ���� ���� �׷��� �� ������ MyReshape ȣ���ϵ��� ���
    glutSpecialFunc(MySpecialKey); // Ű����κ��� Ư��Ű�� �Է¹��� ������ MySpecialKey ȣ���ϵ��� ���
    glutMainLoop(); // GLUT Event ó�� Loop ����
}