/*******************************************************************************************************/
/*                                 HW#6 : glViewport()�� ���� ������ȯ                                 */
/*  �ۼ��� : �̽���                                                             ��¥ : 2021�� 11�� 9�� */
/*                                                                                                     */
/* ���� ���� :                                                                                         */
/* 2�� �̻��� ��ü�� �� ������ �׸���, �� �����쿡 4���� ������ ��� ���� ���Ѵ�.                    */
/* ��� :                                                                                              */
/* 1. ���ܰ� ���ϴ��� ������ Teapot�� Sphere �� ��ü�� �׸���.                                       */
/* 2. ������ ������ ������������ �����Ѵ�.                                                           */
/* 3. ���ϴ��� ������ ������������ �����Ѵ�.                                                           */
/* 4. Mouse Callback�� ���� ���콺�� �ش� ������ �ִ� ��ġ���� ��Ŭ������ ȭ���� �巡���ϸ�            */ 
/*    ī�޶� ���콺�� �����ӿ� ���� x, y�࿡�� �̵��Ѵ�.                                             */
/* 5. Mouse Callback�� ���� ���콺�� �ش� ������ �ִ� ��ġ���� �յڷ� ��ũ���ϸ�                       */
/*    ī�޶� ���콺�� �����ӿ� ���� z�࿡�� �̵��Ѵ�. (�̵� ������ ���� ����)                        */
/* 6. ������ ���� �� Teapot�� ��ġ�� ������ �߽�����, Sphere�� Teapot�� �ڷ� �����Ѵ�.                 */
/* 7. ReShape Callback�� Display Callback�� ���� ������ ũ�� ��ȯ�� ���� ��ü �ְ��� �����Ѵ�.         */ 
/*******************************************************************************************************/

#include <GL/glut.h>

GLfloat Width, Height;
GLfloat size[2];
GLfloat camera1[3], camera2[3];
GLint mousePos[2];

void MyInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // ������� ȭ�� �����

    glGetFloatv(GL_LINE_WIDTH_RANGE, size); // �� �β��� ������ size�� ����

    camera1[0] = 0;
    camera1[1] = 0;
    camera1[2] = 1.5;

    camera2[0] = 5.0;
    camera2[1] = 5.0;
    camera2[2] = 5.0;
}

void DrawScene() {
    glColor3f(0.0, 0.0, 0.0); // ��ǥ�� �� ����
    glPushMatrix(); // ��� ���ÿ� ���� ��ȯ ��� ����
    glLineWidth(size[0] * 5); // �� �β� ���� (�ּڰ��� 5��)
    glBegin(GL_LINES); // x�� �׸���
    glVertex3f(-2.0, 0.0, 0.0); // ��ǥ ����
    glVertex3f(2.0, 0.0, 0.0); // ��ǥ ����
    glEnd(); // �׸��� ������
    glBegin(GL_LINES); // y�� �׸���
    glVertex3f(0.0, -2.0, 0.0); // ��ǥ ����
    glVertex3f(0.0, 2.0, 0.0); // ��ǥ ����
    glEnd(); // �׸��� ������
    glBegin(GL_LINES); // z�� �׸���
    glVertex3f(0.0, 0.0, -2.0); // ��ǥ ����
    glVertex3f(0.0, 0.0, 2.0); // ��ǥ ����
    glEnd(); // �׸��� ������
    glPopMatrix(); // ��� ���ÿ��� top�� �ִ� ��� ����

    glColor3f(0.3, 0.3, 0.7); // Teapot�� ���� ����
    glPushMatrix(); // ��� ���ÿ� ���� ��ȯ ��� ����
    glTranslatef(0.0, 0.0, 0.0); // Teapot ��ġ ����
    glutWireTeapot(1.0); // Teapot�� 1.0�� ũ��� �׸���
    glPopMatrix(); // ��� ���ÿ��� top�� �ִ� ��� ����

    glColor3f(0.5, 0.1, 0.0);
    glPushMatrix();
    glTranslatef(-1.0, 0.0, -1.0);
    glutWireSphere(0.6, 20, 20);
    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �� ����, ���� ���۸� �����Ͽ� ȭ�鿡�� �׸� �����
    glColor3f(1.0, 1.0, 1.0); // ���� ����
    
    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ

    glOrtho(-2.0, 2.0, -2.0 * Height / Width, 2.0 * Height / Width, 0.5, 5.0); // ���� ���� ����
    glMatrixMode(GL_MODELVIEW); // �𵨺� ��� ����
    glLoadIdentity(); // �𵨺� ����� �׵� ��ķ� �ʱ�ȭ

    glViewport(0, 0, Width / 2, Height / 2); // ���� �ϴܿ� ���� ����
    glPushMatrix(); // ��� ���ÿ� ����
    gluLookAt(camera1[0], camera1[1], camera1[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glViewport(Width / 2, 0, Width / 2, Height / 2); // ���� �ϴܿ� ���� ����
    glPushMatrix();
    gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPopMatrix();
    glViewport(0, Height / 2, Width / 2, Height / 2); // ���� ��ܿ� ���� ����
    glPushMatrix();
    gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
    glPopMatrix();
    glViewport(Width / 2, Height / 2, Width / 2, Height / 2); // ���� ��ܿ� ���� ����
    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glPushMatrix();
    glLoadIdentity(); // ���� ����� �׵� ��ķ� �ʱ�ȭ
    gluPerspective(30, Width / Height, 3.0, 50.0); // ���� ���� ����
    glMatrixMode(GL_MODELVIEW); // �𵨺� ��� ����
    glPushMatrix();
    gluLookAt(camera2[0], camera2[1], camera2[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION); // ���� ��� ����
    glPopMatrix();
    glutSwapBuffers(); // ���� ���ۿ� �� ���۸� ��ü�Ͽ� ȭ�鿡 �׸� �׸���
}

void MyReshape(int w, int h) {
    Width = w;
    Height = h;
}

void MyMouseMove1_XY(GLint x, GLint y)
{
    GLint deltaX = x - mousePos[0];
    GLint deltaY = y - mousePos[1];
    camera1[0] = deltaX / 5;
    camera1[1] = deltaY / 5;
    glutPostRedisplay();
}

void MyMouseMove2_XY(GLint x, GLint y)
{
    GLint deltaX = x - mousePos[0];
    GLint deltaY = y - mousePos[1];
    camera2[0] = deltaX / 5;
    camera2[1] = deltaY / 5;
    glutPostRedisplay();
}

void MyMouseMove(GLint x, GLint y)
{
    mousePos[0] = x;
    mousePos[1] = y;
}

void MyMouseClick(GLint button, GLint state, GLint x, GLint y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (x < Width / 2 && y > Height / 2)
            glutMotionFunc(MyMouseMove1_XY);
        else if (x > Width / 2 && y < Height / 2)
            glutMotionFunc(MyMouseMove2_XY);
    }
    else if (button == 3) // ���� ��ũ��
    {
        if (x < Width / 2 && y > Height / 2 && camera1[2] >= -6.0)
        {
            camera1[2] -= 0.25;
            glutPostRedisplay();
        }
        else if (x > Width / 2 && y < Height / 2 && camera2[2] >= -15.0)
        {
            camera2[2] -= 0.25;
            glutPostRedisplay();
        }
    }
    else if (button == 4) // �Ʒ��� ��ũ��
    {
        if (x < Width / 2 && y > Height / 2 && camera1[2] <= 6.0)
        {
            camera1[2] += 0.25;
            glutPostRedisplay();
        }
        else if (x > Width / 2 && y < Height / 2 && camera2[2] <= 15.0)
        {
            camera2[2] += 0.25;
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    Width = 500;
    Height = 500;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Viewpory Partition");
    MyInit();
    glutDisplayFunc(MyDisplay);
    glutReshapeFunc(MyReshape);
    glutPassiveMotionFunc(MyMouseMove);
    glutMouseFunc(MyMouseClick);
    glutMainLoop();
    return 0;
}
