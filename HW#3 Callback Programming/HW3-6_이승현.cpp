/*******************************************************************************************************/
/*                                     HW#3-6. Timer Callback ����                                     */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 10�� 6�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 1. Timer Callback�� �̿��Ͽ� �簢���� �翷���� ���������� �����̵��� �Ѵ�.                          */
/* 2. Mouse Callback�� �̿��Ͽ� ���콺 ���� Ű�� ������ �����̴� ������ ���ߵ��� �Ѵ�.                 */
/* 3. Reshape CAllback�� �̿��Ͽ� �簢���� ������ ������ ����� �ʵ��� �Ѵ�.                         */
/* ��� :                                                                                              */
/* 1. �簢���� �¿�� deltaX��ŭ �����̵��� �Ѵ�.                                                      */
/* 2. �簢���� â�� ���鿡 ����� �� ���� �����̴� ������ �ݴ� �������� �������� â �� ��������        */
/*    �Ѿ�� �ʵ��� �Ѵ�.                                                                            */
/* 3. �簢���� â�� �����ʿ� ������ �Ķ�������, ���ʿ� ������ ���������� ���Ѵ�.                       */
/* 4. â�� ũ�⸦ �ٲ��� �� �簢���� â �� �������� �Ѿ�� �ʵ��� �Ѵ�.                              */
/* 5. ���콺�� ��Ŭ���Ͽ��� �� �����̴� �簢���� ���ߵ��� �Ѵ�.                                        */
/*******************************************************************************************************/


#include <gl/glut.h>

GLfloat deltaX; // �簢���� x������ �����̱� ���� ����
GLfloat windowWidth, windowHeight; // â�� ũ�⿡ ���� ������ �����ϴ� ����
GLboolean stop = false; // ��Ŭ���ϸ� �簢���� �������� �ʵ��� �ϴ� ����
GLboolean left = false, right = true; // �簢���� �����ӿ� ���� ������ �����ϴ� ����
GLfloat red = 1.0, blue = 0.0; // �簢���� â�� �����ʿ� �ε����� �Ķ���, ���ʿ� �ε����� ���������� ���ϵ��� �ϴ� ����

// Display Event�� �Ͼ �� �簢���� �׸����� �ϴ� �Լ�
void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT); // ȭ�鿡�� �׸� �����
    glBegin(GL_POLYGON); // �簢�� �׸���
    glColor3f(red, 0.0, blue); // �簢�� ���� ����
    glVertex3f(-1.0 + deltaX, -0.5, 0.0); // �簢���� x�� �������� deltaX��ŭ �����̵��� ����
    glVertex3f(0.0 + deltaX, -0.5, 0.0);
    glVertex3f(0.0 + deltaX, 0.5, 0.0);
    glVertex3f(-1.0 + deltaX, 0.5, 0.0);
    glEnd(); // �׸��� ������
    glutSwapBuffers(); // �� ���ۿ� ���� ���۸� ���� ��ȯ�Ͽ� �簢���� ȭ�鿡 �׸�
}

// ȭ���� ���� �׷��� �� �� â�� ũ�⿡ ���� ������ �����ϰ�, �簢���� ������ ��ġ�� �������ϴ� �Լ�
void MyReshape(int w, int h)
{
    GLfloat widthFactor = (GLfloat)w / (GLfloat)300;
    GLfloat heightFactor = (GLfloat)h / (GLfloat)300;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
    glOrtho(-1 * widthFactor, 1 * widthFactor, -1 * heightFactor, 1 * heightFactor, -1, 1); // ���ú��Ǹ� ������ ��Ⱦ�� ���߱�

    windowWidth = 2 * widthFactor;
    windowHeight = 2 * heightFactor;

    if (-1.0 + deltaX < -windowWidth / 2)
    {
        deltaX = 1.0 - windowWidth / 2; // �簢���� â�� ���� �ٱ��� ��ġ�ϸ� â�� ���� �鿡 �´굵�� ��ġ ����
    }
    else if (deltaX > windowWidth / 2)
    {
        deltaX = windowWidth / 2; // �簢���� â�� ������ �ٱ��� ��ġ�ϸ� â�� ������ �鿡 �´굵�� ��ġ ����
    }
}

// ���콺 ��Ŭ�� �̺�Ʈ�� ó���ϴ� �Լ�
void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
        stop = true; // ���콺 ��Ŭ���� �Ͽ��� �� �簢�� ���߱�
	}
}

// �ð��� ���� ó���� �ϴ� �Լ�
void MyTimer(int value) {
    if (0.0 + deltaX > windowWidth / 2) 
    {
        right = false;
        left = true; // �簢���� â�� ������ �鿡 ����� �� �簢���� �������� �����̵��� ��

        blue = 1.0; // �簢���� â�� ������ �鿡 ����� �� �簢���� �Ķ������� ����
        red = 0.0;
    }
    if (-1.0 + deltaX < -windowWidth / 2)
    {
        right = true; // �簢���� â�� ���� �鿡 ����� �� �簢���� ���������� �����̵��� ��
        left = false;

        blue = 0.0; 
        red = 1.0; // �簢���� â�� ������ �鿡 ����� �� �簢���� ���������� ����
    }
    if (!stop) // ���콺 ��Ŭ���ϱ� ������ deltaX ���� ���� �簢���� ��� ������
    {
        if (right)
            deltaX += 0.1; // â�� ������ ��迡 ��� ������ �簢���� ���������� �̵�
        else if (left)
            deltaX -= 0.1; // â�� ���� ��迡 ��� ������ �簢���� �������� �̵�
    }

    glutPostRedisplay(); // Display Event�� ������ �߻���Ŵ
    glutTimerFunc(40, MyTimer, 1); // 40�и��ʸ��� MyTimer ȣ��
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv); // Window OS ���ǰ� �����ϰ� GLUT Library �ʱ�ȭ
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // Ʈ���÷� ���� ���� ���۸� ����ϵ��� Display Mode ����
    glutInitWindowPosition(0, 0); // â ��ġ ����
    glutInitWindowSize(300, 300); // â ũ�� ����
    glutCreateWindow("Timer Callback"); // â �̸� ������ �Բ� â ����
    glClearColor(1.0, 1.0, 1.0, 1.0); // ������� ȭ�� �����
    glutDisplayFunc(MyDisplay); // Display Event�� �Ͼ ������ MyDisplay ȣ���ϵ��� ���
    glutReshapeFunc(MyReshape); // ȭ���� ���� �׷��� �� ������ MyReshape ȣ���ϵ��� ���
    glutMouseFunc(MyMouse); // Mouse Event�� �Ͼ ������ MyMouse ȣ���ϵ��� ���
    glutTimerFunc(40, MyTimer, 1); // 40�и��� ���Ŀ� MyTimer ȣ���ϵ��� ���
    glutMainLoop(); // GLUT Event ó�� Loop ����
    return;
}